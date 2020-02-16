//递归
#include<iostream>
using namespace std;

//返回三个数中最大的数
int Max(int a, int b, int c){
	int t = 0;
	if (a < b){
		t = a;
		a = b;
		b = t;
	}
	if (b < c){
		t = b;
		b = c;
		c = t;
	}
	if (a < b){
		t = a;
		a = b;
		b = t;
	}
	return a;
}
//递归找出最大子序列和
static int Maxsum(const int A[], int left, int right){
	int Maxleftsum, Maxrightsum;//左半部分和右半部分的最大子序列和
	int Maxleftbodersum, Maxrightbodersum;//包含最半部分最后一个和右半部分第一个的最大子序列和
	int leftbodersum, rightbodersum;
	int center, i;
	if (left == right){//递归出口
		if (A[left] > 0){
			return A[left];
		}
		else{
			return 0;
		}
	}

	center = (left + right) / 2;
	Maxleftsum = Maxsum(A, left, center);//递归求左半部分最大子序列和
	Maxrightsum = Maxsum(A, center + 1, right);//求右半部分最大子序列和

	Maxleftbodersum = 0; leftbodersum = 0;//左半部分包含最后一个元素的最大子序列和
	for (i = center; i >= left; i--){
		leftbodersum += A[i];
		if (leftbodersum > Maxleftbodersum){
			Maxleftbodersum = leftbodersum;
		}
	}

	Maxrightbodersum = 0; rightbodersum = 0;//右半部分包含第一个元素的最大子序列和
	for (i = center + 1; i < right; i++){
		rightbodersum += A[i];
		if (rightbodersum > Maxrightbodersum){
			Maxrightbodersum = rightbodersum;
		}
	}
	return Max(Maxleftsum, Maxrightsum, Maxleftbodersum + Maxrightbodersum);//返回（左半部分最大子序列和，右半部分最大子序列和，以及包含左半部分最后一个元素和右半部分第一个元素的最大子序列和）三者的最大值
}

int Maxsubsequencesum(const int A[], int n){
	return Maxsum(A, 0, n - 1);
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
	int sum = Maxsubsequencesum(a, len - 1);
	cout << "最大子序列和为：" << sum << endl;
	delete[] a;//释放new的内存
	return 0;
}