// decode.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "decode.h"
#include <fstream>
#include <stack>
#include <string>

using namespace std;

struct HuffNode {
	int myFrequency;
	char myChar;
	HuffNode * left = nullptr;
	HuffNode * right = nullptr;

};
HuffNode * ConstructTree(string treeFile);
string Decode(string treeFile, string encodedMessageFile, string messageFile);


int main(int argc, char * argv[])
{
	//<treefile> <encodedmessagefile> <messagefile>

	Decode(argv[1], argv[2], argv[3]);

    return 0;
}

string Decode(string treeFile, string encodedMessageFile, string messageFile) {

	HuffNode * root = ConstructTree(treeFile);
	return "";
}

HuffNode * ConstructTree(string treeFile)
{
	ifstream treeStream(treeFile);
	string line;
	stack<HuffNode*> myStack;
	HuffNode * root;
	if (treeStream.is_open()) {
		getline(treeStream, line);


		root = new HuffNode();
		root->myChar = line[0];
		myStack.push(root);
		HuffNode* node = root;
		for (int i = 1; i < line.length(); i++) {
			node->left = new HuffNode();
			node = node->left;
			node->myChar = line[i];
			
		}
	}
	
	return root;
}
