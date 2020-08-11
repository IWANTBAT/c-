/*
struct TreeNode {
int val;
struct TreeNode *left;
struct TreeNode *right;
TreeNode(int x) :
val(x), left(NULL), right(NULL) {
}
};*/
class Solution {
public:
	void convers(TreeNode* root, TreeNode** prev){
		if (root == nullptr)
			return;
		convers(root->left, prev);
		root->left = *prev;
		if (*prev)
			(*prev)->right = root;
		*prev = root;
		convers(root->right, prev);
	}
	TreeNode* Convert(TreeNode* pRootOfTree)
	{
		TreeNode* head = pRootOfTree;
		if (head == nullptr){
			return head;
		}
		TreeNode* prev = nullptr;
		convers(head, &prev);
		while (head->left){
			head = head->left;
		}
		return head;
	}
};