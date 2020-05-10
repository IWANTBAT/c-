// 求取一个非负整数的位数
int GetBitNum(int n)
{
	int bitCnt = 0;
	if (n == 0) {
		bitCnt = 1;
	}

	while (n != 0) {
		n = n / 10;
		bitCnt++;
	}

	return bitCnt;
}

// 比较函数
int cmp(const void *a, const void *b)
{
	char tmpBuffa[64], tmpBuffb[64];
	sprintf(tmpBuffa, "%d%d", *(int*)a, *(int*)b);
	sprintf(tmpBuffb, "%d%d", *(int*)b, *(int*)a);

	return strcmp(tmpBuffb, tmpBuffa);
}

char * largestNumber(int* nums, int numsSize){
	if ((nums == NULL) || (numsSize == 0)) {
		return NULL;
	}
	int bitSum = 0;
	int resCnt = 0;

	// 遍历原始数据，求最长的数据位数和所有数据位之和
	for (int i = 0; i < numsSize; i++) {
		bitSum += GetBitNum(nums[i]);
	}

	char *res = (char*)calloc(bitSum + 1, sizeof(char));

	// 排序
	qsort(nums, numsSize, sizeof(int), cmp);

	// 连接字符串输出
	for (int i = 0; i < numsSize; i++) {
		resCnt += sprintf(res + resCnt, "%d", nums[i]);
	}

	// 特殊处理
	if (res[0] == '0') {
		res = "0";
	}

	return res;
}
