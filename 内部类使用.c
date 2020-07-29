class Solution {

public:
	class Sum{
	public:
		Sum(){
			_sum += _num;
			_num++;
		}
	};
	int Sum_Solution(int n) {
		_sum = 0;
		_num = 1;
		Sum sumarra[n];
		return _sum;
	}
private:
	static int _sum;
	static int _num;

};
int Solution::_sum = 0;
int Solution::_num = 1;