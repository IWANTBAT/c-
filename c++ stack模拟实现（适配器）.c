#include<deque>
#include<vector>
#include<list>
#include<iostream>

using namespace std;
template <class T, class Container = deque<T>>
class Stack{
public:
	void push(const T& val){
		_con.push_back(val);
	}
	void pop(){
		_con.pop_back();
	}

	const T& top(){
		return _con.back();
	}

	size_t size(){
		return _con.size();
	}

	bool empty(){
		return _con.empty();
	}
private:
	Container _con;
};

void test(){
	Stack<int> s;
	s.push(1);
	s.push(2);
	s.push(3);
	s.push(3);

	while (!s.empty()){
		cout << s.top() << " ";
		s.pop();
	}
	cout << endl;
}

int main()
{
	test();
	return 0;
}

