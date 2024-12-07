#ifndef SPLIT_FUNCTIONS_CPP
#define SPLIT_FUNCTIONS_CPP

#include <iostream>
#include "split_push_steal_merge_functions.h"

using namespace std;

// split function that takes a leaf and splits to three nodes with the
// second key remaining with the parent and the first and third keys
// going to the children.
void split_node_to_three_nodes(tt_tree* node) {
  // create a child left
  tt_tree* left = create_node(node, node->root);
  
  // and create a child right
  tt_tree* right = create_node(node, node->root);
  
  // populate left keys
  insert(left, node->keys[0]);
  // populate right keys
  insert(right, node->keys[2]);
  
  if (!node->is_leaf) {
    // move left children (if any)
    left->children[0] = node->children[0];
    left->children[1] = node->children[1];
    left->num_children = count_non_null_children(left);
    // move right children (if any)
    right->children[0] = node->children[2];
    right->children[1] = node->children[3];
    right->num_children = count_non_null_children(right);
    // set left and right leaf flags
    left->is_leaf = false;
    right->is_leaf = false;
    
    // set the parent pointers of the children's (left & right)
    // children (I know that's confusing to think about) to
    // the new children (left/right)
    for (int ii = 0; ii < left->num_keys + 1; ii++) {
      left->children[ii]->parent = left;
    }
    for (int ii = 0; ii < right->num_keys + 1; ii++) {
      right->children[ii]->parent = right;
    }
  }
  
  // wipe all keys and children in the current node
  int parking_spot = node->keys[1];
  wipe_all_node_keys_and_kids(node);
  
  // set parent's children equal to the new left/right nodes
  node->children[0] = left;
  node->children[1] = right;
  node->num_children = count_non_null_children(node);
  
  // set key[0] equal to the old key[1]
  node->keys[0] = parking_spot;
  node->num_keys++;
  
  // current node is def no longer a leaf (if it ever was)
  node->is_leaf = false;
}

// pushes the middle element up to the parent
void push_key_to_parent(tt_tree* node) {
  // define parent as its own pointer to improve readability
  tt_tree* parent = node->parent;
 
  // split the node into three nodes (we won't keep the center node,
  // but it's convenient to use the splitting function we already have.
  split_node_to_three_nodes(node);
  
  // grab the elements of the center node that we need to keep;
  // change the parent of the children node to their new parent
  int key = node->keys[0];
  tt_tree* left = node->children[0];
  left->parent = parent;
  tt_tree* right = node->children[1];
  right->parent = parent;
  
  // delete the center node that we don't need
  delete(node);
  
  // insert the key and children to the parent node
  insert_data_to_node(parent, key, left, right);
  
  // update the parent number of children
  parent->num_children = count_non_null_children(parent);
}

// steals an element from the parent node--the element to be stolen
// depends on the position of the child--and returns a pointer to
// the parent node so that the parent node can be checked for
// "too small" condition.
void steal_key_from_parent(tt_tree*& node) {
  // break-out parent to improve readability.
  tt_tree* parent = node->parent;
    
  // determine which child of the parent the key is, smallest,
  // middle, or largest.
  int index = node_array_search(parent->children, node);
    
  // get the key to be stolen and decide if the merge will be to
  // the left or the right
  int key_to_steal;
  string merge_direction;
  switch(index) {
    case 2:
      key_to_steal = parent->keys[1];
      merge_direction = "left";
      break;
    case 1:
      key_to_steal = parent->keys[0];
      merge_direction = "left";
      break;
    default:
      key_to_steal = parent->keys[0];
      merge_direction = "right";
  }
    
  // steal the parents key
  insert_data_to_node(node, key_to_steal, NULL, NULL);
  
  // remove the stolen key from the parent's child array
  int stolen_key_index = int_array_search(parent->keys,
                                          key_to_steal);
  delete_key_and_condense_key_array(parent, stolen_key_index);
    
  // decrement the parent's key counter
  parent->num_keys--;
  
  // create some placeholder variables to be populated
  tt_tree* left_side;
  tt_tree* right_side;
  int merged_node_index;
  
  // merge two children surrounding the stolen key
  if (merge_direction == "left") {
    left_side = parent->children[index - 1];
    right_side = parent->children[index];
    merged_node_index = index - 1;
  } else {
    left_side = parent->children[index];
    right_side = parent->children[index + 1];
    merged_node_index = index;
  }
  
  // merge the two children surrounding the stolen key and place the merged
  // node back into the parent's children array
  node = merge(left_side, right_side);
  parent->children[merged_node_index] = node;
  
  // it should always work out that we can copy the child array value two
  // elements down from the merged node into the element location immediately
  // next to the merged node. Then NULL the child array value two elements down
  // This collapses the children array to account for the merged node in a way
  // that's safe and reliable.
  parent->children[merged_node_index + 1] =
  parent->children[merged_node_index + 2];
  
  parent->children[merged_node_index + 2] = NULL;
 
  // after some merges is it neccessary to re-null some
  // of the parent's children array elements
  for (int ii = parent->num_keys + 1; ii < TT_ORDER + 1; ii++) {
    parent->children[ii] = NULL;
  }
  
  // update the parent's number of children
  parent->num_children = count_non_null_children(parent);
  
  // check if the new merged node is now too large
  check_too_large(node);
}

