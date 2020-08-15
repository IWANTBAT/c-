#include<iostream>
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
		:_value(val)
		, _color(RED)
		, _parent(nullptr)
		, _right(nullptr)
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
		if (_header->_parent == nullptr){
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
			if (cur->_value.first == val.first)
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
				else{
					//u存在且为黑/u不存在
					if (parent->_right == cur){
						//先左旋，就变成同一边的场景
						//左旋之后，cur的父节点为g，子节点为parent;所以需要交换
						RotateL(parent);
						swap(parent, cur);
					}
					//cur在父亲的左边--->右旋
					RotateR(g);

					parent->_color = BLACK;
					g->_color = RED;
				}

			}
			else{
				Node* u = g->_left;
				//叔叔存在并且颜色为RED，将叔叔与父亲的颜色变为黑色，祖父的颜色变为红色
				if (u && u->_color == RED){
					parent->_color = u->_color = BLACK;
					g->_color = RED;
					cur = g;
				}
				else{
					//u存在且为黑/u不存在
					if (parent->_left == cur){
						//先右旋，就变成同一边的场景
						//右旋之后，cur的父节点为g，子节点为parent;所以需要交换
						RotateR(parent);
						swap(parent, cur);
					}
					//cur在父亲的右边--->左旋
					RotateL(g);

					parent->_color = BLACK;
					g->_color = RED;

				}
			}

		}
		//根的颜色
		_header->_parent->_color = BLACK;

		//完整的结构是头节点的左边指向最左节点，头结点的右边指向最右节点

		_header->_left = leftMost();
		_header->_right = rightMost();

		return true;
	}

	void RotateR(Node* parent){
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		subL->_right = parent;
		parent->_left = subLR;

		if (subLR)
			subLR->_parent = parent;
		if (parent == _header->_parent){
			subL->_parent = _header;
			_header->_parent = subL;
		}
		else{
			Node* pp = parent->_parent;
			subL->_parent = pp;
			if (pp->_left == parent)
				pp->_left = subL;
			else
				pp->_right = subL;
		}
		parent->_parent = subL;
	}
	void RotateL(Node* parent){
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		subR->_left = parent;
		parent->_right = subRL;

		if (subRL)
			subRL->_parent = parent;
		if (parent == _header->_parent){
			subR->_parent = _header;
			_header->_parent = subR;
		}
		else{
			Node* pp = parent->_parent;
			subR->_parent = pp;
			if (pp->_left == parent)
				pp->_left = subR;
			else
				pp->_right = subR;
		}
		parent->_parent = subR;
	}

	Node* leftMost(){
		Node* cur = _header->_parent;
		while (cur && cur->_left)
			cur = cur->_left;
		return cur;
	}

	Node* rightMost(){
		Node* cur = _header->_parent;
		while (cur && cur->_right)
			cur = cur->_right;
		return cur;
	}

	void inorder()
	{
		_inorder(_header->_parent);
		cout << endl;
	}
	void _inorder(Node* root){
		if (root){
			_inorder(root->_left);
			cout << root->_value.first << " ";
			_inorder(root->_right);
		}
	}

	bool isRBTree(){
		Node* root = _header->_parent;
		if (root == nullptr)
			return true;
		//1:根是否为黑色
		if (root->_color != BLACK)
			return false;
		//2：每条路径上黑色个数是否相同
		int Blackcount = 0;
		Node* cur = root;
		while (cur){
			if (cur->_color == BLACK)
				Blackcount++;
			cur = cur->_left;
		}

		//遍历
		int curCount = 0;
		return isRB(root, Blackcount, curCount);
	}
	bool isRB(Node* root, int blackCount, int curCount){
		if (root == nullptr){
			if (blackCount != curCount)
				return false;
			return true;
		}
		if (root->_color == BLACK)
			curCount++;
		Node* parent = root->_parent;
		if (parent && parent->_color == RED && root->_color == RED)
			return false;
		return isRB(root->_left, blackCount, curCount) && isRB(root->_right, blackCount, curCount);
	}
private:
	Node* _header;
};

void test()
{
	RBTree<int, int> rbt;
	rbt.insert(make_pair(1, 1));
	rbt.insert(make_pair(0, 1));
	rbt.insert(make_pair(5, 1));
	rbt.insert(make_pair(2, 1));
	rbt.insert(make_pair(3, 1));

	rbt.inorder();

	cout << rbt.isRBTree() << endl;
}

int main()
{
	test();
	return 0;
}