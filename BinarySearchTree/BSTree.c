
#include <stdio.h>
#include <stdlib.h>
#include "BSTree.h"


BSTree Create_BSNode(BSNode *left, BSNode *right, BSNode *parent, DataType val){
	BSNode *node = (BSTree)malloc(sizeof(BSNode));
	if (node){
		node->left = left;
		node->right = right;
		node->parent = parent;
		node->val = val;
	}
	return node;
}
BSTree Search_BSTree(BSNode *node, DataType val){
	if (node == NULL || val == node->val){
		return node;
	}
	if (!node->left || !node->right){
		return node->left;
	}
	//如果比当前节点小,向左子树走
	if (val < node->val){
		return Search_BSTree(node->left, val);
	}//否则,向右子树走
	else{
		return Search_BSTree(node->right, val);
	}
}
