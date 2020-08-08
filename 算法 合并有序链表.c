/*
struct ListNode {
int val;
struct ListNode *next;
ListNode(int x) :
val(x), next(NULL) {
}
};*/
class Solution {
public:
	ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
	{
		if (pHead1 == nullptr)
			return pHead2;
		if (pHead2 == nullptr)
			return pHead1;
		ListNode* new_node = nullptr;
		ListNode* p = nullptr;
		while (pHead1 && pHead2){
			ListNode* temp = pHead1->val < pHead2->val ? pHead1 : pHead2;
			if (temp == pHead1){
				pHead1 = pHead1->next;
			}
			else{
				pHead2 = pHead2->next;
			}
			if (new_node == nullptr){
				new_node = temp;
				p = temp;
			}
			else{
				p->next = temp;
				p = temp;
			}

		}
		if (pHead1){
			p->next = pHead1;
		}
		else{
			p->next = pHead2;
		}
		return new_node;
	}
};