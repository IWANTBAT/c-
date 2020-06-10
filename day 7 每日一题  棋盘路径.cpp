//求n*m的格子，从左上角到右下角有多少种走法；只能往右或往下

//递归解法
/*从(m,n)->(0,0)分两种走法：
一：往右走,f(a,b-1)->(0,0);
二：往下走，f(a-1,b)->(0,0);
注意：当走到格子的边界时，即：a == 0 || b == 0时，只有一条之前的路可走
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