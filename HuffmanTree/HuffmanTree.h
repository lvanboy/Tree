#ifndef _HUFFMAN_TREE_H_
#define _HUFFMAN_TREE_H_

typedef int Type;

typedef struct Huffman{
	Type key;
	struct Huffman *left;
	struct Huffman *right;
	struct Huffman *parent;
}HuffmanNode,Huffman,*HuffmanTree;
HuffmanNode *m_heap;
int m_size;
int m_capacity;

//中序遍历
void inorder_traverser(HuffmanTree tree);

//创建Huffman 节点
HuffmanNode *Create_HuffmanNode(Type key, HuffmanNode *left, HuffmanNode *right, HuffmanNode *parent);

//创建 Huffman 树
Huffman *Create_Huffman(Type a[],int size);

//销毁 Huffman 树
Huffman *Destroy_Huffman(HuffmanTree tree);

//打印 Huffman 树
void Print_Huffman(HuffmanTree tree);

#endif // !_HUFFMAN_TREE_H_
