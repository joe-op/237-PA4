//This is the implementation file the template class SearchTree. 

#include"Tree.h"

	template<class T>
	void SearchTree<T>::insert(T item, TreeNode<T>*& subTreeRoot)
	{
		if (subTreeRoot == NULL)
			subTreeRoot = new TreeNode<T>(item, NULL, NULL);
		else if (item < subTreeRoot->data)
			insert(item, subTreeRoot->leftLink);
		else //item >= subTreeRoot->data
			insert(item, subTreeRoot->rightLink);
	}

	template<class T>
	void SearchTree<T>::insert(T item)
	{
		insert(item, root);
	}

	template<class T>
	bool SearchTree<T>::inTree(T item, TreeNode<T>* subTreeRoot) const
	{
		if (subTreeRoot == NULL)
			return false;
		else if (subTreeRoot->data == item)
			return true;
		else if (item < subTreeRoot->data)
			return inTree(item, subTreeRoot->leftLink);
		else //item >= link->data
			return inTree(item, subTreeRoot->rightLink);
	}

	template<class T>
	bool SearchTree<T>::inTree(T item) const
	{
		return inTree(item, root);
	}

	template<class T> 
	void SearchTree<T>::inOrderPrint(TreeNode<T>* subTreeRoot) const
	{
		if (subTreeRoot != NULL)
		{
			inOrderPrint(subTreeRoot->leftLink);
			cout << subTreeRoot->data << " ";
			inOrderPrint(subTreeRoot->rightLink);
		}
	}

	template<class T>
	void SearchTree<T>::inOrderPrint() const
	{
		inOrderPrint(root);
	}

	template<class T>
	void SearchTree<T>::deleteSubtree(TreeNode<T>* &subTreeRoot)
	{
		if (subTreeRoot != NULL) //if it is not an empty tree
		{
			deleteSubtree(subTreeRoot->leftLink); //delete left subtree
			deleteSubtree(subTreeRoot->rightLink); //delete right subtree
			delete subTreeRoot;   //delete root
		}
	}

	template<class T>
	SearchTree<T>::~SearchTree()
	{
		deleteSubtree(root);
	}


	template<class T>
	bool SearchTree<T>::remove(T item)
	{
		if (root == NULL) //if it is an empty tree
			return false;
		else {
			if (item == root->data) {   //if we need to remove an item stored in root
				//create a dummy root as the parent of the root node
				TreeNode<T> auxRoot(0, NULL, NULL);
				auxRoot.leftLink = root;
				//locate the removed node 
				TreeNode<T>* removedNode = root->remove(item, &auxRoot);
				root = auxRoot.leftLink;
				if (removedNode != NULL) {
					delete removedNode; //discard the removed node
					return true;
				}
				else
					return false;
			}
			else {  //if the removed item is not stored in root
				//locate the removed node in the tree
				TreeNode<T>* removedNode = root->remove(item, NULL);
				if (removedNode != NULL) {  //find the removed node
					delete removedNode;
					return true;
				}
				else    //can not find the removed node
					return false;
			}
		}
	}

	template<class T>
	TreeNode<T>* TreeNode<T>::remove(T item, TreeNode<T>* parent)
	{   //look for item
		if (item < this->data) {
			if (leftLink != NULL)
				//continue looking for item in the left subtree
				return leftLink->remove(item, this);
			else     return NULL;  //not find item
		}
		else if (item > this->data) {
			if (rightLink != NULL)
				//continue looking for item in the right subtree
				return rightLink->remove(item, this);
			else     return NULL;   //not find item
		}
		else {    //find the place of node to be removed		
			//if the removed node has two children
			if (leftLink != NULL && rightLink != NULL) {
				//copy the minimum value in the right subtree to the node
				this->data = rightLink->minRightSubTree()->data;
				//remove the duplicate value in the right substree
				return rightLink->remove(this->data, this);
			}
			//if the removed node is its parent's left child
			//link its single child directly to its parent as left child
			else if (parent->leftLink == this) {
				parent->leftLink = (leftLink != NULL) ? leftLink : rightLink;
				return this;
			}
			//if the removed node is its parent's right child
			//link its single child directly to its parent as right child
			else if (parent->rightLink == this) {
				parent->rightLink = (leftLink != NULL) ? leftLink : rightLink;
				return this;
			}
		}
	}
	template<class T>
	TreeNode<T>* TreeNode<T>::minRightSubTree() {
		if (this->leftLink == NULL)
			return this;
		else
			return leftLink->minRightSubTree();
	}

