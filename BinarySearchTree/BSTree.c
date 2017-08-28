
#include <stdio.h>
#include <stdlib.h>
#include "BSTree.h"

//����һ���ڵ�
BSTree Create_BSNode(DataType val){
	//�ֿ��ڴ�,������һ���ڵ�
	BSNode *node = (BSTree)malloc(sizeof(BSNode));
	if (node){
		node->left = NULL;
		node->right = NULL;
		node->parent = NULL;
		node->val = val;
	}
	return node;
}

//Ѱ��ĳ��ֵ
BSTree Search_BSTree(BSNode *node, DataType val){
	//�ҵ�ֵ,�ͷ��ش洢���ֵ�Ľڵ�
	if (node == NULL || val == node->val){
		return node;
	}//û�����Һ���,���ҵ�Ҷ�ӽڵ㻹δ�ҵ���Ҫ�ҵ�ֵ
	if (!node->left && !node->right){
		return node->left;
	}
	//����ȵ�ǰ�ڵ�С,����������,����С��Χ
	if (val < node->val){
		return Search_BSTree(node->left, val);
	}//����,����������
	else{
		return Search_BSTree(node->right, val);
	}
}

//�ҵ����ֵ
BSTree GetMaximum_BSNode(BSNode *root){
	BSNode *Max_Node = NULL;
	if (root==NULL){
		return root;
	}
	while (root->right){
		root = root->right;
	}
	Max_Node = root;
	return Max_Node;
}

//�ҵ���Сֵ
BSTree GetMinimum_BSNode(BSNode *root){
	BSNode *Min_Node = NULL;
	if (root == NULL){
		return root;
	}
	while (root->left){
		root = root->left;
	}
	Min_Node = root;
	return Min_Node;
}



//����ڵ�
int Insert_BSNode(BSNode *root, BSNode *node){
	BSNode *insert_point = NULL;
	if (root == NULL || node == NULL){
		return 0;
	}
	//Ѱ�Ҳ����
	while (root){
		//Ĭ�ϴӸ���ʼѰ��
		insert_point = root;
		if (node->val < root->val){
			root = root->left;
		}
		else if (node->val > root->val){
			root = root->right;
		}
	}
	//������ֱ�ӽ��������Ϊ����
	if (insert_point == NULL){
		root = node;
	}
	node->parent = insert_point;
	//�ж��½ڵ��ڲ�������߻����ұ�,��������ϵ.
	if (node->val < insert_point->val){
		insert_point->left = node;
	}
	else{
		insert_point->right = node;
	}
	return 1;
}

//����ڵ�֮ǰҪ�½��ڵ�,�����ǰ�����,ֱ�������ﴴ���ڵ�
BSTree WrapInsert_BSNode(BSNode *root, DataType nodeVal){
	BSNode *node = NULL;
	//����Ľڵ�ֵ����
	if (Search_BSTree(root, nodeVal) != NULL){
		return NULL;
	}
	//�ڵ㴴�����ɹ�
	if ((node = Create_BSNode( nodeVal ))== NULL){
		return NULL;
	}
	Insert_BSNode(root, node);
	return node;
}

//�������
void preorder(BSTree root){
	if (root == NULL){
		return ;
	}
	printf(" %d", root->val);
	preorder(root->left);
	preorder(root->right);
}

//�������
void Inorder(BSTree root){
	if (root == NULL){
		return;
	}
	Inorder(root->left);
	printf(" %d", root->val);
	Inorder(root->right);
}

//Ѱ�ҽڵ��ǰ��
BSTree predecessor(BSNode *node){
	BSTree pre = NULL;
	BSTree parent = NULL;
	//����������
	if (node->left){
		//���������׽ڵ㵱�����ڵ㿪ʼ
		node = node->left;
		while (node){
			//�����ж��ҽڵ�,��������ҽڵ�,���������node������ҽڵ�ֱ�ӷ���
			if (node->right){
				pre = node->right;
				return pre;
			}
			//����������
			else if (node->left){
				node = node->left;
			}//Ҳ����˵,whileѭ����nodeһ��ʼ����Ҷ��,ֱ�ӷ���
			else{
				pre = node;
				return pre;
			}
		}
	}//���������������,��Ҫ������,
	else{
		//node�Ǹ�,����û������,��ô,���Ǿ������γ�ѭ������
		parent = node->parent;
		if (!parent){
			while (node->right){
				node = node->right;
			}
			pre = node;
			return pre;
		}//����ýڵ��Ǹ��ڵ���Һ���,���ڵ����ǰ��
		if (parent->right == node){
			pre = parent;
		}
		else{
			//����,��һֱ������,ֱ���ҵ�:���ڵ���Һ����Ǹõ�
			while (parent->right != node){
				node = parent;
				parent = parent->parent;
				//����ҵ���Ҳ�Ҳ���,ͬ����,ʹ����Ϊѭ������
				if (!parent){
						while (node->right){
							node = node->right;
						}
						pre = node;
						return pre;
				}
			}
			
			pre = parent;
		}
		return pre;
	}
	return NULL;
}

