
class Solution {
public:
	bool Find(int target, vector<vector<int> > array) {
		int i = 0;
		int j = array[0].size() - 1;
		while (i<array.size() && j >= 0){
			if (target < array[i][j]){//排除当前列
				j--;
			}
			else if (target > array[i][j]){//排除当前行
				i++;
			}
			else{
				return true;
			}
		}
		return false;//while条件不成立时说明没找到
	}
};