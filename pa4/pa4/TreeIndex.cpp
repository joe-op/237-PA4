#include"TreeIndex.h"

/*
* CS237 PA4
* Joe Opseth & Jens Myklebust
* 8 May 2016
*/

/*
 * Insert record into index
 * Input: key (string or int); pointer to record
 * Output: none
 */
template<class T>
void TreeIndex<T>::insert(T key, Record* record)
{
	insert(key, record, root);
}

/*
 * Helper for insert method
 * Insert record into index starting with subTreeRoot
 * Input: key (string or int), pointer to record, pointer to TreeNode
 * Output: none
 */
template<class T>
void TreeIndex<T>::insert(T key, Record* record, TreeNode<T>* & subTreeRoot)
{
	if (subTreeRoot == NULL) {
		subTreeRoot = new TreeNode<T>(key, NULL, NULL);
		subTreeRoot->records.push_back(record);
	}
	else if (key < subTreeRoot->key)
	{
		insert(key, record, subTreeRoot->leftlink);
	}
	else if (key > subTreeRoot->key) {
		insert(key, record, subTreeRoot->rightlink);
	}
	else if(key == subTreeRoot->key){
		subTreeRoot->records.push_back(record);
	}
	else {
		cerr << "Key could not be placed";
		exit(1);
	}	
}

/*
 * Find a record
 * Input: key (string or int)
 * Output: Pointer to TreeNode
 * This function takes a key and begins a recursive
 * search at the root TreeNode.
 * It returns a pointer to the TreeNode containing
 * the key, or NULL if the key is not found.
 */
template<class T>
TreeNode<T>* TreeIndex<T>::find(T key) const
{
	return find(key, root);
}

/*
 * Helper method for find(T key)
 * Input: key (string or int), TreeNode<T>* subTreeRoot
 * Searches for key recursively by narrowing the location
 * down to subTreeRoot.
 */
template<class T>
TreeNode<T>* TreeIndex<T>::find(T key, TreeNode<T>* subTreeRoot) const
{
	if (subTreeRoot == NULL) {
		return false;
	}
	else if (key == subTreeRoot->key) {
		return subTreeRoot;
	} else if(key < subTreeRoot->key) {
		return find(key, subTreeRoot->leftlink);
	}
	else if(key > subTreeRoot->key) {
		return find(key, subTreeRoot->rightlink);
	}
	else {
		cerr << "Keys could not be compared.";
		exit(1);
	}
}

/*
 * removePrimary: Removes key from the index
 * Input: key (string or int)
 * Output: bool
 * Removes all records referred to by key from the index.
 * Returns true if the record is found, false otherwise.
 */
template<class T>
bool TreeIndex<T>::removePrimary(T key)
{
	if (root == NULL) {
		return false;
	}
	else {
		if (key == root->key) {
			TreeNode<T> auxRoot(key, NULL, NULL);
			auxRoot.leftlink = root;
			TreeNode<T>* removedNode = root->remove(key, &auxRoot);
			root = auxRoot.leftlink;
			if (removedNode != NULL) {
				delete removedNode;
				return true;
			}
			else {
				return false;
			}
		}
		else {
			TreeNode<T>* removedNode = root->remove(key, NULL);
			if (removedNode != NULL) {
				delete removedNode;
				return true;
			}
			else {
				return false;
			}
		}
	}
}

/*
 * Helper method for removePrimary
 * Input: key (string or int), TreeNode<T> *parent
 * Output: TreeNode<T>*
 * Recursively searches for key.
 * If it is found, rearranges the tree as necessary
 * and returns a pointer to the TreeNode to be deleted.
 */
template<class T>
TreeNode<T>* TreeNode<T>::remove(T key, TreeNode<T> *parent)
{
	if (key < this->key) {
		if (leftlink != NULL) {
			return leftlink->remove(key, this);
		}
		else {
			return NULL;
		}
	}
	else if(key > this->key) {
		if (rightlink != NULL) {
			return rightlink->remove(key, this);
		}
		else {
			return NULL;
		}
	}
	else {
		if (leftlink != NULL && rightlink != NULL) {
			this->key = rightlink->minRightSubTree()->key;
			this->records = rightlink->minRightSubTree()->records;
			return rightlink->remove(this->key, this);
		}
		else if (parent->leftlink == this) {
			parent->leftlink = (leftlink != NULL) ? leftlink : rightlink;
			return this;
		}
		else if (parent->rightlink == this) {
			parent->rightlink = (leftlink != NULL) ? leftlink : rightlink;
			return this;
		}
	}
}

/*
 * minRightSubTree(): Returns a pointer to the smallest value on the right subtree.
 * Input: None
 * Output: TreeNode<T>*
 */
template<class T>
TreeNode<T>* TreeNode<T>::minRightSubTree() 
{
	if (this->leftlink == NULL) {
		return this;
	}
	else {
		return leftlink->minRightSubTree();
	}
}

/*
 * get_records(): Returns a pointer to the list records
 * Input: none
 * Output: pointer to list<Record*>
 * Returns a pointer to the list of records
 * for use in displaying the records associated
 * with a key.
 */
template<class T>
list<Record*> *TreeNode<T>::get_records() {
	return &records;
}

/*
 * removeSecondary: removes a record from a secondary index
 * Input: T key, string primekey
 * Output: bool
 * Searches for a key (T) that contains the record with number primekey.
 * If record is found, removes the record.
 * If records is empty, removes key from the TreeIndex.
 * Returns true if record is found, false otherwise.
 */
template<class T>
bool TreeIndex<T>::removeSecondary(T key, string primekey)
{

	TreeNode<T>* the_key = find(key);
	if (the_key == NULL || the_key->records.empty()) {
		return false;
	}
	else {
		list<Record*> remove_records;
		for (list<Record*>::iterator i = the_key->records.begin(); i != the_key->records.end(); i++) {
			if ((*i)->getNumber().compare(primekey) == 0) {
				remove_records.push_back(*i);
			}
		}
		for (list<Record*>::iterator i = remove_records.begin(); i != remove_records.end(); i++) {
			the_key->records.remove(*i);
		}
	}
}

/*
 * deleteSubtree: Deletes a subtree
 * Input: TreeNode<T>*& subTreeRoot
 * Output: none
 * Recursively deletes leftlink and rightlink
 * if subTreeRoot is not null.
 * After deleting subtrees, deletes subTreeRoot.
 */
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

/*~TreeIndex: deletes a TreeIndex and its children
 * Input: none
 * Output: none
 */
template<class T>
TreeIndex<T>::~TreeIndex()
{
	deleteSubtree(root);
}
