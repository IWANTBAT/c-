//�����������
//������������������ڵ�������������

/*
˼·���������������ӽڵ��븸�ڵ�֮��Ĺ�ϵ��root = child/2��

�򣺵� a!=b ʱ�������еĽϴ������Զ������ص��丸�ڵ㣩��ֱ��a == b
*/
class LCA {
public:
	int getLCA(int a, int b) {
		while (a != b){
			if (a>b)
				a = a / 2;
			else
				b = b / 2;
		}
		return a;
	}
};