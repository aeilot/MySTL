//
// Created by Chenluo Deng on 3/30/26.
//

#ifndef MY_STL_HUFFMAN_H
#define MY_STL_HUFFMAN_H
#include <queue>
#include <stack>
#include <vector>

namespace DS {
	class Huffman {
	public:
		struct TreeNode {
			int weight;
			TreeNode* left;
			TreeNode* right;
		};
		using Tree = TreeNode*;

		struct Compare {
			bool operator()(TreeNode* a, TreeNode* b) const {
				return a->weight > b->weight;
			}
		};


		~Huffman() {
			destroy(root);
		}

		void destroy(Tree node) {
			if (!node) return;
			destroy(node->left);
			destroy(node->right);
			delete node;
		}

		Tree root;

		Huffman(int arr[], int N) {
			std::priority_queue<Tree, std::vector<Tree>, Compare> forest;
			for (int i = 0; i<N; i++) {
				TreeNode* tmp = new TreeNode;
				tmp->weight = arr[i];
				tmp->left = nullptr;
				tmp->right = nullptr;
				forest.push(tmp);
			}

			while (forest.size()>1) {
				Tree a = forest.top();
				forest.pop();
				Tree b = forest.top();
				forest.pop();
				Tree n = new TreeNode;
				n->weight = a->weight + b->weight;
				n->left = a;
				n->right = b;
				forest.push(n);
			}

			if (forest.empty()) {
				throw std::exception();
			}

			this->root = forest.top();
			forest.pop();
		}

		int getWPL() {
			return getWPL_private(root, 0);
		}

	private:
		int getWPL_private(TreeNode* cur, int d) {
			if (cur->left == nullptr && cur->right==nullptr) {
				return d*cur->weight;
			}
			int ans = 0;
			if (cur->left != nullptr) {
				ans += getWPL_private(cur->left, d+1);
			}
			if (cur->right != nullptr) {
				ans += getWPL_private(cur->right, d+1);
			}
			return ans;
		}


	};
}

#endif //MY_STL_HUFFMAN_H