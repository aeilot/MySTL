//
// Created by Chenluo Deng on 3/23/26.
//

#ifndef MY_STL_SPLAY_H
#define MY_STL_SPLAY_H
#include <iostream>
#include <stdexcept>

namespace DS {
	class SplayTree {
	private:
		struct TreeNode {
			TreeNode* parent;
			TreeNode* left;
			TreeNode* right;
			int subsize;
			int value;
		};

		void mtv(TreeNode *rt, void (*fn)(TreeNode*)) {
			if (rt==nullptr) {
				return;
			}
			if (rt->left != nullptr) mtv(rt->left, fn);
			fn(rt);
			if (rt->right != nullptr) mtv(rt->right, fn);
		}
		void btv(TreeNode *rt, void (*fn)(TreeNode*)) {
			if (rt==nullptr) {
				return;
			}
			if (rt->left != nullptr) btv(rt->left, fn);
			if (rt->right != nullptr) btv(rt->right, fn);
			fn(rt);
		}
		void ftv(TreeNode *rt, void (*fn)(TreeNode*)) {
			if (rt==nullptr) {
				return;
			}
			fn(rt);
			if (rt->left != nullptr) ftv(rt->left, fn);
			if (rt->right != nullptr) ftv(rt->right, fn);
		}
		static void prt(TreeNode *t) {
			std::cout << t->value << std::endl;
		}
		static void del(TreeNode *t) {
			delete t;
		}


		bool isLeftChild(TreeNode* node) {
			if (node->parent == nullptr) throw std::out_of_range("");
			return node->parent->left == node;
		}

		void pushup(TreeNode* node) {
			if (node == nullptr) return;
			node->subsize = 1 + (node->left==nullptr ? 0 : node->left->subsize) + (node->right==nullptr ? 0 : node->right->subsize);
		}

		void rotate(TreeNode* node) {
			TreeNode* parent = node->parent;
			if (parent == nullptr) return;
			TreeNode* grandparent = parent->parent;
			bool l = isLeftChild(node);
			if (l) {
				parent->left = node->right;
				node->right = parent;
				if (parent->left) {
					parent->left->parent = parent;
				}
			} else {
				parent->right = node->left;
				node->left = parent;
				if (parent->right) {
					parent->right->parent = parent;
				}
			}
			if (grandparent) {
				bool d = isLeftChild(parent);
				if (d) {
					grandparent->left = node;
				} else {
					grandparent->right = node;
				}
			} else {
				root = node;
			}
			parent->parent = node;
			node->parent = grandparent;
			pushup(parent);
			pushup(node);
		}

		// Three cases in splay operation (to exploit spatial locality).
		// Each time, we don't just move node x to the root,
		// we also restructure the path so that x and its ancestors
		// become more shallow in future accesses.
		//
		// Case 1: Zig
		// - x is child of root (no grandparent).
		// - Perform a single rotation (left or right).
		// - This is the final step.
		//
		// Case 2: Zig-Zig
		// - x and its parent p are both left children or both right children.
		// - First rotate p with grandparent g,
		//   then rotate x with p.
		// - This moves x up two levels and keeps structure balanced.
		//
		// Case 3: Zig-Zag
		// - x is a left child and p is a right child, or vice versa.
		// - First rotate x with parent p,
		//   then rotate x with grandparent g.
		// - This also moves x up two levels but restructures differently.
		//
		// Overall effect:
		// - Frequently accessed nodes move closer to root.
		// - Path compression improves future access time.
		void splay(TreeNode* node) {
			if (node == nullptr) return;
			while (node->parent != nullptr) {
				TreeNode* parent = node->parent;
				TreeNode* grandparent = parent->parent;

				if (grandparent == nullptr) {
					rotate(node);                  // Zig
				} else if (isLeftChild(node) == isLeftChild(parent)) {
					rotate(parent);                // Zig-Zig
					rotate(node);
				} else {
					rotate(node);                  // Zig-Zag
					rotate(node);
				}
			}
		}

