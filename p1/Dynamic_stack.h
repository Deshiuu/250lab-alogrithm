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

#ifndef DYNAMIC_STACK_H
#define DYNAMIC_STACK_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Exception.h"
#include <iostream>
using namespace std;


class Dynamic_stack {

	private:
		int *array;
		int count;		
		int array_size;
		int initial_size;
	
	public:
		Dynamic_stack(int = 10);
		~Dynamic_stack();

		int top() const;
		int size() const;
		bool empty() const;
		int capacity() const;
			
		void push( int const & );
		int pop();
		void clear();		
};

Dynamic_stack::Dynamic_stack( int n ):
count( 0 ),
array_size( n ),
initial_size(n)
{
	array = new int[array_size];
}


Dynamic_stack::~Dynamic_stack() {
	delete []array;
}


int Dynamic_stack::top() const {
	if (count < 1){
		throw underflow();
	}
	else{
		int y = array[count-1];
		return y;
	}
	return 0;
}


int Dynamic_stack::size() const {
	if (count < 0){
		throw underflow();
	}
	else if (count > array_size - 1){
		throw overflow();
	}
	else {
		return count;
	}
	
	return 0;
}


bool Dynamic_stack::empty() const {
	if (count == 0){
		return true;
	}
	else{ 
		return false;
	}		
}


int Dynamic_stack::capacity() const {
	return array_size;
	return 0;
}


void Dynamic_stack::push( int const &obj ) {
	if(count > array_size - 1 ){
		array_size = 2 * array_size;
		int *array2 = new int [array_size];
		for (int i = 0; i < count; i++){
			array2[i] = array[i];
		}
		delete []array;
		array = array2;
	}
	array[count] = obj;
	count++;
}


int Dynamic_stack::pop() {
	if (count == 0){
		throw underflow();
	}
	count = count--;
	int z = array[count];
	array[count] = NULL;
	return z;
}

void Dynamic_stack::clear() {
	delete []array;
	array_size = initial_size;
	array = new int [array_size];
}
#endif