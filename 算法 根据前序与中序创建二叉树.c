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
	TreeNode* build(vector<int>& preorder, int* preIdx, vector<int>& inorder, int instart, int inend){
		//先创建出当前节点
		TreeNode* cur = new TreeNode(preorder[*preIdx]);
		//在中序遍历中找到当前节点
		int incur = instart;
		for (; incur <= inend; incur++){
			if (inorder[incur] == cur->val)
				break;
		}
		//判断当前节点有无左孩子
		if (instart<incur){
			(*preIdx)++;
			cur->left = build(preorder, preIdx, inorder, instart, incur - 1);
		}
		else
			cur->left = nullptr;
		//判断当前节点有无右孩子
		if (incur<inend){
			(*preIdx)++;
			cur->right = build(preorder, preIdx, inorder, incur + 1, inend);
		}
		else
			cur->right = nullptr;
		return cur;
	}
	TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
		if (preorder.empty())
			return nullptr;
		int preIdx = 0;
		return build(preorder, &preIdx, inorder, 0, inorder.size() - 1);
	}
};