#ifndef _RB_TREE__CPP_
#define _RB_TREE__CPP_

#include "rb_tree.h"

template <class T>	
rb_tree<T>::rb_tree(const T &val  ){
	root = new rb_tree_node<T>(val);					//��̬���������ռ�
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

/*************�Ժ�����ڵ�x������������ ******************/  
/* 
 * ����ʾ��ͼ���Խڵ�x�������� 
 *     p                       p 
 *    /                       / 
 *   x                       y 
 *  / \                     / \ 
 * lx  y      ----->       x  ry 
 *    / \                 / \ 
 *   ly ry               lx ly 
 * �������������£� 
 * 1. ��y�����ӽڵ㸳��x�����ӽڵ�,����x����y���ӽڵ�ĸ��ڵ�(y���ӽڵ�ǿ�ʱ) 
 * 2. ��x�ĸ��ڵ�p(�ǿ�ʱ)����y�ĸ��ڵ㣬ͬʱ����p���ӽڵ�Ϊy(�����) 
 * 3. ��y�����ӽڵ���Ϊx����x�ĸ��ڵ���Ϊy 
 */ 
template <class T>
void rb_tree<T>::left_rotate(rb_tree_node<T> *x){
	rb_tree_node<T> *y = x->right ;		// ǰ�᣺�������x���Һ���Ϊy�����濪ʼ��ʽ����

	/* xy֮��Ͽ����� */
	y->parent = x->parent;				// �� ��x�ĸ��ס� ��Ϊ ��y�ĸ��ס�
	x->right = y->left;					// �� ��y�����ӡ� ��Ϊ ��x���Һ��ӡ����� ��ly��Ϊx���Һ���

	/* x p ֮��Ͽ�����  */
	if( !x->parent )					// ���1����� ��x�ĸ��ס� �ǿսڵ㣬��y��Ϊ���ڵ�
		root = y;
	else if( x->parent->left == x )		// ���2����� x�������ڵ�����ӣ���y��Ϊ��x�ĸ��ڵ�����ӡ�
		x->parent->left = y;
	else								// ���3��(x�������ڵ���Һ���) ��y��Ϊ��x�ĸ��ڵ���Һ��ӡ�
		x->parent->right = y;
	x->parent = y;						// �� ��x�ĸ��ڵ㡱 ��Ϊ ��y��

	/* y ly ֮��Ͽ����� */
	if(y->left)
		y->left->parent = x;			// �� ��x�� ��Ϊ ��y�����ӵĸ��ס����� ��ly�ĸ�����Ϊx
	y->left = x;						// �� ��x�� ��Ϊ ��y�����ӡ�

}

/*************�Ժ�����ڵ�y������������ ******************/  
/* 
 * ����ʾ��ͼ���Խڵ�y�������� 
 *        p                   p 
 *       /                   / 
 *      y                   x 
 *     / \                 / \ 
 *    x  ry   ----->      lx  y 
 *   / \                     / \ 
 * lx  rx                   rx ry 
 * �������������£� 
 * 1. ��x�����ӽڵ㸳��y�����ӽڵ�,����y����x���ӽڵ�ĸ��ڵ�(x���ӽڵ�ǿ�ʱ) 
 * 2. ��y�ĸ��ڵ�p(�ǿ�ʱ)����x�ĸ��ڵ㣬ͬʱ����p���ӽڵ�Ϊx(�����) 
 * 3. ��x�����ӽڵ���Ϊy����y�ĸ��ڵ���Ϊx 
 */  
template <class T>
void rb_tree<T>::right_rotate(rb_tree_node<T> *y){
	rb_tree_node<T> *x = y->left ;             // ǰ�᣺�������y������Ϊx�����濪ʼ��ʽ����


	/* xy֮��Ͽ����� */
	x->parent = y->parent;				// �� ��y�ĸ��ס� ��Ϊ ��x�ĸ��ס�
	y->left = x->right;					// �� ��x���Һ��ӡ� ��Ϊ ��y�����ӡ����� ��rx��Ϊy������

	/* x p ֮��Ͽ�����  */
	if( !y->parent )					// ���1����� ��y�ĸ��ס� �ǿսڵ㣬��x��Ϊ���ڵ�
		root = x;
	else if( y->parent->left == y )		// ���2����� y�������ڵ�����ӣ���x��Ϊ��y�ĸ��ڵ�����ӡ�
		x->parent->left = x;
	else								// ���3��(y�������ڵ���Һ���) ��x��Ϊ��y�ĸ��ڵ���Һ��ӡ�
		x->parent->right = x;
	y->parent = x;						// �� ��y�ĸ��ڵ㡱 ��Ϊ ��x��

	/* y ly ֮��Ͽ����� */
	if(x->right)
		x->right->parent = y ;			// �� ��y�� ��Ϊ ��x���Һ��ӵĸ��ס����� ��rx�ĸ�����Ϊy
	x->right = y;						// �� ��y�� ��Ϊ ��x���Һ��ӡ�
}

template <class T>
bool rb_tree<T>::insert(const T &val){
	/*	�����½�� */
	rb_tree_node<T> *new_node = new rb_tree_node<T>(val);			
	
	/*  �������ذ汾*/
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
			return false;					//��tree�ҵ���ͬkey�Ľ�㣬 ����false
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
	*	ע ��������Ȼ�����ڴ�ռ䣬 ����ʡ��Ѱ�ҽ��ĸ���� ,
	*	�游��㣬�ֵܽ���ʱ�� ,��Ϊ��Ҫָ��һ������
	*/

	/* ѭ������ */
	while (true){
		
		/* init P  */
		P = new_node->parent;

		/*	���1������ĵ�Ϊ�����	*/
		if (!P){
			new_node->color = RB_BLACK;
			break;
		}
		/*	���2������ĵ�ĸ����Ϊ��ɫ�� ʲô�������� ��������	*/
		else if( P->color == RB_BLACK )
			break;
		/*	���2������ĵ�ĸ����Ϊ��ɫ �� ����4�����	*/
		else{
			/*	�����ڵ����游�ڵ�����ӽڵ㣬����else�����෴	*/

			/* �������PΪ��ɫʱ�� �游���G �ǿ϶����ڵģ� ����p����root ������ì��*/
			G = P->parent;

			if ( P == G->left){
				/*	����ڵ��Ǻ�ɫ,�������3�� c �� d		*/
				S = G->right;
				if( S && S->color == RB_RED ){
					/*	���3�� d	*/
					if ( new_node == P->right ){
						new_node = P;
						left_rotate(new_node);

						/*	�����ת�� �� �����趨PGS	*/
						P = new_node->parent;
						G = P->parent;
						S = G->right;
					}
					/*	���3�� c	*/
					P->color = RB_BLACK;
					G->color = RB_RED;
					S->color = RB_BLACK;					//���Կ����� �������cd��ab���������
					new_node = G;
				}
				/*	����ڵ��Ǻ�ɫ,�������3�� a , b	*/
				else{
					/*	���3�� b	*/
					if ( new_node == P->right ){
						new_node = P;
						left_rotate(new_node);

						/*	�����ת�� �� �����趨PGS	*/
						P = new_node->parent;
						G = P->parent;
						//S = G->right;
					}
					/*	���3�� a	*/
					P->color = RB_BLACK;
					G->color = RB_RED;
					//new_node = G;
					/*	�ԡ��游�ڵ㡱Ϊ֧�����������	*/
					right_rotate(G);
				}
			}
			/*	�����ڵ����游�ڵ�����ӽڵ�,���������ȫ�෴,������  */
			else{
				/*	���3�� c �� d		*/
				S = G->left;
				if( S && S->color == RB_RED ){
					/*	���3�� d	*/
					if ( new_node == P->left ){
						new_node = P;
						right_rotate(new_node);

						/*	�����ת�� �� �����趨PGS	*/
						P = new_node->parent;
						G = P->parent;
						S = G->left;
					}
					/*	���3�� c	*/
					P->color = RB_BLACK;
					G->color = RB_RED;
					S->color = RB_BLACK;					//���Կ����� �������cd��ab���������
					new_node = G;
				}
				/*	���3�� a , b	*/
				else{
					/*	���3�� b	*/
					if ( new_node == P->left ){
						new_node = P;
						right_rotate(new_node);

						///*	�����ת�� �� �����趨PGS	*/
						P = new_node->parent;
						G = P->parent;
						//S = G->left;
					}
					/*	���3�� a	*/
					P->color = RB_BLACK;
					G->color = RB_RED;
					//new_node = G;
					/*	�ԡ��游�ڵ㡱Ϊ֧�����������	*/
					left_rotate(G);
				}
			}
		}
	}
}

/*********************** �õ���ǰ���ĺ�̽��,�����ڽڵ�x����С�ڵ�  **********************/  
template <class T>
rb_tree_node<T> *rb_tree<T>::successor(rb_tree_node<T> *p_cur){
	rb_tree_node<T> *p_ret , *p_par ;

	/*	�ж�����	*/
	if(	p_cur ){
		if ( p_cur->right ){
			/*	һֱ���£��ҵ�Ҷ���	*/
			p_ret = p_cur->right;
			while(p_ret->left)
				p_ret = p_ret->left;
		}
		else{
			/*	û���ҽ�㣬��鿴������뵱ǰ���Ĺ�ϵ	*/

			//���xû�����ӽڵ㣬������������������  
			//1. x���丸�ڵ�����ӽڵ㣬��x�ĺ�̽ڵ�Ϊ���ĸ��ڵ�  
			//2. x���丸�ڵ�����ӽڵ㣬���Ȳ���x�ĸ��ڵ�p��Ȼ���p
			//�ٴν����������������ж�  
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
/*********************** ɾ��������еĽڵ� **********************/  
template <class T>
bool rb_tree<T>::remove(const T &val){
	rb_tree_node<T> *rm_node ;
	bool b_ret;

	b_ret = false;
	if( !( rm_node = this->search(val)) )
		b_ret = this->remove(rm_node);

	return b_ret;
}

/*********************** ɾ��������еĽڵ㣬���ذ汾 **********************/  
template <class T>
bool rb_tree<T>::remove(rb_tree_node<T> *rm_node){
	rb_tree_node<T> *Y ,*X;
	RB_TREE_COLOR Y_color;

	// ����z�����ӡ� �� ��z���Һ��ӡ�Ϊ�գ��򽫡�z����ֵ�� ��y����
	// ���򣬽���z�ĺ�̽ڵ㡱��ֵ�� ��y����
	if( !rm_node->left || !rm_node->right )
		/* case 1 2 3 */
		Y = rm_node;
	else
		/*	case 4	*/
		Y = this->successor(rm_node);

	// ����y�����ӡ� ��Ϊ�գ��򽫡�y�����ӡ� ��ֵ�� ��x����
	// ���򣬡�y���Һ��ӡ� ��ֵ�� ��x���� ע���Һ����п���Ϊ��
	if( Y->left )
		X = Y->left;
	else
		X = Y->right;

	/* ��ʼ���� P��X������	*/

	// ����y�ĸ��ڵ㡱 ����Ϊ ��x�ĸ��ڵ㡱
	if(X)
		X->parent = Y;

	if(!Y->parent)
		root = X;						//ɾ���Ľ��yΪ�����
	else if (Y->parent->left == Y)
		// ���2������y�������ڵ�����ӡ��������á�x�� Ϊ ��y�ĸ��ڵ�����ӡ�
		Y->parent->left = X;
	else
		// ���3������y�������ڵ���Һ��ӡ��������á�x�� Ϊ ��y�ĸ��ڵ���Һ��ӡ�
		Y->parent->right = X;
	
	/*	��Y�Ǻ�̽��	*/
	if ( Y != rm_node ){
		// ����y��ֵ�� ��ֵ�� ��z����ע�⣺����ֻ����z��ֵ��y����û�п���z����ɫ������
		rm_node->key = Y->key;			
	}
	
	Y_color = Y->color;
	/*	ɾ�����Y	*/
	delete Y; Y = NULL;

	/*��Ϊɾ����һ����ɫ��㣬 ��Ҫ��ʼ����*/
	if( Y_color == RB_BLACK )
		this->remove_fixup(X);

	return true;
}

template <class T>
void rb_tree<T>::remove_fixup(rb_tree_node<T> *rep_node){
	rb_tree_node<T> *p ,*s , *ls , *rs;

	/*	�ȴ������3 �����1 ��2 ��ѭ����������ֱ�ӽ�rep_node ����Ϊblack����	*/
	while(rep_node != this-get_root() && rep_node->color == RB_BLACK){
		/*	X������Ϊ�գ�������ĺ�������֤ʵ	*/
		p = rep_node->parent;
		if ( p->left == rep_node ){
			/*rep_node�����ӽڵ㣬����else������ĸպ��෴ */
			s = p->right;
			if ( s->color == RB_RED ){
				/*	case 1	,��Ϊ�ֵܽ��Ϊred �� ����Ů�ض�Ϊblack�� ���Բ����ж�*/
				p->color = RB_RED;
				s->color = RB_BLACK;
				this->left_rotate(p);
				s = p->right;
			}
			/*	���ﲻ��else��ԭ�� �� ������ͼ */
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
			/*	rep_node�����ӽڵ� �� ���һ��if��Ӧ */
			s = p->left;
			if ( s->color == RB_RED ){
				/*	case 1	,��Ϊ�ֵܽ��Ϊred �� ����Ů�ض�Ϊblack�� ���Բ����ж�*/
				p->color = RB_RED;
				s->color = RB_BLACK;
				this->right_rotate(p);
				s = p->left;
			}
			/*	���ﲻ��else��ԭ�� �� ������ͼ */
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