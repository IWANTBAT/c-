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
	int *a = new int[len];//������̬����
	int i = 0;
	cout << "��������:\n";
	for (i = 0; i < len; i++){
		cin >> a[i];
	}
	int sum = Maxsubsum(a, len - 1);
	cout << "��������к�Ϊ��" << sum << endl;
	delete[] a;//�ͷ�new���ڴ�
	return 0;
}