#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BinTree.h"

// 先序遍历
void Preorder(BiTree root){
	if (root != NULL){
		printf(" %d", root->data);
		Preorder(root->lchild);
		Preorder(root->rchild);
	}
}

//中序遍历
void Infixorder(BiTree root){
	if (root != NULL){
		Infixorder(root->lchild);
		printf(" %d", root->data);
		Infixorder(root->rchild);
	}
}

//后续遍历
void Postorder(BiTree root){
	if (root != NULL){
		Postorder(root->lchild);
		Postorder(root->rchild);
		printf(" %d", root->data);
	}
}

//了解递归输入的数据,便于理解递归建立树
BiTree CreateReCur_BinTree(){
	BiTree pbnode;
	int data;
	printf("data: ");
	scanf("%d", &data);
	//叶子节点的孩子用0代替
	if (data == 0){
		pbnode = NULL;
	}else{
		pbnode = (BiTree)malloc(sizeof(BiNode));
		if (pbnode == NULL){
			return pbnode;
		}
	
		pbnode->lchild = CreateReCur_BinTree();
		pbnode->rchild = CreateReCur_BinTree();
		//与写入顺序无关
		pbnode->data = data;
	}
	return pbnode;
}

int main(){
	
	BiTree root = CreateReCur_BinTree();
   printf("\nPreorder traverse :");
   Preorder(root);
   printf("\nInfixorder traverse :");
   Infixorder(root);
   printf("\nPostorder traverse :");
   Postorder(root);
   printf("\n");
   system("pause");
   return 0;
}
