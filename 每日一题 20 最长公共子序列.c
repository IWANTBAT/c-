/*建立一个dp矩阵，是两个字符串一个纵对应，一个横向对应。
dp[i][j]表示str1[0...i]和str2[0...j]的最长公共子序列的长度

求解
dp[i][j]为：


若str1[i] == str2[j]，则
dp[i][j] = max(
dp[i - 1][j],
dp[i][j - 1],
dp[i - 1][j - 1] + 1
)


若str1[i] != str2[j]，则
dp[i][j] = max(
dp[i - 1][j],
dp[i][j - 1]
)


最后返回dp[M - 1][N - 1]，M、N为两个字符串的长度
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	string A, B;
	while (cin >> A >> B) {
		int aLength = A.length();
		int bLength = B.length();
		vector<vector<int> > dp(aLength, vector<int>(bLength, 0));
		// 初始化边界
		dp[0][0] = (A[0] == B[0]) ? 1 : 0;
		for (int i = 1; i<aLength; i++) {
			dp[i][0] = (A[i] == B[0]) ? 1 : 0;
			dp[i][0] = max(dp[i - 1][0], dp[i][0]);
		}
		for (int j = 1; j<bLength; j++) {
			dp[0][j] = (A[0] == B[j]) ? 1 : 0;
			dp[0][j] = max(dp[0][j - 1], dp[0][j]);
		}
		// 计算
		for (int i = 1; i<aLength; i++) {
			for (int j = 1; j<bLength; j++) {
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
				if (A[i] == B[j]) {
					dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + 1);
				}
			}
		}
		cout << dp[aLength - 1][bLength - 1] << endl;
	}

	return 0;
}
