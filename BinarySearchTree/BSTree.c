
#include <stdio.h>
#include <stdlib.h>
#include "BSTree.h"

//创建一个节点
BSTree Create_BSNode(DataType val){
	BSNode *node = (BSTree)malloc(sizeof(BSNode));
	if (node){
		node->left = NULL;
		node->right = NULL;
		node->parent = NULL;
		node->val = val;
	}
	return node;
}

//寻找某个值
BSTree Search_BSTree(BSNode *node, DataType val){
	if (node == NULL || val == node->val){
		return node;
	}
	if (!node->left && !node->right){
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

//找到最大值
BSTree GetMaximum_BSNode(BSNode *root){
	BSNode *Max_Node = NULL;
	if (root==NULL){
		return root;
	}
	while (root->right){
		root = root->right;
	}
	Max_Node = root;
	return Max_Node;
}

//找到最小值
BSTree GetMinimum_BSNode(BSNode *root){
	BSNode *Min_Node = NULL;
	if (root == NULL){
		return root;
	}
	while (root->left){
		root = root->left;
	}
	Min_Node = root;
	return Min_Node;
}



//插入节点
int Insert_BSNode(BSNode *root, BSNode *node){
	BSNode *insert_point = NULL;
	if (root == NULL || node == NULL){
		return 0;
	}
	//寻找插入点
	while (root){
		//默认从根开始寻找
		insert_point = root;
		if (node->val < root->val){
			root = root->left;
		}
		else if (node->val > root->val){
			root = root->right;
		}
	}
	//空树则直接将插入点作为树根
	if (insert_point == NULL){
		root = node;
	}
	node->parent = insert_point;
	//判断新节点在插入点的左边还是右边,并建立关系.
	if (node->val < insert_point->val){
		insert_point->left = node;
	}
	else{
		insert_point->right = node;
	}
	return 1;
}

//插入节点之前要新建节点,这里是包裹层,直接在这里创建节点
BSTree WrapInsert_BSNode(BSNode *root, DataType nodeVal){
	BSNode *node = NULL;
	//插入的节点值存在
	if (Search_BSTree(root, nodeVal) != NULL){
		return NULL;
	}
	//节点创建不成功
	if ((node = Create_BSNode( nodeVal ))== NULL){
		return NULL;
	}
	Insert_BSNode(root, node);
	return node;
}

//先序遍历
void preorder(BSTree root){
	if (root == NULL){
		return ;
	}
	printf(" %d", root->val);
	preorder(root->left);
	preorder(root->right);
}

//中序遍历
void Inorder(BSTree root){
	if (root == NULL){
		return;
	}
	Inorder(root->left);
	printf(" %d", root->val);
	Inorder(root->right);
}

//寻找节点的前驱
BSTree predecessor(BSNode *node){
	return;
}

//寻找节点的后继
BSTree successor(BSNode *node){
	return;
}

//订一套规则,标识左孩子,右孩子,和根
//打印节点之间的关系
void printRelation(BSNode *child, BSNode *parent, int direction){
	if (child == NULL || parent == NULL){
		return;
	}
	if (direction != -1 && direction != 1&& direction !=0){
		return;
	}
	if (direction == 0){
		printf("the %d is the root\n", parent->val);
	}
	else if (direction == -1){
		printf("the %d is the left child of the  %d\n", child->val, parent->val);
	}
	else{
		printf("the %d is the right child of the %d\n", child->val, parent->val);
	}
	printRelation(child->left, child, -1);
	printRelation(child->right, child, 1);
}

//销毁二叉搜索树
void Destroy_BSTree(BSTree root){
	if (root == NULL){
		return;	
	}
	Destroy_BSTree(root->left);
	Destroy_BSTree(root->right);
	free(root);
}
