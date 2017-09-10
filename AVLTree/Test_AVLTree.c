#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AVLTree.h"

int main(){
	int height = 0;
	AVLNode *max = NULL;
	AVLNode *min = NULL;
	AVLNode *root = Create_AVLTree(3);
	root = Wrap_Insert_AVLNode(root, 2);
	root = Wrap_Insert_AVLNode(root, 1);
	root = Wrap_Insert_AVLNode(root, 4);
	root = Wrap_Insert_AVLNode(root, 5);
	root = Wrap_Insert_AVLNode(root, 6);
	root = Wrap_Insert_AVLNode(root, 7);
	root = Wrap_Insert_AVLNode(root, 16);
	root = Wrap_Insert_AVLNode(root, 15);
	root = Wrap_Insert_AVLNode(root, 14);
	root = Wrap_Insert_AVLNode(root, 13);
	root = Wrap_Insert_AVLNode(root, 12);
	root = Wrap_Insert_AVLNode(root, 11);
	root = Wrap_Insert_AVLNode(root, 10);
	root = Wrap_Insert_AVLNode(root, 8);
	root = Wrap_Insert_AVLNode(root, 9);
	printf("the results of the inorderTraverse is : \n");
	InorderTraverse(root);
	printf("\nthe relationship of the tree is :\n");
	printRelation(root);
	height = Get_Height(root);
	printf("the height of the tree is %d\n", height);
	max = Get_Maximum(root);
	printf("the maximum of the tree is %d\n", max->key);
	min = Get_Minimum(root);
	printf("the minimum of the tree is %d\n", min->key);
	printf("delete one node.\n");
	Wrap_Delete_AVLNode(root, 8);
	printf("the results of the inorderTraverse is : \n");
	InorderTraverse(root);
	printf("\ndestroying the tree\n");
	Destory_AVLNode(root);
	//销毁后,将拿不到任意节点的值了.
	printf("the key of root is : %d\n", root->key);
	getchar();
	return 0;
}