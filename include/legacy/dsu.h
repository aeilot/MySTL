//
// Created by Chenluo Deng on 3/2/26.
//

#ifndef MY_STL_DSU_H
#define MY_STL_DSU_H

#include <vector>

namespace DS {
	class DSU {
		public:
		std::vector<int> pa, size;
		int count;

		DSU(int count) : count(count) {
			size.resize(count, 1);
			pa.resize(count, 0);
			for (int i = 0; i < count; i++) {
				pa[i] = i;
			}
		}

		int find(int x) {
			return pa[x]==x ? x : pa[x] =  find(pa[x]);
		}

		void unite(int x, int y){
			x = find(x);
			y = find(y);
			if (x==y) return;
			if (size[x] < size[y]) std::swap(x,y);
			pa[y] = x;
			size[x] += size[y];
		}
	};
}

#endif //MY_STL_DSU_H