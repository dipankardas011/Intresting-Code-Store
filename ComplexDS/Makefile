CP = g++
CC = cc
CFLAGS = -g -w -Wall

BTREE = B_treeg
MWAYTREE = MWayTree
B_P_TREE = B+_tree

BTree:
	$(CP) $(CFLAGS) -o ../ComplexDS/$(BTREE).out ../ComplexDS/$(BTREE).cpp
	echo "Compiled main.c ✅"
	./$(BTREE).out

MWayTree:
	$(CC) $(CFLAGS) -o ../ComplexDS/$(MWAYTREE).out ../ComplexDS/$(MWAYTREE).c
	echo "Compiled main.c ✅"
	./$(MWAYTREE).out

B+Tree:
	$(CC) $(CFLAGS) -o ../ComplexDS/$(B_P_TREE).out ../ComplexDS/$(B_P_TREE).c
	echo "Compiled main.c ✅"
	./$(B_P_TREE).out


clean:
	rm *.out
	echo "Cleaned 🧹"
