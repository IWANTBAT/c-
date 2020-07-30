/**  
* Definition for binary tree
* struct TreeNode {
*     int val;
*     TreeNode *left;
*     TreeNode *right;
*     TreeNode(int x) :val(x), left(NULL), right(NULL) {}
* }; 
*/
class Solution {
public:
	TreeNode* reConstructBinaryTreeCore(vector<int> pre, int preStart, int preEnd, vector<int> vin, int vinStart, int vinEnd) {
				if (preStart > preEnd || vinStart > vinEnd){
					return nullptr;
				}
				TreeNode *root = new TreeNode(pre[preStart]);
				for (auto i = vinStart; i <= vinEnd; i++){
					//在中序序列中，找根节点，可以将数组划分为两部分
					if(pre[preStart] == vin[i]){
						root->left = reConstructBinaryTreeCore(pre, preStart + 1, i - vinStart + preStart, vin, vinStart, i - 1);
						root->right = reConstructBinaryTreeCore(pre, i - vinStart + preStart + 1, preEnd, vin, i + 1, vinEnd);
						break;
					}
				}
				return root;
	}
	TreeNode* reConstructBinaryTree(vector<int> pre, vector<int> vin) {
		if (pre.empty() || vin.empty())
		{
			return nullptr;
		}
		return reConstructBinaryTreeCore(pre, 0, pre.size() - 1, vin, 0, vin.size() - 1);
	}
};