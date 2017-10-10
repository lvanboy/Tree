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

//�������
void inorder_traverser(HuffmanTree tree);

//����Huffman �ڵ�
HuffmanNode *Create_HuffmanNode(Type key, HuffmanNode *left, HuffmanNode *right, HuffmanNode *parent);

//���� Huffman ��
Huffman *Create_Huffman(Type a[],int size);

//���� Huffman ��
Huffman *Destroy_Huffman(HuffmanTree tree);

//��ӡ Huffman ��
void Print_Huffman(HuffmanTree tree);

#endif // !_HUFFMAN_TREE_H_
