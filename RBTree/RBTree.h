/*
红黑树是特殊的二叉搜索树
满足以下条件,则把二叉搜索树称之为红黑树
（1）每个节点或者是黑色，或者是红色。
（2）根节点是黑色。
（3）每个叶子节点（NIL）是黑色。 [注意：这里叶子节点，是指为空(NIL或NULL)的叶子节点！]
（4）如果一个节点是红色的，则它的子节点必须是黑色的。
（5）从一个节点到该节点的子孙节点的所有路径上包含相同数目的黑节点。

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

//创建根节点
RBRoot *RBTree_Create();

//创建节点
Node *RBTree_CreateNode(int key);

//查找是否存在某个节点
Node *IsExisting(RBRoot *root, Type key);

//左旋
void RBTree_Left_Rotate(RBRoot *root, Node *x);

//右旋
void RBTree_Right_Rotate(RBRoot *root, Node *y);

//插入
void RBTree_Insert(RBRoot *root, Node	*node);

//插入包裹
int RBTree_Insert_Wrap(RBRoot *root, Type key);

//修复插入
void RBTree_Insert_Fixup(RBRoot *root, Node	*node);

//修复插入辅助
RBTree_Insert_Fixup_Helper(Node *uncle, Node *parent, Node *graparent, Node *node, RBRoot *root);

//删除
void RBTree_Delete(RBRoot *root, Node *node);

//删除包裹
void RBTree_Delete_Wrap(RBRoot *root, Type key);

//修复删除
void RBTree_Delete_Fixup(RBRoot *root, Node	*node, Node * parent);

//修复删除辅助
void RBTree_Delete_Fixup_Helper(RBRoot *root, Node	*node, Node * parent,int f);

#endif
