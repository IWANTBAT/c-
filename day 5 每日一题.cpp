//将字符串转换成整数
class Solution {
public:
	int StrToInt(string str) {
		if (str.empty())
			return 0;
		int s = 1;
		if (str[0] == '-'){
			s = -1;
			str[0] = '0';
		}
		else if (str[0] == '+'){
			s = 1;
			str[0] = '0';
		}
		int sum = 0;
		for (int i = 0; i<str.size(); i++){
			if (str[i] < '0' || str[i]>'9'){
				sum = 0;
				break;
			}
			sum = sum * 10 + str[i] - '0';
		}
		return s*sum;
	}
};