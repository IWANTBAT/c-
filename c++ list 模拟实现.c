#include<iostream>

using namespace std;

template <class T>
struct ListNode
{
	T _value;
	ListNode<T>* _next;
	ListNode<T>* _prev;

	ListNode(const T& val = T())
		:_value(val)
		, _next(nullptr)
		, _prev(nullptr)
	{}
};

template <class T, class Ref, class Ptr >
struct Listiterator
{
	typedef ListNode<T> node;

	Listiterator()
		:_node(node)
	{}

	//解引用
	Ref operator*(){
		return _node->_value;
	}

	//++
	Listiterator<T>& operator++(){
		_node = _node->_next;
		return *this;
	}

	//--
	Listiterator<T>& operator--(){
		_node = _node->_prev;
		return *this;
	}

	//判断
	bool operator!=(const Listiterator<T>& it){
		return _node != it._node;
	}

	//->  //根据指针可以使用->来写
	Ptr operator->()
	{
		return &_node->_value;
	}


	node* _node;
};

//const迭代器（冗余）
/*template <class T>
struct ConstListiterator
{
typedef ConstListNode<T> node;

ConstListiterator()
:_node(node)
{}

//解引用
const T& operator*(){
return _node->_value;
}

//++
Listiterator<T>& operator++(){
_node = _node->_next;
return *this;
}

//--
Listiterator<T>& operator--(){
_node = _node->_prev;
return *this;
}

//判断
bool operator!=(const Listiterator<T>& it){
return _node != it._node;
}

//->  //根据指针可以使用->来写
const T* operator->()
{
return &_node->_value;
}


node* _node;
};
*/
template <class T>
class List{
public:
	typedef ListNode<T> Node;

	//根据不同的参数来区分const和非const迭代器
	typedef Listiterator<T, T&, T*> iterator;//迭代器
	typedef Listiterator<T, const T&, const T*> const_iterator;//const迭代器

	//迭代器使用
	//可读可写
	iterator begin()
	{
		return iterator(_header->_next);
	}

	iterator end(){
		return iterator(_header);
	}
	//只读
	const_iterator begin()
	{
		return const_iterator(_header->_next);
	}

	const_iterator end(){
		return const_iterator(_header);
	}

	//构造函数			
	List()
		:_header(new Node)
	{
		//构建循环结构
		_header->_next = _header->_prev = _header;
	}

	//尾插
	void push_back(const T& val){
		/*Node* cur = new Node(val;

		Node* prev = _header->_prev;

		//链接
		prev->_next = cur;
		cur->_prev = prev;

		_header->_prev = cur;
		cur->_next = _header;*/

		insert(end(), val);
	}

	//头插
	void push_front(const T& val){
		/*Node* cur = new Node(val);

		Node* next = _header->_next;

		next->_prev = cur;
		cur->_next = next;

		_header->_next = cur;
		cur->_prev = _header;*/
		insert(begin(), val);
	}

	//insert
	void inert(iterator it, const T& val){
		Node* cur = new Node(val);

		Node* node = it._node;
		Node* prev = node->_prev;

		cur->_prev = prev;
		prev->_next = cur;

		node->_prev = cur;
		cur->_next = node;
	}

	//erase(删除之后迭代器会失效)
	iterator erase(iterator pos){
		//不能删除头节点
		if (pos == end())
			return pos;
		Node* node = pos._node;
		Node* prev = node->_prev;
		Node* next = node->_next;

		delete node;

		prev->_next = next;
		next->_prev = prev;

		return iterator(next);//需要创建迭代器对象
	}

	//尾删
	void pop_back(){
		erase(--end());
	}

	//头删
	void pop_front(){
		erase(begin());
	}

	//size
	size_t size()
	{
		size_t coubt = 0;
		for (const auto& e : *this){
			++count;
		}
		return count;
	}


	//clear
	void clear(){
		//清空所有非头结点
		Node* cur = _header->_next;
		while (cur != _header){
			Node* next = cur->_next;
			delete cur;
			cur = next;
		}
		//重新构建
		_header->_next = _header->_prev = _header;
	}

	//拷贝构造
	List(const List<T>& lis)
		:_header(new Node)
	{
		_header->_next = _header->_prev = _header;

		//深拷贝（尾插）
		for (const auto& e : lis)
			push_back(e);
	}

	//赋值运算符
	List<T>& operator=(List<T> lis){
		swap(_header, lis->_header);
		return *this;
	}
	//析构函数
	~List(){
		clear();
		delete _header;
		_header = nullptr;
	}
private:
	Node* _header;
};

int main()
{
	return 0;
}