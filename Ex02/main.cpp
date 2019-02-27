#include "function.h"
void main() {
	//ofstream out1, out2;
	bool check[100] = { 0 };
	//out1.open("out1.txt"); out2.open("out2.txt");
	Node* root = NULL;
	CreateTree(root);
	Draw(root, 0, check, 0);
	//PreOrder(root, out1);
	//PostOrder(root, out2);
	//out1.close(); out2.close();
}