//����һ��ʮ������M���Լ���Ҫת���Ľ�����N,��ʮ������Mת��ΪN������
#include<iostream>
#include<string>

using namespace std;

int main()
{
	int m, n;
	cin >> m >> n;
	string str = "";
	string s = "0123456789ABCDEF";
	while (m){
		if (m<0){
			m = -m;
			cout << "-";
		}
		str = s[m%n] + str;
		m = m / n;
	}
	cout << str << endl;
	return 0;
}
//�����ǹ�
#include<iostream>

using namespace std;

int main()
{
	int a, b, c, d;
	cin >> a >> b >> c >> d;

	int A = (int)(a + c) / 2;
	int B = (int)(c - a) / 2;
	int C = (int)(d - b) / 2;
	if (A - B == a && B - C == b && A + A == c && B + C == d){
		cout << A << " " << B << " " << C << endl;
	}
	else
		cout << "No" << endl;
	return 0;
}