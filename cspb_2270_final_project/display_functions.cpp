//
//  display_functions.cpp
//  cspb_2270_final_project
//
//  Created by Robert Waelchli on 12/08/24.
//

#ifndef DISPLAY_FUNCTIONS_CPP
#define DISPLAY_FUNCTIONS_CPP

#include "display_functions.h"
#include "print_functions.h"

using namespace std;

// reads stored data from a properly formatted memory file into a
// tt_tree object; returns true if the read was successful.
bool read_from_memory_file(tt_tree* tree) {
  
  // change the working directory to the location of the records file
  const char* directory = "/Users/waelchli/Documents/mac_cpp_projects/cspb_2270_final_project/cspb_2270_final_project/records";
  
  if (chdir(directory) == 0) {
    std::cout << "Working directory now set.\n";
  } else {
    std::cerr << "Error: Unable to change the working directory.\n";
  }
  
  // read in saved data from file
  ifstream input_file;
  input_file.open("records.txt");
  
  // error handling
  if (!input_file.is_open()) {
    cerr << "Error opening the file!" << endl;
    return false;
  }
 
  string line;
  while (getline(input_file, line)) {
    insert(tree, create_data_packet(line));
  }
  
  // close the input file stream
  input_file.close();
  
  return true;
}

// function that displays the main menu.
void display_main_menu() {
  cout << "== Main Menu ==" << endl;
  cout << "Pleease choose from the following options:" << endl;
  cout << endl;
  cout << "1. Insert new record" << endl;
  cout << "2. Remove existing record" << endl;
  cout << "3. View existing record" << endl;
  cout << "4. Count current keys" << endl;
  cout << "5. Count current nodes" << endl;
  cout << "6. Print current tree" << endl;
  cout << "7. Quit and Exit" << endl;
  cout << endl;
  cout << "Make your selection now [1, 2, ..., etc.]: ";
}

// functions that handles user menu choice; returns an integer to
// drive further actions.
int user_request_handling(int choice, tt_tree* tree) {
  int ret = 0;
  int nodes;
  int keys;
  
  switch (choice) {
    case 1:
      user_insert_function(tree);
      ret = 8;
      break;
    case 2:
      user_remove_function(tree);
      ret = 8;
      break;
    case 3:
      user_find_function(tree);
      ret = 8;
      break;
    case 4:
      keys = count_keys(tree);
      cout << endl;
      cout << "There are currently " << keys <<
        " keys in the database." << endl;
      cout << endl;
      ret = 8;
      break;
    case 5:
      nodes = count_nodes(tree);
      cout << endl;
      cout << "There are currently " << nodes <<
        " nodes in the database." << endl;
      cout << endl;
      ret = 8;
      break;
    case 6:
      cout << endl;
      print_tree(tree);
      cout << endl;
      ret = 8;
      break;
    case 7:
      ret = -1;
      break;
    default:
      ret = -1;
      break;
  }
  return ret;
}

// function that handles manual user insert of new data.
void user_insert_function(tt_tree* tree) {
  
  // instantiate a new data_packet from heap memory
  data_packet* packet = new data_packet();
  
  // walk user through entering the required fields
  cout << endl;
  cout << "Hello! I will walk you through making a new entry." << endl;
  cout << endl;
  cout << "First, please enter the an area code [three digits]: ";
  cin >> packet->area_code;
  cout << endl;

  cout << "Good, now enter a phone number [seven digits]: ";
  cin >> packet->phone_num;
  cout << endl;
  
  string first_name;
  cout << "Good, now enter a first name: ";
  cin >> first_name;
  
  string last_name;
  cout << "Good, now enter a last name: ";
  cin >> last_name;
  cout << endl;
  
  packet->name = first_name + " " + last_name;

  string occupation;
  cout << "Finally, enter an occupation: ";
  cin >> packet->occupation;
  cout << endl;
  
  // insert the new packet into the tree
  insert(tree, packet);
  
  // update user on progress
  cout << "User added. Return to Main Menu." << endl;
  cout << endl;
}

// function that handles manual user removal of data.
void user_remove_function(tt_tree* tree) {
  // prompt user for key
  cout << endl;
  cout << "Please enter the key/phone number you'd like to remove." << endl;
  cout << "Should be seven digits, no area code [ex: 1234567]: ";
  
  // user defines key for removal
  int key;
  cin >> key;
  
  // remove key
  remove(tree, key);
  
  // update user on progress
  cout << "User removed. Return to Main Menu." << endl;
  cout << endl;
}

// function that handles user retrieval of data.
void user_find_function(tt_tree* tree) {
  bool repeat = true;
  
  while (repeat) {
    // prompt user for key
    cout << endl;
    cout << "Please enter the key/phone number you'd like to retrieve." << endl;
    cout << "Should be seven digits, no area code [ex: 1234567]: ";
    
    // user defines key for removal
    int key;
    cin >> key;
    
    // retrieve key
    tt_tree* found_node;
    int del;
    find_node_and_index(tree, key, found_node, del);
    
    // get data_packet with information
    data_packet* data = found_node->data_map[key];
    
    // display the data
    cout << endl;
    cout << "Name: " << data->name << endl;
    cout << "Phone Number: " << data->area_code << " "
    << data->phone_num << endl;
    cout << "Occupation: " << data->occupation << endl;
    
    cout << endl;
    
    // give user the option to repeat
    string repeat_choice;
    cout << "Would you like to retrieve another record [yes/no]: ";
    cin >> repeat_choice;
    
    if (repeat_choice == "yes" || repeat_choice == "YES") {
      repeat = true;
    } else {
      repeat = false;
    }
  }
  // update user on progress
  cout << endl;
  cout << "Return to Main Menu." << endl;
  cout << endl;
}

#endif // DISPLAY_FUNCTIONS_CPP
