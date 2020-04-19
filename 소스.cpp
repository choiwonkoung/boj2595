#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
using namespace std;
typedef struct _Sbfs{
	int count;
	int pre,prei;
	int remain;
}Sbfs;
typedef struct _Sans {
	char answer[300010];
}Sans;
bool cmp_str(char *a, char *b) {
	if (strlen(a) > strlen(b))return true;
	if (strlen(a) < strlen(b))return false;
	for (int i=0;i<strlen(a);i++) {
		if (a[i] > b[i])return true;
		else if (a[i] < b[i])return false;
	}
	return false;
}
int check[30010] = { 0, };
int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int n; cin >> n;
	vector<Sbfs> bfs;
	vector<Sans> answers;
	for (int a = 1; a < 10; a++) {
		for (int i = 0; i <= 30001; i++)check[i] = 0;
		bfs.clear();
		Sbfs tmp;
		tmp.remain = a % n; tmp.count = 1;
		check[tmp.remain] = 1;
		bfs.push_back(tmp);
		for (int i = 0; i < bfs.size(); i++) {
			if (bfs[i].remain == 0) {
				Sans ans;
				for (int j = 0; j < bfs[i].count; j++) {
					ans.answer[j] = a+'0';
				}
				ans.answer[bfs[i].count] = '\0';
				answers.push_back(ans);
				break;
			}
			if (bfs[i].count <= 30001) {
				Sbfs tmp;
				tmp.count = bfs[i].count + 1;
				tmp.remain = (bfs[i].remain * 10 + a) % n;
				if (check[tmp.remain]==0) {
					check[tmp.remain] = 1;
					bfs.push_back(tmp);
				}
			}
		}
	}
	if (answers.size() != 0) {
		char* ans;
		ans = answers[0].answer;
		for (int i = 0; i < answers.size(); i++) {
			if (cmp_str(ans, answers[i].answer) == true)ans = answers[i].answer;
		}
		cout << ans;
		return 0;
	}
	for (int a = 0; a < 10; a++) {
		for (int b = a+1; b < 10; b++) {
			for (int i = 0; i <= 30001; i++)check[i] = 0;
			bfs.clear();
			Sbfs tmp;
			tmp.count = 1;	tmp.prei = 0; 
			if (a != 0) {
				tmp.pre = a; tmp.remain = a % n;
				check[tmp.remain] = 1;
				bfs.push_back(tmp);
			}
			tmp.pre = b; tmp.remain = b % n;
			if (check[tmp.remain] == 0) {
				check[tmp.remain] = 1;
				bfs.push_back(tmp);
			}
			for (int i = 0; i < bfs.size(); i++) {
				if (bfs[i].remain == 0) {
					Sans ans;
					int now_i=i;
					for (int j = bfs[i].count - 1; j >= 0; j--) {
						ans.answer[j] = bfs[now_i].pre + '0';
						now_i = bfs[now_i].prei;
					}
					ans.answer[bfs[i].count] = '\0';
					answers.push_back(ans);
					break;
				}
				if (bfs[i].count <= 30001) {
					Sbfs tmp;
					tmp.count = bfs[i].count + 1; tmp.prei = i;
					tmp.pre = a; tmp.remain = (bfs[i].remain * 10 + a) % n;
					if (check[tmp.remain] == 0) {
						check[tmp.remain] = 1;
						bfs.push_back(tmp);
					}
					tmp.pre = b; tmp.remain = (bfs[i].remain * 10 + b) % n;
					if (check[tmp.remain] == 0) {
						check[tmp.remain] = 1;
						bfs.push_back(tmp);
					}
				}
			}
		}
	}
	char* ans;
	ans = answers[0].answer;
	for (int i = 0; i < answers.size(); i++) {
		if (cmp_str(ans, answers[i].answer) == true)ans = answers[i].answer;
	}
	cout << ans;
	return 0;
}