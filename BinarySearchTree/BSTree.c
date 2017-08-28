
#include <stdio.h>
#include <stdlib.h>
#include "BSTree.h"

//创建一个节点
BSTree Create_BSNode(DataType val){
	//分开内存,即开辟一个节点
	BSNode *node = (BSTree)malloc(sizeof(BSNode));
	if (node){
		node->left = NULL;
		node->right = NULL;
		node->parent = NULL;
		node->val = val;
	}
	return node;
}

//寻找某个值
BSTree Search_BSTree(BSNode *node, DataType val){
	//找到值,就返回存储这个值的节点
	if (node == NULL || val == node->val){
		return node;
	}//没有左右孩子,即找到叶子节点还未找到需要找的值
	if (!node->left && !node->right){
		return node->left;
	}
	//如果比当前节点小,向左子树走,逐渐缩小范围
	if (val < node->val){
		return Search_BSTree(node->left, val);
	}//否则,向右子树走
	else{
		return Search_BSTree(node->right, val);
	}
}

//找到最大值
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

//找到最小值
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



//插入节点
int Insert_BSNode(BSNode *root, BSNode *node){
	BSNode *insert_point = NULL;
	if (root == NULL || node == NULL){
		return 0;
	}
	//寻找插入点
	while (root){
		//默认从根开始寻找
		insert_point = root;
		if (node->val < root->val){
			root = root->left;
		}
		else if (node->val > root->val){
			root = root->right;
		}
	}
	//空树则直接将插入点作为树根
	if (insert_point == NULL){
		root = node;
	}
	node->parent = insert_point;
	//判断新节点在插入点的左边还是右边,并建立关系.
	if (node->val < insert_point->val){
		insert_point->left = node;
	}
	else{
		insert_point->right = node;
	}
	return 1;
}

//插入节点之前要新建节点,这里是包裹层,直接在这里创建节点
BSTree WrapInsert_BSNode(BSNode *root, DataType nodeVal){
	BSNode *node = NULL;
	//插入的节点值存在
	if (Search_BSTree(root, nodeVal) != NULL){
		return NULL;
	}
	//节点创建不成功
	if ((node = Create_BSNode( nodeVal ))== NULL){
		return NULL;
	}
	Insert_BSNode(root, node);
	return node;
}

//先序遍历
void preorder(BSTree root){
	if (root == NULL){
		return ;
	}
	printf(" %d", root->val);
	preorder(root->left);
	preorder(root->right);
}

//中序遍历
void Inorder(BSTree root){
	if (root == NULL){
		return;
	}
	Inorder(root->left);
	printf(" %d", root->val);
	Inorder(root->right);
}

//寻找节点的前驱
BSTree predecessor(BSNode *node){
	BSTree pre = NULL;
	BSTree parent = NULL;
	//存在左子树
	if (node->left){
		//把左子树首节点当做根节点开始
		node = node->left;
		while (node){
			//优先判断右节点,如果存在右节点,这个属于离node最近的右节点直接返回
			if (node->right){
				pre = node->right;
				return pre;
			}
			//继续向左找
			else if (node->left){
				node = node->left;
			}//也就是说,while循环的node一开始就是叶子,直接返回
			else{
				pre = node;
				return pre;
			}
		}
	}//存在右子树的情况,就要向上找,
	else{
		//node是根,而且没有左孩子,那么,我们就让他形成循环链表
		parent = node->parent;
		if (!parent){
			while (node->right){
				node = node->right;
			}
			pre = node;
			return pre;
		}//如果该节点是父节点的右孩子,父节点就是前驱
		if (parent->right == node){
			pre = parent;
		}
		else{
			//否则,就一直向上找,直到找到:父节点的右孩子是该点
			while (parent->right != node){
				node = parent;
				parent = parent->parent;
				//如果找到根也找不到,同样的,使它成为循环链表
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

//寻找节点的后继
BSTree successor(BSNode *node){
	//后继节点
	BSTree next = NULL;
	//父节点
	BSTree parent = NULL;
	//如果有右子树
	if (node->right){
		//向右走一步
		node = node->right;
		while (node){
			//优先向左走
			if (node->left){
				node = node->left;
			}
			//向右走
			else if (node->right){
				node = node->right;
			}//最左边的叶子节点,也就是最小的(右子树中),因为刚开始向右走了一步
			else{
				return node;
			}
		}
	}
	else{
		//左子树下面肯定都是小的,后继肯定是大的,所以我们要向上找,
		parent = node->parent;
		//是根,做成循环链表
		if (!parent){
			while (node->left){
				node = node->left;
			}
			next = node;
		}
		//该节点刚好在父节点的左边,父节点肯定比该节点大,所以就是后继,返回咯
		if (parent->left == node){
			next = parent;
		}
		else{
			//不是在父节点的左边,就一直找,直到找到咯
			while (parent->left != node){
				node = parent;
				parent = parent->parent;
				//实在找不到,那肯定到根了,做成循环链表吧!
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
	//删除点子节点
	BSTree child = NULL;
	//后继节点
	BSTree next = NULL;
	//删除点
	BSTree delete_node = node;
	//只有左孩子,存储左孩子
	if (node->left && !node->right){
		child = node->left;
	}
	//只有右孩子,存储右孩子
	else if (!node->left && node->right){
		child = node->right;
	}//左右孩子都存在
	else if (node->left&&node->right){
		//先拿后继
		next = successor(node); 
		//删除点已经变成后继
		node = next;
		//在拿后继的孩子,后继没有孩子拿到的就是NULL
		if (next->left){
			child = next->left;
		}
		else if(next->right){
			child = next->right;
		}
	}//在拿到孩子的情况下
	if (child){
		//孩子的父亲,指向删除点的父亲
		child->parent = node->parent;
	}
	//判断删除点是否为根
	if (!node->parent){
		root = child;
	}
	//删除点在父节点的左边,孩子就给左边
	if (node->parent->left == node){
		node->parent->left = child;
	}//如果是右边,就给右边
	if (node->parent->right == node){
		node->parent->right = child;
	}//如果删除是后继节点,别忘了把后继的值覆盖原节点
	if (next){
		node->parent->val = next->val;
	}//释放删除点的内存
	if (node){
		free(node);
	}
	return delete_node;
}


BSTree WrapDelete_BSTree(BSTree root, BSNode *node){
	if (root == NULL || node == NULL){
		return root;
	}//存在节点才可以删除
	if (Search_BSTree(root, node->val) == NULL){
		return NULL;
	}
	Delete_BSTree(root, node);
}

//订一套规则,标识左孩子,右孩子,和根
//打印节点之间的关系
void printRelation(BSNode *child, BSNode *parent, int direction){
	if (child == NULL || parent == NULL){
		return;
	}//肯定是左右根中的一种类型
	if (direction != -1 && direction != 1&& direction !=0){
		return;
	}//根
	if (direction == 0){
		printf("the %d is the root\n", parent->val);
	}//左孩子和左孩子的父亲
	else if (direction == -1){
		printf("the %d is the left child of the  %d\n", child->val, parent->val);
	}//右孩子和右孩子的父亲
	else{
		printf("the %d is the right child of the %d\n", child->val, parent->val);
	}//向左走,用-1表示左孩子
	printRelation(child->left, child, -1);
	//向右走,用1表示右孩子
	printRelation(child->right, child, 1);
}

//销毁二叉搜索树
void Destroy_BSTree(BSTree root){
	if (root == NULL){
		return;	
	}
	Destroy_BSTree(root->left);
	Destroy_BSTree(root->right);
	//没有左右孩子了,在清理内存的值.
	free(root);
}
