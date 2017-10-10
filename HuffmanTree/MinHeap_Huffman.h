#include "HuffmanTree.h"
#ifndef _MINHEAP_HUFFMAN_H_
#define _MINHEAP_HUFFMAN_H_

//�ϵ�
void filterup_minheap(int pos);

//�µ�
void filterdown_minheap(int pos);

//����
int insert_minheap(HuffmanNode *node);

//ȡ����СԪ�أ���ɾ����СԪ��
HuffmanNode *dump_from_minheap();

//��ӡ��С��
void print_minheap();

//������С��
void Create_minheap(Type a[], int size);

//������С��
void Destroy_minheap();

#endif // !_MINHEAP_HUFFMAN_H_
