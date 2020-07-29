class Solution {
public:     int jumpFloor(int number) {
				//dp[n] = dp[n-1]+dp[n-2];
				int *dp = new int[number+1];
				dp[0] = 1;
				dp[1] = 1;
				for(int i = 2; i<= number;i++){
					dp[i] = dp[i-1] + dp[i-2]; 
				}         
				int num = dp[number];
				//第number下标，就是第number阶台阶
				delete dp;
				return num;
} 
}; 