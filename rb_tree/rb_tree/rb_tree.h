#ifndef _RB_TREE__H_
#define _RB_TREE__H_

#include "rb_tree_node.h"
//

template <class T>				//��Ϊ�õ���rb_tree_node , Ҫ��data��ֵ
class rb_tree
{
public:
	rb_tree(const T &val /*const rb_tree_node<T> *p = NULL */);
	rb_tree():root(NULL){};
	~rb_tree(void);

public:
	rb_tree_node<T> *get_root() const;					//����root
	rb_tree_node<T> *search( const T &val);				//����key�Ľ��

	bool insert(const T &val);							//����key
	bool insert(rb_tree_node<T> *new_node);				//������

	bool remove(const T &val);							//ɾ��keyΪval�Ľ�㣬 ʵ�ʵ��õ�������
	bool remove(rb_tree_node<T> *rm_node);				//������
private:
	void set_root(rb_tree_node<T> *p){ root = p;}		//���ø����

	void insert_fixup(rb_tree_node<T> *new_node);		//������Ľ��new_node����
	void remove_fixup(rb_tree_node<T> *rep_node);		//������Ľ��rep_node����

	void destroy(rb_tree_node<T> *current_node);		//ɾ����current_node���Ϊ�������н��

	void left_rotate( rb_tree_node<T> *x);				//����
	void right_rotate( rb_tree_node<T> *y);				//����

	rb_tree_node<T> *successor(rb_tree_node<T> *p_cur);	//�õ���ǰ���ĺ�̽��

private:
	rb_tree_node<T> *root;
};

#include "rb_tree_node.cpp"



#endif
