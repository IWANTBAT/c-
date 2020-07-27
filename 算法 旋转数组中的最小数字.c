class Solution {
public:
	int minNumberInRotateArray(vector<int> rotateArray) {
		if (rotateArray.empty()){
			return 0;
		}
		int left = 0;
		int right = rotateArray.size() - 1;
		int mid = 0;
		//要一直满足该条件，以证明旋转特性         
		while (rotateArray[left] >= rotateArray[right]){
			if (right - left == 1){
				//两个下标已经相邻了
				mid = right;
				break;
			}
			mid = left + ((right - left) >> 1); //注意操作符优先级
			if (rotateArray[mid] == rotateArray[left] && rotateArray[left] == rotateArray[right]){
				//无法判定目标数据在mid左侧，还是右侧采用线性遍历方式
				int result = rotateArray[left];
				for (int i = left + 1; i < right; i++){
					if (result > rotateArray[i]){
						result = rotateArray[i];
					}
				}
				return result;
			}
			if (rotateArray[mid] >= rotateArray[left]){
				//试想两者相等， 隐含条件 rotateArray[left] >= rotateArray[right]
				//说明mid在前半部分
				left = mid;
			}
			else{//说明mid在后半部分
				right = mid;
			}
		}
		return rotateArray[mid];
	}
};