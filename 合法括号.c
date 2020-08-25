class Parenthesis {
public:
	bool chkParenthesis(string A, int n) {
		// write code here
		stack<char> res;
		for (auto ch : A)
		{
			switch (ch){
			case'(':
				res.push(ch);
				break;
			case')':
			{
					   if (res.empty() || res.top() != '(')
						   return false;
					   else
						   res.pop();
			}
				break;
			default:
				return false;
			}
		}
		return true;
	}
};