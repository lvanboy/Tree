#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "RBTree.h"


//左旋转
void RBTree_Left_Rotate(RBRoot *root, Node *x){
	Node *y = x->right;
	if (!y){
		return;
	}
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

//右旋转
void RBTree_Right_Rotate(RBRoot *root, Node *y){
	Node *x = y->left;
	if (!x){
		return;
	}

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

//插入节点
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
	//x为根，y为null，node直接给根
	if (!y){
		root->node = node;
	}//否则判断当前节点相对父节点的位置
	else{
		if (node->key < y->key){
			y->left = node;
		}
		else{
			y->right = node;
		}
	}
	//默认新增节点是红色
	node->color = RED;
	RBTree_Insert_Fixup(root, node);
}

//插入修复辅助
void  RBTree_Insert_Fixup_Helper(Node *uncle, Node *parent, Node *graparent, Node *node, RBRoot *root,int f ,int *t){
	Node *relativePos = NULL;
	//叔叔节点的位置，取决于当前的相对父节点的位置
	if (f){
		relativePos = node->parent->right;
	}
	else{
		
		relativePos = node->parent->left;
	}//叔叔节点存在且是红色
	if (uncle&&uncle->color == RED){
		parent->color = BLACK;
		uncle->color = BLACK;
		graparent->color = RED;
		node = graparent;
		return;
	}//反面是，叔叔节点不存在 或者 叔叔节点是黑色，因为不存在也是一种特殊的黑色
	/*else if (uncle&&uncle->color == BLACK){*/

		if (relativePos == node){
			Node temp;
			*t = parent;
			//无论是发生左旋还是右旋，parent和node节点位置会发生交换（这里说的是逻辑关系），但parent和node节点存储还是原来的关系，下面进行更新。
			f ? RBTree_Left_Rotate(root, parent) : RBTree_Right_Rotate(root, parent);
			//交换地址，达不到节点交换的效果，只有把地址里面的值（可以是结构）互相交换，才可以。
			/*temp = *parent;
			*parent = *node;
			*node = temp;*/
			parent = node;
		}
		
		//当匹配了上面的if,下一次循环一定是执行这三行代码，这里省去else，不用等到下次循环，直接做
			parent->color = BLACK;
			graparent->color = RED;
			f ? RBTree_Right_Rotate(root, graparent) : RBTree_Left_Rotate(root, graparent);

	//}
	return;
}

//插入修复
void RBTree_Insert_Fixup(RBRoot *root, Node	*node){
	Node *parent = NULL, *graparent = NULL,*uncle = NULL;
	int  f = 0;
	int  f1 = 0;
	int *temp = &f1;
	while ((parent = node->parent)&&parent->color == RED){
		graparent = parent->parent;
		if (!graparent){
			return;
		}
		if (graparent->left == parent){
			f = 1;
			uncle = graparent->right;
			//叔叔节点为空，也是黑色
			RBTree_Insert_Fixup_Helper(uncle, parent, graparent, node, root,f,temp);
			if (*temp){
				node = *temp;
				*temp = 0;
			}
		}
		else{
			uncle = graparent->left;
			f = 0;
			RBTree_Insert_Fixup_Helper(uncle, parent, graparent, node, root,f,temp);
			if (*temp){
				node = *temp;
				*temp = 0;
			}
		}
	}
	root->node->color = BLACK;
	return;
}

//删除节点
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
			root->node = replace;
		}
		//保存后继节点的相关信息
		child = replace->right;
		parent = replace->parent;
		color = replace->color;
		//不存在右子树,后继的父亲才会等于当前节点
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
		return;
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

//删除修复
void RBTree_Delete_Fixup(RBRoot *root, Node	*node,Node * parent){
	
	int f;
	int res = 0;
	while (node->color == BLACK && node != root->node){
		if (parent->left == node){
			f = 1;
			res = RBTree_Delete_Fixup_Helper(root, node, parent, f);
			if (res == 2){
				break;
			}
		}
		else{
			f = 0;
			res = RBTree_Delete_Fixup_Helper(root, node, parent, f);
			if (res == 2){
				break;
			}
		}
	}
}

//删除修复辅助
int RBTree_Delete_Fixup_Helper(RBRoot *root, Node	*node, Node * parent,int f){
	Node *brother = NULL;
	Node *temp = NULL;
	Node *temp01 = NULL;
	brother = f ? parent->right : parent->left;
	if (brother->color == RED){
		brother->color = BLACK;
		parent->color = RED;
		f?RBTree_Left_Rotate(root, parent) : RBTree_Right_Rotate(root, parent);
		brother = f ? parent->right : parent->left;
	}
	else{
		if (brother->left->color == BLACK&&brother->right->color == BLACK){
			brother->color = RED;
			node = parent;
			parent = node->parent;
		}
		else{
			temp = f ? brother->right : brother->left;
			temp01 = f ? brother->left : brother->right;
			if (temp->color == BLACK){
				temp01->color = BLACK;
				brother->color = RED;
				f ? RBTree_Right_Rotate(root, brother) : RBTree_Left_Rotate(root, brother);
				brother = f ? parent->right : parent->left;
			}
			else{
				brother->color = parent->color;
				parent->color = BLACK;
				temp->color = BLACK;
				f ? RBTree_Left_Rotate(root, parent) : RBTree_Right_Rotate(root, brother);
				node = root->node;
				f = 2;
				return f;
			}
		}
	}
	return 0;
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

//判断key值节点是否存在
Node *IsExisting(RBRoot *root, Type key){
	Node *node = root->node;
	if (!node){
		return NULL;
	}
	while (node){
		if (key > node->key){
			node = node->right;
		}
		else if (key < node->key){
			node = node->left;
		}
		else{
			return node;
		}
	}
	return NULL;
}

//创建一个节点
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

//插入包裹
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

//删除包裹
void RBTree_Delete_Wrap(RBRoot *root, Type key){
	Node *node = NULL;
	if (!root){
		return;
	}
	if (!(node = IsExisting(root, key))){
		return;
	}
	RBTree_Delete(root, node);
	return;
}

//打印关系
void RBTree_Print_Relationship(Node * node){

	if (!node){
		return;
	}
	if (node->left){
		printf("the left child of %d node of RBTree(%c) is %d\n", node->left->parent->key, node->left->color ? 'B' : 'R', node->left->key);
	}
	if (node->right){
		printf("the right child of %d node of RBTree(%c) is %d\n", node->right->parent->key, node->right->color ? 'B' : 'R', node->right->key);
	}
	RBTree_Print_Relationship(node->left);
	RBTree_Print_Relationship(node->right);

	return;
}

//销毁树
void RBTree_Destroy(RBRoot *root){
	Node *node = root->node;
	if (!node){
		return;
	}
	while (node){
		if (node->left){
			node = node->left;
		}
		else if (node->right){
			node = node->right;
		}
		else{
			free(node);
		}
	}
}



