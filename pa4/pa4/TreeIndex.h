#ifndef TREEINDEX_H_INCLUDED
#define TREEINDEX_H_INCLUDED

#include"Record.h"
#include"KeyType.h"
#include<list>
#include<iostream>
using namespace std;


template<class T>
class TreeIndex;

template<class T>
class TreeNode
{
public:
	TreeNode() :root(NULL){}
	TreeNode(T theKey, TreeNode<T>* left, TreeNode<T>* right) :
		key(theKey), leftlink(left), rightlink(right){}
	TreeNode* remove(T key, TreeNode *parent);
	TreeNode* minRightSubTree();
	list<Record*> *get_records() const;
	friend class TreeIndex<T>;
private:
	T key;
	TreeNode<T> *leftlink;
	TreeNode<T> *rightlink;
	//Since we allow nonunique keys, the nodes of the search tree must use
	//a linked list to store all the records with the key values stored in the nodes.
	list<Record*> records; //store record's pointer in the list
	/*
	   You could also store record's index (where it is stored in the array/vector) in the list:
	   list<int> records;  
	*/
};

template<class T>
class TreeIndex
{
public:
	TreeIndex() : root(NULL){}
	virtual ~TreeIndex(); 
	//Insert the reference of record into the index tree
	void insert(T key, Record* record);
	TreeNode<T>* find(T key) const;
	bool removePrimary(T key);
	bool removeSecondary(T key, string primekey);
private:
	void insert(T key, Record* record, TreeNode<T>* & subTreeRoot);
	TreeNode<T>* find(T key, TreeNode<T>* subTreeRoot) const;
	void deleteSubtree(TreeNode<T>* & subTreeRoot);
	TreeNode<T> *root;
};


#endif 