//��n*m�ĸ��ӣ������Ͻǵ����½��ж������߷���ֻ�����һ�����

//�ݹ�ⷨ
/*��(m,n)->(0,0)�������߷���
һ��������,f(a,b-1)->(0,0);
���������ߣ�f(a-1,b)->(0,0);
ע�⣺���ߵ����ӵı߽�ʱ������a == 0 || b == 0ʱ��ֻ��һ��֮ǰ��·����
*/
#include<iostream>

using namespace std;

int func(int a, int b){
	if (a == 0 || b == 0){
		return 1;
	}
	return func(a, b - 1) + func(a - 1, b);
}

int main()
{
	int a, b;
	while (cin >> a >> b){
		cout << func(a, b) << endl;
	}

	return 0;
}