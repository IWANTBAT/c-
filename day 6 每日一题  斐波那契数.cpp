//����һ��N,ÿ�ο��Ա�ΪN+1����N-1�������ٶ��ٲ����Ա�Ϊ쳲�������
#include<iostream>
using namespace std;

int main()
{
	int N, l, r;
	int f0 = 0, f1 = 1, f;
	cin >> N;
	while (1){//ѭ�����쳲�������
		f = f0 + f1;
		f0 = f1;
		f1 = f;
		if (f<N)
			l = N - f;//�����С����
		else{
			r = f - N;//�Ҳ���С����
			break;
		}
	}
	cout << min(l, r) << endl;
	return 0;
}