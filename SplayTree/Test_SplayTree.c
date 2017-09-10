#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SplayTree.h"

int main(){
	SplayTree *root = Create_SplayNode(10);
	printf("the root of the tree is %d\n", root->key);
	root = Wrap_Insert_SplayTree(root, 50);
	root = Wrap_Insert_SplayTree(root, 40);
	root = Wrap_Insert_SplayTree(root, 30);
	root = Wrap_Insert_SplayTree(root, 20);
	root = Wrap_Insert_SplayTree(root, 60);
	printf("the results of the inorderTraverse is :\n");
	InorderTraverse(root);
	printf("\nthe relationship of the node is:\n");
	Print_SplayTree(root);
	printf("after splaying the node of 30 :\n");
	root = Splay_SplayTree(root,30);
	printf("the root of the tree is %d\n", root->key);
	printf("after deleting the node:\n");
	root =	Wrap_Delete_SplayTree(root, 20);
	printf("the results of the inorderTraverse is :\n");
	InorderTraverse(root);
	printf("\nthe relationship of the node is:\n");
	Print_SplayTree(root);
	getchar();
	return 0;
}