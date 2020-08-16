#include<vector>
#include<iostream>
using namespace std;

class BitMap{
public:
	BitMap(size_t size){
		_bit.resize(size / 32 + 1);
	}

	//查询:Test
	bool Test(size_t n){
		int idx = n / 32;
		int bitidx = n % 32;
		if ((_bit[idx] >> bitidx) & 1)
			return true;
		return false;
	}
	//存储：Set
	void Set(size_t n){
		int idx = n / 32;
		int bitidx = n % 32;

		_bit[idx] |= (1 << bitidx);
	}
	//删除:Reset
	void Reset(size_t n){
		int idx = n / 32;
		int bitidx = n % 32;

		_bit[idx] &= ~(1 << bitidx);
	}
private:
	vector<int> _bit;
};
template <class T, class HF1, class HF2, class HF3>
class BloomFilter{
public:
	BloomFilter(size_t num)
		:_bit(5 * num)
		, _bcount(5 * num)
	{}

	void Set(const T& val){
		HF1 hf1;
		HF2 hf2;
		Hf3 hf3;
		size_t h1 = hf1(val);
		size_t h2 = hf2(val);
		size_t h3 = hf3(val);

		_bit.Set(h1%_bcount);
		_bit.Set(h2%_bcount);
		_bit.Set(h3%_bcount);
	}

	bool Test(const T& val){
		HF1 hf1;
		size_t h1 = hf1(val);
		if (!_bit.Test(h1%_bcount))
			return false;
		HF2 hf2;
		size_t h2 = hf2(val);
		if (!_bit.Test(h2%_bcount))
			return false;
		HF3 hf3;
		size_t h3 = hf3(val);
		if (!_bit.Test(h3%_bcount))
			return false;
		return true;
	}
private:
	BitMap _bit;
	size_t _bcount;
};