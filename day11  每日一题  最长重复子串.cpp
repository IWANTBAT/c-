#include<iostream>
#include<string>

using namespace std;

int mian()
{
	string a;
	string b;
	while (cin >> a >> b){
		if (a.size()>b.size())
			swap(a, b);
		string res;
		for (int i = 0; i<a.size(); i++){
			for (int j = i; j<a.size(); j++){
				string temp = a.substr(i, j - i + 1);
				if (int(b.find(temp))<0)
					break;
				else if (res.size()<temp.size())
					res = temp;
			}
		}
		cout << res << endl;
	}
	return 0;
}