//����һ�����֣��������������������1�ĸ���
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