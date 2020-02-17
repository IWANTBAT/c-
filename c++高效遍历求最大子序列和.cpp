#include<iostream>
using namespace std;

int Maxsubsum(const int A[], int n){
	int thissum, Maxsum, i;
	thissum = Maxsum = 0;
	for (i = 0; i < n; i++){
		thissum += A[i];
		if (thissum > Maxsum){
			Maxsum = thissum;
		}
		else if (thissum < 0){
			thissum = 0;
		}
	}
	return Maxsum;
}
int main()
{
	int len = 0;
	cout << "Enter len:\n";
	cin >> len;
	int *a = new int[len];//创建动态数组
	int i = 0;
	cout << "输入序列:\n";
	for (i = 0; i < len; i++){
		cin >> a[i];
	}
	int sum = Maxsubsum(a, len - 1);
	cout << "最大子序列和为：" << sum << endl;
	delete[] a;//释放new的内存
	return 0;
}