#ifndef KEYTYPE_H_INCLUDED
#define KEYTYPE_H_INCLUDED

#include<string>
using namespace std;

/*
	Generate different type of key
	For example, KeyType("Mike") generates a string key "Mike"
	             KeyType(1234) generates a int key 1234
*/
class KeyType
{
public:
	KeyType(){ key1 = ""; key2 = 0; }
	KeyType(string theKey1){ key1 = theKey1; }
	KeyType(int theKey2) { key2 = theKey2; }
	void setKey1(string theKey1){ key1 = theKey1; }
	string getKey1() const { return key1; }
	void setKey2(int theKey2){ key2 = theKey2; }
	int getKey2() const { return key2; }
private:
	string key1;
	int key2;
};

#endif