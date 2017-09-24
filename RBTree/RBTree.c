#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "RBTree.h"

void RBTree_Left_Rotate(RBRoot *root, Node *x){
	Node *y = x->right;
	x->right = y->left;
	if (y->left){
		y->left->parent = x;
	}

	y->parent = x->parent;

	if (!x->parent){
		root->node = y;
	}
	else{
		if (x->parent->left == x){
			x->parent->left = y;
		}
		if (x->parent->right == x){
			x->parent->right = y;
		}
	}
	
	y->left = x;
	x->parent = y;

}

void RBTree_Right_Rotate(RBRoot *root, Node *y){
	Node *x = y->left;
	y->left = x->right;
	if (x->right){
		x->right->parent = y;
	}
	x->parent = y->parent;
	if (!y->parent){
		root->node = x->parent;
	}
	else{
		if (y->parent->left == y){
			y->parent->left = x;
		}
		if (y->parent->right == y){
			y->parent->right = x;
		}
	}
	x->right = y;
	y->parent = x;
}

void RBTree_Insert(RBRoot *root, Node	*node){
	//插入点
	Node *y = NULL;
	Node *x = root->node;
	while (x){
		//初始化插入点是根
		y = x;
		if (node->key > x->key){
			x = x->right;
		}
		else{
			x = x->left;
		}		
	}
	node->parent = y;
	if (!y){
		root->node = node;
	}
	else{
		if (node->key < y->key){
			y->left = node;
		}
		else{
			y->right = node;
		}
	}
	node->color = RED;
	RBTree_Insert_Fixup(root, node);
}

RBTree_Insert_Fixup_Helper(Node *uncle, Node *parent, Node *graparent, Node *node, RBRoot *root){
	if (uncle&&uncle->color == RED){
		parent->color = BLACK;
		uncle->color = BLACK;
		graparent->color = RED;
		node = graparent;
	}
	else{
		if (node->parent->left == node){
			parent->color = BLACK;
			graparent->color = RED;
			RBTree_Right_Rotate(root, graparent);
		}
		else{
			Node *temp;
			RBTree_Left_Rotate(root, parent);
			temp = parent;
			parent = node;
			node = temp;
		}
	}
}
void RBTree_Insert_Fixup(RBRoot *root, Node	*node){
	Node *parent, *graparent,*uncle;
	while ((parent = node->parent) && parent->color == RED){
		graparent = parent->parent;
		if (graparent->left == parent){
			uncle = graparent->right;
			RBTree_Insert_Fixup_Helper(uncle, parent, graparent, node, root);
		}
		else{
			uncle = graparent->left;
			RBTree_Insert_Fixup_Helper(uncle, parent, graparent, node, root);
		}
	}
	root->node->color = BLACK;
}

void RBTree_Delete(RBRoot *root, Node *node){
	Node *child, *parent;
	int color;
	//删除节点有2个孩子
	if (node->left&&node->right){
		//初始后继节点
		Node *replace = node;
		replace = node->right;
		//寻找后继节点
		while (replace->left){
			replace = replace->left;
		}
		//判断删除节点是否为根
		if (node->parent){
			//后继节点赋给删除节点
			if (node->parent->left == node){
				node->parent->left = replace;
			}
			else{
				node->parent->right = replace;
			}
		}
		else{
			root->node = node;
		}
		//保存后继节点的相关信息
		child = replace->right;
		parent = replace->parent;
		color = replace->color;

		if (parent == node){
			parent = replace;
		}
		else{
			if (child){
				child->parent = parent;
			}
			parent->left = child;

			replace->right = node->right;
			node->right->parent = replace;
		}
		replace->parent = node->parent;
		replace->color = node->color;
		replace->left = node->left;
		node->left->parent = replace;

		if (color == BLACK){
			RBTree_Delete_Fixup(root, child, parent);
		}
		free(node);
	}


	//删除节点有一个孩子
	if (node->left){
		child = node->left;
	}
	else{
		child = node->left;
	}
	//保存删除节点信息
	color = node->color;
	parent = node->parent;
	if (child){
		child->parent = parent;
	}
	if (parent){
		if (node->parent->left == node){
			node->parent->left = child;
		}
		else{
			node->parent->right = child;
		}
	}
	else{
		root->node = child;
	}
	if (color == BLACK){
		RBTree_Delete_Fixup(root, child, parent);
	}
	free(node);
}

