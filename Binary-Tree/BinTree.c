#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkList.h"
#include "LinkStack.h"
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
BiTree GoLeftLeaf(LinkStack *stack ,BiTree t){
	if (t == NULL){
		return t;
	}
	//存储所有有左孩子的节点
	while (t->lchild){
		//入栈
		Push(stack, t);
		//继续向左走
		t = t->lchild;
	}
	//返回没有左孩子的节点
	return t;
		 
}
//中序非递归
void NonRecur_Infixorder(BiTree root){
	LinkStack *stack = Create_LinkStack();
	BiTree t = GoLeftLeaf(stack, root);
	while (t){
		printf(" %d", t->data);
		if (t->rchild){
			t= GoLeftLeaf(stack, t->rchild);
		}
		//在没有右子树的清空下,判断栈中是否还有双亲
		else if (Get_Length(stack)){
			t = Top(stack);
			//往双亲关系上找
			Pop(stack);
		}
		else{
			t = NULL;
		}
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

//了解递归输入的数据,便于理解递归建立树,
BiTree CreateReCur_BinTree(){
	BiTree pbnode;
	int data;
	printf("data: ");
	scanf("%d", &data);
	//建立树的结束条件是输入数据为0;
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

//计算树的叶子
void CountLeafNum(BiTree t,int *sum){

	//首先校验参数
	if (t == NULL){
		return ;
	}

	if (t->lchild == NULL && t->rchild == NULL){
		//++优先级高
		(*sum)++;
	}

	if (t->lchild){
		CountLeafNum(t->lchild, sum);
	}

	if (t->rchild){
		CountLeafNum(t->rchild, sum);
	}

	return;

}
//计算树的深度
int Get_Depth(BiTree t){
	
	int depthleft = 0;
	int depthright = 0;
	int depth = 0;
	int max = 0;
	//每个节点都可以看作双亲节点
	//以叶子为起点,我们先跑到起点.
	
	if (t == NULL){

		return depth;
	}
	//拿左子树的深度
	depthleft = Get_Depth(t->lchild);
	//拿右子树的深度
	depthright = Get_Depth(t->rchild);
	max = depthleft > depthright ? depthleft : depthright;
	return max + 1;
	
}
//copy二叉树
BiTree CopyTree(BiTree t){
	
	BiTree newlchild, newrchild, newnode;
	if (t == NULL){
		return t;
	}
	//左边
	//叶子节点时,回溯,则会拿到各个新建的孩子节点,
	if (t->lchild){
		newlchild = CopyTree(t->lchild);
	}//叶子节点的孩子为空
	else{
		newlchild = NULL;
	}
	//右边
	if (t->rchild){
		newrchild = CopyTree(t->rchild);
	}
	else{
		newrchild = NULL;
	}
	//从叶子节点开始建立关系
	newnode = (BiTree)malloc(sizeof(BiNode));
	newnode->lchild = newlchild;
	newnode->rchild = newrchild;
	newnode->data = t->data;
	return newnode;
}

int main(){ 
	int Leafs = 0;
	int depth = 0;
	BiTree root = CreateReCur_BinTree();
	BiTree copyTree = CopyTree(root);
	CountLeafNum(root, &Leafs);
	printf("the num of leafs are %d\n", Leafs);
	depth = Get_Depth(root);
	printf("the depth of tree is %d\n", depth);
	printf("\nPreorder traverse :");
	Preorder(root);
	printf("\nInfixorder traverse :");
	Infixorder(root);
	printf("\nNonRecur_Infixorder traverse :");
	NonRecur_Infixorder(root);
	printf("\nPostorder traverse :");
	Postorder(root);
	printf("\n");
	printf("---------------------------------copytree-------------------------------- - ");
	printf("\nPreorder traverse :");
	Preorder(copyTree);
	printf("\n");
	system("pause");
	return 0;
	}
