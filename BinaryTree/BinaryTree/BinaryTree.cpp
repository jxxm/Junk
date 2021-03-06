// BinaryTree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <ctime>
#include <iostream>
#include <stack>
#include <queue>

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
	int value() {
		return _value;
	}
private:
	Node * _left;
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
			}
			else if (root->right() == NULL) {
				root->setRight(new Node(value++));
				stack.push(root->right());
				++depth;
			}
			else {
				stack.pop();
				--depth;
			}
		}
		else {
			stack.pop();
			--depth;
		}
	} while (depth > 0);
	return root;
}

const char NULLCHAR = '.';

void printPreOrder(Node* node, bool withNull = false) {
	if (node != NULL) {
		cout << node->value() << " ";
		printPreOrder(node->left(), withNull);
		printPreOrder(node->right(), withNull);
	} else if (withNull) {
		cout << NULLCHAR << " ";
	}
}

void printInOrder(Node* node, bool withNull = false) {
	if (node != NULL) {
		printInOrder(node->left(), withNull);
		cout << node->value() << " ";
		printInOrder(node->right(), withNull);
	} else if (withNull) {
		cout << NULLCHAR << " ";
	}
}

void printPostOrder(Node* node, bool withNull = false) {
	if (node != NULL) {
		printPostOrder(node->left(), withNull);
		printPostOrder(node->right(), withNull);
		cout << node->value() << " ";
	} else if (withNull) {
		cout << NULLCHAR << " ";
	}
}

bool isPowerOf2(const int x) {
	return (x & (x - 1)) == 0;
}

void printBreadthFirst(Node* node) {
	if (node == NULL) {
		return;
	}
	queue<Node*> queue;
	queue.push(node);
	Node* currentNode;
	int lines = 1;
	while (!queue.empty()) {
		currentNode = queue.front();
		cout << currentNode->value() << " ";
		++lines;
		if (isPowerOf2(lines)) {
			cout << "\n";
		}
		if (currentNode->left() != NULL) {
			queue.push(currentNode->left());
		}
		if (currentNode->right() != NULL) {
			queue.push(currentNode->right());
		}
		queue.pop();
	}
}

int main()
{
	srand(time(NULL));
	Node* root = createTree();

	cout << "\nPrinting pre-order (NLR)\n";
	printPreOrder(root, true);

	cout << "\nPrinting in-order (LNR)\n";
	printInOrder(root, true);

	cout << "\nPrinting post-order (LRN)\n";
	printPostOrder(root, true);

	cout << "\nPrinting breadth first\n";
	printBreadthFirst(root);

	// serialize
	// deserialize
	// and also need to free this tree
	// add this to spoink

	cin.get();
	return 0;
}

