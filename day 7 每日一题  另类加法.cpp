//����ӷ�  -��  λ����ӷ�

class UnusualAdd {
public:
	int addAB(int A, int B) {
		int a, b;
		while (B != 0){
			a = A^B;
			b = (A&B) << 1;
			A = a;
			B = b;
		}
		return A;
	}
};