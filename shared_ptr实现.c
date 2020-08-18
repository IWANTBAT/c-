template <class T, class deletor>
class sharedPtr
{
public:
	sharedPtr(T* ptr, deletor del)
		:_ptr(ptr)
		, _useCount(new int(1))
		, _mtx(new mutex)
		, _del(del)
	{}

	~sharedPtr()
	{
		//引用计数自减
		//if (--(*_useCount) == 0)
		if (subRef() == 0)
		{
			//delete _ptr;
			//定制删除器进行空间释放
			del(_ptr);
			delete _useCount;
			delete _mtx;
			cout << "~sharedPtr" << endl;
		}
	}

	sharedPtr(const sharedPtr<T>& sp)
		:_ptr(sp._ptr)
		, _useCount(sp._useCount)
		, _mtx(sp._mtx)
	{
		//++(*_useCount);
		addRef();
	}

	sharedPtr<T>& operator=(const sharedPtr<T>& sp)
	{
		//if (this != &sp)
		//判断管理的资源是否相同
		if (_ptr != sp._ptr)
		{
			//判断当前管理的资源是否需要释放
			//if (--(*_useCount) == 0)
			if (subRef() == 0)
			{
				delete _ptr;
				delete _useCount;
				delete _mtx;
			}
			//赋值
			_ptr = sp._ptr;
			_useCount = sp._useCount;
			_mtx = sp._mtx;
			//++(*_useCount);
			addRef();
		}
		return *this;
	}

	int getUseCount()
	{
		return *_useCount;
	}

	int addRef()
	{
		_mtx->lock();
		++(*_useCount);
		_mtx->unlock();
		return *_useCount;
	}

	int subRef()
	{
		_mtx->lock();
		--(*_useCount);
		_mtx->unlock();
		return *_useCount;
	}

private:
	T* _ptr;
	int* _useCount;
	mutex* _mtx;
	deletor _del;
};