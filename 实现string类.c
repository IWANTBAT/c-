#include<string>

#include<iostream>

using namespace std;



class String{
public:
	//无参构造
	String()
		:_str(new char[16])
		, _size(0)
		, _capacity(15)
	{
		_str[0] = '\0';
	}
	//带参构造
	String(const char* str){
		_size = strlen(str);
		_str = new char[_size + 1];
		strcpy(_str, str);
		_capacity = _size;
	}

	//拷贝构造(深拷贝)
	String(const String& str)
		:_str(new char[str._capacity + 1])
		, _size(str._size)
		, _capacity(str._capacity)
	{
		strcpy(_str, str._str);
	}
	//拷贝构造的现代写法
	/*String(const String& str)
	:_str(nullptr)
	, _size(0)
	, _capacity(0)
	{
	String tem(str._str);
	Swap(tem);
	}
	void Swap(String& str){
	swap(_str, str._str);
	swap(_size, str._size);
	swap(_capacity, str._capacity);
	}*/

	//复制运算符重载
	String& operator=(const String& str){
		if (this != &str){
			char* temp = new char[str._capacity + 1];

			strcpy(temp, str._str);

			delete[] _str;
			_str = temp;
			_size = str._size;
			_capacity = str._capacity;
		}
		return *this;
	}
	//赋值运算符的现代写法
	//传值->发生值拷贝->调用拷贝构造->开空间->内容拷贝
	/*String& operator = (String str){
	Swap(str);//交换临时变量（str的拷贝）与*this;
	return *this;
	}*/

	//尾插
	void pushBack(char ch){
		/*//扩容
		if (_size == _capacity){
		size_t newcapacity = _capacity == 0 ? 15 : 2 * _capacity;
		reserve(newcapacity);
		}
		//尾插
		_str[_size] = ch;
		_size++;
		_str[_size] = '\0';*/

		//根据insert，遵循代码复用原则，可以写为：
		insert(_size, ch);

	}
	void reserve(size_t n){
		if (n > _capacity){
			//开空间：
			char* temp = new char[n + 1];
			//拷贝
			strcpy(temp, _str);
			//释放原有空间
			delete[] _str;
			//更新容量
			_capacity = n;
		}
	}
	//遍历
	const char* c_str() const{
		return _str;
	}

	//迭代器
	typedef char* iterator;
	typedef const char* const_iterator;
	iterator begin(){
		return _str;
	}
	iterator end(){
		return _str + _size;
	}
	const_iterator begin() const{
		return _str;
	}
	const_iterator end() const{
		return _str + _size;
	}

	//[]重载
	char& operator[](size_t pos){
		if (pos < _size)
			return _str[pos];
	}
	const char& operator[](size_t pos)const{
		if (pos < _size)
			return _str[pos];
	}

	//插入字符串
	void Append(const char* str){
		/*//检查容量
		int len = strlen(str);
		if (_size + len > _capacity){
		reserve(_size + len);
		}
		//拷贝内容
		strcpy(_str + _size, str);
		//修改大小
		_size += len;*/

		//根据insert，代码复用，可写为：
		insert(_size, str);
	}

	//根据pushBack()和Append()函数，可以写出 += 重载
	String& operator+=(const char& ch){
		pushBack(ch);
		return *this;
	}
	String& operator+=(const char* str){
		Append(str);
		return *this;
	}

	//insert函数
	void insert(size_t pos, const char& ch){
		//是否合法
		if (pos > _size)//非法
			return;
		//检查容量
		if (_size == _capacity){
			size_t newcapacity = _capacity == 0 ? 15 : 2 * _capacity;
			reserve(newcapacity);
		}

		//移动元素：从后向前，防止覆盖
		size_t end = _size + 1;
		while (end > pos){
			_str[end] = _str[end - 1];
			end--;
		}
		//插入元素
		_str[pos] = ch;
		++_size;
		_str[_size] = '\0';
	}
	void insert(size_t pos, const char* str){
		//是否合法
		if (pos > _size)//非法
			return;
		//检查容量
		int len = strlen(str);
		if (_size + len > _capacity){
			reserve(_size + len);
		}
		size_t end = _size + len;
		while (end > _size + len - 1){
			_str[end] = _str[end - len];
			end--;
		}
		//插入
		for (int i = 0; i < len; i++){
			_str[i + pos] = str[i];
		}

		_size += len;
	}
	//析构函数
	~String(){
		delete[] _str;
		_size = _capacity = 0;
		_str = nullptr;
	}
private:
	char* _str;
	size_t _size;
	size_t _capacity;
};

void test(){
	String str = "";
	str.pushBack('a');
	str.pushBack('a');
	str.pushBack('a');
	str.pushBack('a');
	str.pushBack('a');


	cout << str.c_str() << endl;
	////String str1 = str;
	////String str2(str);

	//String::iterator it = str.begin();
	//while (it != str.end()){
	//	cout << *it << " ";
	//	++it;
	//}
	//cout << endl;
	//范围for：通过迭代器实现，在编译时，把范围for转化为迭代器遍历方式
	for (const char& ch : str){
		cout << ch << " ";
	}
	cout << endl;
}
int main(){

	test();
	return 0;
}