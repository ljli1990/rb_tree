#ifndef _RB_TREE__CPP_
#define _RB_TREE__CPP_

#include "rb_tree.h"

template <class T>	
rb_tree<T>::rb_tree(const T &val  ){
	root = new rb_tree_node<T>(val);					//动态创建根结点空间
}

template <class T>	
rb_tree<T>::~rb_tree(){
	destroy(root);
}

template <class T>	
rb_tree_node<T> *rb_tree<T>::get_root() const{
	return root;
}

template <class T>	
rb_tree_node<T> *rb_tree<T>::search(const T &val){
	rb_tree_node<T> *pret;
	
	pret = this->get_root() ;
	while(pret){
		if(pret->key < val )
			pret = pret->right;
		else if( pret->key > val )
			pret = pret->left;
		else
			break;
	}
	return pret;
}

template <class T>
void rb_tree<T>::destroy(rb_tree_node<T> *current_node){
	if(!current_node)
		return;
	else{
		if(current_node->left)
			destroy(current_node->left);
		if(current_node->right)
			destroy(current_node->right);
		delete current_node;
		current_node = NULL;
	}

}

/*************对红黑树节点x进行左旋操作 ******************/  
/* 
 * 左旋示意图：对节点x进行左旋 
 *     p                       p 
 *    /                       / 
 *   x                       y 
 *  / \                     / \ 
 * lx  y      ----->       x  ry 
 *    / \                 / \ 
 *   ly ry               lx ly 
 * 左旋做了三件事： 
 * 1. 将y的左子节点赋给x的右子节点,并将x赋给y左子节点的父节点(y左子节点非空时) 
 * 2. 将x的父节点p(非空时)赋给y的父节点，同时更新p的子节点为y(左或右) 
 * 3. 将y的左子节点设为x，将x的父节点设为y 
 */ 
template <class T>
void rb_tree<T>::left_rotate(rb_tree_node<T> *x){
	rb_tree_node<T> *y = x->right ;		// 前提：这里假设x的右孩子为y。下面开始正式操作

	/* xy之间断开重连 */
	y->parent = x->parent;				// 将 “x的父亲” 设为 “y的父亲”
	x->right = y->left;					// 将 “y的左孩子” 设为 “x的右孩子”，即 将ly设为x的右孩子

	/* x p 之间断开重连  */
	if( !x->parent )					// 情况1：如果 “x的父亲” 是空节点，则将y设为根节点
		root = y;
	else if( x->parent->left == x )		// 情况2：如果 x是它父节点的左孩子，则将y设为“x的父节点的左孩子”
		x->parent->left = y;
	else								// 情况3：(x是它父节点的右孩子) 将y设为“x的父节点的右孩子”
		x->parent->right = y;
	x->parent = y;						// 将 “x的父节点” 设为 “y”

	/* y ly 之间断开重连 */
	if(y->left)
		y->left->parent = x;			// 将 “x” 设为 “y的左孩子的父亲”，即 将ly的父亲设为x
	y->left = x;						// 将 “x” 设为 “y的左孩子”

}

/*************对红黑树节点y进行右旋操作 ******************/  
/* 
 * 左旋示意图：对节点y进行右旋 
 *        p                   p 
 *       /                   / 
 *      y                   x 
 *     / \                 / \ 
 *    x  ry   ----->      lx  y 
 *   / \                     / \ 
 * lx  rx                   rx ry 
 * 右旋做了三件事： 
 * 1. 将x的右子节点赋给y的左子节点,并将y赋给x右子节点的父节点(x右子节点非空时) 
 * 2. 将y的父节点p(非空时)赋给x的父节点，同时更新p的子节点为x(左或右) 
 * 3. 将x的右子节点设为y，将y的父节点设为x 
 */  
