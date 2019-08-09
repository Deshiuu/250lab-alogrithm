
/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  c59sun @uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter|Spring|Fall) 2017
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

#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#ifndef nullptr
#define nullptr 0
#endif

#include <iostream>
#include <limits>
#include "Exception.h"
#include "Disjoint_sets.h"

using namespace std;
struct adjlistnode{
	int dest;
	double weight;
	adjlistnode* next;
};
struct adjlist{
	adjlistnode* head;
};
class Weighted_graph {
	private:
		static const double INF;
		double** graph;
		int num_nodes;
		int num_edges;
		adjlist* graph_1;

		// Do not implement these functions!
		// By making these private and not implementing them, any attempt
		// to make copies or assignments will result in errors
		Weighted_graph( Weighted_graph const & );
		Weighted_graph &operator=( Weighted_graph );

	public:
		Weighted_graph( int = 10 );
		~Weighted_graph();

		int degree( int ) const;
		int edge_count() const;
		std::pair<double, int> minimum_spanning_tree() const;

		bool insert_edge( int, int, double );
		bool erase_edge( int, int );
		void clear_edges();

	// Friends

	friend std::ostream &operator<<( std::ostream &, Weighted_graph const & );
};

const double Weighted_graph::INF = std::numeric_limits<double>::infinity();

Weighted_graph::Weighted_graph(int n ) {
	if(n<0){
		throw illegal_argument();
	}
	if(n==0){
		n=50;
	}
	graph_1=new adjlist[n];
	for(int k=0;k<n;k++){
		graph_1[k].head = nullptr;
	}
	num_nodes=n;
}

Weighted_graph::~Weighted_graph() {
	delete[] graph_1;
}

int Weighted_graph::degree(int u) const {
	if(u<0){
		throw illegal_argument();
	}
	if(u>num_nodes-1){
		throw illegal_argument();
	}
	
	adjlistnode* current_node = graph_1[u].head;
	int num_degree=0;
	
	while(current_node->next!=nullptr){
		num_degree = num_degree + 1;
		current_node=current_node->next;
	}
	return num_degree;

}

int Weighted_graph::edge_count() const {
	int num_redges = num_edges / 2; 
	return num_redges;
}



bool Weighted_graph::erase_edge(int i, int j) {
	if(i<0||j<0||i>num_nodes-1||j>num_nodes-1){
		throw illegal_argument();
	}
	
	
	
	adjlistnode* current_node = graph_1[i].head;
	
	
	int k=0;
	while(current_node->next!=nullptr && current_node!=nullptr){
		if (current_node->dest==j){
			k=1;
			break;
		}
		current_node=current_node->next;
	}
	if(k!=1){
		return false;
	}
	
	
	if(current_node->next->next==nullptr){
		current_node->weight=0;
		current_node->dest=-1;
		current_node->next=nullptr;
	}
	else{
		current_node->weight=current_node->next->weight;
		current_node->dest=current_node->next->dest;
		current_node->next=current_node->next->next;
	}
	//-----------------------------------------------------------do the same thing again
	current_node=graph_1[j].head;
	
	while(current_node->next!=nullptr && current_node!=nullptr){
		if (current_node->dest==i){
			break;
		}
		current_node=current_node->next;
	}
	
//	while(current_node->next!=nullptr && current_node->dest!=i){
//		current_node = current_node->next;
//	}
	//if(current_node->dest!=i){
	//	return false;
	//}
	
	
	if(current_node->next->next==nullptr){
		current_node->dest=-1;
		current_node->weight=0;
		current_node->next=nullptr;
	}
	else{
		current_node->weight=current_node->next->weight;
		current_node->dest=current_node->next->dest;
		current_node->next=current_node->next->next;
	}
	return true;
}



void Weighted_graph::clear_edges() {
	for(int k=0;k<num_nodes-1;k++){
		erase_edge(k,k+1);
	}
	return;
}

bool Weighted_graph::insert_edge( int i, int j, double d ) {
	if(d<=0||i<0||j<0||i>num_nodes-1||j>num_nodes-1){
		throw illegal_argument();
	}
	
	
	
	if(i==j){
		return false;
	}
	
	adjlistnode* current_node=graph_1[i].head;
	
	
	int k=0;

	
	while(current_node!=nullptr){
		if (current_node->dest==j){
			k=1;
			break;
		}
		current_node=current_node->next;
	}
	if(k!=1){
		adjlistnode* new_node= new adjlistnode;
		
		new_node->weight=d;
		new_node->dest=i;
		new_node->next=graph_1[j].head;
		graph_1[j].head=new_node;
		
		new_node= new adjlistnode;
		new_node->dest=j;
		new_node->weight=d;
		new_node->next=graph_1[i].head;
		graph_1[i].head=new_node;
		num_edges++;
	}
	else{
		current_node->weight=d;
		current_node=graph_1[j].head;
		while(current_node->next!=nullptr && current_node!=nullptr){
			if (current_node->dest==i){
				break;
			}
			current_node=current_node->next;
		}
		current_node->weight=d;
	}
	return true;
}

std::pair<double, int> Weighted_graph::minimum_spanning_tree() const {
	

	return std::pair<double, int>( 0.0, 0 );
}

std::ostream &operator<<( std::ostream &out, Weighted_graph const &graph ) {
	
	
	return out;
}


#endif
