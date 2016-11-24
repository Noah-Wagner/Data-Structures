#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <string>

using namespace std;

struct HuffNode {
	int myFrequency;
	char myChar;
	HuffNode * left = nullptr;
	HuffNode * right = nullptr;
	HuffNode * parent = nullptr;
};
HuffNode * ConstructTree(string treeFile);
void Decode(string treeFile, string encodedMessageFile, string messageFile);
string ReadEncodedMessage(string);
string DecodeMessage(string, HuffNode*);
void WriteDecodedMessage(string, string);
char CorrectChar(char c);



int main(int argc, char * argv[])
{
	if (argc != 4) {
		cout << "Error: Requires 3 arguments!";
		return -1;
	}
	Decode(argv[1], argv[2], argv[3]);
    return 0;
}

void Decode(string treeFile, string encodedMessageFile, string messageFile) 
{
	HuffNode * root = ConstructTree(treeFile);
	string encodedMessage = ReadEncodedMessage(encodedMessageFile);
	string decodedMessage = DecodeMessage(encodedMessage, root);
	WriteDecodedMessage(decodedMessage, messageFile);
}

string ReadEncodedMessage(string encodedMessageFile)
{
	string encodedMessage;
	basic_ifstream<unsigned char> encodedMessageStream(encodedMessageFile, ios::in | ios::binary);
	string temp;
	unsigned char c;
	while (encodedMessageStream.get(c)) {
		int mask = 1 << 7;
		for (int i = 0; i < 8; i++) {
			encodedMessage += ((mask & c) != 0) ? '1' : '0';
			mask = mask >> 1;
		}
	}
	return encodedMessage;
}

string DecodeMessage(string encodedMessage, HuffNode * root)
{
	HuffNode * node = root;
	string decodedMessage;
	for (int i = 0; i < encodedMessage.length(); i++) {
		if (encodedMessage[i] == '0') {
			node = node->left;
		} else {
			node = node->right;
		}
		if (!node->left && !node->right) {
			decodedMessage += CorrectChar(node->myChar);
			node = root;
		}
	}
	return decodedMessage;
}

char CorrectChar(char c) {
	if (c == '-') {
		return ' ';
	} else if (c == '!') {
		return '\n';
	} else if (c == '+') {
		return char(-1);
	} else {
		return c;
	}
}

void WriteDecodedMessage(string decodedMessage, string messageFile)
{
	ofstream decodedMessageStream(messageFile);
	decodedMessageStream << decodedMessage;
	decodedMessageStream.close();
}

HuffNode * ConstructTree(string treeFile)
{
	ifstream treeStream(treeFile);
	string line;
	stack<HuffNode *> myStack;
	HuffNode * root = new HuffNode();
	if (treeStream.is_open()) {
		getline(treeStream, line);
		myStack.push(root);
		HuffNode * node = root;
		int index = 0;
		while (!myStack.empty()) {
			node = myStack.top();
			myStack.pop();
			node->myChar = line[index++];
			if (node->myChar != '/') {
				HuffNode * right = new HuffNode();
				node->right = right;
				right->parent = node;
				myStack.push(right);
				HuffNode * left = new HuffNode();
				node->left = left;
				left->parent = node;
				myStack.push(left);
			} else {
				if (node->parent->left == node) {
					node->parent->left = nullptr;
				} else {
					node->parent->right = nullptr;
				}
			}
		}
	}
	return root;
}
