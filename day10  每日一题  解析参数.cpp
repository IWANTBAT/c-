#include <iostream>
#include <string>
#include <vector>

using namespace std;

void cmdExplain(const string & str)
{
	string temp = "";
	vector<string> svec;
	int size = str.size();
	int flag = 0;
	for (int i = 0; i< size; i++)
	{
		if ('"' == str[i])
		{
			flag = ~flag;  // flagΪ1��ʾ��""���棬Ϊ0��ʾ��""����
		}
		else if (' ' == str[i] && 0 == flag)
		{
			svec.push_back(temp);
			temp = "";
		}
		else
			temp += str[i];
	}
	svec.push_back(temp);  // ���һ��ѭ������һ��temp
	int t = svec.size();
	cout << t << endl;
	for (int i = 0; i < t; i++){
		cout << svec[i] << endl;
	}
		
}

int main()
{
	string str;
	while (getline(cin, str))
	{
		cmdExplain(str);
	}
}

