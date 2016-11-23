#include <iostream>
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
void Decode(string treeFile, string encodedMessageFile, string messageFile);
string ReadEncodedMessage(string);
string DecodeMessage(string, HuffNode*);
void WriteDecodedMessage(string, string);



int main(int argc, char * argv[])
{
	
	Decode(argv[1], argv[2], argv[3]);

    return 0;
}

void Decode(string treeFile, string encodedMessageFile, string messageFile) 
{
	HuffNode * root = ConstructTree(treeFile);
	string encodedMessage = ReadEncodedMessage(encodedMessageFile);
	string decodedMessage = DecodeMessage(encodedMessage, root);
	WriteDecodedMessage(messageFile, decodedMessage);
}

string ReadEncodedMessage(string encodedMessageFile)
{
	string encodedMessage;
	ifstream encodedMessageStream(encodedMessageFile, ios::in | ios::binary);
	while (!encodedMessageStream.eof()) {
		encodedMessage.append(1, encodedMessageStream.get());
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
			decodedMessage += node->myChar;
			node = root;
		}
	}
	return decodedMessage;
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
	stack<HuffNode*> myStack;
	HuffNode * root = nullptr;
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
