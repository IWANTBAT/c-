class Solution {
public:
	bool IsPopOrder(vector<int> pushV, vector<int> popV) {

		//用一个栈来模拟出栈的序列，最后判断栈是否为空
		stack<int> sta;
		int push = 0;
		int pop = 0;
		while (push<pushV.size()){
			//先入栈
			sta.push(pushV[push++]);

			//判断是否需要出栈
			while (!sta.empty() && sta.top() == popV[pop]){
				sta.pop();
				pop++;
			}
		}
		return sta.empty();
	}
};