// merges two nodes together; some recursion required since children
// will also need to be merged if not leaf
tt_tree* merge(tt_tree* left, tt_tree* right) {
  // create the new merged node to be populated
  tt_tree* ret = create_node(left->parent, left->root);
  
  // populate the keys from left first then from right
  int ii = 0;
  int jj = ii;
  
  // add left keys
  while (ii < left->num_keys) {
    ret->keys[jj] = left->keys[ii];
    ii++; jj++;
  }
  
  // add right keys
  ii = 0;
  while (ii < right->num_keys) {
    ret->keys[jj] = right->keys[ii];
    ii++; jj++;
  }
  
  // set num_keys as sum of both merged keys
  ret->num_keys = left->num_keys + right->num_keys;
  
  // if either of the keys are not leaves, then it will be
  // necessary to merge the children too. this may require
  // recursion on the middle child. If however, one of the
  // nodes has only a single child, then recusion isn't
  // necessary.
  if (!left->is_leaf) {
    // case where recursion is required--merging two non-empty nodes.
    if (left->num_children > 1 && right->num_children > 1) {
      ii = 0;
      jj = 0;
      
      // add left children except middle one
      while (ii < left->num_keys) {
        ret->children[jj] = left->children[ii];
        ii++; jj++;
      }
      
      int missing_child_index = jj;
      jj++;
      ii = 1;
      
      // add right children except first one
      while (ii < right->num_keys + 1) {
        ret->children[jj] = right->children[ii];
        ii++; jj++;
      }
      
      // create the merged center child and place in the new parent's
      // child array.
      tt_tree* merged_child = merge(left->children[left->num_keys],
                                    right->children[0]);
      ret->children[missing_child_index] = merged_child;
      
      // check if the merged child is too large
      check_too_large(ret->children[missing_child_index]);
      
    // case where recursion is not rquired--one node has zero keys
    } else {
      ii = 0; jj = 0;
      
      // add left children
      while (ii < TT_ORDER + 1 && jj < TT_ORDER + 1) {
        if (left->children[jj] != NULL) {
          ret->children[ii] = left->children[jj];
          ii++;
        }
        jj++;
      }

      // reset the counters for the right children
      jj = 0;
      
      // add right children
      while (ii < TT_ORDER + 1 && jj < TT_ORDER + 1) {
        if (right->children[jj] != NULL) {
          ret->children[ii] = right->children[jj];
          ii++;
        }
        jj++;
      }
    }
    
    // for both case 1 and case 2, set is_leaf to false
    ret->is_leaf = false;
    
    // update the number of children counter
    ret->num_children = count_non_null_children(ret);
  }
  
  // delete both the left and right nodes
  delete(left);
  delete(right);
  
  return ret;
}

void clone_node(tt_tree* node_to_be_filled,
                tt_tree* node_to_be_cloned) {
    
  // move all the keys and children over one-by-one
  for (int ii = 0; ii < TT_ORDER; ii++) {
    node_to_be_filled->keys[ii] = node_to_be_cloned->keys[ii];
    node_to_be_filled->children[ii] = node_to_be_cloned->children[ii];
  }
  node_to_be_filled->children[TT_ORDER] = node_to_be_cloned->children[TT_ORDER];

  // copy over the remaining two fields
  node_to_be_filled->is_leaf = node_to_be_cloned->is_leaf;
  node_to_be_filled->num_keys = node_to_be_cloned->num_keys;
  node_to_be_filled->num_children = node_to_be_cloned->num_children;
}

#endif // SPLIT_FUNCTIONS_CPP
