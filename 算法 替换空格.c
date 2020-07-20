/*
不使用容器，降低空间占用；
依然使用之前的空间，因为空间变大，所以从后往前进行移动；
*/

class Solution {
public:
	void replaceSpace(char *str, int length) {
		int count = 0;
		char* start = str;
		while (*start){
			if (isspace(*start)){
				count++;
			}
			start++;
		}
		char* old_end = str + length;
		char* new_end = str + length + 2 * count;
		while (old_end >= str && new_end >= str){
			if (isspace(*old_end)){
				*new_end-- = '0';
				*new_end-- = '2';
				*new_end-- = '%';
				old_end--;
			}
			else{
				*new_end = *old_end;
				new_end--;
				old_end--;

			}
		}
	}
};