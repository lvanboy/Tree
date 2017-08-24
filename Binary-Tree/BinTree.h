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
//generate binary - tree
BiTree CreateReCur_BinTree();


#endif
