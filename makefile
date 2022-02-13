# keepcoding lib
#
# Daniel Tanase
# 16/1/22

###############################################################################
# MARK: ALL
###############################################################################

# Create top level static library and all sub-libraries
all: main data_structures

###############################################################################
# MARK: MAIN
###############################################################################

# Creates just the top level static library
main: data_structures_sub
	ar rcs keepcoding.a data_structures/trees/BinarySearchTree.o data_structures/sets/Dictionary.o data_structures/utils/Entry.o data_structures/lists/LinkedList.o data_structures/utils/Node.o data_structures/lists/Queue.o

###############################################################################
# MARK: DATA STRUCTURES
###############################################################################

# Creates the data structures library
data_structures: data_structures_sub
	ar rcs data_structures/DataStructures.a data_structures/trees/BinarySearchTree.o data_structures/sets/Dictionary.o data_structures/utils/Entry.o data_structures/lists/LinkedList.o data_structures/utils/Node.o data_structures/lists/Queue.o

# Sub components of the data structures library
data_structures_sub: BinarySearchTree Dictionary Entry LinkedList Node Queue

BinarySearchTree:
	gcc -c data_structures/trees/BinarySearchTree.c && mv BinarySearchTree.o data_structures/trees

Dictionary:
	gcc -c data_structures/sets/Dictionary.c && mv Dictionary.o data_structures/sets

Entry:
	gcc -c data_structures/utils/Entry.c && mv Entry.o data_structures/utils

LinkedList:
	gcc -c data_structures/lists/LinkedList.c && mv LinkedList.o data_structures/lists

Node:
	gcc -c data_structures/utils/Node.c && mv Node.o data_structures/utils

Queue:
	gcc -c data_structures/lists/Queue.c && mv Queue.o data_structures/lists

###############################################################################
# MARK: CLEAN
###############################################################################

# Remove the main file
clean_all:
	rm *.o data_structures/lists/*.o data_structures/sets/*.o data_structures/trees/*.o data_structures/utils/*.o *.a data_structures/*.a

clean_o:
	rm *.o data_structures/lists/*.o data_structures/sets/*.o data_structures/trees/*.o data_structures/utils/*.o

clean_a:
	rm *.a data_structures/*.a
