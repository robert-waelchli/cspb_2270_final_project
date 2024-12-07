#ifndef TT_TREE_CPP
#define TT_TREE_CPP

#include <iostream>
#include "tt_tree.h"
#include "split_push_steal_merge_functions.h"

// insert data (keys and children) to a node
void insert(tt_tree* root, int key, tt_tree* left, tt_tree* right) {
  // identify which node should receive the data
  tt_tree* node = find(root, key);
  
  // if node came back NULL, then the key is a duplicate
  if (node == NULL) { return; }

  // attempt to insert the data into the node
  insert_data_to_node(node, key, left, right);
}

void remove(tt_tree* root, int key) {
    
  // if tt_tree is empty, take no action
  if (root->is_leaf && root->num_keys == 0) {
    return;
  }
  
  // if tt_tree has only a single element, delete the element
  // if requested, but take no other action
  if (root->is_leaf && root->num_keys == 1) {
    if (key == root->keys[0]) {
      root->keys[0] = 0;
      root->num_keys--;
    }
    return;
  }
    
  // identify which node should contain the data and the index
  // the data is located within that node
  int index;
  tt_tree* node;
  find_node_and_index(root, key, node, index);

  // delete the data at "index" from the node--usually
  // this means swapping the data with the next highest element
  // from a leaf node and then deleting it from the leaf.
  delete_and_replace_key(node, index);
}

tt_tree* find(tt_tree* root, int key) {
  // tt_tree pointer to store result
  tt_tree* ret;
   
  // recursively search for the target
  find_recursive_helper(key, root, ret);
    
  return ret;
}

int count_nodes(tt_tree* root) {
  // instantiate a counter variable
  int node_count = 0;
    
  // recursively count all nodes using the helper function
  recursive_counter(root, node_count, "-n");

  // return the final count
  return node_count;
}

int count_keys(tt_tree* root) {
  // instantiate a counter variable
  int key_count = 0;
  
  // recursively count all nodes using the helper function
  recursive_counter(root, key_count, "-k");

  // return the final count
  return key_count;
}

// HELPER FUNCTIONS //

// helper function provides the matching index to the target if it
// exists in the integer array
int int_array_search(int array[3], int target){
  int index = -1;
  for (int ii = 0; ii < 3; ii++) {
    if (array[ii] == target) {
      index = ii;
    }
  }
  return index;
}

// helper function provides the matching index to the target if it
// exists in the tt_tree* array
int node_array_search(tt_tree* array[4], tt_tree* target){
  int index = -1;
  for (int ii = 0; ii < 3; ii++) {
    if (array[ii] == target) {
      index = ii;
    }
  }
  return index;
}

tt_tree* create_node(tt_tree* parent, tt_tree* root) {
  // instantiate a new node and get a pointer to address
  tt_tree* ptr = new tt_tree;
  ptr->parent = parent;

  // if the provided root is NULL, then this node is root; else
  // trust the root provided by the calling function.
  if (root == NULL) {
    ptr->root = ptr;
  } else {
    ptr->root = root;
  }
  
  // default is_leaf to true
  ptr->is_leaf = true;
    
  // default num_keys to 0
  ptr->num_keys = 0;
  
  // default num_children to 0
  ptr->num_children = 0;
    
  // set all children and keys to null
  for (int ii = 0; ii < TT_ORDER; ii++) {
    ptr->keys[ii] = 0;
  }
  for (int jj = 0; jj < TT_ORDER + 1; jj++) {
    ptr->children[jj] = NULL;
  }
    
  return ptr;
}

void find_recursive_helper(int target_key, tt_tree* node,
                           tt_tree*& location) {
  
  // if the current node contains the target_key (e.g. duplicate)
  // return location = NULL as a flag
  for (int ii = 0; ii < TT_ORDER; ii++) {
    if (node->keys[ii] == target_key) {
      location = NULL;
      return;
    }
  }
  
  // if the current node is a leaf, return the current node
  if (node->is_leaf == true) {
    location = node;
    return;
    
  // if the current node is not a leaf, recurse down the first, second,
  // or third child depending on value
  } else {
    if (node->keys[0] > target_key) {
      find_recursive_helper(target_key, node->children[0], location);
    } else if ((node->keys[1] > target_key) || (node->keys[1] == 0)) {
      find_recursive_helper(target_key, node->children[1], location);
    } else {
      find_recursive_helper(target_key, node->children[2], location);
    }
  }
}

 void insert_data_to_node(tt_tree* node, int data,
                          tt_tree* left_child, tt_tree* right_child) {
   // determine insert location in the node
   // start by instantiating a counter and a boolean flag
   int insert_index = 0;
   bool stop_counting = false;
   
   // count through the keys index, looking for values greater than the target
   while (!stop_counting && insert_index < TT_ORDER) {
     if ((node->keys[insert_index] >= data) ||
         node->keys[insert_index] == 0) {
       stop_counting = true;
     } else {
       insert_index++;
     }
   }
   
   // prepare node for insert by shifting the data
   shift_node_data(node, insert_index);
   
   // insert the data at the insert index
   node->keys[insert_index] = data;
   
   // insert children at the insert index
   if (left_child != NULL) {
     node->children[insert_index] = left_child;
   }
   if (right_child != NULL) {
     node->children[insert_index + 1] = right_child;
   }

   // increment num_keys
   node->num_keys++;
   
   // check if the node is now overloaded
   check_too_large(node);
}

