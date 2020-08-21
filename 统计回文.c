#include<iostream>
#include<string>

using namespace std;

bool isHW(string str){
	int len = str.length() - 1;
	int i = 0;
	while (i <= len){
		if (str[i] != str[len])
			return false;
		i++;
		len--;
	}
	return true;
}
int main()
{
	string str1, str2;
	getline(cin, str1);
	getline(cin, str2);
	int count = 0;
	for (int i = 0; i <= str1.size(); i++){
		string str = str1;
		str.insert(i, str2);
		if (isHW(str))
			count++;
	}
	cout << count << endl;
	return 0;
}