void RBTree_Delete_Fixup(RBRoot *root, Node	*node,Node * parent){
	
	int f;
	while (node->color == BLACK && node != root->node){
		if (parent->left == node){
			f = 1;
			RBTree_Delete_Fixup_Helper(root, node, parent, f);
		}
		else{
			f = 0;
			RBTree_Delete_Fixup_Helper(root, node, parent, f);
		}
	}
}

void RBTree_Delete_Fixup_Helper(RBRoot *root, Node	*node, Node * parent,int f){
	Node *brother = NULL;
	brother = f ? parent->right : parent->left;
	if (brother->color == RED){
		brother->color = BLACK;
		parent->color = RED;
		RBTree_Left_Rotate(root, parent);
		brother = f ? parent->right : parent->left;
	}
	else{
		if (brother->left->color == BLACK&&brother->right->color == BLACK){
			brother->color = RED;
			node = parent;
			parent = node->parent;
		}
		else{
			if (brother->right->color == BLACK){
				brother->left->color = BLACK;
				brother->color = RED;
				RBTree_Right_Rotate(root, brother);
				brother = f ? parent->right : parent->left;
			}
			else{
				brother->color = parent->color;
				parent->color = BLACK;
				brother->right->color = BLACK;
				RBTree_Right_Rotate(root, parent);
				node = root->node;
			}
		}
	}
}

//创建根节点
RBRoot *RBTree_Create(){
	RBRoot *root = (RBRoot *)malloc(sizeof(RBRoot));
	root->node = NULL;
	return root;
}

//先序遍历
static void preorder(RBTree tree)
{
	if (tree != NULL)
	{
		printf("%d ", tree->key);
		preorder(tree->left);
		preorder(tree->right);
	}
}
void preorder_rbtree(RBRoot *root)
{
	if (root)
		preorder(root->node);
}

/*
* 中序遍历"红黑树"
*/
static void inorder(RBTree tree)
{
	if (tree != NULL)
	{
		inorder(tree->left);
		printf("%d ", tree->key);
		inorder(tree->right);
	}
}

void inorder_rbtree(RBRoot *root)
{
	if (root)
		inorder(root->node);
}

/*
* 后序遍历"红黑树"
*/
static void postorder(RBTree tree)
{
	if (tree != NULL)
	{
		postorder(tree->left);
		postorder(tree->right);
		printf("%d ", tree->key);
	}
}

void postorder_rbtree(RBRoot *root)
{
	if (root)
		postorder(root->node);
}

Node *IsExisting(RBRoot *root, Type key){
	if (!root){
		return NULL;
	}
	while (root->node){
		if (key > root->node->key){
			root->node = root->node->right;
		}
		else if (key < root->node->key){
			root->node = root->node->left;
		}
		else{
			return root->node;
		}
	}
	return NULL;
}

Node *RBTree_CreateNode(int key){
	Node *node = (Node *)malloc(sizeof(Node));
	if (!node) return NULL;
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;
	node->color = BLACK;
	return node;
}

int RBTree_Insert_Wrap(RBRoot *root, Type key){
	Node *node = NULL;
	if (!root){
		return -1;
	}
	if (IsExisting(root, key)){
		return -1;
	}
	if (!(node = RBTree_CreateNode(key))){
		return -1;
	}

	RBTree_Insert(root, node);
	return 0;
}

void RBTree_Delete_Wrap(RBRoot *root, Type key){
	Node *node = NULL;
	if (!root){
		return;
	}
	if (!(node = IsExisting(root, key))){
		return;
	}
	RBTree_Delete(root, node);
}
