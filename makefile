# keepcoding lib
#
# Daniel Tanase
# 16/1/22

###############################################################################
# MARK: COMPILE
###############################################################################

output: tests/main.c tests/data_structures/node.c data_structures/utils/Node.c
	gcc -o tests/main tests/main.c tests/data_structures/node.c data_structures/utils/Node.c

###############################################################################
# MARK: CLEAN
###############################################################################

# Remove the main file
clean:
	rm tests/main
