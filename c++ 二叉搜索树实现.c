#include<iostream>
using namespace std;

template <class T>
struct Node{
	T _val;
	Node* _left;
	Node* _right;

	Node(const T& val = T())
		:_val(val)
		, _left(nullptr)
		, _right(nullptr)
	{

	}
};

template <class T>
class BST{
public:
	typedef Node<T> node;

	//构造函数
	BST() :_root(nullptr){

	}

	//插入
	bool insert(const T& val){
		//判断是否为空树
		if (_root == nullptr){
			_root = new node(val);
			return true;
		}

		//搜索插入位置
		node* cur = _root;
		node* parent = nullptr;
		while (cur){
			parent = cur;
			if (cur->_val == val){
				return false;
			}
			else if (cur->_val > val){
				cur = cur->_left;
			}
			else{
				cur = cur->_right;
			}

		}
		cur = new node(val);
		if (parent->_val < cur->_val)
			parent->_right = cur;
		else
			parent->_left = cur;
		return true;
	}
	//查找
	node* find(const T& val){
		//从根节点开始查找
		node* cur = _root;
		while (cur){
			if (cur->_val == val)
				return cur;
			else if (cur->_val > val)
				cur = cur->_left;
			else
				cur = cur->_right;
		}
		return nullptr;
	}

	//删除
	bool erase(const T& val){
		if (_root == nullptr)
			return false;
		node* cur = _root;
		node* parent = nullptr;
		while (cur){
			if (cur->_val == val)
				break;
			else if (cur->_val > val){
				parent = cur;
				cur = cur->_left;
			}
			else{
				parent = cur;
				cur = cur->_right;
			}
		}
		if (cur == nullptr){
			return false;
		}
		//删除 叶子还是非叶子节点
		//叶子
		if (cur->_left == nullptr && cur->_right == nullptr){
			if (cur == _root){
				_root = nullptr;
			}
			else{
				if (parent->_left == cur)
					parent->_left = nullptr;
				else
					parent->_right = nullptr;
			}
			delete cur;
		}
		else if (cur->_left == nullptr){
			if (cur == _root){
				_root = cur->_right;
			}
			else{
				if (parent->_left == cur)
					parent->_left = cur->_right;
				else
					parent->_right = cur->_right;
			}
			delete cur;
		}
		else if (cur->_right == nullptr){
			if (cur == _root)
				_root = cur->_left;
			else{
				if (parent->_left == cur)
					parent->_left = cur->_left;
				else
					parent->_right = cur->_left;
			}
			delete cur;
		}
		else{//左右孩子都存在
			//找左子树的最右节点
			node* child = cur->_left;
			parent = cur;
			while (child->_right){
				parent = child;
				child = child->_right;
			}
			//覆盖要删除的
			cur->_val = child->_val;
			//链接
			if (parent->_left == child)
				parent->_left = child->_left;
			else
				parent->_right = child->_left;

			delete child;
		}
	}
private:
	node* _root;
};

void test(){
	BST<int> tree;
	tree.insert(5);
	tree.insert(3);
	tree.insert(7);
	tree.insert(2);
	tree.insert(1);
	tree.insert(0);
	tree.insert(8);
	tree.insert(6);
	tree.insert(9);

	tree.erase(0);
	tree.erase(2);
	tree.erase(8);
	tree.erase(5);
}

int main()
{
	test();
	return 0;
}