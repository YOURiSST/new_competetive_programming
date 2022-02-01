
struct Node {
	bool term;
	int go[26];
	int cnt;
	int parent;
	Node() {
		term = false;
		cnt = 0;
		parent = -1;
		fill(go, go + 26, -1);
	}
};

struct Trie {
	vector<Node> nodes;
	Trie() {
		nodes.eb(Node());
	}

	void insert(const string& s) {
		int v = 0;
		for (auto & c : s) {
			if (nodes[v].go[c - 'a'] == -1) {
				nodes.eb(Node());
				nodes[v].go[c - 'a'] = nodes.size() - 1;
				nodes.back().parent = v;
			}
			nodes[v].cnt++;
			v = nodes[v].go[c - 'a'];
		}
		nodes[v].term = true;
		nodes[v].cnt++;
	}

	bool del(const string& s, int i, int v) {
		if (i == s.size()) {
			if (!nodes[v].term) {
				return false;
			}
			nodes[v].term = false;
			nodes[v].cnt--;
			return true;
		}
		int to = nodes[v].go[s[i] - 'a'];
		if (to == -1) {
			return false;
		}
		if (del(s, i + 1, to)) {
			--nodes[v].cnt;
			if (nodes[to].cnt == 0) {
				nodes[v].go[s[i] - 'a'] = -1;
			}
			return true;
		}
		return false;
	}

	void del(const string& s) {
		del(s, 0, 0);
	}

	string find_sorted(int k) {
        int ind = 0; //int v
        string ret;
        while(true) {
            if (k == 0 && nodes[ind].term) {
                break;
            }
            if (nodes[ind].term) {
                k--;
            }
            int counter = 0, counter_old = 0;
            int i;
            for (i = 0; i < 26; ++i) {
                if (nodes[ind].go[i] == -1) {
                    continue;
                }
                counter += nodes[nodes[ind].go[i]].cnt;
                if (counter >= k) {
                    break;
                }
                counter_old = counter;
                
            }
            ind = nodes[ind].go[i];
            ret.pb(i + 'a');
            k -= counter_old;
        }
        return ret;
    }
};