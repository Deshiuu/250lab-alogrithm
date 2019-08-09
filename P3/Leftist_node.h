
/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  uwuserid @uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter|Spring|Fall) 201N
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

#ifndef LEFTIST_NODE_H
#define LEFTIST_NODE_H

#include <algorithm>
// You may use std::swap and std::min

#ifndef nullptr
#define nullptr 0
#endif

template <typename Type>
class Leftist_node {
	private:
		Type element;
		Leftist_node *left_tree;
		Leftist_node *right_tree;
		int heap_null_path_length;

	public:
		
		Leftist_node( Type const & );
		Type retrieve() const;
		bool empty() const;
		Leftist_node *left() const;
		Leftist_node *right() const;
		int count( Type const & ) const;
		int null_path_length();

		void push( Leftist_node *, Leftist_node *& );
		void clear();
		
};

template <typename Type>
Leftist_node<Type>::Leftist_node( Type const &obj ):
element( obj ),
left_tree( nullptr ),
right_tree( nullptr ),
heap_null_path_length( 0 ) {
	// does nothing
}

// You may need this




template <typename Type>
bool Leftist_node<Type>::empty() const {
	return ( this == nullptr );
}


template <typename Type>
Type Leftist_node<Type>:: retrieve() const{
	return this -> element;
}

//template <typename Type>
//*left() const{
//	return left_tree;
//}

//template <typename Type>
//*right() const{
//	return right_tree;
//}

template <typename Type>
Leftist_node<Type>* Leftist_node<Type>::left() const 
{
	return this->left_tree;
}

template <typename Type>
Leftist_node<Type>* Leftist_node<Type>::right() const
{
	return this->right_tree;
}


template <typename Type>
int Leftist_node<Type>:: count( Type const &obj) const{
	//int x = 0;
	//if(this == nullptr){
	//	return;
	//}
	//else{
	//	(this->left_tree);
	//}
	if (this->empty()) return 0;
	if (element != obj){
		return this->left_tree->count(obj) + this->right_tree->count(obj);
	}
	return this->right_tree->count(obj) + this->left_tree->count(obj) + 1;
	
}

//--------------------------------------------------------------------------------------------------
template <typename Type>
int Leftist_node<Type>:: null_path_length() {
	if (this == nullptr){
		return -1;
	}
	else {
		//if (left_tree ==nullptr || right_tree == nullptr ){
		//	heap_null_path_length = 0;
		//}
		//else{
			//heap_null_path_length = std::min(left_tree->return_null_length(), right_tree->return_null_length());
			//heap_null_path_length++;
		//}
		return heap_null_path_length;
		
	}
}




//-----------------------------------------------------------------------------
//mutator


template <typename Type>
void Leftist_node<Type>:: push(Leftist_node *new_heap, Leftist_node *&ptr_to_this){
	//if (insert_node == nullptr){
	//	return;
	//}
	//else{
	//	if(root_node == nullptr){
	//		root_node = insert_node;
	//	}
	//	else{
	//		Leftist_node <Type> *pass_node = root_node;
	//		Leftist_node <Type> *node_rought[100];
	//		int num1 = 0;
	//		while (pass_node !=nullptr && pass_node->element <= insert_node->element){
	//			node_rought[num1] = pass_node;
	//			num1++;
	//			pass_node = pass_node->right_tree;
	//		}
	//		insert_node->left_tree = pass_node;
	//		
	//		if (num1 > 0){
	//			node_rought[num1-1]->right_tree = insert_node;
	//		
	//			for (int num2 =1; num2 <= num1; num2++){
	//				Leftist_node<Type> *compare_left = node_rought[num1 - num2]->left_tree;
	//				Leftist_node<Type> *compare_right = node_rought[num1 - num2]->right_tree;
					//int num3 = compare_left.heap_null_path_length();
					//int num4 = compare_right.heap_null_path_length();
	//				if (compare_right.heap_null_path_length() > compare_left.heap_null_path_length()){
		//				std::swap(node_rought[num1 - num2]->left_tree, node_rought[num1 - num2]->right_tree);
	//				}
		//		}
		//	}
	//		else {
	//			root_node = insert_node;
	//			int lengthx = root_node->heap_null_path_length();
	//		}
			
			
	//	}
	//}
	
	
	//-------------------------------------------------------------------writing with recusion
	if(new_heap==nullptr){
		return;
	}
	else if(ptr_to_this==nullptr){
		ptr_to_this=new_heap;
		return;
	}
	else{
		
		if(ptr_to_this->element > new_heap->element){
			ptr_to_this=new_heap;
			new_heap->push(this,ptr_to_this);
		}
		
		else{
			right_tree->push(new_heap,right_tree);
			
			int left_null = ptr_to_this->left_tree->null_path_length();
			
			int right_null = ptr_to_this->right_tree->null_path_length();
	//----------------------------------------------------------------------------------------------update null_path_length		
			ptr_to_this->heap_null_path_length=std::min(left_null, right_null)+1;
			
			if(right_null > left_null){
				std::swap(right_tree,left_tree);
			}
		}
	}
	return;
}
template <typename Type>
void Leftist_node<Type>:: clear(){
	if(this!=nullptr) {
		heap_null_path_length--;
		left_tree->clear();
		right_tree->clear();
		delete this;
	}
	return;
}
#endif