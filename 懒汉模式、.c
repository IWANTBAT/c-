#include<iostream>
#include<thread>
#include<mutex>
using namespace std;


class singleton{
public:
	static singleton* Get(){
		//双检查提高效率
		if (_single == nullptr)
		{
			_mux.lock();
			if (_single == nullptr)
				_single = new singleton;
			_mux.unlock();
		}
		return _single;
	}
private:
	singleton()
	{}

	singleton(const singleton&) = delete;

	singleton& operator=(const singleton&) = delete;

	static singleton* _single;

	static mutex _mux;
};

singleton* singleton::_single = nullptr;

mutex singleton::_mux;