		TreeNode *root;
	public:
		TreeNode* getNode(int value) {
			TreeNode* x = root;
			TreeNode* last = nullptr;
			while (x!=nullptr) {
				last = x;
				if (x->value == value) {
					splay(x);
					return x;
				}
				if (x->value < value) {
					x = x->right;
				} else {
					x = x->left;
				}
			}
			// Even if it's not found, we still splay the last node to the root.
			if (last != nullptr) {
				splay(last);
			}
			return nullptr;
		}

		// Each time we access a node, we have it splayed to the root.
		bool search(int value) {
			return getNode(value) != nullptr;
		}

		int getMax() {
			TreeNode* x = root;
			if (x==nullptr) {
				throw std::out_of_range("No such node");
			}
			while (x->right!=nullptr) {
				x = x->right;
			}
			splay(x);
			return x->value;
		}

		int getMin() {
			TreeNode* x = root;
			if (x==nullptr) {
				throw std::out_of_range("No such node");
			}
			while (x->left!=nullptr) {
				x = x->left;
			}
			splay(x);
			return x->value;
		}

		// For deletion, we first check if the node exists.
		// Then, if it exists, we check if it has a left subtree.
		// 1) No left subtree ==> We simply remove the node, and let the right child become the root.
		// 2) With both left & right ===> We isolate the left subtree, and get the maximal element in the left subtree splayed to the root.
		//	  Since it's the largest, it does not have a right child. We simply make the original right subtree as its right descendants.
		// This preserved the spatial locality.
		void remove(int value) {
			TreeNode* node = getNode(value);
			if (node == nullptr) return;

			TreeNode* L = node->left;
			TreeNode* R = node->right;

			if (L == nullptr) {
				root = R;
				if (root) root->parent = nullptr;
				delete node;
				return;
			}

			if (L) L->parent = nullptr;
			if (R) R->parent = nullptr;

			node->left = nullptr;
			node->right = nullptr;

			root = L;

			TreeNode* x = L;
			while (x->right!=nullptr) {
				x = x->right;
			}

			splay(x);

			// Splay keeps the order, so x is still the largest node in the tree.
			// This means x does not have a right node
			root->right = R;
			if (R) R->parent = root;
			pushup(root);
			delete node;
		}

		// Insertion is simple
		void insert(int value) {
			TreeNode* x = root;
			TreeNode* y = nullptr;
			while (x!=nullptr) {
				y = x;
				if (value < x->value) {
					x = x->left;
				} else if (value > x->value) {
					x = x->right;
				} else {
					// If it exists, we simply splay it to the root.
					splay(x);
					return;
				}
			}
			auto *t = new TreeNode;
			t->value = value;
			t->right = nullptr;
			t->subsize = 1;
			t->left = nullptr;

			if (y==nullptr) {
				root = t;
			} else if (t->value < y->value) {
				y->left = t;
			} else {
				y->right = t;
			}
			t->parent = y;
			splay(t);
		}

		// Get kth smallest
		int getKth(int k) {
			TreeNode* x = root;
			if (x == nullptr || k <= 0 || k > x->subsize) {
				throw std::out_of_range("k is out of range");
			}

			while (x != nullptr) {
				int leftSize = (x->left != nullptr) ? x->left->subsize : 0;

				if (k <= leftSize) {
					x = x->left;
				} else if (k == leftSize + 1) {
					splay(x);
					return x->value;
				} else {
					// When entering the right, we must update k.
					k -= (leftSize + 1);
					x = x->right;
				}
			}
			throw std::logic_error("Should not reach here");
		}

		// Get the ranking of value
		int getRank(int value) {
			TreeNode* x = root;
			TreeNode* last = nullptr;
			int rank = 0;

			while (x != nullptr) {
				last = x;
				int leftSize = (x->left != nullptr) ? x->left->subsize : 0;

				if (value < x->value) {
					x = x->left;
				} else if (value > x->value) {
					rank += leftSize + 1;
					x = x->right;
				} else {
					rank += leftSize;
					splay(x);
					return rank + 1;
				}
			}

			if (last != nullptr) {
				splay(last);
			}
			return rank + 1;
		}

		SplayTree() {
			root = nullptr;
		}

		SplayTree(const SplayTree&) = delete;
		SplayTree& operator=(const SplayTree&) = delete;

		~SplayTree() {
			btv(root, del);
		}
	};
}

#endif //MY_STL_SPLAY_H