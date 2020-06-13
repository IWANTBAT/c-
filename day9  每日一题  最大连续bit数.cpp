//给定一个数字，求出其二进制中最大连续1的个数
#include<iostream>

using namespace std;

int main()
{
	int a;
	while (cin >> a){
		int sum = 0, max = 0;
		while (a){
			if (a % 2){
				sum++;
				if (sum>max)
					max = sum;
			}
			else
				sum = 0;
			a >>= 1;
		}
		cout << max << endl;
	}
	return 0;
}