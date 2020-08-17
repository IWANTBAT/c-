#include<vector>
#include<iostream>
#include<string>
using namespace std;


template <class K>
struct KeyOfValue{
	const K& operator()(const K& key){
		return key;
	}
};


//开散列：指针数组+单链表

template <class V>
struct HashNode{
	V _value;
	HashNode<V>* _next;

	HashNode(const V& val = V())
		:_value(val)
		, _next(nullptr)
	{}
};
//前置声明
template <class K, class V, class KeyOfValue>
class HashTable;
//迭代器
template <class K, class V, class KeyOfValue>
struct HashIterator{
	typedef HashNode<V> Node;
	typedef HashIterator<K, V, KeyOfValue> self;
	typedef HashTable<K, V, KeyOfValue> Ht;
	Node* _node;
	Ht* _ht;
	HashIterator(Node* node, Ht* ht)
		:_node(node)
		, _ht(ht)
	{}

	V& operator*(){
		return _node->_value;
	}
	V* operator->(){
		return &_node->_value;
	}
	bool operator!=(const self& it){
		return _node != it._node;
	}

	self& operator++(){
		if (_node->_next)
			_node = _node->_next;
		else{
			KeyOfValue kov;
			int idx = kov(_node->_value) % _ht->_table.size();
			idx++;
			Node* cur = _ht->_table[idx];
			for (; idx < _ht->_table.size(); idx++){
				if (_ht->_table[idx]){
					_node = _ht->_table[idx];
					break;
				}
			}
			if (idx == _ht->_table.size())
				_node = nullptr;
		}
		return *this;
	}
};
template <class K, class V, class KeyOfValue>
class HashTable{
public:
	//将迭代器声明为HashTable的友元类，以访问HashTable的私有成员；	
	template <class K, class V, class KeyOfValue>
	friend struct HashIterator;
	typedef HashNode<V> Node;
	typedef HashIterator<K, V, KeyOfValue> iterator;

	iterator begin(){
		for (int i = 0; i < _table.size(); i++){
			Node* cur = _table[i];
			if (cur)
				return iterator(cur, this);
		}
		return iterator(nullptr, this);
	}
	iterator end(){
		return iterator(nullptr, this);
	}

	bool insert(const V& val){
		//1:检查容量
		checkCapacity();

		//2:计算位置
		KeyOfValue kov;
		int idx = kov(val) % _table.size();
		//搜索位置
		Node* cur = _table[idx];
		while (cur){
			if (kov(cur->_value) == kov(val))
				return false;
			cur = cur->_next;
		}
		//3:插入:头插
		cur = new Node(val);
		cur->_next = _table[idx];
		_table[idx] = cur;

		_size++;
		return true;
	}

	void checkCapacity(){
		if (_size == _table.size()){
			size_t newSize = _size == 0 ? 5 : 2 * _size;
			vector<Node*> newHash;
			newHash.resize(newSize);

			KeyOfValue kov;
			//遍历旧表中的非空单链表
			for (int i = 0; i < _table.size(); i++)
			{
				Node* cur = _table[i];

				//遍历链表
				while (cur){
					//记录旧表中的下一个
					Node* next = cur->_next;
					//计算新的位置
					int idx = kov(cur->_value) % newHash.size();
					//头插
					cur->_next = newHash[idx];
					newHash[idx] = cur;

					cur = next;
				}
				_table[i] = nullptr;
			}
			swap(_table, newHash);
		}

	}

	Node* find(const K& key){
		if (_table.size() == 0)
			return nullptr;

		int idx = key%_table.size();

		Node* cur = _table[idx];
		KeyOfValue kov;
		while (cur)
		{
			if (kov(cur->_value) == key)
				return cur;
			cur = cur->_next;
		}
		return nullptr;
	}

	bool erase(const K& key){
		int idx = key%_table.size();
		Node* cur = _table[idx];

		KeyOfValue kov;
		Node* prev = nullptr;
		//单链表删除
		while (cur){

			if (kov(cur->_value) == key){
				//判断是否为头节点
				if (prev == nullptr)
					_table[idx] = cur->_next;
				else
					prev->_next = cur->_next;
				delete cur;
				_size--;

				return true;
			}
			else{
				prev = cur;
				cur = cur->_next;
			}
		}
		return false;
	}
private:
	vector<Node*> _table;
	size_t _size = 0;
};

void test()
{
	HashTable<int, int, KeyOfValue<int>> ht;
	ht.insert(10);
	ht.insert(7);
	ht.insert(35);
	ht.insert(12);
	ht.insert(25);
	ht.insert(4);
	ht.insert(14);
	ht.insert(11);
	ht.insert(9);

	HashNode<int>* cur = ht.find(14);

	cur = ht.find(100);

	bool ret = ht.erase(14);

	ret = ht.erase(14);
}

//字符转整数
struct strtoint{
	size_t operator()(const string& str){
		size_t hash = 0;
		for (const auto& ch : str){
			hash = hash * 121 + ch;
		}
		return hash;
	}

};

template <class K>
struct hashfun{
	size_t operator()(const K& key){
		return key;
	}
};

//unordered_map
template <class K, class V>
class unordered_map{
	struct MapKeyOfValue
	{
		const K& operator()(const pair<K, V>& val){
			return val.first;
		}
	};
public:
	bool insert(const pair<K, V>& val){
		return _ht.insert(val);
	}
private:
	HashTable<K, pair<K, V>, MapKeyOfValue> _ht;
};

void test1(){
	unordered_map<int, int> um;
	um.insert(make_pair(1, 1));
	um.insert(make_pair(12, 12));
	um.insert(make_pair(3, 3));
	um.insert(make_pair(2, 2));
	um.insert(make_pair(14, 14));
	um.insert(make_pair(40, 40));

}

//unordered_set
template <class K, class HF = hashfun<K>>
class unorder_set{
	struct SetKeyOfValue{
		const K& operator()(const K& key){
			return key;
		}
	};
public:
	typedef typename HashTable<K, K, SetKeyOfValue>::iterator iterator;
	iterator begin()
	{
		return _ht.begin();
	}
	iterator end()
	{
		return _ht.end();
	}
	bool insert(const K& val){
		return _ht.insert(val);
	}
private:
	HashTable<K, K, SetKeyOfValue> _ht;
};


void test2(){
	unorder_set<int> us;
	us.insert(1);
	us.insert(3);
	us.insert(6);
	us.insert(18);
	us.insert(21);
	us.insert(31);

	unorder_set<int>::iterator it = us.begin();
	while (it != us.end()){
		cout << *it << " ";
		++it;
	}
	cout << endl;


}
int main()
{
	//test();
	//test1();
	test2();
	return 0;
}