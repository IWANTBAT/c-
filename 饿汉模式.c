

class singleton{
public:
	static singleton& Get(){
		return _single;
	}
private:
	singleton()
	{}

	singleton(const singleton&) = delete;

	singleton& operator=(const singleton&) = delete;

	static singleton _single;
};

singleton singleton::_single;