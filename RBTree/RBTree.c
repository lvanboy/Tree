#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "RBTree.h"


//����ת
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

//����ת
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

//����ڵ�
void RBTree_Insert(RBRoot *root, Node	*node){
	//�����
	Node *y = NULL;
	Node *x = root->node;
	while (x){
		//��ʼ��������Ǹ�
		y = x;
		if (node->key > x->key){
			x = x->right;
		}
		else{
			x = x->left;
		}		
	}
 	node->parent = y;
	//xΪ����yΪnull��nodeֱ�Ӹ���
	if (!y){
		root->node = node;
	}//�����жϵ�ǰ�ڵ���Ը��ڵ��λ��
	else{
		if (node->key < y->key){
			y->left = node;
		}
		else{
			y->right = node;
		}
	}
	//Ĭ�������ڵ��Ǻ�ɫ
	node->color = RED;
	RBTree_Insert_Fixup(root, node);
}

//�����޸�����
void  RBTree_Insert_Fixup_Helper(Node *uncle, Node *parent, Node *graparent, Node *node, RBRoot *root,int f ,int *t){
	Node *relativePos = NULL;
	//����ڵ��λ�ã�ȡ���ڵ�ǰ����Ը��ڵ��λ��
	if (f){
		relativePos = node->parent->right;
	}
	else{
		
		relativePos = node->parent->left;
	}//����ڵ�������Ǻ�ɫ
	if (uncle&&uncle->color == RED){
		parent->color = BLACK;
		uncle->color = BLACK;
		graparent->color = RED;
		node = graparent;
		return;
	}//�����ǣ�����ڵ㲻���� ���� ����ڵ��Ǻ�ɫ����Ϊ������Ҳ��һ������ĺ�ɫ
	/*else if (uncle&&uncle->color == BLACK){*/

		if (relativePos == node){
			Node temp;
			*t = parent;
			//�����Ƿ�����������������parent��node�ڵ�λ�ûᷢ������������˵�����߼���ϵ������parent��node�ڵ�洢����ԭ���Ĺ�ϵ��������и��¡�
			f ? RBTree_Left_Rotate(root, parent) : RBTree_Right_Rotate(root, parent);
			//������ַ���ﲻ���ڵ㽻����Ч����ֻ�аѵ�ַ�����ֵ�������ǽṹ�����ཻ�����ſ��ԡ�
			/*temp = *parent;
			*parent = *node;
			*node = temp;*/
			parent = node;
		}
		
		//��ƥ���������if,��һ��ѭ��һ����ִ�������д��룬����ʡȥelse�����õȵ��´�ѭ����ֱ����
			parent->color = BLACK;
			graparent->color = RED;
			f ? RBTree_Right_Rotate(root, graparent) : RBTree_Left_Rotate(root, graparent);

	//}
	return;
}

//�����޸�
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
			//����ڵ�Ϊ�գ�Ҳ�Ǻ�ɫ
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

//ɾ���ڵ�
void RBTree_Delete(RBRoot *root, Node *node){
	Node *child, *parent;
	int color;
	//ɾ���ڵ���2������
	if (node->left&&node->right){
		//��ʼ��̽ڵ�
		Node *replace = node;
		replace = node->right;
		//Ѱ�Һ�̽ڵ�
		while (replace->left){
			replace = replace->left;
		}
		//�ж�ɾ���ڵ��Ƿ�Ϊ��
		if (node->parent){
			//��̽ڵ㸳��ɾ���ڵ�
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
		//�����̽ڵ�������Ϣ
		child = replace->right;
		parent = replace->parent;
		color = replace->color;
		//������������,��̵ĸ��ײŻ���ڵ�ǰ�ڵ�
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


	//ɾ���ڵ���һ������
	if (node->left){
		child = node->left;
	}
	else{
		child = node->left;
	}
	//����ɾ���ڵ���Ϣ
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

//ɾ���޸�
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

//ɾ���޸�����
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

//�������ڵ�
RBRoot *RBTree_Create(){
	RBRoot *root = (RBRoot *)malloc(sizeof(RBRoot));
	root->node = NULL;
	return root;
}

//�������
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
* �������"�����"
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
* �������"�����"
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

//�ж�keyֵ�ڵ��Ƿ����
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

//����һ���ڵ�
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

//�������
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

//ɾ������
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

//��ӡ��ϵ
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

//������
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



