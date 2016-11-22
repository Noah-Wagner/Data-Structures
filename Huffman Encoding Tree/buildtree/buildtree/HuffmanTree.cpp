#include "HuffmanTree.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <map>
#include <queue>

using namespace std;

auto comp = [](HuffNode* a, HuffNode* b) { return a->myFrequency > b->myFrequency; };
priority_queue<HuffNode*, vector<HuffNode*>, decltype(comp)> pQueue(comp);

map<char, string> tempMap;

HuffmanTree::HuffmanTree(string freqFile, string treeFile, string dataFile)
{
	string line;
	ifstream stream(freqFile);
	if (stream.is_open()) {
		while (getline(stream, line)) {
			stringstream ss;
			ss.str(line);
			string item;
			getline(ss, item, ' ');
			HuffNode * node = new HuffNode();
			node->myChar = item[0];
			getline(ss, item, ' ');
			node->myFrequency = stoi(item);
			pQueue.push(node);
		}
		stream.close();

		while (pQueue.size() >= 2) {
			HuffNode * node = new HuffNode();
			node->left = pQueue.top();
			pQueue.pop();
			node->right = pQueue.top();
			pQueue.pop();
			node->myFrequency = node->left->myFrequency + node->right->myFrequency;
			node->myChar = '$';
			pQueue.push(node);
		}
		
		HuffNode * root = pQueue.top();
		ofstream treeStream(treeFile);
		treeStream << SerializeTree(root);
		treeStream.close();

		ofstream codeStream(dataFile);
		codeStream << SerializeCodeTable(root);
		codeStream.close();
	}
}

string HuffmanTree::SerializeTree(HuffNode* root) 
{
	stack<HuffNode *> myStack;
	string treeString;
	myStack.push(root);
	while (!myStack.empty()) {
		HuffNode * node = myStack.top();
		treeString += (node == nullptr) ? '/' : node->myChar;
		myStack.pop();
		if (node != nullptr) {
			myStack.push(node->right);
			myStack.push(node->left);
		}
	}
	return treeString;
}

string HuffmanTree::SerializeCodeTable(HuffNode* root) 
{
	GenerateData(root, "");
	string codeTable;
	for (int i = 0; i < 26; i++) {
		codeTable += static_cast<char>('a' + i);
		codeTable += ' ';
		codeTable += tempMap['a' + i];
		codeTable += '\n';
	}
	for (char c : {' ', '.', '\n', char(-1)}) {
		codeTable += c;
		codeTable += ' ';
		codeTable += tempMap[c];
	}
	return codeTable;
}

void HuffmanTree::GenerateData(HuffNode * root, string str)
{
	if (!root) {
		return;
	}
	if (root->myChar != '$') {
		tempMap[root->myChar] = str;
	}
	GenerateData(root->left, str + '0');
	GenerateData(root->right, str + '1');
}

