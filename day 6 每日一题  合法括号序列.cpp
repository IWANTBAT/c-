//∫œ∑®¿®∫≈–Ú¡–
class Parenthesis {
public:
	bool chkParenthesis(string A, int n) {
		int count = 0;
		for (int i = 0; i<n; i++){
			if (A[i] == '('){
				count++;
			}
			else if (A[i] == ')'){
				if (count <= 0)
					return false;
				count--;
			}
			else
				return false;
		}
		return true;
	}
};