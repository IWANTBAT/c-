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

void test(){
	BitMap bit(100);

	bit.Set(4);
	bit.Set(31);
	bit.Set(48);

	bit.Reset(4);
	bool ret = bit.Test(4);
	ret = bit.Test(21);

}

int main()
{
	test();
	return 0;
}