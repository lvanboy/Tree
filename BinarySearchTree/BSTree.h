#ifndef _BANARY_SEARCH_TREE_H_
#define _BANARY_SEARCH_TREE_H_

//�����������ڵ�ṹ����������
typedef int DataType;
typedef struct BSTreeNode{
	DataType val;
	struct BSTreeNode *left;
	struct BSTreeNode *right;
	struct BSTreeNode *parent;
}BSNode,*BSTree;


//����һ���ڵ�
BSTree Create_BSNode(DataType val);

//Ѱ��ĳ��ֵ
BSTree Search_BSTree(BSNode *node, DataType val);

//�ҵ����ֵ
BSTree GetMaximum_BSNode(BSNode *root);

//�ҵ���Сֵ
BSTree GetMinimum_BSNode(BSNode *root);

//����ڵ�
int Insert_BSNode(BSNode *root, BSNode *node); 

//����ڵ������
BSTree WrapInsert_BSNode(BSNode *root, DataType nodeVal);

//Ѱ�ҽڵ��ǰ��
BSTree predecessor(BSNode *node);

//Ѱ�ҽڵ�ĺ��
BSTree successor(BSNode *node);

//ɾ���ڵ�
BSTree Delete_BSTree(BSTree root, BSNode *node);

//ɾ��������
BSTree WrapDelete_BSTree(BSTree root, BSNode *node);

//��ӡ�ڵ�֮��Ĺ�ϵ
void printRelation(BSNode *child, BSNode *parent, int direction);

//���ٶ���������
void Destroy_BSTree(BSTree root);

//�������
void preorder(BSTree root);

//�������
void Inorder(BSTree root);
#endif