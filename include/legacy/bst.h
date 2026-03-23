//
// Created by Chenluo Deng on 3/16/26.
//

#ifndef MY_STL_BST_H
#define MY_STL_BST_H
#include <iostream>
#include <ostream>

class BST {
private:
	struct TreeNode {
		int value{};
		TreeNode *left = nullptr;
		TreeNode *right = nullptr;
		TreeNode *parent = nullptr;
	};

	TreeNode *root;
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

	TreeNode* getNode(int value) {
		TreeNode* x = root;
		while (x!=nullptr) {
			if (x->value == value) {
				return x;
			}
			if (x->value < value) {
				x = x->right;
			} else {
				x = x->left;
			}
		}
		delete x;
		return nullptr;
	}

	TreeNode* findMin(TreeNode* node) {
		while (node && node->left != nullptr) {
			node = node->left;
		}
		return node;
	}

	TreeNode* removeNode(int value, TreeNode *t) {
		if (t==nullptr) {
			return nullptr;
		}

		if (value < t->value) {
			t->left = removeNode(value, t->left);
		} else if (value > t->value) {
			t->right = removeNode(value, t->right);
		} else {
			if (t->left == nullptr) {
				TreeNode* tmp = t->right;
				delete t;
				return tmp;
			}
			if (t->right == nullptr) {
				TreeNode* tmp = t->left;
				delete t;
				return tmp;
			}
			// Find the smallest element in the right sub-tree, so that it can correctly be placed at the position of t.
			// Then we delete that element succ in the right sub-tree.
			TreeNode* succ = findMin(t->right);
			t->value = succ->value;
			t->right = removeNode(succ->value, t->right);
		}
		return t;
	}

public:
	BST() {
		root = nullptr;
	}

	~BST() {
		btv(root, del);
	}

	void traverse() {
		mtv(root, prt);
	}

	void insert(int value) {
		auto *t = new TreeNode;
		t->value = value;
		t->right = nullptr;
		t->left = nullptr;
		TreeNode* x = root;
		TreeNode* y = nullptr;
		while (x!=nullptr) {
			y = x;
			if (t->value < x->value) {
				x = x->left;
			} else if (t->value > x->value) {
				x = x->right;
			} else {
				return;
			}
		}
		if (y==nullptr) {
			root = t;
		} else if (t->value < y->value) {
			y->left = t;
		} else {
			y->right = t;
		}
		t->parent = y;
	}

	bool search(int value) const {
		TreeNode* x = root;
		while (x!=nullptr) {
			if (x->value == value) {
				return true;
			}
			if (x->value < value) {
				x = x->right;
			} else {
				x = x->left;
			}
		}
		delete x;
		return false;
	}

	void remove(int value) {
		root = removeNode(value, root);
	}

	int getMax() const {
		TreeNode* x = root;
		if (x==nullptr) {
			throw std::out_of_range("No such node");
		}
		while (x->right!=nullptr) {
			x = x->right;
		}
		return x->value;
	}

	int getMin() const {
		TreeNode* x = root;
		if (x==nullptr) {
			throw std::out_of_range("No such node");
		}
		while (x->left!=nullptr) {
			x = x->left;
		}
		return x->value;
	}
};

#endif //MY_STL_BST_H