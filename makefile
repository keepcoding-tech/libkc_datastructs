# keepcoding lib
#
# Daniel Tanase
# 16/1/22

###############################################################################
# MARK: COMPILE
###############################################################################

output: tests/main.c tests/data_structures/node.c data_structures/utils/Node.c tests/data_structures/linked_list.c data_structures/lists/LinkedList.c tests/data_structures/queue.c data_structures/lists/Queue.c
	gcc -o tests/main tests/main.c tests/data_structures/node.c data_structures/utils/Node.c tests/data_structures/linked_list.c data_structures/lists/LinkedList.c tests/data_structures/queue.c data_structures/lists/Queue.c

###############################################################################
# MARK: CLEAN
###############################################################################

# Remove the main file
clean:
	rm tests/main
