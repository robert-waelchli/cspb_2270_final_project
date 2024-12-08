//
//  display_functions.h
//  cspb_2270_final_project
//
//  Created by Robert Waelchli on 12/08/24.
//

#ifndef DISPLAY_FUNCTIONS_H
#define DISPLAY_FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <unistd.h>
#include "tt_tree.h"

using namespace std;

// reads stored data from a properly formatted memory file into a
// tt_tree object; returns true if the read was successful.
bool read_from_memory_file(tt_tree*);

// function that displays the main menu.
void display_main_menu();

// functions that handles user menu choice; returns an integer to
// drive further actions.
int user_request_handling(int, tt_tree*);

// function that handles manual user insert of new data.
void user_insert_function(tt_tree*);

// function that handles manual user removal of data.
void user_remove_function(tt_tree*);

// function that handles user retrieval of data.
void user_find_function(tt_tree*);

#endif // DISPLAY_FUNCTIONS_H
