#include<iostream>
#include<fstream>
#include<string>
using namespace std;

struct Bnode{
	string data;
	Bnode* left;
	Bnode* right;
};

void inorder(Bnode* root){
	if(root != NULL){
		inorder(root -> left);
		cout << root -> data << endl;
		inorder(root -> right);
	}
}

void add(Bnode*& root, string item){
	if(root == NULL){
		root = new Bnode;
		root -> data = item;
		root -> left = root -> right = NULL;
	}
	else if (item <= root -> data)
		add(root -> left, item);
	else
		add(root -> right, item);
}

int size(Bnode* root){
	if(root == NULL) return 0;
	else
	return size(root -> left) + size(root -> right) + 1;
}

int getCount(Bnode* root, string item) {
	int count = 0;

	if (root == NULL) {
		return count;
	}
	else if (root -> data == item) {
		count++;
	}

	count += getCount(root -> left, item);
	count += getCount(root -> right, item);
	return count;
}

int getCountGreater(Bnode* root, string item) {
	int count = 0;

	if (root == NULL) {
		return count;
	}
	else if ((root -> data) >= item) {
		count += size(root -> right);
		if ((root -> data) > item) {
			count++;  // add an extra one for the root
		}

		count += getCountGreater(root -> left, item);
		return count;
	}
	else {
		count += getCountGreater(root -> right, item);
		return count;
	}
}


int main() {
	ifstream file;
	string lineIn;

	Bnode* root = NULL;  // root of the binary tree

	// open names file
	file.open("names.txt");

	// check if file failed to open
	if (file.fail()) {
		cout << "Failed to open file." << endl;
		return EXIT_FAILURE;
	}

	// add all the names to the tree
	while (getline(file, lineIn)) {
		// find length of substring without trailing spaces
		int substrLength;
		for (substrLength = lineIn.length(); substrLength > 0; substrLength--) {
			if (!isspace(lineIn[substrLength - 1])) {
				break;
			}
		}

		// add item without trailing spaces
		add(root, lineIn.substr(0, substrLength));
	}

	// get a name to search in the tree
	cout << "Enter the name you want to search for: ";
	cin >> lineIn;

	// get values to print to the screen later
	int count1 = getCount(root, lineIn);         // count the number of times the name appears in the tree
	int count2 = getCountGreater(root, lineIn);  // count the number of names that come alphabetically after the name
	string msg1End = (count1 == 1) ? " time." : " times.";
	string msg2End = (count2 == 1) ? " name alphabetically after that." : " names alphabetically after that.";

	// print the values found earlier
	cout << "Your search name appears " << count1 << msg1End << endl;
	cout << "There are " << count2 << msg2End << endl;

	return EXIT_SUCCESS;
}