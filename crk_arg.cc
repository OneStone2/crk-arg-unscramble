#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

map<vi, vvi> dp;
map<vi, vector<string> > words;

bool fits(vi target, vi cur) {
	for (int i = 0; i < target.size(); ++i) {
		if (target[i] > cur[i]) return false;
	}
	return true;
}

vi nxt(vi target, vi cur) {
	for (int i = 0; i < target.size(); ++i) cur[i] -= target[i];
	return cur;
}

vi prev(vi target, vi cur) {
	for (int i = 0; i < target.size(); ++i) cur[i] += target[i];
	return cur;
}

int weight(vi cur) {
	int total = 0;
	for (int i = 0; i < cur.size(); ++i) total += cur[i];
	return total;
}

void write(vi orig, vi cur, string t, int level) {
	if (orig == cur) cout << t << endl;
	for (vi u:dp[cur]) {
		vi v = prev(u, cur);
		for (string s:words[u]) {
			write(orig, v, t+" "+s, level+1);
		}
	}
}

int main() {
	map<char, int> m;
	
	map<vi, bool> visited;
	priority_queue< pair<int, vi> > pq;
	m['A'] = 0;
	m['E'] = 1;
	m['I'] = 2;
	m['L'] = 3;
	m['M'] = 4;
	m['N'] = 5;
	m['O'] = 6;
	m['R'] = 7;
	m['U'] = 8;
	m['Y'] = 9;
	string s = "UYOALINE";
	vi cur(10, 0);
	for (char c:s) cur[m[c]] += 1;
	dp[cur] = vvi();
	visited[cur] = false;
	pq.push({weight(cur), cur});
	vi orig = cur;
	
	vvi move;
	ifstream myfile;
	myfile.open("words.txt");
	while (myfile) {
		myfile >> s;
		vi target(10, 0);
		for (char c:s) target[m[c]] += 1;
		move.push_back(target);
		words[target].push_back(s);
	}
	
	while (pq.size() > 0) {
		vi u = pq.top().second;
		
		pq.pop();
		if (!visited[u]) {
			visited[u] = true;
			for (int i = 0; i < move.size(); ++i) {
				if (fits(move[i], u)) {
					vi v = nxt(move[i], u);
					dp[v].push_back(move[i]);
					pq.push({weight(v), v});
				}
			}
		}
	}
	
	write(orig, vi(10, 0), "", 0);
	
}
