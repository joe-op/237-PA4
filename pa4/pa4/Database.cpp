#include "Database.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iterator>
using namespace std;

/*
* CS237 PA4
* Joe Opseth & Jens Myklebust
* 8 May 2016
*/

/*
 * Default constructor for Database
 * Input: string
 * Output: Database object
 * Loads a database from filename.
 * Creates and fills indices for Number and Age.
 */
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
			// require minimum length so exception is not thrown
			if (line.length() >= 9) {
				Record r = parse_records(line);
				records.push_back(r);
			}
		}
		infile.close();
		for (vector<Record>::iterator i = records.begin(); i != records.end(); i++) {
			Insert(&(*i), 'S');
			Insert(&(*i), 'A');
		}
	}	
}

/*
 * Insert: inserts a record pointer into an index
 * Input: Record*, char
 * Output: none
 * Inserts a pointer to record into the index
 * corresponding to 'S' or 'A'.
 * Gives an error if indexType is not 'S' or 'A'.
 */
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

/*
 * Find: finds records associated with k
 * Input: KeyType, char
 * Output: none
 * If k is found in the corresponding index,
 * prints all records associated with k.
 */
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

/*
 * FindRange: Finds records within a certain range.
 * Input: KeyType low, KeyType high, char indexType
 * Output: bool
 * Searches for records in a certain range.
 * If records are found, displays records and returns true;
 * displays notice and returns false otherwise.
 */
bool Database::FindRange(KeyType low, KeyType high, char indexType) {
	bool found = false;
	if (indexType == 'A') {
		for (int i = low.getKey2(); i <= high.getKey2(); i++) {
			TreeNode<int> *node = indexA.find(i);
			if (node != NULL) {
				found = true;
				for (list<Record*>::iterator i = node->get_records()->begin();
				i != node->get_records()->end(); i++) {
					(*i)->print();
				}
			}
		}
		if (!found) {
			cout << "FINDRANGE ** NO RECORDS FOUND BETWEEN " << low.getKey2()
				<< " AND " << high.getKey2() << endl;
		}
	}
	else if (indexType == 'S') {
		int low_int, high_int;
		stringstream(low.getKey1()) >> low_int;
		stringstream(high.getKey1()) >> high_int;
		for (int i = low_int; i <= high_int; i++) {
			TreeNode<string> *node = indexS.find(to_string(i));
			if (node != NULL) {
				found = true;
				node->get_records()->front()->print();
			}
		}
		if (!found) {
			cout << "FINDRANGE ** NO RECORDS FOUND BETWEEN " << low.getKey1()
				<< " AND " << high.getKey1() << endl;
		}
	}
	else {
		cout << "FINDRANGE ** INVALID INDEX TYPE" << endl;
	}
	return found;
}

/*
 * DeletePrimary: deletes the primary key from the index
 * Input: KeyType
 * Output: bool
 * Returns true if record is found, false otherwise.
 * Does not delete record from the database.
 */
bool Database::DeletePrimary(KeyType k)
{
	bool removed;
	string key_str;

	removed = indexS.removePrimary(k.getKey1());
	key_str = k.getKey1();
	
	if (removed) {
		cout << "DELETE RECORD " << key_str << " FROM PRIMARY INDEX SUCCESSFULLY!" << endl;
	}
	else {
		cout << "DELETE ** FAIL TO DELETE RECORD "
			<< key_str << " FROM PRIMARY INDEX" << endl;
	}
	
	return removed;
}

/*
 * DeleteSecondary: Deletes record with number primekey and age k from index 'A'
 * Input: KeyType, KeyType, char
 * Output: bool
 * Returns true if input is valid and record is found, false otherwise.
 * Can only be used for indexA since age is the only secondary index.
 */
bool Database::DeleteSecondary(KeyType primekey, KeyType k, char indexType)
{

	if (indexType == 'A') {
		bool removed = indexA.removeSecondary(k.getKey2(), primekey.getKey1());
		if (removed) {
			cout << "DELETE RECORD " << primekey.getKey1() << " FROM SECONDARY INDEX SUCESSFULLY!" << endl;
		}
		else {
			cout << "DELETE ** FAIL TO DELETE RECORD " << primekey.getKey1() << " FROM SECONDARY INDEX" << endl;
		}
		return removed;
	}

	cout << "DELETE ** SECONDARY KEY WITH WRONG INDEX TYPE" << endl;
	return false;

}

/*
 * Delete: delete a record from the database
 * Input: KeyType
 * Output: bool
 * Finds the record associated with primekey,
 * deletes it from the indices,
 * and marks the record as deleted.
 * Returns true if record is found and not already deleted,
 * false otherwise.
 */
bool Database::Delete(KeyType primekey) {
	int age = 0;
	bool found = false;
	for (vector<Record>::iterator i = records.begin(); i != records.end(); i++) {
		if (i->getNumber() == primekey.getKey1()) {
			if (!i->get_deleted()) {
				found = true;
				age = i->getAge();
				i->set_deleted(true);
			}
			break;
		}
	}
	if (found) {
		indexA.removeSecondary(age, primekey.getKey1());
		indexS.removePrimary(primekey.getKey1());
		cout << "DELETE RECORD " << primekey.getKey1() << " FROM DATABASE SUCCESSFUL" << endl;
	}
	else {
		cout << "DELETE ** FAIL TO DELETE RECORD " << primekey.getKey1() << " FROM DATABASE" << endl;
	}
	return found;	
}

/*
 * parse_records: parses a line for inclusion in the database
 * Input: string
 * Output: none
 */
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
