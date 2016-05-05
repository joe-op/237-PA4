#include"TreeIndex.h"


template<class T>
void TreeIndex<T>::insert(T key, Record* record)
{
	//TODO: Refer to binary search tree sample code 
}

template<class T>
void TreeIndex<T>::insert(T key, Record* record, TreeNode<T>* & subTreeRoot)
{
	//TODO: Refer to binary search tree sample code 
	//Besides insert the key into the tree, you also need to insert record into the list records
	
}


template<class T>
TreeNode<T>* TreeIndex<T>::find(T key) const
{
	//TODO: Refer to binary search tree sample code 
}

template<class T>
TreeNode<T>* TreeIndex<T>::find(T key, TreeNode<T>* subTreeRoot) const
{
	//TODO: Refer to binary search tree sample code 
}

template<class T>
bool TreeIndex<T>::removePrimary(T key)
{
	//TODO: Refer to binary search tree sample code 
}

template<class T>
TreeNode<T>* TreeNode<T>::remove(T key, TreeNode<T> *parent)
{
	//TODO: Refer to binary search tree sample code 
}

template<class T>
TreeNode<T>* TreeNode<T>::minRightSubTree() 
{
	//TODO: Refer to binary search tree sample code 
}

template<class T>
bool TreeIndex<T>::removeSecondary(T key, string primekey)
{
	//TODO
	/*
	1. Find the node with key in the index tree
	2. Traverse the node's list records to find the record (actually its reference) with primekey
	3. Delete the record from the list records
	4. Check whether the list records is empty or not
		4.1 If it is empty, delete the node from the index tree
		4.2 Otherwise, do nothing
	*/


}
template<class T>
void TreeIndex<T>::deleteSubtree(TreeNode<T>*& subTreeRoot)
{
	if (subTreeRoot != NULL)
	{
		deleteSubtree(subTreeRoot->leftlink);

		deleteSubtree(subTreeRoot->rightlink);

		//subTreeRoot now points to a one node tree.
		delete subTreeRoot;
		subTreeRoot = NULL;
	}
}

template<class T>
TreeIndex<T>::~TreeIndex()
{
	deleteSubtree(root);
}