void shift_node_data(tt_tree* node, int index){
  // indentify the length of the node
  int end = node->num_keys;

  // shift each element of the node (from the end to the insertion
  // location) down by one element
  for (int ii = end; ii > index; ii--) {
    node->keys[ii] = node->keys[ii - 1];
    node->keys[ii - 1] = 0;
  }
  for (int ii = end + 1; ii > index; ii--) {
    node->children[ii] = node->children[ii - 1];
    node->children[ii - 1] = NULL;
  }
}

// helper function to recursively search the tree for a
// specific key and provide the node and index of that key
bool find_node_and_index(tt_tree* node, int key,
                         tt_tree*& location, int& index) {
  
  bool success = false;
  
  // go through all the keys in the node, if the key is >= the
  // target, stop incrementing.
  int ii = -1;
  bool halted = false;
  while (ii < TT_ORDER && !halted) {
    ii++;
    if (node->keys[ii] >= key || node->keys[ii] == 0) {
      halted = true;
    }
  }
  
  // if the reason the loop halted was an exact match, set
  // location and index and exit, job done.
  if (node->keys[ii] == key) {
    location = node;
    index = ii;
    success = true;
    
  // else recurse to the correct child node and repeat.
  } else if (!node->is_leaf) {
    success = find_node_and_index(node->children[ii],
                                  key, location, index);
    return success;
  } else {
    return false;
  }
  
  return success;
}

// helper function that locates the value, node, and index of the
// next highest key
void find_next_highest_key(tt_tree* root, int key,
                           tt_tree*& location, int& index, int& value) {
  
  // stopping boolean for while loop stopping condition
  bool halted = false;
  
  // start with the provided key
  while (!halted) {
    // increment the key by 1 each loop
    key++;
    // check if the key is found in the tree
    halted = find_node_and_index(root, key, location, index);
  }
  
  // set the value equal to the key
  value = key;
}

// helper function deletes the data at "index" from the
// node--usually this means swapping the data with the next
// highest element from a leaf node, then deleting from the leaf.
void delete_and_replace_key(tt_tree* node, int index) {
  // get the value of the key for simplicity and readibility
  int key = node->keys[index];
  
  // CASE 1 //
  // if node is a leaf, simply remove the key and condense the array.
  if (node->is_leaf) {
    
    // helper function performs the removal and condensing
    delete_key_and_condense_key_array(node, index);
    
    // decrement counter
    node->num_keys--;
    
    // now check if the leaf node has become too small
    check_too_small(node);
    
    // CASE 2 //
    // if the node is not a leaf, but, it's children are leaves,
    // swap the key with the next highest value. Then delete the
    // key from the leaf.
  } else if (!node->is_leaf) {
    
    // instantiate some place holders to be populated by the search
    // function
    tt_tree* location;
    int swap_index;
    int value;
    
    // swap the target key with the next highest-value key
    find_next_highest_key(node->root, key, location, swap_index, value);
    node->keys[index] = value;
    location->keys[swap_index] = key;
    
    
    // helper function performs the key removal and condensing
    // from the child array.
    delete_key_and_condense_key_array(location, swap_index);
    
    if (!location->is_leaf) {
      
      // have to merge the children at the location we removed from
      tt_tree* merged_node = merge(location->children[swap_index],
                                   location->children[swap_index + 1]);
      // place the merged node back into the removal location
      location->children[swap_index] = merged_node;
      location->children[swap_index + 1] = NULL;
      // update the num_children at the removal location
      location->num_children = count_non_null_children(location);
      
      location->num_keys--;
      
    } else if (location->is_leaf) {
      
      // decrement the child node's counter
      location->num_keys--;
      
      // now check if the leaf node has become too small
      check_too_small(location);
    }
  }
}

