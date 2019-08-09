
#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

#ifndef nullptr
#define nullptr 0
#endif


#include <limits>
#include "Exception.h"

using namespace std;

struct ll_entry; // represents each element of the linked list
struct set_info; // keeps track of the information (pointers to head and tail and the size of the set) of each set
//could we delete the above two lines?


struct ll_entry{ 
	int content;
	set_info* ptr_to_info; // ptr to the info entry of the corresponding set
	ll_entry* next;
	
};

struct set_info { 
	ll_entry* head;
	ll_entry* tail;
	int size;
};

class Disjoint_set {

private:
	ll_entry** nodes;
	set_info** sets;
	int set_counter;
	int initial_num_sets;
public:
	Disjoint_set(int);
	~Disjoint_set();
	int find_set(int) const;
	int num_sets() const;
	void union_sets(int, int);
};





Disjoint_set::Disjoint_set(int n) : nodes(new ll_entry*[n]), 
sets (new set_info*[n]), 
set_counter(n),
initial_num_sets(n) {
	// initialize the sets	
}

Disjoint_set::~Disjoint_set() {
	set_counter=1;
	delete[] sets;
	delete[] nodes;
}
int Disjoint_set::find_set(int item) const{
	if(item < 0||item > initial_num_sets-1){
		throw illegal_argument();
	}
	return nodes[item]->ptr_to_info->head->content;
	return 0;
}


int Disjoint_set::num_sets() const {
	return set_counter;
}



void Disjoint_set::union_sets(int node_index1, int node_index2) {
	
	if (node_index1 == node_index2)
		return;
	
	set_info* si1 = nodes[node_index1]->ptr_to_info;
	set_info* si2 = nodes[node_index2]->ptr_to_info;

	// ni1: the index of the larger set, ni2: the index of the smaller index
	int ni1 = si1->size >= si2->size ? node_index1 : node_index2; 
	int ni2 = si1->size < si2->size ? node_index1 : node_index2;
	
	
	

	ll_entry* current_node = nodes[ni2]->ptr_to_info->head;
	// iterate through the shorter list and modify the pointers
	while (current_node!=NULL) {
		current_node -> ptr_to_info=si1;
		current_node = current_node->next;
	}
	//(si2->tail)->next=si1->tail;
	//si1->tail=si2->tail;
	(si1->tail)->next=si2->tail;
	si1->tail=si2->tail;

	// do we need to modify anything else?
	delete si2;
	// delete the set_info entry that no longer exists
	
	
	
}


#endif
