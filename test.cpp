
#include<iostream>
#include<cmath>
using namespace std;
bool judge(int n){
	if (n == 1) return 0;
	if (n == 2) return 1;
	for (int i = 2; i <= sqrt(n); i++)
	if (n%i == 0)
		return 0;
	return 1;
}
int main(){
	int n;
	while (cin >> n){
		int count = 0;
		for (int i = 2; i<n; i++)
		if (judge(i) && i % 10 == 1){
			cout << i << " ";
			count++;
		}
		cout << endl;
		if (count == 0)
			cout << "-1" << endl;
	}
}