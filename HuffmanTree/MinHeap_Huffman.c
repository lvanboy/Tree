
#include <stdio.h>
#include <stdlib.h>
#include "MinHeap_Huffman.h"



void filterup_minheap(int pos){
	//当前元素位置
	int cur = pos;
	//父元素位置
	int par = (cur - 1) / 2;
	//当前元素副本
	HuffmanNode temp = m_heap[cur];
	while (cur > 0){
		if (m_heap[par].key <= temp.key){
			break;
		}
		else{
			m_heap[cur] = m_heap[par];
			cur = par;
			par = (par - 1) / 2;
		}
	}
	m_heap[cur] = temp;
	return;
}



void filterdown_minheap(int pos){
	int cur = pos;
	int chd = pos * 2 + 1;
	HuffmanNode temp = m_heap[cur];

	while (chd <= m_size -1 ){

		//选择左右孩子中较小的进行比较
		if (chd < m_size - 1 && m_heap[chd].key > m_heap[chd + 1].key){
			chd++;
		}
		// 孩子元素大，则直接结束
		if (temp.key <= m_heap[chd].key){
			break;
		}
		else{
			m_heap[cur] = m_heap[chd];
			cur = chd;
			chd = chd * 2 + 1;
		}
	}
	m_heap[cur] = temp;
	return;
}

int insert_minheap(HuffmanNode *node){
	//判断容器是否已满
	if (m_capacity == m_size){
		return -1;
	}
	//放入容器
	m_heap[m_size] = *node;

	//增加长度
	m_size++;

	//上调位置
	filterup_minheap(m_size-1);

	return 0;
}


//取得最小节点，并将除最小节点以外元素，重新生成最小堆
HuffmanNode *dump_from_minheap(){
	int  index = -1;
	HuffmanNode *minNode = NULL;

	//容器必须有元素
	if (m_size == 0){
		return -1;
	}
	
	if ((minNode = (HuffmanNode *)malloc(sizeof(HuffmanNode))) == NULL){
		return minNode;
	}
	*minNode = m_heap[0];
	//用最后一个元素覆盖需要删除的元素
	m_heap[0] = m_heap[--m_size];

	//下调
	filterdown_minheap(0);

	return minNode;
}

void print_minheap(){
	for (int i = 0; i < m_size; i++){
		printf("%d ", m_heap[i].key);
	}
	printf("\n");
}

void Create_minheap(Type a[],int size){
	
	m_size = 0;
	m_capacity = size;
	m_heap = (HuffmanNode *)malloc(sizeof(HuffmanNode)* size);

	for (int i = 0; i < size; i++){
		m_heap[i].key = a[i];
		m_heap[i].parent = m_heap[i].left = m_heap[i].right = NULL;
		insert_minheap(&m_heap[i]);
	}
}

void Destroy_minheap(){
	free(m_heap);
	m_size = 0;
	m_capacity = 0;
}