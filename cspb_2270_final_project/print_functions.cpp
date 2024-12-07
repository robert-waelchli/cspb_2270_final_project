#ifndef PRINT_FUNCTIONS_CPP
#define PRINT_FUNCTIONS_CPP

#include <iostream>
#include <climits>
#include <cmath>
#include <sstream>
#include <string>

#include "print_functions.h"

using namespace std;

string get_id_for_dot(tt_tree* node) {
  stringstream ss;
  ss << node; // address in memory
  string as_addr = ss.str();
  as_addr.replace(0, 2, "BT_");
  return as_addr;
}

string get_label_for_dot(tt_tree* node) {
  stringstream ss;
  for (int i = 0; i < node->num_keys; i++) {
    ss << "" << node->keys[i];
    if (i + 1 < node->num_keys) {
      ss << " ";
    }
  }
  return ss.str();
}

void print_dot_label(tt_tree* node) {
  cout << "    " << get_id_for_dot(node) << " [label=\""
       << get_label_for_dot(node) << "\"];" << endl;
}

void print_graphviz_dotfile(tt_tree* node, int depth) {
  string spaces = "    ";
  if (depth == 0) {
    print_dot_label(node);
  }
  int idx = 0;
  string my_id = get_id_for_dot(node);
  for (; idx < node->num_keys; idx++) {
    if (!node->is_leaf) { // don't recurse if this is a leaf.
      print_dot_label(node->children[idx]);
      cout << spaces << my_id << " -- " << get_id_for_dot(node->children[idx])
           << ";" << endl;
      print_graphviz_dotfile(node->children[idx], depth + 1);
    }
  }
  // there is always one leftover child, assuming it is not a leaf.
  if (!node->is_leaf) {
    print_dot_label(node->children[idx]);
    cout << spaces << my_id << " -- " << get_id_for_dot(node->children[idx])
         << ";" << endl;
    print_graphviz_dotfile(node->children[idx], depth + 1);
  }
}

// print_tree prints the tree to stdout using the graphviz 'dot'
// format. just copy the generated text and run it through graphviz to
// view it.
//
// there is a web-based viewer at http://www.webgraphviz.com/
void print_tree(tt_tree* root) {
  cout << "graph btree {" << endl;
  int depth = 0;
  print_graphviz_dotfile(root, depth);
  cout << "}" << endl;
}

#endif // PRINT_FUNCTIONS_CPP
