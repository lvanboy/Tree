#ifndef _BANARY_SEARCH_TREE_H_
#define _BANARY_SEARCH_TREE_H_

//二叉搜索树节点结构是三叉链表
typedef int DataType;
typedef struct BSTreeNode{
	DataType val;
	struct BSTreeNode *left;
	struct BSTreeNode *right;
	struct BSTreeNode *parent;
}BSNode,*BSTree;


//创建一个节点
BSTree Create_BSNode(DataType val);

//寻找某个值
BSTree Search_BSTree(BSNode *node, DataType val);

//找到最大值
BSTree GetMaximum_BSNode(BSNode *root);

//找到最小值
BSTree GetMinimum_BSNode(BSNode *root);

//插入节点
int Insert_BSNode(BSNode *root, BSNode *node); 

//插入节点包裹层
BSTree WrapInsert_BSNode(BSNode *root, DataType nodeVal);

//寻找节点的前驱
BSTree predecessor(BSNode *node);

//寻找节点的后继
BSTree successor(BSNode *node);

//删除节点
BSTree Delete_BSTree(BSTree root, BSNode *node);

//删除包裹层
BSTree WrapDelete_BSTree(BSTree root, BSNode *node);

//打印节点之间的关系
void printRelation(BSNode *child, BSNode *parent, int direction);

//销毁二叉搜索树
void Destroy_BSTree(BSTree root);

//先序遍历
void preorder(BSTree root);

//中序遍历
void Inorder(BSTree root);
#endif