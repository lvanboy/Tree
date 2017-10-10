#include <stdio.h>
#include <stdlib.h>
#include "HuffmanTree.h"
#include "MinHeap_Huffman.h"

void inorder_traverser(HuffmanTree tree){
	if (!tree){
		return;
	}
	if (tree->left){
		inorder_traverser(tree->left);
	}
	printf("%d ", tree->key);
	
	if (tree->right){
		inorder_traverser(tree->right);
	}
	return;
}


HuffmanNode *Create_HuffmanNode(Type key, HuffmanNode *left, HuffmanNode *right, HuffmanNode *parent){
	HuffmanNode *node = NULL;
	if ((node = (HuffmanNode *)malloc(sizeof(HuffmanNode))) == NULL){
		return node;
	}
	node->key = key;
	node->left = left;
	node->right = right;
	node->parent = parent;
	return node;
}

Huffman *Create_Huffman(Type a[], int size){
	//生成最小堆
	Create_minheap(a, size);
	printf("the min heap is :");
	print_minheap();
	HuffmanNode *left = NULL;
	HuffmanNode *right = NULL;
	HuffmanNode *parent = NULL;

	//依次拿最小值和次小值
	for (int i = 0; i < size-1; i++){
		left = dump_from_minheap();
		right = dump_from_minheap();
		
		printf("the min and the second min is %d,%d\n", left->key, right->key);

		if (!left || !right){
			return NULL;
		}
		parent = Create_HuffmanNode(left->key + right->key, left, right, NULL);

		if (!parent){
			return parent;
		}
		left->parent = parent;
		right->parent = parent;

		if (insert_minheap(parent) == -1){
			printf("插入失败！");
			Destroy_minheap(parent);
			return NULL;
		}
		print_minheap();
	}
	Destroy_minheap(parent);
	return parent;
}

Huffman *Destroy_Huffman(HuffmanTree tree){
	if (!tree){
		return tree;
	}
	if (tree->left){
		Destroy_Huffman(tree->left);
	}
	if (tree->right){
		Destroy_Huffman(tree->right);
	}
	free(tree);
	return NULL;
}

void Print_Huffman(HuffmanTree tree){
	
		if (!tree){
			return;
		}
		if (tree->left){
			printf("the left child of %d node of HuffmanTree is %d\n", tree->left->parent->key,  tree->left->key);
		}
		if (tree->right){
			printf("the right child of %d node of HuffmanTree is %d\n", tree->right->parent->key,  tree->right->key);
		}
		Print_Huffman(tree->left);
		Print_Huffman(tree->right);

		return;

}
