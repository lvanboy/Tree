
#include <stdio.h>
#include <stdlib.h>
#include "BSTree.h"

//����һ���ڵ�
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

//Ѱ��ĳ��ֵ
BSTree Search_BSTree(BSNode *node, DataType val){
	if (node == NULL || val == node->val){
		return node;
	}
	if (!node->left && !node->right){
		return node->left;
	}
	//����ȵ�ǰ�ڵ�С,����������
	if (val < node->val){
		return Search_BSTree(node->left, val);
	}//����,����������
	else{
		return Search_BSTree(node->right, val);
	}
}

//�ҵ����ֵ
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

//�ҵ���Сֵ
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



//����ڵ�
int Insert_BSNode(BSNode *root, BSNode *node){
	BSNode *insert_point = NULL;
	if (root == NULL || node == NULL){
		return 0;
	}
	//Ѱ�Ҳ����
	while (root){
		//Ĭ�ϴӸ���ʼѰ��
		insert_point = root;
		if (node->val < root->val){
			root = root->left;
		}
		else if (node->val > root->val){
			root = root->right;
		}
	}
	//������ֱ�ӽ��������Ϊ����
	if (insert_point == NULL){
		root = node;
	}
	node->parent = insert_point;
	//�ж��½ڵ��ڲ�������߻����ұ�,��������ϵ.
	if (node->val < insert_point->val){
		insert_point->left = node;
	}
	else{
		insert_point->right = node;
	}
	return 1;
}

//����ڵ�֮ǰҪ�½��ڵ�,�����ǰ�����,ֱ�������ﴴ���ڵ�
BSTree WrapInsert_BSNode(BSNode *root, DataType nodeVal){
	BSNode *node = NULL;
	//����Ľڵ�ֵ����
	if (Search_BSTree(root, nodeVal) != NULL){
		return NULL;
	}
	//�ڵ㴴�����ɹ�
	if ((node = Create_BSNode( nodeVal ))== NULL){
		return NULL;
	}
	Insert_BSNode(root, node);
	return node;
}

//�������
void preorder(BSTree root){
	if (root == NULL){
		return ;
	}
	printf(" %d", root->val);
	preorder(root->left);
	preorder(root->right);
}

//�������
void Inorder(BSTree root){
	if (root == NULL){
		return;
	}
	Inorder(root->left);
	printf(" %d", root->val);
	Inorder(root->right);
}

//Ѱ�ҽڵ��ǰ��
BSTree predecessor(BSNode *node){
	return;
}

//Ѱ�ҽڵ�ĺ��
BSTree successor(BSNode *node){
	return;
}

//��һ�׹���,��ʶ����,�Һ���,�͸�
//��ӡ�ڵ�֮��Ĺ�ϵ
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

//���ٶ���������
void Destroy_BSTree(BSTree root){
	if (root == NULL){
		return;	
	}
	Destroy_BSTree(root->left);
	Destroy_BSTree(root->right);
	free(root);
}
