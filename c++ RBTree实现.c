#incude<iostream>
#include<utility>
using namespace std;

enum Color
{
	RED,
	BLACK
};
template <class K, class V>
struct RBNode{
	pair<K, V> _value;
	Color _color;

	RBNode<K, V>* _parent;
	RBNode<K, V>* _right;
	RBNode<K, V>* _left;

	RBNode(const pair<K, V>& val = pair<K, V>())
		:__value(val)
		, _color(RED)
		, _parent(nullptr)
		, _right(nu;; ptr)
		, _left(nullptr)
	{}
};
template<class K, class V>
class RBTree{
public:
	typedef RBNode<K, V> Node;

	RBTree()
		:_header(new Node)
	{
		_header->_parent = nullptr;
		_header->_left = _header->_right = _header;
	}

	bool insert(const pair<K, V>& val){
		if (_header == nullptr){
			Node* root = new Node(val);
			root->_color = BLACK;
			_header->_parent = root;
			root->_parent = _header;
			_header->_left = root;
			_header->_right = root;
		}
		//二叉搜索树插入
		Node* cur = _header->_parent;
		Node* parent = nullptr;
		while (cur){
			parent = cur;
			//存储K-V数据,按照key值来比较
			if (cur->_value->first == val.first)
				return false;
			else if (cur->_value.first < val.first)
				cur = cur->_right;
			else
				cur = cur->_left;
		}
		cur = new Node(val);
		if (parent->_value.first < val.first)
			parent->_right = cur;
		else
			parent->_left = cur;
		cur->_parent = parent;


		//调整：修改颜色 旋转
		//查看是否又连续的红色
		while (cur != _header->_parent && cur->_parent->_color == RED){
			parent = cur->_parent;
			Node* g = parent->_parent;

			if (g->_left == parent)
			{
				Node* u = g->_right;
				//叔叔存在并且颜色为RED，将叔叔与父亲的颜色变为黑色，祖父的颜色变为红色
				if (u && u->_color == RED){
					parent->_color = u->_color = BLACK;
					g->_color = RED;
					cur = g;
				}

			}
		}
		//根的颜色
		_header->_parent->_color = BLACK;

	}
private:
	Node* _header;
};