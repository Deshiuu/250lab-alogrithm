#ifndef DOUBLE_HASH_TABLE_H
#define DOUBLE_HASH_TABLE_H


/****************************************
 * UW User ID:  uwuserid
 * Submitted for ECE 250
 * Semester of Submission:  (Winter|Spring|Fall) 20NN
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 ****************************************/

#include "Exception.h"
#include "ece250.h"
//using namespace std;
enum state { EMPTY, OCCUPIED, DELETED };

template<typename T>
class DoubleHashTable {
	private:
		int count;
		int power;
		int array_size;
		T *array;
		state *array_state;

		int h1( T const & ) const; // first hash function
		int h2( T const & ) const; // second hash function

	public:
		DoubleHashTable( int = 5 );
		~DoubleHashTable();
		int size() const;
		int capacity() const;		
		bool empty() const;
		bool member( T const & ) const;
		T bin( int ) const;

		void print() const;

		void insert( T const & );
		bool remove( T const & );
		void clear();
};

template<typename T >
DoubleHashTable<T >::DoubleHashTable( int m ):
count( 0 ), power( m ), 

array_size( 1 << power ),
array( new T [array_size] ),
array_state( new state[array_size] ) {

	for ( int i = 0; i < array_size; ++i ) {
		array_state[i] = EMPTY;
	}
}

template<typename T >
DoubleHashTable<T >::~DoubleHashTable() {
	// enter your implemetation here 
		delete[] array;
		delete[] array_state;
}

template<typename T >
int DoubleHashTable<T >::size() const {
	//int ArraySize = 0;
	//for (int i = 0; i < array_size; i++){
	//	if (array_state[i] == OCCUPIED){
	//		ArraySize++;
	//	}
	//}
	return count;
	return 0;
}

template<typename T >
int DoubleHashTable<T >::capacity() const {
    return array_size;
	return 0;
}



template<typename T >
bool DoubleHashTable<T >::empty() const {
    // enter your implemetation here 
	if(count == 0){
		return true;
	}
	return false;
}

template<typename T >
int DoubleHashTable<T >::h1( T const &obj ) const {
	int obj_int = obj;
	int x = obj_int % array_size;
	if(x < 0){
		x = x + array_size;
	}
	return x;

	return 0;
}

template<typename T >
int DoubleHashTable<T >::h2( T const &obj ) const {
	double y = obj/array_size;
	int inty = y;
	inty = inty % array_size;
	if(inty < 0){
		inty = inty + array_size;
	}
	if(inty % 2 == 0){
		inty++;
	}
	return inty;
	return 0;
}

template<typename T >
bool DoubleHashTable<T>::member( T const &obj ) const {
	// enter your implemetation here 
	
	int addre1 = h1(obj);
	int addre2 = h2(obj);
	for(int i1 = 0; i1 < count; i1++){
		if (array_state[addre1] == OCCUPIED){
			if (array[addre1] == obj){
				return true;
			}
		}
		addre1 = (addre1+addre2)%array_size;
	}

	return false;
}

template<typename T >
T DoubleHashTable<T >::bin( int n ) const {
    // enter your implemetation here 	      
	if (array_state[n] == OCCUPIED){
		return array[n];
	}
	return T();
}

template<typename T >
void DoubleHashTable<T >::insert( T const &obj ) {
	if (count == array_size){
		throw overflow();
	}
	else {
		int probe = h1(obj);
		int offset = h2(obj);
		while(array_state[probe] == OCCUPIED){
			probe = probe + offset;
			probe = probe % array_size;
		}
		array[probe] = obj;
		array_state[probe] = OCCUPIED;
		count++;
	}
	return ; 
}

template<typename T >
bool DoubleHashTable<T >::remove( T const &obj ) {
	 // enter your implemetation here 	
	int addre3 = h1(obj);
	int addre4 = h2(obj);
	for(int i2 = 0; i2 < count; i2++){
		if (array_state[addre3] == OCCUPIED){
			if (array[addre3] == obj){
				array[addre3] = NULL;
				array_state[addre3] = DELETED;
				count--;
				return true;
			}
		}
		addre3 = (addre3+addre4)%array_size;
	}
	return false;
}

template<typename T >
void DoubleHashTable<T >::clear() {
	 // enter your implemetation here 	
	 for(int i3 = 0; i3 < array_size; i3++){
		 array[i3] = NULL;
		 array_state[i3] = EMPTY;
	 }
	 count = 0;
	 return ; 
}




template<typename T >
void DoubleHashTable<T >::print() const {
   // for(int i3 = 0; i3 < array_size; i3++){
	//	if (array_state[i3] == OCCUPIED){
//			cout << i3 << ' ' << array[i3] << endl; 
//		}
	//	else {
//			cout << i3 << ' ' << endl;
//		}
//	 }
//	 cout << h1(159) << " " << h2(159);
//	return;
}

#endif