template <class T>
void rb_tree<T>::right_rotate(rb_tree_node<T> *y){
	rb_tree_node<T> *x = y->left ;             // 前提：这里假设y的左孩子为x。下面开始正式操作


	/* xy之间断开重连 */
	x->parent = y->parent;				// 将 “y的父亲” 设为 “x的父亲”
	y->left = x->right;					// 将 “x的右孩子” 设为 “y的左孩子”，即 将rx设为y的左孩子

	/* x p 之间断开重连  */
	if( !y->parent )					// 情况1：如果 “y的父亲” 是空节点，则将x设为根节点
		root = x;
	else if( y->parent->left == y )		// 情况2：如果 y是它父节点的左孩子，则将x设为“y的父节点的左孩子”
		x->parent->left = x;
	else								// 情况3：(y是它父节点的右孩子) 将x设为“y的父节点的右孩子”
		x->parent->right = x;
	y->parent = x;						// 将 “y的父节点” 设为 “x”

	/* y ly 之间断开重连 */
	if(x->right)
		x->right->parent = y ;			// 将 “y” 设为 “x的右孩子的父亲”，即 将rx的父亲设为y
	x->right = y;						// 将 “y” 设为 “x的右孩子”
}

template <class T>
bool rb_tree<T>::insert(const T &val){
	/*	创建新结点 */
	rb_tree_node<T> *new_node = new rb_tree_node<T>(val);			
	
	/*  调用重载版本*/
	 return this->insert(new_node);
}
template <class T>
bool rb_tree<T>::insert(rb_tree_node<T> *new_node){
	rb_tree_node<T> *p ,*q;
	
	//p = NULL; q = NULL;
	/* start to search */
	q = p = this->get_root();
	while(p){
		q = p;
		if(p->key < new_node->key )
			p = p->right;
		else if( p->key > new_node->key )
			p = p->left;
		else
			return false;					//在tree找到相同key的结点， 返回false
	}

	/* judge left or right  */
	if(!q)				
		this->set_root(new_node);
	else if( q->key > new_node->key )
		q->left = new_node;
	else
		q->right = new_node;

	/* set new_node's parent */
	new_node->parent = q;

	/* fixup */
	insert_fixup(new_node);

	return true;
}

template <class T>
void rb_tree<T>::insert_fixup(rb_tree_node<T> *new_node){
	rb_tree_node<T> *P , *G , *S;

	/*	
	*	注 ：这里虽然多了内存空间， 但节省了寻找结点的父结点 ,
	*	祖父结点，兄弟结点的时间 ,因为需要指针一个个找
	*/

	/* 循环调整 */
	while (true){
		
		/* init P  */
		P = new_node->parent;

		/*	情况1：插入的点为根结点	*/
		if (!P){
			new_node->color = RB_BLACK;
			break;
		}
		/*	情况2：插入的点的父结点为黑色， 什么都不做， 结束调整	*/
		else if( P->color == RB_BLACK )
			break;
		/*	情况2：插入的点的父结点为红色 ， 又有4种情况	*/
		else{
			/*	若父节点是祖父节点的左子节点，下面else与其相反	*/

			/* 当父结点P为红色时， 祖父结点G 是肯定存在的， 否则p就是root ，产生矛盾*/
			G = P->parent;

			if ( P == G->left){
				/*	叔叔节点是红色,就是情况3的 c ， d		*/
				S = G->right;
				if( S && S->color == RB_RED ){
					/*	情况3的 d	*/
					if ( new_node == P->right ){
						new_node = P;
						left_rotate(new_node);

						/*	完成旋转后 ， 重新设定PGS	*/
						P = new_node->parent;
						G = P->parent;
						S = G->right;
					}
					/*	情况3的 c	*/
					P->color = RB_BLACK;
					G->color = RB_RED;
					S->color = RB_BLACK;					//可以看出， 这是情况cd与ab处理的区别
					new_node = G;
				}
				/*	叔叔节点是黑色,就是情况3的 a , b	*/
				else{
					/*	情况3的 b	*/
					if ( new_node == P->right ){
						new_node = P;
						left_rotate(new_node);

						/*	完成旋转后 ， 重新设定PGS	*/
						P = new_node->parent;
						G = P->parent;
						//S = G->right;
					}
					/*	情况3的 a	*/
					P->color = RB_BLACK;
					G->color = RB_RED;
					//new_node = G;
					/*	以“祖父节点”为支点进行右旋。	*/
					right_rotate(G);
				}
			}
			/*	若父节点是祖父节点的右子节点,与上面的完全相反,镜像处理  */
			else{
				/*	情况3的 c ， d		*/
				S = G->left;
				if( S && S->color == RB_RED ){
					/*	情况3的 d	*/
					if ( new_node == P->left ){
						new_node = P;
						right_rotate(new_node);

						/*	完成旋转后 ， 重新设定PGS	*/
						P = new_node->parent;
						G = P->parent;
						S = G->left;
					}
					/*	情况3的 c	*/
					P->color = RB_BLACK;
					G->color = RB_RED;
					S->color = RB_BLACK;					//可以看出， 这是情况cd与ab处理的区别
					new_node = G;
				}
				/*	情况3的 a , b	*/
				else{
					/*	情况3的 b	*/
					if ( new_node == P->left ){
						new_node = P;
						right_rotate(new_node);

						///*	完成旋转后 ， 重新设定PGS	*/
						P = new_node->parent;
						G = P->parent;
						//S = G->left;
					}
					/*	情况3的 a	*/
					P->color = RB_BLACK;
					G->color = RB_RED;
					//new_node = G;
					/*	以“祖父节点”为支点进行左旋。	*/
					left_rotate(G);
				}
			}
		}
	}
}

