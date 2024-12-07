#ifndef TT_TREE_H
#define TT_TREE_H

#include <memory>
#include <string>
#include <map>
#include <vector>
#include <iostream>

using namespace std;

#define TT_ORDER 3

// data structure that contains area code, name, and occupation
struct data_packet {
  int area_code;
  int phone_num;
  string name;
  string occupation;
};

// primary structure of the tt_tree
struct tt_tree {
  // num_keys is the number of keys in the keys array that are
  // currently valid.
  int num_keys;
  
  // num_children is the number of children in the child array
  int num_children;

  // keys is an array of values
  int keys[TT_ORDER];
  
  // area_code is a map of keys to area codes
  map<int, data_packet*> data_map;
  
  // is_leaf is true if this is a leaf, false otherwise
  bool is_leaf;

  // children is an array of pointers to tt_trees
  tt_tree* children[TT_ORDER + 1];
  
  // pointer to the parent node; NULL if root
  tt_tree* parent;
  
  // pointer to the root node, should never be NULL
  tt_tree* root;
};

// insert data (keys, data_packet and children) to a node.
void insert(tt_tree*, data_packet*, tt_tree* = NULL, tt_tree* = NULL);

// remove locates and deletes the provided key if it is present.
void remove(tt_tree*, int);

// find locates the node that would contain the key if it were
// present or creates a new node if root is empty. Always non-NULL.
tt_tree* find(tt_tree*, int);

// recursively count all nodes
int count_nodes(tt_tree*);

// recursively count all keys
int count_keys(tt_tree*);

// HELPER FUNCTIONS //

// instantiate and return a new data packet
data_packet* create_data_packet(int, int, string, string);

// helper function that creates new nodes; accepts an argument for
// the parent node and the root node; so the child always knows its
// parent and always knows the tree root node
tt_tree* create_node(tt_tree*, tt_tree*);

// helper function provides the matching index to the target if it
// exists in the integer array
int int_array_search(int [3], int);

// helper function provides the matching index to the target if it
// exists in the tt_tree* array
int node_array_search(tt_tree* [4], tt_tree*);

// helper function that recursively searches for a target key
// within a tt_tree* (root) and assigns that value to a
// tt_tree* (location varible) that has been passsed in as
// reference.
void find_recursive_helper(int, tt_tree*, tt_tree*&);

// helper function to insert data into a node
void insert_data_to_node(tt_tree*, int, data_packet*, tt_tree*, tt_tree*);

// helper function to shift data within a node to make
// room for an insertion
void shift_node_data(tt_tree*, int);

// helper function to recursively search the tree for a
// specific key and provide the node and index of that key
bool find_node_and_index(tt_tree*, int, tt_tree*&, int&);

// helper function that locates the value, node, and index of the
// next highest key
void find_next_highest_key(tt_tree*, int, tt_tree*&, int&, int&);

// delete data from a node--usually this means swapping
// the data with the next highest element from a leaf
// node and then deleting it from the leaf.
void delete_and_replace_key(tt_tree*, int);

// helper function to very specifically delete a key from a key array
// and condense that array. this is actually a little tedious to do
// which is why I'm putting it in its own helper function.
void delete_key_and_condense_key_array(tt_tree*, int);

// helper function that inserts a data packet to a node.
void insert_data_packet(tt_tree*, data_packet*);

// helper function that removes a data packet from a node.
void remove_data_packet(tt_tree*, int);

// this helper function examines a specific node and determines if it's
// overloaded (keys = 3); if it is, then it corrects that situation
// while maintaining the 23-tree invariants.
void check_too_large(tt_tree*);

// this helper function examines a specific node and determines if it's
// underloaded (keys = 0); if it is, then it corrects that situation
// while maintaining the 23-tree invariants.
void check_too_small(tt_tree*&);

// helper function wipes all keys and children in a node.
void wipe_all_node_keys_and_kids(tt_tree*);

// helper function counts non-null child array elements
// and returns an integer value.
int count_non_null_children(tt_tree*);

// helper function that count all nodes or keys.
void recursive_counter(tt_tree*, int&, string nodes_keys);

#endif // TT_TREE_H
