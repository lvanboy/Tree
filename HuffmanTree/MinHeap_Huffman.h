#include "HuffmanTree.h"
#ifndef _MINHEAP_HUFFMAN_H_
#define _MINHEAP_HUFFMAN_H_

//上调
void filterup_minheap(int pos);

//下调
void filterdown_minheap(int pos);

//插入
int insert_minheap(HuffmanNode *node);

//取得最小元素，并删除最小元素
HuffmanNode *dump_from_minheap();

//打印最小堆
void print_minheap();

//创建最小堆
void Create_minheap(Type a[], int size);

//销毁最小堆
void Destroy_minheap();

#endif // !_MINHEAP_HUFFMAN_H_
