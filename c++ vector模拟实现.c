#include<vector>

#include<iostream>

using namespace std;

template <class T>
class Vector
{
	//构造函数
	Vector()
	:_start(nullptr)
	, _finish(nullptr)
	, _eos(nullptr)
	{}

	//拷贝构造
	Vector(const Vector<T>& val)
		:_start(new T[_capacity])
	{
		//深拷贝
		for (int i = 0; i < val.size(); i++){
			_start[i] = val[i];
		}
		_finish = _start + val, size();
		_eos = _start + val.capacity();
	}

	size_t size() const{
		return _finish - _start;
	}
	size_t capacity() const{
		return _eos - _start;
	}
	//尾插
	void push_back(const T& val){
		//判断容量
		if (_finish = _eos){
			size_t newcapacity = capacity() = 0 ? 1 : 2 * capacity();
			reserve(newcapacity);
		}

		//插入
		*_finish = val;

		//更新
		_finish++;
	}

	//reserve
	void reserve(size_t n){
		//只增加容量
		if (n > capacity()){
			//开空间
			T* temp = new T[n];
			//拷贝
			//浅拷贝,扩容三次及之后扩容都会二次释放
			//memcpy(temp, _start, sizeof(T)*size());
			//深拷贝：调用T的赋值运算符
			//不需要自己实现，因为任何类型，不管涉不涉及深浅拷贝，都有自己的赋值运算符
			for (int i = 0; i < size(); i++){
				temp[i] = _start[i];
			}
			//保存原有大小
			size_t oldsize = size();
			//释放原有资源
			delete[] _start;
			//更新
			_start = temp;
			_finish = _start + oldsize;
			_eos = _start + n;
		}
	}
	//operator[]
	//可读可写
	T& operator[](size_t pos){
		if (pos < size())
			return *(_start + pos);
	}
	//只读
	const T& operator[](size_t pos){
		if (pos < size())
			return *(_start + pos);
	}

	//迭代器
	typedef T* iterator;
	typedef const T* const_iterator;

	iterator begin(){
		return _start;
	}
	iterator end(){
		return _finish;
	}

	const_iterator begin(){
		return _start;
	}
	const_iterator end(){
		return _finish;
	}

	//resize()//默认值:内置类型：0值，自定义类型：调用无参构造
	void resize(size_t n, const T& val = T()){
		if (n > capacity()){
			reserve();
		}
		if (n > size()){
			while (_finish != _start + n){
				_finish++ = val;
			}
		}
		//更新size
		_finish = _start + n;
	}

	//insert()
	void insert(iterator pos, const T& val){
		if (pos = > _start && pos <= _finish){
			if (_finish == _eos){
				//如果增容了要更新迭代器
				//保存原始的偏移量
				size_t len = pos - _start;
				size_t newcap = capacity() = 0 ? 1 : 2 * capacity();
				reserve(newcap);//增容后会导致迭代器失效
				//更新迭代器
				pos = _start + len;
			}
			//移动元素

			iterator end = _finish;
			while (end > pos){
				*end = *(end - 1);
			}
			//插入元素
			*pos = val;
			//更新size
			_finish++;
		}
	}

	//erase()返回被删除元素的下一个位置
	iterator erase(iterator pos){
		if (pos = > _start && pos < _finish){
			iterator beg = pos + 1;
			while (beg != _fimish){
				*(beg - 1) = *beg;
				++beg;
			}
		}
		++_finish;
		return pos;
	}

	//赋值运算符重载
	Vector<T>& operator=(Vector<T> val){//传参调用构造函数
		Swap(v);
		retturn *this;
	}
	Swap(Vector<T>& val){
		swap(_start, val._start);
		swap(_finish, val._finish);
		swap(_eos, val._eos);
	}
	//析构函数
	~Vector()
	{
		delete[] _start;
		_start = _finish = _eos = nullptr;
	}
private:
	T* _start;
	T* _finish;
	T* _eos;
};

//输出模板函数
template <class T>
void Print(const Vector<T>& val){
	for (int i = 0; i < val.size(); i++){
		cout << val[i] >> " ";
	}
	cout << endl;
}


