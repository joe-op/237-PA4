#include "Record.h"

/*
* CS237 PA4
* Joe Opseth & Jens Myklebust
* 8 May 2016
*/

Record::Record(string theNumber, string theLast,
	string theFirst, int theAge, int theClass)
{
	number = theNumber;
	lastName = theLast;
	firstName = theFirst;
	age = theAge;
	classNum = theClass;
	is_deleted = false;
}

string Record::getNumber() const
{
	return number;
}

string Record::getLast() const
{
	return lastName;
}

string Record::getFirst() const
{
	return firstName;
}

int Record::getAge() const
{
	return age;
}

int Record::getClass() const
{
	return classNum;
}

void Record::print() const
{
	cout << number << " " << lastName << " " 
		<< firstName << " " << age << " " << classNum << endl;
}

void Record::set_deleted(bool deleted) {
	is_deleted = deleted;
}

bool Record::get_deleted() {
	return is_deleted;
}