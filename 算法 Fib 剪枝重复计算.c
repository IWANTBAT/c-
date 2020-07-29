class Solution {
	
private:
	unordered_map<int, int> filter;
public:
	int Fibonacci(int n) {
		if (n == 0 || n == 1){ return n; }
		int pre = 0;
		if (filter.find(n - 1) == filter.end())
		{ pre = Fibonacci(n - 1);
		filter.insert({ n - 1, pre });
		}
		else{
			pre = filter[n - 1];
		}
		int ppre = 0;
		if (filter.find(n - 2) == filter.end()){
			ppre = Fibonacci(n - 2);
			filter.insert({ n - 2, ppre });
		}
		else{ ppre = filter[n - 2]; }
		return  pre + ppre;
	}
};