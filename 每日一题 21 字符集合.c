//字符集合

#include<iostream>
#include<string>

using namespace std;

int main()
{
	string str;
	while (cin >> str){
		int l = str.length();
		int a[123] = { 0 };
		for (int i = 0; i < l; i++){
			a[str[i]] = 1;
		}
		for (int i = 0; i < l; i++){
			if (a[str[i]] == 1){
				cout << str[i];
				a[str[i]] = 0;
			}
		}
		cout << endl;
	}
	return 0;
}