//Ѱ�ҽڵ�ĺ��
BSTree successor(BSNode *node){
	//��̽ڵ�
	BSTree next = NULL;
	//���ڵ�
	BSTree parent = NULL;
	//�����������
	if (node->right){
		//������һ��
		node = node->right;
		while (node){
			//����������
			if (node->left){
				node = node->left;
			}
			//������
			else if (node->right){
				node = node->right;
			}//����ߵ�Ҷ�ӽڵ�,Ҳ������С��(��������),��Ϊ�տ�ʼ��������һ��
			else{
				return node;
			}
		}
	}
	else{
		//����������϶�����С��,��̿϶��Ǵ��,��������Ҫ������,
		parent = node->parent;
		//�Ǹ�,����ѭ������
		if (!parent){
			while (node->left){
				node = node->left;
			}
			next = node;
		}
		//�ýڵ�պ��ڸ��ڵ�����,���ڵ�϶��ȸýڵ��,���Ծ��Ǻ��,���ؿ�
		if (parent->left == node){
			next = parent;
		}
		else{
			//�����ڸ��ڵ�����,��һֱ��,ֱ���ҵ���
			while (parent->left != node){
				node = parent;
				parent = parent->parent;
				//ʵ���Ҳ���,�ǿ϶�������,����ѭ�������!
				if (!parent){
					while (node->left){
						node = node->left;
					}
					next = node;
					return next;
				}
			}
			next = parent;
		}
		return next;
	}
	return NULL;
}


BSTree Delete_BSTree(BSTree root,BSNode *node){
	//ɾ�����ӽڵ�
	BSTree child = NULL;
	//��̽ڵ�
	BSTree next = NULL;
	//ɾ����
	BSTree delete_node = node;
	//ֻ������,�洢����
	if (node->left && !node->right){
		child = node->left;
	}
	//ֻ���Һ���,�洢�Һ���
	else if (!node->left && node->right){
		child = node->right;
	}//���Һ��Ӷ�����
	else if (node->left&&node->right){
		//���ú��
		next = successor(node); 
		//ɾ�����Ѿ���ɺ��
		node = next;
		//���ú�̵ĺ���,���û�к����õ��ľ���NULL
		if (next->left){
			child = next->left;
		}
		else if(next->right){
			child = next->right;
		}
	}//���õ����ӵ������
	if (child){
		//���ӵĸ���,ָ��ɾ����ĸ���
		child->parent = node->parent;
	}
	//�ж�ɾ�����Ƿ�Ϊ��
	if (!node->parent){
		root = child;
	}
	//ɾ�����ڸ��ڵ�����,���Ӿ͸����
	if (node->parent->left == node){
		node->parent->left = child;
	}//������ұ�,�͸��ұ�
	if (node->parent->right == node){
		node->parent->right = child;
	}//���ɾ���Ǻ�̽ڵ�,�����˰Ѻ�̵�ֵ����ԭ�ڵ�
	if (next){
		node->parent->val = next->val;
	}//�ͷ�ɾ������ڴ�
	if (node){
		free(node);
	}
	return delete_node;
}


BSTree WrapDelete_BSTree(BSTree root, BSNode *node){
	if (root == NULL || node == NULL){
		return root;
	}//���ڽڵ�ſ���ɾ��
	if (Search_BSTree(root, node->val) == NULL){
		return NULL;
	}
	Delete_BSTree(root, node);
}

//��һ�׹���,��ʶ����,�Һ���,�͸�
//��ӡ�ڵ�֮��Ĺ�ϵ
void printRelation(BSNode *child, BSNode *parent, int direction){
	if (child == NULL || parent == NULL){
		return;
	}//�϶������Ҹ��е�һ������
	if (direction != -1 && direction != 1&& direction !=0){
		return;
	}//��
	if (direction == 0){
		printf("the %d is the root\n", parent->val);
	}//���Ӻ����ӵĸ���
	else if (direction == -1){
		printf("the %d is the left child of the  %d\n", child->val, parent->val);
	}//�Һ��Ӻ��Һ��ӵĸ���
	else{
		printf("the %d is the right child of the %d\n", child->val, parent->val);
	}//������,��-1��ʾ����
	printRelation(child->left, child, -1);
	//������,��1��ʾ�Һ���
	printRelation(child->right, child, 1);
}

//���ٶ���������
void Destroy_BSTree(BSTree root){
	if (root == NULL){
		return;	
	}
	Destroy_BSTree(root->left);
	Destroy_BSTree(root->right);
	//û�����Һ�����,�������ڴ��ֵ.
	free(root);
}
