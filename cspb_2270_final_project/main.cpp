#ifndef MAIN
#define MAIN

#include <iostream>
#include "print_functions.h"
#include "split_push_steal_merge_functions.h"

int main() {
    
  tt_tree* my_tree = create_node(NULL, NULL);
  insert(my_tree, 4);
  insert(my_tree, 6);

  insert(my_tree, 8);

  insert(my_tree, 2);

  insert(my_tree, 13);

  insert(my_tree, 3);

  insert(my_tree, 11);

  insert(my_tree, 5);

  insert(my_tree, 7);
  // print_tree(my_tree);
  insert(my_tree, 9);
  // print_tree(my_tree);
  insert(my_tree, 10);
  // print_tree(my_tree);
  insert(my_tree, 14);
  // print_tree(my_tree);
  insert(my_tree, 9);
  // print_tree(my_tree);
  insert(my_tree, 3);
  // print_tree(my_tree);
  insert(my_tree, 2);
  print_tree(my_tree);
  insert(my_tree, 2);
  print_tree(my_tree);
  insert(my_tree, 1);
  insert(my_tree, 2);
  insert(my_tree, 3);
  insert(my_tree, 4);
  insert(my_tree, 5);
  insert(my_tree, 21);
  insert(my_tree, 22);
  insert(my_tree, 23);
  insert(my_tree, 24);
  insert(my_tree, 25);
  insert(my_tree, 26);
  insert(my_tree, 27);
  insert(my_tree, 28);
  insert(my_tree, 29);
  insert(my_tree, 30);
  print_tree(my_tree);
  
  int node_count = count_nodes(my_tree);
  int key_count = count_keys(my_tree);
  
  cout << "Nodes: " << node_count << endl;
  cout << "Keys: " << key_count << endl;
  
  return 0;
}

#endif // MA
