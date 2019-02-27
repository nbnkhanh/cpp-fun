#include<iostream>
#include<fstream>
using namespace std;
struct Node {
	int num;
	Node* left;
	Node* right;
};
void insert(int key, Node*&root);
void CreateTree(Node* &root);
//void PreOrder(Node*root, ofstream& file);
//void PostOrder(Node*root, ofstream& file);
void Draw(Node* root, int count, bool check[], int child);