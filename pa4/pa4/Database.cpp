#include "Database.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iterator>
using namespace std;

Database::Database(string filename)
{

	ifstream infile;

	infile.open(filename.c_str());
	if (infile.fail()) {
		cerr << "Invalid database file.";
		exit(1);
	}
	else {
		string line;
		while (!infile.eof()) {
			getline(infile, line);
			cout << line << endl;
			Record r = parse_records(line);
			records.push_back(r);
		}
		infile.close();
		for (vector<Record>::iterator i = records.begin(); i != records.end(); i++) {
			Insert(&(*i), 'S');
			Insert(&(*i), 'A');
		}
	}	
}

void Database::Insert(Record* record, char indexType)
{
	// According to indexType, insert record into different indexes
	if(indexType == 'S') {
		indexS.insert(record->getNumber(), record);
	} else if(indexType == 'A') {
		indexA.insert(record->getAge(), record);
	}
	else {
		cerr << "Invalid index type.";
	}
}


void Database::Find(KeyType k, char indexType) const
{
	if (indexType == 'A') {
		TreeNode<int> *ages = indexA.find(k.getKey2());
		if(ages == NULL || ages->get_records()->empty()) {
			cout << "FIND ** NO RECORDS FOUND FOR KEY " << k.getKey2() << endl;
		}
		else {
			for (list<Record*>::iterator i = ages->get_records()->begin();
			i != ages->get_records()->end(); i++)
			{
				(*i)->print();
			}
		}
	}
	else if (indexType == 'S') {
		TreeNode<string> *number = indexS.find(k.getKey1());
		if (number == NULL || number->get_records()->empty()) {
			cout << "FIND ** NO RECORDS FOUND FOR KEY " << k.getKey1() << endl;
		}
		else {
			number->get_records()->front()->print();
		}
	}
	else {
		cout << "FIND ** WRONG INDEX TYPE" << endl;
	}

}


bool Database::DeletePrimary(KeyType k)
{
	bool removed;
	string key_str;

	if (k.getKey1() == "") {
		removed = indexA.removePrimary(k.getKey2());
		key_str = to_string(k.getKey2());
	}
	else {
		removed = indexS.removePrimary(k.getKey1());
		key_str = k.getKey1();
	}
	
	if (removed) {
		cout << "DELETE RECORD " << key_str << " FROM PRIMARY INDEX SUCCESSFULLY!" << endl;
	}
	else {
		cout << "DELETE ** FAIL TO DELETE RECORD "
			<< key_str << "FROM PRIMARY INDEX" << endl;
	}
	
	return removed;
}

bool Database::DeleteSecondary(KeyType primekey, KeyType k, char indexType)
{

	if (indexType == 'A') {
		bool removed = indexA.removeSecondary(k.getKey2(), primekey.getKey1());
		if (removed) {
			cout << "DELETE RECORD " << k.getKey2() << " FROM SECONDARY INDEX SUCESSFULLY!" << endl;
		}
		else {
			cout << "DELETE ** FAIL TO DELETE RECORD " << k.getKey2() << " FROM SECONDARY INDEX" << endl;
		}
		return removed;
	}

	cout << "DELETE ** FAIL TO DELETE RECORD " << k.getKey1() << " FROM SECONDARY INDEX" << endl;
	return false;

}


Record Database::parse_records(string line)
{
	// Find the index of the first blank (the end of first string).
	int first_end = line.find(' ');
	if (first_end == string::npos) {
		cout << "Error: missing blank" << endl;
	}
	string stuNumber = line.substr(0, first_end);

	// Find the index of the second blank (the end of second string).
	int second_end = line.find(' ', first_end + 1);
	if (second_end == string::npos) {
		cout << "Error: missing blank" << endl;
		// and return from the function
	}
	int second_start = first_end + 1;
	string lastname = line.substr(second_start, second_end - second_start);

	// Skip the blanks in order to find the begining of the third string
	int third_start;
	for (third_start = second_end; third_start < line.length(); third_start++)
	{
		if (line.at(third_start) != ' ') break;
	}

	// Find the end of third string
	int third_end = line.find(' ', third_start);
	if (third_end == string::npos) {
		cout << "Error: missing blank" << endl;
		// and return from the function
	}
	string firstname = line.substr(third_start, third_end - third_start);

	// Skip the blanks in order to find the begining of the fourth string
	int fourth_start;
	for (fourth_start = third_end; fourth_start < line.length(); fourth_start++)
	{
		if (line.at(fourth_start) != ' ') break;
	}
	// Find the end of fourth string
	int fourth_end = line.find(' ', fourth_start);
	if (fourth_end == string::npos) {
		cout << "Error: missing blank" << endl;
		// and return from the function
	}
	string age_str = line.substr(fourth_start, fourth_end - fourth_start);
	istringstream age_stream(age_str);
	int age;
	age_stream >> age;

	// Get the fifth string
	string class_str = line.substr(fourth_end + 1);
	istringstream class_stream(class_str);
	int classnumber;
	class_stream >> classnumber;

	Record new_student(stuNumber, lastname, firstname, age, classnumber);
	return new_student;
}
