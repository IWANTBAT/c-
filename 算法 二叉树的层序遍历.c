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
	vector<vector<int>> levelOrder(TreeNode* root) {
		queue<TreeNode*> q;
		vector<vector<int>> res;

		if (root == nullptr){
			return res;
		}
		q.push(root);
		while (!q.empty()){
			int size = q.size();
			vector<int> v;
			while (size-- > 0){
				TreeNode* cur = q.front();
				q.pop();
				v.push_back(cur->val);
				if (cur->left){
					q.push(cur->left);
				}
				if (cur->right){
					q.push(cur->right);
				}
			}
			res.push_back(v);
		}
		return res;
	}
};