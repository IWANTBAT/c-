/**
* Definition for a binary tree node.
* struct TreeNode {
*     int val;
*     TreeNode *left;
*     TreeNode *right;
*     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
* };
*/
class Solution {
public:
	bool getpath(TreeNode* root, TreeNode* cur, stack<TreeNode*>& st){
		if (root == nullptr)
			return false;
		st.push(root);
		if (root == cur){
			return true;
		}

		if (getpath(root->left, cur, st))
			return true;
		if (getpath(root->right, cur, st))
			return true;

		st.pop();
		return false;
	}
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		stack<TreeNode*> st1;
		stack<TreeNode*> st2;
		getpath(root, p, st1);
		getpath(root, q, st2);
		while (st1.size() != st2.size()){
			if (st1.size() > st2.size()){
				st1.pop();
			}
			else
				st2.pop();
		}

		while (!st1.empty()){
			if (st1.top() != st2.top()){
				st1.pop();
				st2.pop();
			}
			else
				break;
		}
		return st1.top();

	}
};