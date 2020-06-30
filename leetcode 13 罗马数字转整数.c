#include<stdio.h>
#include<windows.h>
#pragma warning(disable:4996)
int romanToInt(char * s){
	int count = 0;
	while (*s){
		if (*s == 'V')         count += 5;
		else if (*s == 'L')    count += 50;
		else if (*s == 'D')    count += 500;
		else if (*s == 'M')    count += 1000;
		else if (*s == 'I')
			count = (*(s + 1) == 'V' || *(s + 1) == 'X') ? count - 1 : count + 1;
		else if (*s == 'X')
			count = (*(s + 1) == 'L' || *(s + 1) == 'C') ? count - 10 : count + 10;
		else
			count = (*(s + 1) == 'D' || *(s + 1) == 'M') ? count - 100 : count + 100;
		s++;
	}
	return count;
}

int main()
{
	char *s = "III";
	int a = romanToInt(s);
	printf("%d\n", a);
	system("pause");
	return 0;
}
