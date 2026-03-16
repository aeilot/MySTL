//
// Created by Chenluo Deng on 3/16/26.
//

#ifndef MY_STL_PRIORITY_QUEUE_H
#define MY_STL_PRIORITY_QUEUE_H
#include <vector>

inline int getLFT(int id) {
	return id*2;
}

inline int getRFT(int id) {
	return id*2+1;
}

inline int getFA(int id) {
	return id / 2;
}

class PriorityQueue {
private:
	std::vector<int> PQ;

	void up(int id) {
		while (id>1) {
			int fa = getFA(id);
			if (PQ[fa] >= PQ[id]) break;
			std::swap(PQ[fa], PQ[id]);
			id = fa;
		}
	}

	void down(int id) {
		int n = static_cast<int>(PQ.size()) - 1;
		while (true) {
			int l = getLFT(id);
			int r = getRFT(id);
			int largest = id;

			if (l <= n && PQ[l] > PQ[largest]) {
				largest = l;
			}
			if (r <= n && PQ[r] > PQ[largest]) {
				largest = r;
			}

			if (largest == id) break;

			std::swap(PQ[id], PQ[largest]);
			id = largest;
		}
	}
public:
	PriorityQueue() {
		PQ.push_back(114514);
	}

	PriorityQueue(std::initializer_list<int> list) {
		PQ.push_back(114514);
		for (auto &v : list) {
			PQ.push_back(v);
			up(PQ.size() - 1);
		}
	}

	int front() const {
		if (PQ.size() <= 1) {
			throw std::out_of_range("PriorityQueue is empty");
		}
		return PQ[1];
	}

	void push(int val) {
		PQ.push_back(val);
		up(PQ.size()-1);
	}

	void pop() {
		if (PQ.size() <= 1) {
			throw std::out_of_range("PriorityQueue is empty");
		}
		std::swap(PQ[1], PQ[PQ.size()-1]);
		PQ.pop_back();
		down(1);
	}

	bool empty() const {
		return PQ.size() == 1;
	}

	int size() const {
		return static_cast<int>(PQ.size()) - 1;
	}
};

#endif //MY_STL_PRIORITY_QUEUE_H