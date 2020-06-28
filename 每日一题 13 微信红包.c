//Å£¿Í Î¢ÐÅºì°ü
class Gift {
public:
	int getValue(vector<int> gifts, int n) {
		sort(gifts.begin(), gifts.end());
		int mid = gifts[n / 2];
		int count = 0;
		for (int i = 0; i<n; i++){
			if (gifts[i] == mid)
				count++;
		}
		if (count>n / 2)
			return mid;
		return 0;
	}
};