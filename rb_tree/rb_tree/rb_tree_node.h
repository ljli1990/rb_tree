#ifndef _RB_TREE_NODE_H_
#define _RB_TREE_NODE_H_

//#ifndef bool
//typedef enum bool{false	,true}bool;
//#endif
#ifndef RB_TREE_COLOR
typedef enum RB_TREE_COLOR{
	RB_RED = 0,
	RB_BLACK = 1
};
#endif

/************************************************************************/
/*		名称：红黑树的结点

		时间：2016-08-19	
*/
/************************************************************************/

template <class T>				//结点元素类型
struct rb_tree_node
{
	T key;						//关键字(键值)
	RB_TREE_COLOR color;
	
	rb_tree_node<T> *left;
	rb_tree_node<T> *right;
	rb_tree_node<T> *parent;


	rb_tree_node(const T &val = 0 , const RB_TREE_COLOR &col = RB_RED 
		/*, const rb_tree_node *p = NULL*/);
	~rb_tree_node(void);

};

#include "rb_tree_node.cpp"

#endif

