/**************************************************
*
*					BST.h
*				    written by:
*					Noah Wagner
*
***************************************************/
#pragma once

struct Node {
	int data;
	Node* left = nullptr;
	Node* right = nullptr;
	Node* parent = nullptr;
};

class BST {
public:
	BST();
	BST(int);
	int Depth(int);
	int FindCost();
	Node* Find(int);
	bool Insert(int);
	bool Delete(int);
	int Depth(Node*);
	bool IsBalanced();
	int FindCost(Node*);
	static void PrintAll();
private:
	int Height(Node*);
	bool IsBalanced(Node*);
	Node* Find(int key, Node*);
	bool Insert(int key, Node*);
	static void PrintAll(Node*);
	Node* GetPredecessor(Node*);
};