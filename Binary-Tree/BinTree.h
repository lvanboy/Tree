#ifndef _BINTREE_H_
#define _BINTREE_H_
//the node of binary-tree: binary-link-list-structure
typedef int ElemData;
typedef struct BiNode{
	ElemData data;
	struct BiNode *lchild, *rchild;
}BiNode,*BiTree;


//recursion traverse
void Preorder(BiTree root);
void Infixorder(BiTree root);
void Postorder(BiTree root);
BiTree GoLeftLeaf(LinkStack *stack, BiTree t);
//generate binary - tree
BiTree CreateReCur_BinTree();
//statistic the num of leaf
void CountLeafNum(BiTree t,int *sum);
//get the depth of tree 
int Get_Depth(BiTree t);
//copy the tree.
BiTree CopyTree(BiTree t);


#endif

