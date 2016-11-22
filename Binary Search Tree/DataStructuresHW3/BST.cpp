/**************************************************
*
*					BST.cpp 
*				    written by:
*					Noah Wagner
*
***************************************************/
#include "BST.h"
#include <algorithm>
#include <iostream>

Node * root;

BST::BST() {}

BST::BST(int key) {
	root = new Node;
	root->data = key;
}

Node * BST::Find(int key)
{
	return Find(key, root);
}

Node * BST::Find(int key, Node* node) 
{
	if (!node) { return node; }
	if (node->data == key) { return node; }
	return Find(key, (key < node->data) ? node->left : node->right);
}

bool BST::Insert(int key)
{
	return Insert(key, root);
}

bool BST::Insert(int key, Node* node) 
{
	if (!node) {
		root = new Node;
		root->data = key;
		return true;
	}

	if (node->data == key) { return false; } 
	else if (key > node->data) {
		if (!node->right) {
			node->right = new Node;
			node->right->data = key;
			node->right->parent = node;
			return true;
		} else {
			return Insert(key, node->right);
		}
	} else if (key < node->data) {
		if (!node->left) {
			node->left = new Node;
			node->left->data = key;
			node->left->parent = node;
			return true;
		} else {
			return Insert(key, node->left);
		}
	}
	return false;
}

bool BST::Delete(int key)
{
	Node* deleteNode = Find(key);
	if (!deleteNode) { return false; }

	if (!deleteNode->left) {
		if (!deleteNode->parent) {
			root = deleteNode->right;
		} else if (deleteNode->data > deleteNode->parent->data) {
			deleteNode->parent->right = deleteNode->right;
		} else {
			deleteNode->parent->left = deleteNode->right;
		}
		delete deleteNode;
		return true;
	} else {
		if (!deleteNode->right) {
			if (!deleteNode->parent) {
				root = deleteNode->left;
			} else if (deleteNode->data > deleteNode->parent->data) {
				deleteNode->parent->right = deleteNode->left;
			} else {
				deleteNode->parent->left = deleteNode->left;
			}
			delete deleteNode;
			return true;
		} else {
			Node* preNode = GetPredecessor(deleteNode);
			deleteNode->data = preNode->data;
			if (preNode != deleteNode->left) {
				preNode->parent->right = preNode->left;
			} else { 
				deleteNode->left = preNode->left; // Case where there is only one left node
			}
			delete preNode;
			return true;
		}
	}
	return false;
}

Node * BST::GetPredecessor(Node* node) {
	Node* ptr = node->left;
	while (ptr->right) {
		ptr = ptr->right;
	}
	return ptr;
}

void BST::PrintAll() 
{
	PrintAll(root);
}

void BST::PrintAll(Node* node)
{
	if (!node) { return; }
	PrintAll(node->right);
	std::cout << node->data << " ";
	PrintAll(node->left);
}

int BST::FindCost()
{
	return FindCost(root);
}

int BST::FindCost(Node* node) 
{
	if (!node) { return 0; }
	return node->data + std::max(FindCost(node->left), FindCost(node->right));
}

int BST::Depth(int key) 
{
	return Depth(Find(key));
}

int BST::Depth(Node* node)
{
	if (!node) { return -1; }
	int depth = 0;
	Node* ptr = node->parent;
	while (ptr) {
		ptr = ptr->parent;
		++depth;
	}
	return depth;
}

bool BST::IsBalanced() 
{
	return IsBalanced(root);
}

bool BST::IsBalanced(Node* node) 
{
	if (!node) { return true; }
	return (IsBalanced(node->left) && IsBalanced(node->right) && std::abs(Height(node->left) - Height(node->right)) < 2);
}

int BST::Height(Node* node) 
{
	if (!node) { return 0; }
	return 1 + std::max(Height(node->left), Height(node->right));
}


