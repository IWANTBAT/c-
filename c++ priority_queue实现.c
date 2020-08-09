#include<vector>
#include<iostream>

using namespace std;

template <class T>
struct Greater{
	bool operator()(const T& v1, const T& v2){
		return v1 > v2;
	}
};

template <class T>
struct Less{
	bool operator()(const T& v1, const T& v2){
		return v1 < v2;
	}
};
template <class T, class Continaner = vector<T>, class Compare = Less<T>>
class Priority_queue{
public:
	void push(const T& val){
		_con.push_back(val);
		shiftUp(_con.size() - 1);
	}

	void pop(){
		swap(_con[0], _con[_con.size() - 1]);
		_con.pop_back();
		shiftDown(0);
	}

	T& top(){
		return _con.front();
	}

	size_t size(){
		return _con.size();
	}

	bool empty(){
		return _con.empty();
	}
private:
	void shiftDown(int parent){
		int child = 2 * parent + 1;
		while (child < _con.size()){
			/*if (child + 1 < _con.size() && _con[child] < _con[child + 1])*/
			//使用仿函数
			if (child + 1 < _con.size() && _cmp(_con[child], _con[child + 1]))

				child++;
			if (_cmp(_con[parent], _con[child])){
				swap(_con[parent], _con[child]);
				parent = child;
				child = 2 * parent + 1;
			}
			else
				break;
		}
	}

	void shiftUp(int child){
		int parent = (child - 1) / 2;
		while (child > 0){
			if (_cmp(_con[parent], _con[child])){
				swap(_con[parent], _con[child]);
				child = parent;
				parent = (child - 1) / 2;
			}
			else
				break;
		}
	}
private:
	Continaner _con;
	Compare _cmp;//仿函数
};

void test(){
	Priority_queue<int, vector<int>, Greater<int>> pq;
	pq.push(111);
	pq.push(222);
	pq.push(77);
	pq.push(11);
	pq.push(55);
	pq.push(33);
	pq.push(22);
	pq.push(100);

	while (!pq.empty()){
		cout << pq.top() << " ";
		pq.pop();
	}
	cout << endl;
}

int main()
{
	test();
	return 0;
}