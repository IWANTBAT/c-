#include<iostream>
#include<vector>
#include<string>

using namespace std;

int main()
{
	int n;
	cin >> n;
	vector<string> v;
	v.resize(n);
	for (auto& str : v){
		cin >> str;
	}

	bool len = true, lex = true;
	for (size_t i = 1; i<v.size(); i++){
		if (v[i - 1].size() >= v[i].size()){
			len = false;
			break;
		}
	}

	for (size_t i = 1; i<v.size(); i++){
		if (v[i - 1] >= v[i]){
			lex = false;
			break;
		}
	}
	if (len&&lex)
		cout << "both" << endl;
	else if (!len&&lex)
		cout << "lexicographically" << endl;
	else if (len && !lex)
		cout << "lengths" << endl;
	else if (!len && !lex)
		cout << "none" << endl;
	return 0;

}