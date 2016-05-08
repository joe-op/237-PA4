#include "Database.h"
#include <fstream>
#include <iostream>
#include <sstream>

/*
* CS237 PA4
* Joe Opseth & Jens Myklebust
* 8 May 2016
*/

//Run command line on database db
//Use Database pointer as parameter
void issueCommand(string line, Database* db);
//Convert a numerical string to corresponding number
int stringToNumber(string str);
void pause_237(bool have_newline);


int main()
{
	cout << "Relational Database by Group 5 - CS 237 PA4" << endl;
	cout << "Bonus features implemented: Delete and FindRange" << endl;
	cout << "Loading database records.txt . . . " << endl;

	Database* db = new Database("records.txt");

	cout << "Set up database and indices successfully" << endl;
	cout << endl;

	ifstream infile;
	string filename = "commands.txt";

	infile.open(filename.c_str());
	if (infile.fail()) {
		cerr << "Invalid commands file.";
		exit(1);
	}
	else {
		string line;
		while (!infile.eof()) {
			getline(infile, line);
			issueCommand(line, db);
		}
	}

	pause_237(false);
}

void issueCommand(string line, Database* db)
{
	cout << line << endl;
	cout << "********************" << endl;
	string command = line.substr(0, 2);
	if (command == "DP")
	{
		KeyType key2(line.substr(3));
		db->DeletePrimary(key2);
	}
	else if (command == "DS")
	{
		KeyType primeKey(line.substr(3, 7));
		KeyType secondaryKey(stringToNumber(line.substr(11, 2)));
		char type = line.at(14);
		db->DeleteSecondary(primeKey, secondaryKey, type);
	}
	else if (command == "DE")
	{
		KeyType key2(line.substr(3));
		db->Delete(key2);
	}
	else
	{
		char indexType = line.at(3);

		if (command == "FI")
		{
			KeyType key2;

			if (indexType == 'S')
			{
				key2.setKey1(line.substr(5));
			}
			else
			{
				key2.setKey2(stringToNumber(line.substr(5)));
			}
			db->Find(key2, indexType);
		}
		else if (command == "FR") {
			// FR S 9600000 9630000
			// FR A 18 22
			KeyType key_low, key_high;
			int first_end = line.find(' ');
			int second_start = first_end + 1;
			int second_end = line.find(' ', second_start);
			int third_start = second_end + 1;
			int third_end = line.find(' ', third_start);
			int fourth_start = third_end + 1;
			if (indexType == 'S') {
				key_low.setKey1(line.substr(third_start, third_end - third_start));
				key_high.setKey1(line.substr(fourth_start));
				db->FindRange(key_low, key_high, 'S');
			}
			else {
				key_low.setKey2(stringToNumber(line.substr(third_start, third_end - third_start)));
				key_high.setKey2(stringToNumber(line.substr(fourth_start)));
				db->FindRange(key_low, key_high, 'A');
			}
		}
	}
	cout << endl << endl << endl;
}


int stringToNumber(string str)
{
	string input = str;
	istringstream str_stream(input);
	int number;
	str_stream >> number;
	return number;
}

void pause_237(bool have_newline)
{
	if (have_newline) {
		// Ignore the newline after the user's previous input.
		cin.ignore(200, '\n');
	}

	// Prompt for the user to press ENTER, then wait for a newline.
	cout << endl << "Press ENTER to continue." << endl;
	cin.ignore(200, '\n');
}