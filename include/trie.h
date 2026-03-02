//
// Created by Chenluo Deng on 3/2/26.
//

#ifndef MY_STL_TRIE_H
#define MY_STL_TRIE_H
#include <algorithm>
#include <string>

namespace DS {
	const int N = 100000;

	class Trie {
		public:
		int trie[N][26];
		int tot;
		int cnt[N];
		Trie() {
			std::memset(trie, 0, sizeof(trie));
			std::memset(cnt, 0, sizeof(cnt));
			tot = 0;
		}

		void insert(const std::string & x) {
			int sz = x.size();
			int p = 0;
			for (int i = 0; i<sz; i++) {
				int ch = x[i] - 'a';
				if (!trie[p][ch]) {
					trie[p][ch] = ++tot;
				}
				p = trie[p][ch];
			}
			cnt[p]++;
		}

		int find(const std::string & x) {
			int sz = x.size();
			int p = 0;
			for (int i = 0; i<sz; i++) {
				int ch = x[i] - 'a';
				if (trie[p][ch] == -1) {
					return 0;
				}
				p = trie[p][ch];
			}
			return cnt[p];
		}
	};
}

#endif //MY_STL_TRIE_H