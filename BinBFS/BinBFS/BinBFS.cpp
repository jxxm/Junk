// BinBFS.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <ctime>
#include <iostream>
#include <stack>

using namespace std;

class Node {
public:
	Node(int value) : _value(value) {
		cout << " created " << _value << '\n';
		_left = NULL;
		_right = NULL;
	};
	~Node() {
		cout << " destroyed " << _value << '\n';
	};
	void setLeft(Node* node) {
		_left = node;
	}
	void setRight(Node* node) {
		_right = node;
	}
	Node* left() {
		return _left;
	}
	Node* right() {
		return _right;
	}
private:
	Node* _left;
	Node* _right;
	int _value;
};

Node* createTree() {
	int depth = 1;
	int value = 1;
	stack<Node*> stack;
	stack.push(new Node(value++));
	Node* root;
	do {
		root = stack.top();
		if (depth < 4) {
			if (root->left() == NULL) {
				root->setLeft(new Node(value++));
				stack.push(root->left());
				++depth;
			} else if (root->right() == NULL) {
				root->setRight(new Node(value++));
				stack.push(root->right());
				++depth;
			}
			else {
				stack.pop();
				--depth;
			}
		} else {
			stack.pop();
			--depth;
		}
	} while (depth > 0);
	return root;
}

int main()
{
	srand(time(NULL));
	createTree(); // and also need to free this tree
	cin.get();
	return 0;
}

