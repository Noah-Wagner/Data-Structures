// encode.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <sstream>
#include <fstream>
#include <map>


using namespace std;

string Encode(string, string, string);
string EncodeMessage(string, map<char, string>);
string ReadMessage(string);
map<char, string> GenerateCodeTable(string);
void WriteBinary(string, string);

int main(int argc, char * argv[])
{
	// code, message, encode
	Encode(argv[2], argv[1], argv[3]);


    return 0;
}

string Encode(string messageFile, string codeFile, string encodedMessage) 
{
	string message = ReadMessage(messageFile);
	map<char, string> myMap = GenerateCodeTable(codeFile);

	message = EncodeMessage(message, myMap);

	WriteBinary(message, encodedMessage);

	return "test";
}

void WriteBinary(string encodedMessage, string encodedMessageFile) 
{
	ofstream encodedMessageStream(encodedMessage, ios::out | ios::binary);
	//encodedMessageStream.write()

	/*ofstream numFile;*/
	unsigned char buffer = 0;
	int i = 0;
	int j = 0;

	for ( ; i < encodedMessage.length(); i++, j++) {
		buffer = buffer << 1;
		buffer = buffer |= (encodedMessage[i] == '1') ? 0x1 : 0x0;
		if (j == 7) {
			encodedMessageStream.write((char*)&buffer, 1);
			buffer = 0;
			j = -1;
		}
	}
	while (j < 7) {
		buffer = buffer << 1;
	}
	encodedMessageStream.write((char*)&buffer, 1);

	encodedMessageStream.close();

}


string EncodeMessage(string message, map<char, string> codeTable) 
{
	string encodedMessage;

	for (int i = 0; i < message.length(); i++) {
		encodedMessage += codeTable[message[i]];
	}

	return encodedMessage;
}

string ReadMessage(string messageFileName) 
{
	ifstream messageStream(messageFileName);
	string messageHelper;
	string message;
	if (messageStream.is_open()) {
		while (getline(messageStream, messageHelper)) {
			message += messageHelper;
			message.push_back('\n');
		}
		messageStream.close();
	}
	return message;
}


map<char, string> GenerateCodeTable(string codeFile) 
{
	map<char, string> myMap;

	ifstream codeStream(codeFile);
	string code;
	if (codeStream.is_open()) {
		while (getline(codeStream, code)) {
			stringstream str;
			str.str(code);
			string s1;
			string s2;
			getline(str, s1, ' ');
			getline(str, s2, ' ');
			myMap[s1[0]] = s2;
		}
	}
	return myMap;
}