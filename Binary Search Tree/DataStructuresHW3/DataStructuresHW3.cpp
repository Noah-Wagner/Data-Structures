// DataStructuresHW3.cpp : Defines the entry point for the console application.
//

#include "BST.h"
#include <iostream>

int main()
{
	BST tree;
	while (true) {

		std::cout << "\n\n";
		std::cout << "Binary Search Tree Operations:\n";
		std::cout << "1. Search for node\n";
		std::cout << "2. Insert node\n";
		std::cout << "3. Delete node\n";
		std::cout << "4. Print tree\n";
		std::cout << "5. Find depth of node\n";
		std::cout << "6. Get most expensive path cost\n";
		std::cout << "7. Check if the BST is balanced\n\n";
		std::cout << "Enter selected operation: ";

		char option;
		std::cin >> option;

		switch (option) {

		case '1':
			int searchKey;
			std::cout << "\nNode key: ";
			std::cin >> searchKey;
			std::cout << (tree.Find(searchKey) ? "Node found" : "Node not found");
			break;

		case '2':
			int insertKey;
			std::cout << "\nNode to insert: ";
			std::cin >> insertKey;
			std::cout << (tree.Insert(insertKey) ? "Node inserted" : "Node insertion failed");
			break;

		case '3': 
			int deleteKey;
			std::cout << "\nNode to delete: ";
			std::cin >> deleteKey;
			std::cout << (tree.Delete(deleteKey) ? "Node deleted" : "Node deletion failed");
			break;

		case '4': 
			std::cout << "\nPrinting tree:\n";
			tree.PrintAll();
			break;

		case '5':
			int depthKey;
			std::cout << "\nNode to find depth of: ";
			std::cin >> depthKey;
			std::cout << "\nNode depth: " << tree.Depth(depthKey);
			break;

		case '6': 
			std::cout << "\nMost expensive path cost: " << tree.FindCost();
			break;

		case '7':
			std::cout << (tree.IsBalanced() ? "The tree is balanced" : "The tree is not balanced");
			break;

		}
	}
	return 0;
}

