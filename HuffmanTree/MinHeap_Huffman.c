
#include <stdio.h>
#include <stdlib.h>
#include "MinHeap_Huffman.h"



void filterup_minheap(int pos){
	//��ǰԪ��λ��
	int cur = pos;
	//��Ԫ��λ��
	int par = (cur - 1) / 2;
	//��ǰԪ�ظ���
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

		//ѡ�����Һ����н�С�Ľ��бȽ�
		if (chd < m_size - 1 && m_heap[chd].key > m_heap[chd + 1].key){
			chd++;
		}
		// ����Ԫ�ش���ֱ�ӽ���
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
	//�ж������Ƿ�����
	if (m_capacity == m_size){
		return -1;
	}
	//��������
	m_heap[m_size] = *node;

	//���ӳ���
	m_size++;

	//�ϵ�λ��
	filterup_minheap(m_size-1);

	return 0;
}


//ȡ����С�ڵ㣬��������С�ڵ�����Ԫ�أ�����������С��
HuffmanNode *dump_from_minheap(){
	int  index = -1;
	HuffmanNode *minNode = NULL;

	//����������Ԫ��
	if (m_size == 0){
		return -1;
	}
	
	if ((minNode = (HuffmanNode *)malloc(sizeof(HuffmanNode))) == NULL){
		return minNode;
	}
	*minNode = m_heap[0];
	//�����һ��Ԫ�ظ�����Ҫɾ����Ԫ��
	m_heap[0] = m_heap[--m_size];

	//�µ�
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