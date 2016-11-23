#include "HuffmanTree.h"
#include <iostream>

int main(int argc, char * argv[])
{
	/*if (argc != 4) {
		std::cout << "Error: 3 arguments required!";
		return -1;
	}*/
	//HuffmanTree tree(argv[1], argv[2], argv[3]);
	HuffmanTree tree("D:\\basic_freq.txt", "D:\\treefile.txt", "D:\\codefile.txt");
    return 0;
}

