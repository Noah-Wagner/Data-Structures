#pragma once
#include <string>

struct HuffNode {
	int myFrequency;
	char myChar;
	HuffNode * left = nullptr;
	HuffNode * right = nullptr;

};

class HuffmanTree {
public:
	HuffmanTree(std::string fName, std::string, std::string);
	std::string SerializeTree(HuffNode* root);
	std::string SerializeCodeTable(HuffNode*);
	void GenerateData(HuffNode* root, std::string);
private:
};
