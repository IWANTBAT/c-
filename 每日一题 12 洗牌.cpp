
#include <iostream>
#include <vector>
using namespace std;

void shuffle(unsigned int n, int k, std::vector<unsigned int>& out) {
	std::vector<unsigned int> tmp;
	while (k--) {
		tmp = out;
		for (unsigned int i = 0; i < n; ++i) {
			out[2 * i] = tmp[i];
			out[2 * i + 1] = tmp[n + i];
		}
	}
}


int main() {
	int T, k;
	unsigned int n;
	cin >> T;
	while (T--) {
		cin >> n >> k;
		std::vector<unsigned int> out(2 * n);
		for (unsigned int j = 0; j < 2 * n; ++j) {
			cin >> out[j];
		}
		shuffle(n, k, out);
		for (unsigned int j = 0; j < 2 * n; ++j) {
			if (j == 0) {
				cout << out[j];
			}
			else {
				cout << ' ' << out[j];
			}
		}
		cout << endl;
	}
	return 0;
}


