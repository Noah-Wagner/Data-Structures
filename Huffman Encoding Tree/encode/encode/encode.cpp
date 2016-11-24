#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <map>

using namespace std;

void Encode(string, string, string);
string EncodeMessage(string, map<char, string>);
string ReadMessage(string);
map<char, string> GenerateCodeTable(string);
void WriteBinary(string, string);

int main(int argc, char * argv[])
{
	if (argc != 4) {
		cout << "Error: Requires 3 arguments!";
		return -1;
	}
	Encode(argv[1], argv[2], argv[3]);
    return 0;
}

void Encode(string codeFile, string messageFile, string encodedMessage)
{
	string message = ReadMessage(messageFile);
	map<char, string> myMap = GenerateCodeTable(codeFile);
	message = EncodeMessage(message, myMap);
	WriteBinary(message, encodedMessage);
}

void WriteBinary(string encodedMessage, string encodedMessageFile) 
{
	ofstream encodedMessageStream(encodedMessageFile, ios::out | ios::binary);
	unsigned char buffer = 0;
	int i = 0;
	int j = 0;

	for ( ; i < encodedMessage.length(); i++, j++) {
		buffer = buffer << 1;
		buffer |= (encodedMessage[i] == '1') ? 0x1 : 0x0;
		if (j == 7) {
			encodedMessageStream << buffer;
			buffer = 0;
			j = -1;
		}
	}
	if (j > 0) {
		while (j < 7) {
			buffer = buffer << 1;
			++j;
		}
		encodedMessageStream << buffer;
	}
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
			if (s1[0] == '-') {
				myMap[' '] = s2;
			} else if (s1[0] == '!') {
				myMap['\n'] = s2;
			} else if (s1[0] == '+') {
				myMap[char(-1)] = s2;
			} else {
				myMap[s1[0]] = s2;
			}
		}
	}
	return myMap;
}