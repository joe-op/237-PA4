#include"TreeIndex.h"


template<class T>
void TreeIndex<T>::insert(T key, Record* record)
{
	insert(key, record, root);
}

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
	else {
		insert(key, record, subTreeRoot->rightlink);
	}
	//TODO: Refer to binary search tree sample code 
	//Besides insert the key into the tree, you also need to insert record into the list records
	
}


template<class T>
TreeNode<T>* TreeIndex<T>::find(T key) const
{
	return find(key, root);
}

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
	}
}

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

template<class T>
list<Record*> *TreeNode<T>::get_records() {
	return &records;
}

template<class T>
bool TreeIndex<T>::removeSecondary(T key, string primekey)
{

	TreeNode<T>* the_key = find(key);
	if (the_key == NULL || the_key->records.empty()) {
		return false;
	}
	else {
		the_key->get_records()[0];
	}
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
