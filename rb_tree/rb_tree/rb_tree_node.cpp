#ifndef _RB_TREE_NODE_CPP_
#define _RB_TREE_NODE_CPP_
#include "rb_tree_node.h"

template <class T>	
rb_tree_node<T>::rb_tree_node(const T &val , const RB_TREE_COLOR &col
							  /*, const rb_tree_node *p = NULL*/):
left(NULL) , right(NULL) ,parent(NULL) ,key(val) , color(col){
}

template <class T>	
rb_tree_node<T>::~rb_tree_node(void)
{
}

#endif