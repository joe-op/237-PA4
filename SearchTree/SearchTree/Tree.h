//The only way to insert data in a tree is with the insert function. 
//So, the tree satisfies the Binary Search Tree Storage Rule.
//The functions inTree depends on this. < must be defined and give a well behaved
//ordering to the type T.

#ifndef TREE_H
#define TREE_H

	template<class T>
	class SearchTree; //forward declaration

	template<class T>
	class TreeNode
	{
	public:
		TreeNode() : root(NULL){}
		TreeNode(T theData, TreeNode<T>* left, TreeNode<T>* right)
			: data(theData), leftLink(left), rightLink(right){}
		friend class SearchTree<T>;
	private:
		/* helper for BST remove: find the removed node */
		TreeNode<T> *remove(T item, TreeNode<T>* parent);
		/* helper for BST remove: find the minimum value of right subTree */
		TreeNode* minRightSubTree();
		T data;
		TreeNode<T> *leftLink;
		TreeNode<T> *rightLink;
	};


	template<class T>
	class SearchTree
	{
	public:
		SearchTree() : root(NULL){}
		~SearchTree(); //deconstructor
		//Adds item to the tree
		void insert(T item);
		//Finds item in the tree 
		bool inTree(T itme) const;
		//Prints items stored in the tree in order (smallest to largest)
		void inOrderPrint() const;
		//Removes item from the tree
		bool remove(T item);
	private:
		/* helper function for the destructor */
		void deleteSubtree(TreeNode<T>* &subTreeRoot);
		/* helper function for recursive definition of insert method */
		void insert(T item, TreeNode<T>* &subTreeRoot);
		/* helper function for recursive definition of inTree method */
		bool inTree(T item, TreeNode<T>* subTreeRoot) const;
		/* helper function for recursive definition of inOrderPrint method */
		void inOrderPrint(TreeNode<T>* subTreeRoot) const;
		TreeNode<T> *root;
	};


#endif