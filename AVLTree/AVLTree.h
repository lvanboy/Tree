#ifndef _AVLTREE_H_
#define _AVLTREE_H_
#define HEIGHT(p) ( (p == NULL)?0: ( ( (AVLNode *)(p) )->height ) )
#define MAX(a,b) ( (a) > (b) ? (a) : (b))

//节点构成
typedef int DataType;
typedef struct AVLNode{
	DataType key;
	struct AVLNode *left;
	struct AVLNode *right;
	int height;
}AVLNode;

//创建一个节点
AVLNode *Create_AVLTree(DataType key);

//当前节点的高度
int Get_Height(AVLNode *node);

//获取最大值
AVLNode *Get_Maximum(AVLNode *node);

//获取最小值
AVLNode *Get_Minimum(AVLNode *node);

//LL旋转
AVLNode *Left_Left_Rotation(AVLNode *tree);

//RR旋转
AVLNode *Right_Right_Rotation(AVLNode *tree);

//LR旋转
AVLNode *Left_Right_Rotation(AVLNode *tree);

//RL旋转
AVLNode *Right_Left_Rotation(AVLNode *tree);

//查找
AVLNode *Find_AVLNode(AVLNode *tree, DataType key);

//先序遍历
void PreorderTraverse(AVLNode *tree);

//中序遍历
void InorderTraverse(AVLNode *tree);

//后序遍历
void PostorderTraverse(AVLNode *tree);

//插入操作
AVLNode *Insert_AVLNode(AVLNode *tree, AVLNode *node);

//插入包裹层
AVLNode *Wrap_Insert_AVLNode(AVLNode *tree, DataType key);

//删除操作
AVLNode *Delete_AVLNode(AVLNode *tree, AVLNode *node);

//删除包裹层
AVLNode *Wrap_Delete_AVLNode(AVLNode *tree, DataType key);

//销毁树
void Destory_AVLNode(AVLNode *tree);
#endif
