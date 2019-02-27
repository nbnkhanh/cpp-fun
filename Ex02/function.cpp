#include"function.h"
void insert(int key, Node*&root) {
	if (root == NULL) {
		root = new Node;
		root->num = key;
		root->left = NULL;
		root->right = NULL;
		return;
	}
	Node* cur = root;
	while (1) {
		if (key > cur->num) {
			if (cur->right == NULL) {
				cur->right = new Node;
				cur = cur->right;
				cur->right = NULL;
				cur->left = NULL;
				cur->num = key;
				return;
			}
			cur = cur->right;
		}
		else {
			if (cur->left == NULL) {
				cur->left = new Node;
				cur = cur->left;
				cur->right = NULL;
				cur->left = NULL;
				cur->num = key;
				return;
			}
			cur = cur->left;
		}
	}
}
void CreateTree(Node* &root) {
	ifstream file;
	file.open("input.txt");
	while (!file.eof()) {
		int key; file >> key;
		insert(key, root);
	}
	file.close();
}

void Draw(Node* root, int count, bool check[], int child) {
	if (!root) return;
	for (int i = 0; i < count - 1; ++i) {
		if (check[i] == 0)cout << "|";
		else cout << " ";
	}
	if (count&&child == 2) cout << char(195);
	else if (count&&child == 1) cout << char(192);
	cout << root->num << endl;
	if (root->left&&root->right) child = 2;
	else {
		child = 1;
		check[count] = 1;
	}
	Draw(root->left, count + 1, check, child);
	check[count] = 1;
	child = 1;
	Draw(root->right, count + 1, check, child);
	check[count] = 0;
}
/*
void PreOrder(Node*root, ofstream& file) {//root, left, right
	if (root == NULL) return;
	file << root->num << endl;
	PreOrder(root->left, file);
	PreOrder(root->right, file);
}
void PostOrder(Node*root, ofstream& file) {//left, right, root
	if (root == NULL) return;
	PostOrder(root->left, file);
	PostOrder(root->right, file);
	file << root->num << endl;
}
*/