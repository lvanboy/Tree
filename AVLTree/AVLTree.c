#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AVLTree.h"

AVLNode *Create_AVLTree(DataType key){

	AVLNode *node = (AVLNode *)malloc(sizeof(AVLNode));
	if (node == NULL){
		return node;
	}
	node->height = 0;
	node->left = NULL;
	node->right = NULL;
	node->key = key;
	return node;
}


int Get_Height(AVLNode *node){
	return HEIGHT(node);
}

AVLNode *Get_Maximum(AVLNode *node){
	if (node->right == NULL){
		return node;
	}
	return Get_Maximum(node->right);
}

AVLNode *Get_Minimum(AVLNode *node){
	if (node->left == NULL){
		return node;
	}
	return Get_Minimum(node->left);
}

void PreorderTraverse(AVLNode *tree){
	if (tree == NULL){
		return;
	}
	printf("%d ", tree->key);
	PreorderTraverse(tree->left);
	PreorderTraverse(tree->right);
}

void InorderTraverse(AVLNode *tree){
	if (tree == NULL){
		return;
	}
	InorderTraverse(tree->left);
	printf("%d ", tree->key);
	InorderTraverse(tree->right);
}

void PostorderTraverse(AVLNode *tree){
	if (tree == NULL){
		return;
	}
	PostorderTraverse(tree->left);
	PostorderTraverse(tree->right);
	printf("%d ", tree->key);
}

AVLNode *Left_Left_Rotation(AVLNode *tree){
	if (tree == NULL){
		return tree;
	}
	AVLNode *left = tree->left;
	tree->left = left->right;
	left->right = tree;
	//发生旋转后,高度会发生变化,重置高度
	tree->height = MAX(HEIGHT(tree->left), HEIGHT(tree->right))+1;
	left->height = MAX(HEIGHT(left->left), tree->height) + 1;
	return left;
}

AVLNode *Right_Right_Rotation(AVLNode *tree){
	AVLNode *right = tree->right;
	tree->right = right->left;
	right->left = tree;
	tree->height = MAX(HEIGHT(tree->left), HEIGHT(tree->right)) + 1;
	right->height = MAX(HEIGHT(right->right), tree->height) + 1;
	return right;
}

//LR
AVLNode *Left_Right_Rotation(AVLNode *tree){
	if (tree == NULL){
		return tree;
	}
	tree->left = Right_Right_Rotation(tree->left);
	return Left_Left_Rotation(tree);
}

//RL
AVLNode *Right_Left_Rotation(AVLNode *tree){
	if (tree == NULL){
		return tree;
	}
	tree->right = Left_Left_Rotation(tree->right);
	return Right_Right_Rotation(tree);
}


AVLNode *Find_AVLNode(AVLNode *tree, DataType key){
	if (tree == NULL || tree->key == key){
		return tree;
	}
	if (!tree->left && !tree->right){
		return tree->left;
	}
	if (key < tree->key){
		return Find_AVLNode(tree->left, key);
	}
	else if (key>tree->key){
		return  Find_AVLNode(tree->right, key);
	}

}
AVLNode *Insert_AVLNode(AVLNode *tree, AVLNode *node){

	if (tree == NULL){
		tree = node;
	}
	else if (node->key < tree->key){
		tree->left = Insert_AVLNode(tree->left, node);
		//判断是否失衡
		if (HEIGHT(tree->left) - HEIGHT(tree->right) == 2){
			if (node->key < tree->left->key){
				//旋转后,拿到新的节点值
				tree = Left_Left_Rotation(tree);
			}
			else{
				tree = Left_Right_Rotation(tree);
			}
		}
	}
	else if (node->key > tree->key){
		tree->right = Insert_AVLNode(tree->right, node);
		if (HEIGHT(tree->right) - HEIGHT(tree->left) == 2){
			if (node->key < tree->right->key){
				//旋转后,得到新的节点值
				tree = Right_Left_Rotation(tree);
			}
			else{
				tree = Right_Right_Rotation(tree);
			}
		}
	}
	tree->height = MAX( HEIGHT(tree->left), HEIGHT(tree->right) ) + 1;
	return tree;
}

AVLNode *Wrap_Insert_AVLNode(AVLNode *tree, DataType key){
	AVLNode *node = NULL;

	if (Find_AVLNode(tree, key) != NULL){
		return NULL;
	}
	else{
		node = Create_AVLTree(key);
		tree = Insert_AVLNode(tree, node);
		
	}
	return tree;
}

AVLNode *Delete_AVLNode(AVLNode *tree, AVLNode *node){
	if (node->key < tree->key){
		tree->left = Delete_AVLNode(tree->left, node);
		if (HEIGHT(tree->right) - HEIGHT(tree->left) == 2){
			if (HEIGHT(tree->right->left )> HEIGHT(tree->right->right)){
				tree = Right_Left_Rotation(tree);
			}
			else{
				tree = Right_Right_Rotation(tree);
			}
		}
	}
	else if (node->key > tree->key){
		tree->right = Delete_AVLNode(tree->right, node);
		if (HEIGHT(tree->left) - HEIGHT(tree->right) == 2){

			if (HEIGHT(tree->left->right)< HEIGHT(tree->left->left)){
				tree = Left_Right_Rotation(tree);
			}
			else{
				tree = Left_Left_Rotation(tree);
			}
		}
	}
	else{
		if (tree->left&&tree->right){
			if (HEIGHT(tree->left) > HEIGHT(tree->right)){
				AVLNode *max = Get_Maximum(tree->left);
				tree->key = max->key;
				tree->left = Delete_AVLNode(tree->left, max);
			}
			else{
				AVLNode *min = Get_Minimum(tree->right);
				tree->key = min->key;
				tree->right = Delete_AVLNode(tree->right, min);
			}
		}
		else{
			AVLNode *temp = tree;
			tree = tree->left ? tree->left : tree->right;
			free(temp);
		}
	}
	return tree;
}

AVLNode *Wrap_Delete_AVLNode(AVLNode *tree, DataType key){
	AVLNode *delete_point = NULL;
	AVLNode *node = NULL;
	if (tree == NULL){
		return tree;
	}
	if ((node = Find_AVLNode(tree, key)) != NULL){
		delete_point = Delete_AVLNode(tree, node);
	}
	return delete_point;
}

void printRelation(AVLNode *tree){
	if (tree == NULL){
		return;
	}//肯定是左右根中的一种类型
		printRelation(tree->left);
		if (tree->left){
			printf("the left child of %d is %d\n", tree->key, tree->left->key);

		}
		printRelation(tree->right);
		if (tree->right){
			printf("the right child of %d is %d\n", tree->key, tree->right->key);
		}
}

void Destory_AVLNode(AVLNode *tree){
	if (tree == NULL){
		return tree;
	}
	Destory_AVLNode(tree->left);
	Destory_AVLNode(tree->right);
	free(tree);
}