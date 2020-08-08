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
	ListNode* ReverseList(ListNode* pHead) {
		//头插解法
		if (pHead == nullptr || pHead->next == nullptr)
			return pHead;
		ListNode *p = pHead;
		pHead = pHead->next;
		ListNode* newl = nullptr;
		while (pHead){
			p->next = newl;
			newl = p;
			p = pHead;
			pHead = pHead->next;
		}
		p->next = newl;
		newl = p;
		pHead = newl;
		return pHead;
		//三指针解法
		/*if(pHead == nullptr || pHead->next == nullptr)
		return pHead;
		ListNode* first = pHead;
		ListNode* second = pHead->next;
		ListNode* third = second->next;

		while(third){
		second->next = first;
		first = second;
		second = third;
		third = third->next;
		}
		second->next = first;
		pHead->next = nullptr;
		pHead = second;

		return pHead;
		*/
	}
};