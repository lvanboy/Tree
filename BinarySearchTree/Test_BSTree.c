#include <stdio.h>
#include <stdlib.h>
#include "BSTree.h"


int main01(){
	BSNode  t2, t3;
	BSTree search_result = NULL;
	BSTree t1 = NULL;
	t2.val = 1;
	t3.val = 3;
	t2.left = NULL;
	t2.parent = t1;
	t2.right = NULL;
	t3.left = NULL;
	t3.parent = t1;
	t3.right = NULL;
	t1 = Create_BSNode( 2);
	search_result = Search_BSTree(t1, 4);
	if (search_result){
		printf("finding!");
	}
	else{
		printf("not finding.");
	}
	getchar();
	return 0;
}

int main(){
	BSTree root = Create_BSNode(6);
	BSTree t1, t2, t3, t4, t5, t7;
	BSNode *max = NULL;
	BSNode *min = NULL;
	BSNode *pre = NULL;
	BSNode *next = NULL;
	BSNode *delete_node = NULL;

	printf("insert some number between 1 and 7\n");
	t1 = WrapInsert_BSNode(root, 1);
	t5 = WrapInsert_BSNode(root, 5);
	t3 = WrapInsert_BSNode(root, 3);
	t2 = WrapInsert_BSNode(root, 2);
	t4 = WrapInsert_BSNode(root, 4);
	t7 = WrapInsert_BSNode(root, 7);

	max = GetMaximum_BSNode(root);
	min = GetMinimum_BSNode(root);
	printf("the max value of tree is %d\n", max->val);
	printf("the min value of tree is %d\n\n", min->val);

	printf("the result of infix traverse is :");
	Inorder(root);

	pre = predecessor(t7);
	next = successor(t7);
	printf("\n\nthe predecessor of the node 7 is %d\n", pre->val);
	printf("the successor of the node 7 is %d\n\n", next->val);

	printf("the structure of the tree\n");
	printRelation(root,root,0);


	printf("\ndelete the allocation node : %d\n",t1->val);
    WrapDelete_BSTree(root, t1);
	printf("the result of infix traverse is :");
	Inorder(root); 
	printf("\ndestorying.\n");
	Destroy_BSTree(root);

	getchar();
	return 0;
}