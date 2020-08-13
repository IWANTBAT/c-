
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
	AVLTree(AVLNode* root = nullptr)
		:_root(root)
	{}
	//插入
	bool insert(const T& val)
	{
		if (_root == nullptr){
			_root = new AVLNode(val);
			return true;
		}

		AVLNode* cur = _root;
		AVLNode* parent = nullptr;
		while (cur){
			parent = cur;
			if (cur->_value == val)
				return false;
			else if (cur->_value < val)
				cur = cur->_right;
			else
				cur = cur->_left;
		}
		cur = new AVLNode(val);
		if (parent->_value < val)
			parent->right = cur;
		else
			prent->_left = cur;
		cur->_parent = parent;

		//调整
		while (parent){
			if (parent->left == cur)
				parent->_bf--;
			else
				parent->_bf++;
			if (parent->_bf == 0)
				break;
			else if (parent->_bf == 1 || parent->_bf == -1){
				//继续向上更新
				cur = parent;
				parent = parent->parent;
			}
			else if (abs(parent->_bf) == 2){
				if (parent->_bf == -2 && cur->_bf == -1){
					//左边的左边高--->右旋
					RotateR(parent);
				}
				break;
			}
		}

	}

	void RotateR(AVLNode* parent){
		AVLNode* subL = parent->_left;
		AVLNOde* subLR = subL->_right;

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
			AVLNode* pp = parent->_parent;
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
private:
	AVLNode* _root;
};