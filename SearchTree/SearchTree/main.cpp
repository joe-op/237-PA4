//Demonstration program for the Tree template class.
#include <iostream>
#include "tree.h"
#include "tree.cpp"
using namespace std;

void pause_237(bool have_newline);

int main()
{
	SearchTree<int> t;

	//test insert and inOrderPrint
	cout << "Enter a list of nonnegative integers.\n"
		<< "Place a negative integer at the end.\n";
	int next;
	cin >> next;
	while (next >= 0)
	{
		t.insert(next);
		cin >> next;
	}

	cout << "After insertion, In sorted order: \n";
	t.inOrderPrint();
	cout << endl;

	//test inTree
	cout << "Enter a number you want to search: \n";
	int target;
	cin >> target;
	if (t.inTree(target))
		cout << "Find the target!\n";
	else
		cout << "Cannot find the target.\n";

	//test remove
	cout << "Enter a number you want to remove.\n";
	int removed;
	cin >> removed;
	if (t.remove(removed))
		cout << "The number is removed successfully!\n";
	else
		cout << "Cannot find the number you want to remove.\n";

	cout << "After remove, In sorted order: \n";
	t.inOrderPrint();
	cout << endl;

	pause_237(true);

	return 0;
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