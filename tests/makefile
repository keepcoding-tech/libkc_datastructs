###############################################################################
# MARK: COMPILE
###############################################################################

run_tests: run_tests.c data_structures/node.c ../data_structures/utils/Node.c data_structures/linked_list.c ../data_structures/lists/LinkedList.c data_structures/queue.c ../data_structures/lists/Queue.c data_structures/binary_search_tree.c ../data_structures/trees/BinarySearchTree.c data_structures/entry.c ../data_structures/utils/Entry.c data_structures/dictionary.c ../data_structures/sets/Dictionary.c
	gcc -o run_tests run_tests.c data_structures/node.c ../data_structures/utils/Node.c data_structures/linked_list.c ../data_structures/lists/LinkedList.c data_structures/queue.c ../data_structures/lists/Queue.c data_structures/binary_search_tree.c ../data_structures/trees/BinarySearchTree.c data_structures/entry.c ../data_structures/utils/Entry.c data_structures/dictionary.c ../data_structures/sets/Dictionary.c

###############################################################################
# MARK: CLEAN
###############################################################################

# Remove the run_tests file
clean:
	rm run_tests
