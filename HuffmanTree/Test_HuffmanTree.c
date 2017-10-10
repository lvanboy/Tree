#include <stdio.h>
#include <stdlib.h>
#include "MinHeap_Huffman.h"
#include "HuffmanTree.h"

int main(){
	int a[] = { 15 ,5, 6, 7, 8};
	int len = sizeof(a) / sizeof(a[0]);
	Huffman *tree = NULL;
	tree = Create_Huffman(a, len);
	inorder_traverser(tree);
	printf("\nthe root of the HuffmanTree is %d\n", tree->key);
	Print_Huffman(tree);
	printf("destorying...\n");
	Destroy_Huffman(tree);
	getchar();
	return 0;
}