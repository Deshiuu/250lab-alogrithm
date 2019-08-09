
/*************************************************
 * Leftist_heap_tester
 * A class for testing leftist heaps
 *
 * Author:  Douglas Wilhelm Harder
 * Copyright (c) 2006 by Douglas Wilhelm Harder.  All rights reserved.
 *
 * DO NOT EDIT THIS FILE
 *************************************************/

#ifndef LEFTIST_HEAP_TESTER_H
#define LEFTIST_HEAP_TESTER_H

#ifndef nullptr
#define nullptr 0
#endif

#include "ece250.h"
#include "Exception.h"
#include "Tester.h"
#include "Leftist_heap.h"

#include <iostream>

template <typename Type>
class Leftist_heap_tester:public Tester< Leftist_heap<Type> > {
	using Tester< Leftist_heap<Type> >::object;
	using Tester< Leftist_heap<Type> >::command;

	public:
		Leftist_heap_tester( Leftist_heap<Type> *obj = 0 ):
		Tester< Leftist_heap<Type> >( obj ) {
			// empty
		}

		void process();
};

/****************************************************
 * void process()
 *
 * Process the current command.  For leftist heaps, these include:
 *
 *           Member
 *   Flag   Function         Tests if ...
 *
 *  Accessors
 *   empty b        empty             the value of empty
 *   size n         size              the size of the tree equals n
 *   npl n          null_path_length  the null-path length of the heap
 *   top n          top               the top of the heap is n
 *   top!           top               there is no least element
 *   count n m      count             the count of n in the heap is m
 *
 *  Mutators
 *   push n         push              insert n into the heap
 *   pop n          pop               the value n is popped off the heap
 *   pop!           pop               there is no element to pop
 *   clear          clear             empty the heap
 *
 *  Others
 *   assign          operator =       assign this heap to a new heap
 *   summary                          prints the amount of memory allocated
 *                                    minus the memory deallocated
 *   details                          prints a detailed description of which
 *                                    memory was allocated with details
 *   !!                               use the previous command,
 *                                       e.g.  $ push 3
 *                                             $ !! 7   // same as push 7
 *   !n                              use the command used in line n
 ****************************************************/

template <typename Type>
void Leftist_heap_tester<Type>::process() {
	if ( command == "new" ) {
		object = new Leftist_heap<Type>();
		std::cout << "Okay" << std::endl;
	} else if ( command == "empty" ) {
		// check if empty equals the next Boolean value read

		bool expected_empty;

		std::cin >> expected_empty;

		bool actual_empty = object->empty();

		if ( actual_empty == expected_empty ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << ": Failure in empty(): expecting the value '"
			          << expected_empty << "' but got '"
			          << actual_empty << "'" << std::endl;
		}
	} else if ( command == "size" ) {
		// check if the size equals the next integer read

		int expected_size;

		std::cin >> expected_size;

		int actual_size = object->size();

		if ( actual_size == expected_size ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << ": Failure in size(): expecting the value '"
			          << expected_size << "' but got '" << actual_size
			          << "'" << std::endl;
		}
	} else if ( command == "npl" ) {
		// check if the null-path length equals the next integer read

		int expected_null_path_length;

		std::cin >> expected_null_path_length;

		int actual_null_path_length = object->null_path_length();

		if ( actual_null_path_length == expected_null_path_length ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << ": Failure in null_path_length(): expecting the value '"
			          << expected_null_path_length << "' but got '"
			          << actual_null_path_length
			          << "'" << std::endl;
		}
	}  else if ( command == "top" ) {
		// find the smallest element

		Type expected_top;

		std::cin >> expected_top;

		Type actual_top = object->top();

		if ( actual_top == expected_top ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << ": Failure in top(): expecting the value '" << expected_top << "' but got '" << actual_top << "'" << std::endl;
		}
	} else if ( command == "top!" ) {
		// top of an empty leftist heap - catch an exception

		Type actual_top;

		try {
			actual_top = object->top();
			std::cout << "Failure in top(): expecting to catch an exception but got '" << actual_top << "'" << std::endl;
		} catch( underflow ) {
			std::cout << "Okay" << std::endl;
		} catch (...) {
			std::cout << "Failure in top(): expecting an underflow exception but caught a different exception" << std::endl;
		}
	}  else if ( command == "count" ) {
		// check for membership

		int expected_count;
		Type n;

		std::cin >> n;
		std::cin >> expected_count;

		int actual_count = object->count( n );

		if ( actual_count == expected_count ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << ": Failure in count(" << n << "): expecting the value '" << expected_count << "' but got '" << actual_count << "'" << std::endl;
		}
	}  else if ( command == "push" ) {
		// push the next integer read onto the leftist heap

		Type n;
		std::cin >> n;

		object->push( n );
		std::cout << "Okay" << std::endl;
	} else if ( command == "pop" ) {
		// remove the top from the leftist heap

		Type expected_pop;
		std::cin >> expected_pop;

		Type actual_pop = object->pop();

		if ( actual_pop == expected_pop ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << ": Failure in pop(): expecting the value '" << expected_pop << "' but got '" << actual_pop << "'" << std::endl;
		}
	} else if ( command == "pop!" ) {
		// pop of an empty leftist heap - catch an exception

		Type actual_pop;

		try {
			actual_pop = object->pop();
			std::cout << "Failure in pop(): expecting to catch an exception but got '" << actual_pop << "'" << std::endl;
		} catch( underflow ) {
			std::cout << "Okay" << std::endl;
		} catch (...) {
			std::cout << "Failure in pop(): expecting an underflow exception but caught a different exception" << std::endl;
		}
	} else if ( command == "clear" ) {
		object->clear();
		std::cout << "Okay" << std::endl;
	} else if ( command == "assign" ) {
		Leftist_heap<Type> *new_object = new Leftist_heap<Type>();

		*new_object = *(object);

		std::cout << "Okay" << std::endl;

		Leftist_heap_tester<Type> tester( new_object );

		tester.run();
	} else if ( command == "cout" ) {
		std::cout << *object << std::endl;
	} else {
		std::cout << command << ": Command not found." << std::endl;
	}
}
#endif