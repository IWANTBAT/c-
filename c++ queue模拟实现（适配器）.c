#include<iostream>
#include<deque>

using namespace std;

template <class T, class Container = deque<T>>
class Queue{
public:
	void push(const T& val){
		_con.push_back(val);
	}

	void pop(){
		_con.pop_front();
	}

	T& front(){
		return _con.front();
	}

	T& back(){
		return _con.back();
	}
	const T& front() const{
		return _con.front();
	}

	const T& back() const{
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
	Queue<int> q;
	q.push(1);
	q.push(2);
	q.push(3);
	q.push(4);

	while (!q.empty()){
		cout << q.front() << " ";
		q.pop();
	}
	cout << endl;
}

int main()
{
	test();
	return 0;
}