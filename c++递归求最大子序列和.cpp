//�ݹ�
#include<iostream>
using namespace std;

//������������������
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
//�ݹ��ҳ���������к�
static int Maxsum(const int A[], int left, int right){
	int Maxleftsum, Maxrightsum;//��벿�ֺ��Ұ벿�ֵ���������к�
	int Maxleftbodersum, Maxrightbodersum;//������벿�����һ�����Ұ벿�ֵ�һ������������к�
	int leftbodersum, rightbodersum;
	int center, i;
	if (left == right){//�ݹ����
		if (A[left] > 0){
			return A[left];
		}
		else{
			return 0;
		}
	}

	center = (left + right) / 2;
	Maxleftsum = Maxsum(A, left, center);//�ݹ�����벿����������к�
	Maxrightsum = Maxsum(A, center + 1, right);//���Ұ벿����������к�

	Maxleftbodersum = 0; leftbodersum = 0;//��벿�ְ������һ��Ԫ�ص���������к�
	for (i = center; i >= left; i--){
		leftbodersum += A[i];
		if (leftbodersum > Maxleftbodersum){
			Maxleftbodersum = leftbodersum;
		}
	}

	Maxrightbodersum = 0; rightbodersum = 0;//�Ұ벿�ְ�����һ��Ԫ�ص���������к�
	for (i = center + 1; i < right; i++){
		rightbodersum += A[i];
		if (rightbodersum > Maxrightbodersum){
			Maxrightbodersum = rightbodersum;
		}
	}
	return Max(Maxleftsum, Maxrightsum, Maxleftbodersum + Maxrightbodersum);//���أ���벿����������кͣ��Ұ벿����������кͣ��Լ�������벿�����һ��Ԫ�غ��Ұ벿�ֵ�һ��Ԫ�ص���������кͣ����ߵ����ֵ
}

int Maxsubsequencesum(const int A[], int n){
	return Maxsum(A, 0, n - 1);
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
	int sum = Maxsubsequencesum(a, len - 1);
	cout << "��������к�Ϊ��" << sum << endl;
	delete[] a;//�ͷ�new���ڴ�
	return 0;
}