#ifndef RECORD_H_INCLUDED
#define RECORD_H_INCLUDED

#include <string>
#include <iostream>
using namespace std;

class Record
{
public:
	//constructor
	Record(string theNumber, string theLast, string theFirst, int theAge, int theClass);
	
	//getters
	string getNumber() const;
	string getLast() const;
	string getFirst() const;
	int getAge() const;
	int getClass() const;
	
	void print() const;

private:
	string number;
	string lastName;
	string firstName;
	int age;
	int classNum;

};


#endif 