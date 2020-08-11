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
	TreeNode* build(vector<int>& inorder, int instart, int inend, vector<int>& postorder, int* postidx){
		//从后往前遍历后序，先创建当前节点
		TreeNode* cur = new TreeNode(postorder[*postidx]);
		//在中序中找到当前节点
		int incur = instart;
		for (; incur<inend; incur++){
			if (inorder[incur] == cur->val)
				break;
		}
		//判断有无右子树
		if (incur < inend){
			(*postidx)--;
			cur->right = build(inorder, incur + 1, inend, postorder, postidx);
		}
		else
			cur->right = nullptr;

		//判断有无左子树
		if (instart<incur){
			(*postidx)--;
			cur->left = build(inorder, instart, incur - 1, postorder, postidx);
		}
		else
			cur->left = nullptr;
		return cur;
	}
	TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
		if (inorder.empty())
			return nullptr;
		int postidx = postorder.size() - 1;
		return build(inorder, 0, inorder.size() - 1, postorder, &postidx);
	}
};