/*********************** 得到当前结点的后继结点,即大于节点x的最小节点  **********************/  
template <class T>
rb_tree_node<T> *rb_tree<T>::successor(rb_tree_node<T> *p_cur){
	rb_tree_node<T> *p_ret , *p_par ;

	/*	判断条件	*/
	if(	p_cur ){
		if ( p_cur->right ){
			/*	一直左下，找到叶结点	*/
			p_ret = p_cur->right;
			while(p_ret->left)
				p_ret = p_ret->left;
		}
		else{
			/*	没有右结点，则查看父结点与当前结点的关系	*/

			//如果x没有右子节点，会出现以下两种情况：  
			//1. x是其父节点的左子节点，则x的后继节点为它的父节点  
			//2. x是其父节点的右子节点，则先查找x的父节点p，然后对p
			//再次进行这两个条件的判断  
			p_par = p_ret->parent;
			while( !p_par&&p_par->right == p_ret ){	
				p_ret = p_par;
				p_par = p_ret->parent;
			}
			p_ret = p_par;
		}
	}
	return p_ret;
}
/*********************** 删除红黑树中的节点 **********************/  
template <class T>
bool rb_tree<T>::remove(const T &val){
	rb_tree_node<T> *rm_node ;
	bool b_ret;

	b_ret = false;
	if( !( rm_node = this->search(val)) )
		b_ret = this->remove(rm_node);

	return b_ret;
}

