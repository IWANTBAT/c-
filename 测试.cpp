
#include<iostream>

int Maxsum(const int A[], int n){
	int thissum, maxsum, i, j, k;
	maxsum = 0;
	for (i = 0; i < n; i++){
		for (j = i; j < n; j++){
			thissum = 0;
			for (k = i; k < n; k++){
				thissum += A[k];
				if (thissum>maxsum){
					maxsum = thissum;
				}
			}
		}
	}
	return maxsum;
}
int main()
{
	using namespace std;
	int len = 0;
	cout << "Enter len" << endl;
	cin >> len;
	int *a = new int[len];
	int i = 0;
	cout << "输入序列" << endl;
	for (i = 0; i < len; i++){
		cin >> a[i];
	}
	int sum = Maxsum(a, len);
	delete[] a;
	cout << "最大子序列和为：" << sum << endl;
	return 0;
}

减少不必要的循环
#include<iostream>

int Maxsum(const int A[], int n){
	int thissum, maxsum, i, j;
	maxsum = 0;
	for (i = 0; i < n; i++){
		thissum = 0;
		for (j = i; j < n; j++){
			thissum += A[j];
			if (thissum>maxsum){
				maxsum = thissum;
			}
		}
	}
	return maxsum;
}
int main()
{
	using namespace std;
	int len = 0;
	cout << "Enter len" << endl;
	cin >> len;
	int *a = new int[len];
	int i = 0;
	cout << "输入序列" << endl;
	for (i = 0; i < len; i++){
		cin >> a[i];
	}
	int sum = Maxsum(a, len);
	delete[] a;
	cout << "最大子序列和为：" << sum << endl;
	return 0;
}