#include <iostream>
#include "rb_tree.cpp"

using namespace std;


int main(){
	/*
	*	依次插入下面的结点 ，效果可以看《STL源码剖析》 P230-P232
	*/
	int arr[] = {10,7,8,15,5,6,11,13,12};
	rb_tree<int> rb_obj;
	int i ,arr_size ;

	arr_size = sizeof(arr)/sizeof(arr[0]) ;
	for ( i = 0 ; i < arr_size ; ++i ){
		rb_obj.insert(arr[i]);
	}


	return 0;
}