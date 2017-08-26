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

BSTree Create_BSNode(BSNode *left, BSNode *right, BSNode *parent, DataType val);
BSTree Search_BSTree(BSNode *node, DataType val);

#endif