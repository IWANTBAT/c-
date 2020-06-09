//给定一个N,每次可以变为N+1或者N-1，求最少多少步可以变为斐波那契数
#include<iostream>
using namespace std;

int main()
{
	int N, l, r;
	int f0 = 0, f1 = 1, f;
	cin >> N;
	while (1){//循环求出斐波那契数
		f = f0 + f1;
		f0 = f1;
		f1 = f;
		if (f<N)
			l = N - f;//最侧最小距离
		else{
			r = f - N;//右侧最小距离
			break;
		}
	}
	cout << min(l, r) << endl;
	return 0;
}