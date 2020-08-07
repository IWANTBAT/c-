class Solution {
public:
	int evalRPN(vector<string>& tokens) {
		stack<int> res;

		for (auto & str : tokens){
			if (str == "+" || str == "-" || str == "*" || str == "/"){
				int right = res.top();
				res.pop();
				int left = res.top();
				res.pop();

				if (str == "+"){
					res.push(left + right);
				}
				if (str == "-"){
					res.push(left - right);
				}
				if (str == "*"){
					res.push(left * right);
				}
				if (str == "/"){
					res.push(left / right);
				}
			}
			//不是运算符就是操作数
			else{
				res.push(stoi(str));
			}
		}
		return res.top();
	}
};