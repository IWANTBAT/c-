//牛客 变态跳台阶
/*
因为n级台阶，第一步有n种跳法：跳1级、跳2级、到跳n级
跳1级，剩下n-1级，则剩下跳法是f(n-1)
跳2级，剩下n-2级，则剩下跳法是f(n-2)
所以f(n)=f(n-1)+f(n-2)+...+f(1)
因为f(n-1)=f(n-2)+f(n-3)+...+f(1)

所以f(n)=2*f(n-1)
*/
class Solution {
public:
	int jumpFloorII(int number) {
		if (number == 0)
			return 1;
		else if (number == 1){
			return 1;
		}
		else
			return 2 * jumpFloorII(number - 1);
	}
};