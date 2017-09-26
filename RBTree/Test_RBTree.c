#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "RBTree.h"

int main(){
	RBRoot *root = RBTree_Create();
	RBTree_Insert_Wrap(root, 10);
	RBTree_Insert_Wrap(root, 40);
	RBTree_Insert_Wrap(root, 30);
	RBTree_Insert_Wrap(root, 60);
	RBTree_Insert_Wrap(root, 90);
	RBTree_Insert_Wrap(root, 70);
	RBTree_Insert_Wrap(root, 20);
	RBTree_Insert_Wrap(root, 50);
	RBTree_Insert_Wrap(root, 80);
	inorder_rbtree(root);
	printf("\nprintf the relationship of RBTree\n");
	printf("\nthe root of the RBTree(%c) is %d\n", root->node->color ?  'B':'R',root->node->key);
	RBTree_Print_Relationship(root->node);

	//RBTree_Delete_Wrap(root, 30);
	//RBTree_Delete_Wrap(root, 60);
	//inorder_rbtree(root);
	getchar();
	return 0;
}