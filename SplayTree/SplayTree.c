#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SplayTree.h"

SplayTree *Splay_SplayTree(SplayTree *tree, DataType key){
	//��������һ���ڵ��������ʲô?
	SplayTree node, *temp,*successor,*precursor;
	if (tree == NULL){
		return tree;
	}
	successor = precursor = &node;
	node.left = NULL;
	node.right = NULL;
	//����
	for (;;){
		if (key < tree->key){
			if (tree->left == NULL){
				//�Ѿ��ҵ�Ҷ�ӽڵ���,��δ�ҵ�,ֻ�ܽ�����
				break;
			}
			if (key < tree->left->key){
				//��ת
				temp = tree->left;
				tree->left = temp->right;
				temp->right = tree;
				tree = temp;
				//���ڵ㷢���仯,�ٴ��ж�����Ƿ��нڵ�,û�о�ֱ�ӽ���
				if (tree->left == NULL){
					break;
				}
			}
			//����
			//right �� node��ǰ��
			precursor->left = tree;
			precursor = tree;
			//����������
			tree = tree->left;
		}//�������
		else if (key > tree->key){
			if (tree->right == NULL){
				break;
			}
			if (key > tree->right->key){
				temp = tree->right;
				tree->right = temp->left;
				temp->left = tree;
				tree = temp;
				if (tree->right == NULL){
					break;
				}
			}
			successor->right = tree;
			//left��node ���
			successor = tree;
			tree = tree->right;
		}
		else{
			break;
		}
	}
	//node ��̵������� ���� Ŀ��ڵ��������
	successor->right = tree->left;
	//node ǰ����������  ���� Ŀ��ڵ��������
	precursor->left = tree->right;
	//tree ��ת���ɸ��Ľڵ�
	//tree��ǰ�� ����node ���
	tree->left = node.right;
	//tree�ĺ�� ���� node ǰ��
	tree->right = node.left;
	return tree;
}

SplayTree *Create_SplayNode(DataType key){
	SplayTree *node = NULL;
	if ((node = (SplayTree *)malloc(sizeof(SplayTree))) == NULL){
		return node;
	}
	node->left = NULL;
	node->right = NULL;
	node->key = key;
	return node;
}

void PreorderTraverse(SplayTree *tree){
	if (tree == NULL){
		return;
	}
	printf("%d ", tree->key);
	PreorderTraverse(tree->left);
	PreorderTraverse(tree->right);
}

void InorderTraverse(SplayTree *tree){
	if (tree == NULL){
		return;
	}
	InorderTraverse(tree->left);
	printf("%d ", tree->key);
	InorderTraverse(tree->right);
}

void PostorderTraverse(SplayTree *tree){
	if (tree == NULL){
		return;
	}
	PostorderTraverse(tree->left);
	PostorderTraverse(tree->right);
	printf("%d ", tree->key);
}
SplayTree *Find_SpalyNode(SplayTree *tree, DataType key){
	if (tree == NULL || tree->key == key){
		return tree;
	}
	if (!tree->left&&!tree->right){
		return tree->left;
	}
	if (key < tree->key){
		return Find_SpalyNode(tree->left, key);
	}
	else if (key > tree->key){
		return Find_SpalyNode(tree->right, key);
	}
	return tree;
}

SplayTree *Insert_SplayTree(SplayTree *tree, SplayTree *node){
	SplayTree *insert_point = NULL;
	if (tree == NULL){
		tree = node;
	}
	while (tree){
		insert_point = tree;
		if (node->key < tree->key){
			tree = tree->left;
		}
		else if (node->key > tree->key){
			tree = tree->right;
		}
	}
	if (node->key < insert_point->key){
		insert_point->left = node;
	}
	else{
		insert_point->right = node;
	}
	return tree;
}

SplayTree *Wrap_Insert_SplayTree(SplayTree *tree, DataType key){
	SplayTree *node = NULL;
	if ( (node = Find_SpalyNode(tree,key) ) != NULL){
		return node;
	}
	node = Create_SplayNode(key);
	Insert_SplayTree(tree,node);
	tree = Splay_SplayTree(tree,node->key);
	return tree;
}


SplayTree *Delete_SplayTree(SplayTree *tree, DataType key){
	SplayTree *t = NULL;
	if (tree->key != key){
		tree = Splay_SplayTree(tree, key);
	}
	
	if (tree->left){
		t = tree->left;
		t->right = tree->right;
	}
	else{
		t = tree->right;
	}
	free(tree);
	return t;
}


SplayTree *Wrap_Delete_SplayTree(SplayTree *tree, DataType key){
	SplayTree *node = NULL;
	if (tree == NULL){
		return tree;
	}
	if ((node = Find_SpalyNode(tree, key)) != NULL){
		tree = Delete_SplayTree(tree, key);
	}
	return tree;
}

void Print_SplayTree(SplayTree *tree){
	if (tree == NULL){
		return ;
	}
	if (tree->left){
		printf("the left child of the %d is %d:\n", tree->key, tree->left->key);
	}
	if (tree->right){
		printf("the right child of the %d is %d\n", tree->key, tree->right->key);
	}
	Print_SplayTree(tree->left);
	Print_SplayTree(tree->right);
	return;
}

void Destory_SplayTree(SplayTree *tree){
	if (tree == NULL){
		return ;
	}
	Destory_SplayTree(tree->left);
	Destory_SplayTree(tree->right);
	free(tree);
	return;
}