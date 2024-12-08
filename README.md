Robert Waelchli
CSPB-2270, Fall 2024

Final Project Walkthrough/Readme - 2-3 Tree

Project goal: Create an example implementation of a 23-Tree data structure. For this example, 
I choose to implement the 2-3 tree as a directory of professionals (names, phone numbers, occupation).


2-3 Tree Definition and Invariants:
A 2-3 tree is a tree data structure where each node has either two or three children, essentially a B-tree of 
order 3. [1] [2] It is balanced, meaning all leaf-nodes occur at the same level, and data is spread evenly or 
close to evenly across the tree. [2]

For my 2-3 Tree, I have defined the following invariants:

  1. Balanced
  2. Data is stored in sorted order
  3. Each node is either a 2-node or a 3-node

I have found in my research that there are some conflicts between sources as to additional invariants, however
these three have been universal acorss definitions as far as I can tell.


Project-Specific 2-3 Tree Implementation:
For my project, I have chosen to implement a directory of professionals including the following fields:

  1. Name
  2. Phone Number
  3. Occupation

Obviously these fields are fairly arbitrary and any set of data could have been substituted for the purpose of
illustration. The seven-digit phone number (not including the area code) works well because it can also double
directly (with no substitution or conversion) for the key of the record. Since I'm not including the area code
there is a small risk that two records could have the same seven-digit phone number, but I judged that risk to 
be acceptably small with the limited size of the data sets I intended to use for this demonstration.

I wrote the program using Xcode on my Mac Mini. It has been stored on GitHub at the following repository:

  https://github.com/robert-waelchli/cspb_2270_final_project.git

This is a public project and should be readily accessible.

The program consists of the following files:

  1. /records/records.txt
  2. main.cpp
  3. tt_tree.h
  4. tt_tree.cpp
  5. split_push_steal_merge_functions.h
  6. split_push_steal_merge_functions.cpp
  7. display_functions.h
  8. display_functions.cpp
  9. print_functions.h
  10. print_functions.cpp


Walkthough:
In order for the program to be successfully run locally, it is necessary to modify the path to the records.txt
file. This is manually coded within the display_functions.cpp file, within the read_from_memory_file() function.

Once the path is correctly set, the program will run by reading in 10 demonstration records from the records.txt
file that are meant to illustrate the program pulling in records from a memory storage location. This action will
build an initial tree with ten records stored across eight nodes. An illustration of this initial tree, made
with assistance from http://webgraphviz.com/ is included in the project directory as "initial_tree.png."

Once loaded with the initial tree built, a menu will display that should be fairly self explanatory. The user 
has options for the following actions:

  1. Insert new record
  2. Remove existing record
  3. View existing record
  4. Count current keys
  5. Count current nodes
  6. Print current tree
  7. Quit and Exit

Option 6, to print the current tree, copies code directly from the B-Tree Assignemnet #5 of our course, CSPB-2270. 
[3] I judged this to be an acceptable re-use of that code--with attribution of course--given that the print function
is not a core functionality of the project and is merely included as a convenience for the user/instructor/grader
to help visualize the structure with the assistance of http://webgraphviz.com/.

References:
[1] 2-3 Trees | (Search, Insert and Deletion). GeeksforGeeks.org. https://www.geeksforgeeks.org/2-3-trees-search-and-insert/
[2] 2-3 tree. Wikipedia.org. https://en.wikipedia.org/wiki/2%E2%80%933_tree
[3] CSPB-2270
