//最近公共祖先
//满二叉树求两个任意节点的最近公共祖先

/*
思路：根据满二叉树子节点与父节点之间的关系：root = child/2；

则：当 a!=b 时，让其中的较大数除以二（即回到其父节点），直到a == b
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