void delete_key_and_condense_key_array(tt_tree* node, int index) {
  // key removal and condensing is performed by first creating
  // a duplicate array without the removed key, and then copying that
  // array back into the node.
  node->keys[index] = 0;
  
  int replacement_keys[TT_ORDER];
  int ii = 0;
  int jj = ii;
  while (ii < TT_ORDER) {
    if (node->keys[ii] != 0) {
      replacement_keys[jj] = node->keys[ii];
      ii++;
      jj++;
    } else {
      ii++;
    }
  }
  // ensure that the replacement keys array elements all have
  // valid integer values
  while (jj < TT_ORDER) {
    replacement_keys[jj] = 0;
    jj++;
  }
  // copy the duplicate array back into the node
  for (int ii = 0; ii < TT_ORDER; ii++) {
    node->keys[ii] = replacement_keys[ii];
  }
}

// helper functions checks if the size of the node is > 2 keys. if the
// node is too large, it either splits into three (if root) or pushes
// the middle element up to the parent (if not root).
void check_too_large(tt_tree* node) {
  // define a new tt_tree* root for readability
  tt_tree* root = node->root;
  
  // if number of keys is less than TT_ORDER, return with no action
  if (node->num_keys < TT_ORDER) {
    return;
    
  // split a 3-key root into left and right children
  } else if (node == root && node->num_keys >= TT_ORDER)  {
    split_node_to_three_nodes(node);
    return;
    
  // 3-key case, not root:
  // in this case, we need need to push the middle key (and associated
  // children) up to the parent
  } else if (node != root) {
    push_key_to_parent(node);
    return;
  }
}

// helper functions checks if the size of the node is 0 keys. if the
// node is too small, the lowest value is stolen from the parent's node
// and then the node is merged with it's left-sibling.
void check_too_small(tt_tree* &node) {
  // if the number of keys is greater than zero, return with no action
  if (node->num_keys > 0) {
    return;
    
  // if node is root and has zero keys, then the newly merged
  // child node becomes the new root node--tree decreases height
  // by one level.
  } else if (node == node->root) {
    
    // get a pointer to the newly merged child
    tt_tree* child = node->children[0];
    
    // clone the child into the old root node (making the new root
    // the old child essentially, but without changing the root
    // pointer).
    clone_node(node->root, child);
    
    // set the parent pointers of the new root's children to be
    // pointed to the new root.
    for (int ii = 0; ii < node->num_children; ii++) {
      node->children[ii]->parent = node;
    }
  
    // delete the old child
    delete(child);
    
  // if the number of keys is zero, and the parent is not root,
  // pull the next highest or lowest value (depending on
  // position) from the parent node and then merge two of the
  // parent's children.
  } else {
 
    // define parent here so we can check it later to make sure
    // it didn't become too small after it was stolen from. It
    // is necessary to do this here, before stealing, because
    // it is possible that "node" will change (split) if it becomes
    // too large during the steal/merge process.
    tt_tree* parent = node->parent;
    
    // steal the key from the parent and obtain a pointer to the
    // new node (node may have been merged during the process)
    steal_key_from_parent(node);
    
    // check if the parent stolen from is now too small
    check_too_small(parent);
  }
}

// this helper function wipes all keys and children in a node.
void wipe_all_node_keys_and_kids(tt_tree* node) {
  for (int ii = 0; ii < TT_ORDER; ii++) {
    node->keys[ii] = NULL;
    node->children[ii] = NULL;
  }
  // wipe the final child entry
  node->children[TT_ORDER] = NULL;
  // reset num_keys
  node->num_keys = 0;
}

// helper function counts non-null child array elements
// and returns an integer value.
int count_non_null_children(tt_tree* node) {
  int ret = 0;
  for (int ii = 0; ii < TT_ORDER + 1; ii++) {
    if (node->children[ii] != NULL) {
      ret++;
    }
  }
  
  return ret;
}

// helper function that count all nodes or keys.
void recursive_counter(tt_tree* root, int& counter, string nodes_keys) {
  
  // if we're counting nodes, increment the counter just for arriving
  if (nodes_keys == "-n") {
    counter++;
  }
  
  if (nodes_keys == "-k") {
    counter = counter + root->num_keys;
  }
  
  // if the node is not a leaf, visit each child element and count it
  if (!root->is_leaf) {
    int ii = 0;
    while (root->children[ii] != NULL) {
      recursive_counter(root->children[ii], counter, nodes_keys);
      ii++;
    }
  }
}

#endif //TT_TREE_CPP
