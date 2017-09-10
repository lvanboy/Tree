#ifndef _SPLAY_TREE_H_
#define _SPLAY_TREE_H_
//节点 结构
typedef int DataType;
typedef struct SplayTree{
	DataType key;
	struct SplayTree *left;
	struct SplayTree *right;
}SplayTree;

//旋转某个节点为根
SplayTree *Splay_SplayTree(SplayTree *tree,DataType key);

//创建一个节点
SplayTree *Create_SplayNode(DataType key);

//先序遍历
void PreorderTraverse(SplayTree *tree);

//中序遍历
void InorderTraverse(SplayTree *tree);

//后序遍历
void PostorderTraverse(SplayTree *tree);

//查找一个节点
SplayTree *Find_SpalyNode(SplayTree *tree, DataType key);

//插入节点
SplayTree *Insert_SplayTree(SplayTree *tree, SplayTree *node);

//插入包裹层
SplayTree *Wrap_Insert_SplayTree(SplayTree *tree, DataType key);

//删除节点
SplayTree *Delete_SplayTree(SplayTree *tree, DataType key);

//删除包裹层
SplayTree *Wrap_Delete_SplayTree(SplayTree *tree, DataType key);

//打印关系
void Print_SplayTree(SplayTree *tree);

//销毁树
void Destory_SplayTree(SplayTree *tree);
#endif
