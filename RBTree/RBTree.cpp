// RBTree.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "RBTree.h"


int main()
{
	return 0;
}


void RBTree::deleteFixup(Node * x)
{
	while (x == root && x->color == BLACK) {
		if (x == x->parent->left) {
			Node* w = x->parent->right;
			if (x->color == RED) {
				w->color = BLACK;
				x->parent->color = RED;
				leftRotate(x->parent);
				w = x->parent->right;
			}

			if (w->left->color == BLACK && w->right->color == BLACK) {
				w->color = RED;
				x = x->parent;
			}
			else if(w->right->color == BLACK)
			{
				w->left->color = BLACK;
				w->color = RED;
				rightRotate(w);
				w = x->parent->right;
			}

			w->color = x->parent->color;
			x->parent->color = BLACK;
			w->right->color = BLACK;
			leftRotate(x->parent);
			x = root;
		}
		else {

		}
	}
	x->color = BLACK;
}

void RBTree::insertFixup(Node * z)
{
	while (z->parent->color == RED) {
		if (z->parent == z->parent->parent->left) {
			Node* y = z->parent->parent->left;
			if (y->color == RED) {
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}
			else if (z == z->parent->right) {
				z = z->parent;
				leftRotate(z);
			}
			z->parent->color = BLACK;
			z->parent->parent->color = RED;
			rightRotate(z->parent->parent);
		}
		else// todo 补充对称逻辑
		{

		}
	}
	root->color = BLACK;
}

/*
左旋转
修改的时候注意：
修改完一对关系之后再修改下一对（这里的一对是指在旋转完成之后，所形成的一对关系）
			p
			|1
			x
		  /   \2
		 a     y
			 /3  \
			b     r
*/
void RBTree::leftRotate(Node * x)
{
	//获取x的右子节点
	Node* y = x->right;

	//设置x的右子节点
	x->right = y->left;
	//设置y的左子节点的父节点
	if (y->left != NULL)
		y->left->parent = x;

	//设置y的父节点
	y->parent = x->parent;
	//设置x的父节点的子节点
	if (x->parent == NULL)
		root = y;
	else if (x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;

	//设置y的左子节点
	y->left = x;
	//设置x的父节点
	x->parent = y;
}
/*
右旋转
			p
			|1
			y
		  /2   \
		x       r
	  /   \3
	a       b
需要修改的为1、2、3这三个连接
*/
void RBTree::rightRotate(Node * y)
{
	//获取y的左子树x
	Node* x = y->left;

	//设置y的左子节点
	y->left = x->right;
	//设置x的右子节点的父节点
	if (x->right != NULL) {
		x->right->parent = y;
	}

	//设置x的父节点
	x->parent = y->parent;
	//设置x的父节点的子节点
	if (y->parent == NULL)
		root = x;
	else if (y == y->parent->left)
		x->parent->left = x;
	else
		x->parent->right = x;

	//设置x的右子节点
	x->right = y;
	//设置y的父节点
	y->parent = x;
}

void RBTree::transplant(Node * u, Node * v)
{
	if (u->parent == NULL)
		root = v;
	else if (u == u->parent->left)
		u->parent->left = v;
	else
		u->parent->right = v;

	v->parent = u->parent;
}

Node * RBTree::minimum(Node * start)
{
	while (start->left != NULL)
		start = start->left;
	return start;
}

RBTree::RBTree() :root(NULL)
{
}


RBTree::~RBTree()
{
}

void RBTree::RBDelete(Node * z)
{
	//待删除节点或移至树内的节点
	Node* y = z;
	COLOR y_original_color = y->color;

	Node* x = NULL;
	if (z->left == NULL) {
		x = z->right;
		transplant(z, z->right);
	}
	else if(z->right == NULL)
	{
		x = z->left;
		transplant(z, z->left);
	}
	else
	{
		y = minimum(z->right);
		y_original_color = y->color;
		x = y->right;
		if (y->parent == z)
			x->parent == y;
		else
		{
			transplant(y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		transplant(z, y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}

	//如果y是红色，那么y被删除或移动时，红黑性质仍然保持
	if (y_original_color == BLACK) {
		//todo RB-DELETE-FIXUP()
	}
}
