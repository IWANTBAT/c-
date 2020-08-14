#include<iostream>

using namespace std;

template <class T>
struct AVLNode{
	T _value;
	int _bf;
	AVLNode<T>* _left;
	AVLNode<T>* _right;
	AVLNode<T>* _parent;

	AVLNode(const T& val = T())
		:_value(val)
		, _bf(0)
		, _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
	{}
};

template <class T>
class AVLTree{
public:
	typedef AVLNode<T> Node;
	AVLTree(Node* root = nullptr)
		:_root(root)
	{}
	//插入
	bool insert(const T& val)
	{
		if (_root == nullptr){
			_root = new Node(val);
			return true;
		}

		Node* cur = _root;
		Node* parent = nullptr;
		while (cur){
			parent = cur;
			if (cur->_value == val)
				return false;
			else if (cur->_value < val)
				cur = cur->_right;
			else
				cur = cur->_left;
		}
		cur = new Node(val);
		if (parent->_value < val)
			parent->_right = cur;
		else
			parent->_left = cur;
		cur->_parent = parent;

		//调整
		while (parent){
			if (parent->_left == cur)
				parent->_bf--;
			else
				parent->_bf++;
			if (parent->_bf == 0)
				break;
			else if (parent->_bf == 1 || parent->_bf == -1){
				//继续向上更新
				cur = parent;
				parent = parent->_parent;
			}
			else if (abs(parent->_bf) == 2){
				if (parent->_bf == -2 && cur->_bf == -1){
					//左边的左边高--->右旋
					RotateR(parent);
				}
				else if (parent->_bf == 2 && cur->_bf == 1){
					//右边的右边高--->左旋
					RotateL(parent);
				}
				else if (parent->_bf == -2 && cur->_bf == 1){
					//左边的右边高--->左右双旋（先以cur为轴左旋，在以parent为轴右旋）
					Node* subL = parent->_left;
					Node* subLR = subL->_right;
					int bf = subLR->_bf;

					RotateL(cur);
					RotateR(parent);

					if (bf == -1){
						subL->_bf = 0;
						parent->_bf = 1;
					}
					else{
						subL->_bf = 1;
						parent->_bf = 0;
					}
				}
				else if (parent->_bf == 2 && cur->_bf == -1){
					//右边的左边高--->右左双旋（先以cur为轴右旋，再以parent为轴左旋）
					Node* subR = parent->_right;
					Node* subRL = subR->_left;
					int bf = subRL->_bf;

					RotateR(cur);
					RotateL(parent);

					if (bf == 1)
					{
						subR->_bf = 0;
						parent->_bf = -1;
					}
					else
					{
						subR->_bf = 1;
						parent->_bf = 0;
					}
				}
				break;
			}
		}

	}

	void RotateR(Node* parent){
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		subL->_right = parent;
		parent->_left = subLR;

		if (subLR){
			subLR->_parent = parent;
		}

		if (parent == _root){
			_root = subL;
			subL->_parent = nullptr;
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

		//更新平衡因子
		subL->_bf = parent->_bf = 0;
	}

	//左旋
	void RotateL(Node* parent){
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		subR->_left = parent;
		parent->_right = subRL;
		if (subRL){
			subRL->_parent = parent;
		}
		if (parent == _root){
			_root = subR;
			subR->_parent = nullptr;
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

		parent->_bf = subR->_bf = 0;
	}

	void inorder(){
		_inorder(_root);
		cout << endl;
	}
	void _inorder(Node* root){
		if (root){
			_inorder(root->_left);
			cout << root->_value << " ";
			_inorder(root->_right);
		}
	}

	bool isBalance(){
		return _isbalance(_root);
	}
	bool _isbalance(Node* root){
		if (root == nullptr)
			return true;
		int left = high(root->_left);
		int right = high(root->_right);

		if (right - left != root->_bf)
			return false;

		return abs(root->_bf) < 2 && _isbalance(root->_left) && _isbalance(root->_right);
	}
	int high(Node* root){
		if (root == nullptr)
			return 0;
		int left = high(root->_left);
		int right = high(root->_right);

		return left>right ? left + 1 : right + 1;

	}
private:
	Node* _root;
};

void test()
{
	AVLTree<int> avl;
	avl.insert(1);
	avl.insert(2);
	avl.insert(3);
	avl.insert(4);
	avl.insert(5);
	avl.insert(6);
	avl.insert(7);
	avl.insert(8);
	avl.insert(9);

	avl.inorder();

	cout << avl.isBalance() << endl;
}

int main()
{
	test();
	return 0;
}