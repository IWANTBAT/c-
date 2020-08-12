#include<iostream>
#include<set>

using namespace std;

void Printset(const set<int>& val){
	set<int>::iterator it = val.begin();
	while (it != val.end()){

		cout << *it << " ";
		it++;
	}
	cout << endl;
}
void test()
{
	set<int> a;

	int arr[] = { 1, 2, 3, 5, 0, 4 };
	set<int> b(arr, arr + 6);

	set<int> c(b);

	b.insert(10);
	b.insert(b.begin(), 11);//迭代器指定的位置只是一个建议，插入数据的位置不一定是指定位置，要保持二叉搜索树的结构
	b.insert(b.end(), 12);

	Printset(b);
	Printset(c);

}

int main()
{
	test();

	return 0;
}