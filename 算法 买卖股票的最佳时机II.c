class Solution {
public:
	int maxProfit(vector<int>& prices) {
		int result = 0;
		int len = prices.size() - 1;
		for (int i = 0; i<len; i++){
			int temp = prices[i + 1] - prices[i];
			if (temp > 0){
				result += temp;
			}
		}
		return result;
	}
};