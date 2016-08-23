#ifndef _RB_TREE__H_
#define _RB_TREE__H_

#include "rb_tree_node.h"
//

template <class T>				//因为用到了rb_tree_node , 要给data赋值
class rb_tree
{
public:
	rb_tree(const T &val /*const rb_tree_node<T> *p = NULL */);
	rb_tree():root(NULL){};
	~rb_tree(void);

public:
	rb_tree_node<T> *get_root() const;					//返回root
	rb_tree_node<T> *search( const T &val);				//搜索key的结点

	bool insert(const T &val);							//插入key
	bool insert(rb_tree_node<T> *new_node);				//插入结点

	bool remove(const T &val);							//删除key为val的结点， 实际调用的是重载
	bool remove(rb_tree_node<T> *rm_node);				//插入结点
private:
	void set_root(rb_tree_node<T> *p){ root = p;}		//设置根结点

	void insert_fixup(rb_tree_node<T> *new_node);		//将插入的结点new_node调整
	void remove_fixup(rb_tree_node<T> *rep_node);		//将替代的结点rep_node调整

	void destroy(rb_tree_node<T> *current_node);		//删除以current_node结点为根的所有结点

	void left_rotate( rb_tree_node<T> *x);				//左旋
	void right_rotate( rb_tree_node<T> *y);				//右旋

	rb_tree_node<T> *successor(rb_tree_node<T> *p_cur);	//得到当前结点的后继结点

private:
	rb_tree_node<T> *root;
};

#include "rb_tree_node.cpp"



#endif
