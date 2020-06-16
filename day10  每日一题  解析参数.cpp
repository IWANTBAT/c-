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
			flag = ~flag;  // flag为1表示在""里面，为0表示在""外面
		}
		else if (' ' == str[i] && 0 == flag)
		{
			svec.push_back(temp);
			temp = "";
		}
		else
			temp += str[i];
	}
	svec.push_back(temp);  // 最后一个循环还有一个temp
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

