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
		add(root, lineIn);
	}

	// print the size of the tree as a basic test
	cout << size(root) << endl;

	return EXIT_SUCCESS;
}