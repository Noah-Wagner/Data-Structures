
#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <fstream>
#include <sstream>

struct HuffNode {
	int myFrequency;
	char myChar;
	HuffNode * left = nullptr;
	HuffNode * right = nullptr;
};

using namespace std;

auto comp = [](HuffNode* a, HuffNode* b) { return a->myFrequency > b->myFrequency; };
priority_queue<HuffNode*, vector<HuffNode*>, decltype(comp)> pQueue(comp);

map<char, string> tempMap;

void GenerateHuffmanTree(string freqFile, string treeFile, string dataFile);
string SerializeTree(HuffNode * root);
string SerializeCodeTable(HuffNode * root);
void GenerateData(HuffNode * root, string str);

int main(int argc, char * argv[])
{
	if (argc != 4) {
		std::cout << "Error: 3 arguments required!";
		return -1;
	}
	GenerateHuffmanTree(argv[1], argv[2], argv[3]);
    return 0;
}

void GenerateHuffmanTree(string freqFile, string treeFile, string dataFile)
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

string SerializeTree(HuffNode * root)
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

string SerializeCodeTable(HuffNode* root)
{
	GenerateData(root, "");
	string codeTable;
	for (int i = 0; i < 26; i++) {
		codeTable += static_cast<char>('a' + i);
		codeTable += ' ';
		codeTable += tempMap['a' + i];
		codeTable += '\n';
	}
	for (char c : {'-', '.', '!', '+'}) {
		codeTable += c;
		codeTable += ' ';
		codeTable += tempMap[c];
		codeTable += '\n';
	}
	return codeTable;
}

void GenerateData(HuffNode * root, string str)
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
