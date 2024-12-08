//
//  split_push_steal_merge_functions.h
//  cspb_2270_final_project
//
//  Created by Robert Waelchli on 12/02/24.
//

#ifndef SPLIT_FUNCTIONS_H
#define SPLIT_FUNCTIONS_H

#include <iostream>
#include "tt_tree.h"

using namespace std;

// split function that takes a node and splits to three nodes with the
// second key remaining with the parent and the first and third keys
// going to the children.
void split_node_to_three_nodes(tt_tree*);

// pushes the middle element up to the parent and brings 
void push_key_to_parent(tt_tree*);

// steals an element from the parent node--the element to be stolen
// depends on the position of the child--and returns a pointer to
// the node since the address may have changed due to node merges.
void steal_key_from_parent(tt_tree*&);

// merges two nodes together; some recursion required since children
// will also need to be merged if not leaf
tt_tree* merge(tt_tree*, tt_tree*);

void clone_node(tt_tree*, tt_tree*);

#endif // SPLIT_FUNCTIONS_H