/*********************** 删除红黑树中的节点，重载版本 **********************/  
template <class T>
bool rb_tree<T>::remove(rb_tree_node<T> *rm_node){
	rb_tree_node<T> *Y ,*X;
	RB_TREE_COLOR Y_color;

	// 若“z的左孩子” 或 “z的右孩子”为空，则将“z”赋值给 “y”；
	// 否则，将“z的后继节点”赋值给 “y”。
	if( !rm_node->left || !rm_node->right )
		/* case 1 2 3 */
		Y = rm_node;
	else
		/*	case 4	*/
		Y = this->successor(rm_node);

	// 若“y的左孩子” 不为空，则将“y的左孩子” 赋值给 “x”；
	// 否则，“y的右孩子” 赋值给 “x”。 注意右孩子有可能为空
	if( Y->left )
		X = Y->left;
	else
		X = Y->right;

	/* 开始处理 P与X的连接	*/

	// 将“y的父节点” 设置为 “x的父节点”
	if(X)
		X->parent = Y;

	if(!Y->parent)
		root = X;						//删除的结点y为根结点
	else if (Y->parent->left == Y)
		// 情况2：若“y是它父节点的左孩子”，则设置“x” 为 “y的父节点的左孩子”
		Y->parent->left = X;
	else
		// 情况3：若“y是它父节点的右孩子”，则设置“x” 为 “y的父节点的右孩子”
		Y->parent->right = X;
	
	/*	若Y是后继结点	*/
	if ( Y != rm_node ){
		// 若“y的值” 赋值给 “z”。注意：这里只拷贝z的值给y，而没有拷贝z的颜色！！！
		rm_node->key = Y->key;			
	}
	
	Y_color = Y->color;
	/*	删除结点Y	*/
	delete Y; Y = NULL;

	/*因为删除了一个黑色结点， 就要开始调整*/
	if( Y_color == RB_BLACK )
		this->remove_fixup(X);

	return true;
}

template <class T>
void rb_tree<T>::remove_fixup(rb_tree_node<T> *rep_node){
	rb_tree_node<T> *p ,*s , *ls , *rs;

	/*	先处理情况3 ，情况1 ，2 在循环结束可以直接将rep_node 设置为black即可	*/
	while(rep_node != this-get_root() && rep_node->color == RB_BLACK){
		/*	X不可能为空，在上面的函数可以证实	*/
		p = rep_node->parent;
		if ( p->left == rep_node ){
			/*rep_node是左子节点，下面else与这里的刚好相反 */
			s = p->right;
			if ( s->color == RB_RED ){
				/*	case 1	,因为兄弟结点为red ， 其子女必定为black， 所以不用判断*/
				p->color = RB_RED;
				s->color = RB_BLACK;
				this->left_rotate(p);
				s = p->right;
			}
			/*	这里不加else的原因 ， 看流程图 */
			ls = s->left;
			rs = s->right;

			if( ( ls &&  ls->color == RB_BLACK ) && ( rs && rs->color == RB_BLACK ) ){
				/* case 2 */
				s->color = RB_RED ;
				rep_node = p;
			}
			else{
				/* case 3 , 4  */
				if (ls && ls->color == RB_RED && rs && rs->color == RB_BLACK ){
					/* case 3   */
					ls->color = RB_BLACK ; 
					s->color = RB_RED ;
					this->right_rotate(s);
					s = p->right;
					ls = s->left;
					rs = s->right;
				}
				/* case  4  */
				s->color = p->color ;
				p->color = RB_BLACK ;
				rs->color = RB_BLACK;
				this->left_rotate(p);
				break;
			}
		}
		else{
			/*	rep_node是右子节点 ， 与第一个if对应 */
			s = p->left;
			if ( s->color == RB_RED ){
				/*	case 1	,因为兄弟结点为red ， 其子女必定为black， 所以不用判断*/
				p->color = RB_RED;
				s->color = RB_BLACK;
				this->right_rotate(p);
				s = p->left;
			}
			/*	这里不加else的原因 ， 看流程图 */
			ls = s->left;
			rs = s->right;

			if( ( ls &&  ls->color == RB_BLACK ) && ( rs && rs->color == RB_BLACK ) ){
				/* case 2 */
				s->color = RB_RED ;
				rep_node = p;
			}
			else{
				/* case 3 , 4  */
				if (rs && rs->color == RB_RED && ls && ls->color == RB_BLACK ){
					/* case 3   */
					rs->color = RB_BLACK ; 
					s->color = RB_RED ;
					this->right_rotate(s);
					s = p->left;
					ls = s->left;
					rs = s->right;
				}
				/* case  4  */
				s->color = p->color ;
				p->color = RB_BLACK ;
				ls->color = RB_BLACK;
				this->left_rotate(p);
				break;
			}
		}
	}
	root->color = RB_BLACK;
}
#endif