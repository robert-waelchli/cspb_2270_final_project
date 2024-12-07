#ifndef MAIN
#define MAIN

#include <iostream>
#include "print_functions.h"
#include "split_push_steal_merge_functions.h"

int main() {
    
  tt_tree* my_tree = create_node(NULL, NULL);
  
  // (720) 555-1111, Jon Doe, Bricklayer
  // (720) 555-1112, Jane Doe, Doctor
  // (720) 555-1113, Fred Orange, Computer Programer
  // (720) 555-1114, Betty Grable, Technicain
  // (720) 555-1115, Lee Zhang, Engineer
  
  data_packet* first = create_data_packet(720, 5551111, "Jon Doe", "Bricklayer");
  data_packet* second = create_data_packet(720, 5551112, "Jane Doe", "Doctor");
  data_packet* third = create_data_packet(720, 5551113, "Fred Orange", "Computer Programmer");
  
  insert(my_tree, first);
  insert(my_tree, second);
  insert(my_tree, third);

  print_tree(my_tree);

  int node_count = count_nodes(my_tree);
  int key_count = count_keys(my_tree);
  
  tt_tree* one = my_tree->children[0];
  tt_tree* two = my_tree;
  tt_tree* three = my_tree->children[1];
  
  
  cout << "One: " << one->data_map[one->keys[0]]->name << endl;
  cout << "Two: " << two->data_map[two->keys[0]]->name << endl;
  cout << "Three: " << three->data_map[three->keys[0]]->name << endl;
  
  return 0;
}

#endif // MA
