/*
�����������Ķ���������
������������,��Ѷ�����������֮Ϊ�����
��1��ÿ���ڵ�����Ǻ�ɫ�������Ǻ�ɫ��
��2�����ڵ��Ǻ�ɫ��
��3��ÿ��Ҷ�ӽڵ㣨NIL���Ǻ�ɫ�� [ע�⣺����Ҷ�ӽڵ㣬��ָΪ��(NIL��NULL)��Ҷ�ӽڵ㣡]
��4�����һ���ڵ��Ǻ�ɫ�ģ��������ӽڵ�����Ǻ�ɫ�ġ�
��5����һ���ڵ㵽�ýڵ������ڵ������·���ϰ�����ͬ��Ŀ�ĺڽڵ㡣

*/

#ifndef _RBTREE_H_
#define _RBTREE_H_
#define BLACK 1
#define RED 0

typedef  int Type;
typedef struct RBTreeNode{
	unsigned char color;
	Type key;
	struct RBTreeNode *left;
	struct RBTreeNode *right;
	struct RBTreeNode *parent;
}Node,*RBTree;

typedef struct TRBRoot{
	Node *node;
}RBRoot;

//�������ڵ�
RBRoot *RBTree_Create();

//�����ڵ�
Node *RBTree_CreateNode(int key);

//�������
static void inorder(RBTree tree);

void inorder_rbtree(RBRoot *root);

//�����Ƿ����ĳ���ڵ�
Node *IsExisting(RBRoot *root, Type key);

//����
void RBTree_Left_Rotate(RBRoot *root, Node *x);

//����
void RBTree_Right_Rotate(RBRoot *root, Node *y);

//�������
int RBTree_Insert_Wrap(RBRoot *root, Type key);

//����
void RBTree_Insert(RBRoot *root, Node	*node);

//�޸�����
void RBTree_Insert_Fixup(RBRoot *root, Node	*node);

//�޸����븨��
 void RBTree_Insert_Fixup_Helper(Node *uncle, Node *parent, Node *graparent, Node *node, RBRoot *root,int f);

 //ɾ������
 void RBTree_Delete_Wrap(RBRoot *root, Type key);

//ɾ��
void RBTree_Delete(RBRoot *root, Node *node);

//�޸�ɾ��
void RBTree_Delete_Fixup(RBRoot *root, Node	*node, Node * parent);

//�޸�ɾ������
int RBTree_Delete_Fixup_Helper(RBRoot *root, Node	*node, Node * parent,int f);

//��ӡ��ϵ
void RBTree_Print_Relationship(Node * root);

//������
void RBTree_Destroy(RBRoot *root);

#endif
