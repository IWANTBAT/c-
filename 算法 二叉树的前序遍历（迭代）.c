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
	vector<int> preorderTraversal(TreeNode* root) {
		vector<int> res;
		stack<TreeNode*> s;
		s.push(root);
		while (!s.empty()){
			TreeNode* temp = s.top();
			s.pop();

			if (temp == nullptr)
				continue;
			res.push_back(temp->val);
			s.push(temp->right);
			s.push(temp->left);
		}
		return res;
	}
};