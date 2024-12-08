//
//  main.cpp
//  cspb_2270_final_project
//
//  Created by Robert Waelchli on 12/02/24.
//

#ifndef MAIN
#define MAIN

#include <iostream>
#include <fstream>
#include <unistd.h>
#include "display_functions.h"
#include "print_functions.h"
#include "split_push_steal_merge_functions.h"

int main() {
  
  // instantiate a new 23-Tree from heap memory
  tt_tree* directory_demo = create_node(NULL, NULL);
  
  // attempt to load in directory records from memory file
  bool successful_load = read_from_memory_file(directory_demo);
  if (!successful_load) {
    cout << "ERROR with file load. Program will exit now." << endl;
    return 1;
  } else {
    cout << "Successful file load, continuing." << endl;
  }
  
  // cout statement for formatting
  cout << endl;
  
  // this is the data we attempt to load from the file:
  
  //  (720) 555-1111, Jon Doe, Bricklayer
  //  (720) 555-1112, Jane Doe, Doctor
  //  (720) 555-1113, Fred Orange, Computer Programmer
  //  (720) 555-1114, Betty Grable, Technicain
  //  (720) 555-1115, Lee Zhang, Engineer
  //  (720) 555-1116, Zephram Cochrane, Scientist
  //  (720) 555-1117, Stanley Tool, Chef
  //  (720) 555-1118, Tiffany Patel, Data Scientist
  //  (720) 555-1119, Donna Smith, Real Estate
  //  (720) 555-1120, Blake Tap, Restaurateur
  
  // -- end file data --
  
  // while the user does not select to exit, display main menu
  // and respond to user inputs.
  int user_choice = 8;
  while (user_choice > 0) {
    display_main_menu();
    cin >> user_choice;
    user_choice = user_request_handling(user_choice,
                                        directory_demo);
  }
  return 0;
}

#endif // MAIN
