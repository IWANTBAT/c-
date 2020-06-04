//数组出现次数超过一般的数字

class Solution {
public:
	int MoreThanHalfNum_Solution(vector<int> numbers) {
		int n = numbers.size();
		if (n == 0)
			return 0;
		int num = numbers[0];
		int count = 1;
		for (int i = 1; i<n; i++)
		{
			if (num == numbers[i])
				count++;
			else
				count--;
			if (count == 0)
			{
				num = numbers[i];
				count = 1;
			}
		}
		count = 0;
		for (int i = 0; i<n; i++)
		{
			if (numbers[i] == num)
				count++;
		}
		if (count * 2 > n)
			return num;
		return 0;
	}
};

//字符串中找出连续最长的数字串
#include<iostream>
#include<string>

using namespace std;

int main()
{
	string str1, str2, str3;
	cin >> str1;
	int i = 0;
	for (; i<str1.length(); i++)
	{
		if (str1[i] >= '0'&&str1[i] <= '9')
			str2 += str1[i];
		else
		{
			if (str3.length()<str2.length())
			{
				str3 = str2;
				str2 = "";
			}
		}
	}
	cout << str3;
	return 0;
}