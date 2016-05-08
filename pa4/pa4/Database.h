#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED

#include "Record.h"
#include "TreeIndex.h"
//You must include implementation (.cpp) file when using template class type 
#include "TreeIndex.cpp" 
#include "KeyType.h"
#include <vector>
#include <string>
using namespace std;


class Database{
public:
	//Constructor: load file to build database vector, primary index and secondary index
	Database(string filename);
	
	//Insert a record into indexType denoted index
	void Insert(Record* record, char indexType);
	
	//Find a record in indexType denoted index with a keyvalue k and print them
	void Find(KeyType k, char indexType) const;
	
	bool FindRange(KeyType low, KeyType high, char indexType);

	//Delete the record with primary key k from primary index
	bool DeletePrimary(KeyType k);

	//Delete the record with primary key primekey from a non-primary key index specified by indexType
	bool DeleteSecondary(KeyType primekey, KeyType k, char indexType);

	bool Delete(KeyType primekey);


private:
	
	//Helper function: parse a line from records file to generate a Record object
	//(already implemented)
	Record parse_records(string line);
	
	vector<Record> records;  //database vector which stores Record objects 
	                         //you can also use an array to store Record objects
	
	//Primary index: index on number (unique attribute)
	TreeIndex<string> indexS; 
	
	//Non-primary(secondary) index: index on age (nonunique attribute)
	TreeIndex<int> indexA; 
};

#endif