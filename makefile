###############################################################
# Program:
#     Week 13, Geneology Project
#     Data structures, CS235
# Author:
#     Claire Haderlie Hocker
# Summary:
#     This program reads in a .ged file from the command line.
#     It inserts the information into Persons and puts the Persons
#     into Gen(eology) Nodes. The nodes are put into a Pedigree,
#     which is a doubly linked list / binary tree implementation.
#     The Persons are inserted into the list in alphabetical order
#     first by last name, then first name, then by birthdate. The
#     sorted list is written into the sorted.dat file. 
#
#     After the alphabetizing is completed and writen, the family 
#     section of the .ged file is read in. The program assembles
#     the families by linking the pMom and pDad pointers to the 
#     appropriate Persons. The program then outputs each generation
#     of ancestors to the screen.
#
#
#############################################################

a.out: final.o
	g++ -o a.out final.o -g
	tar -cf final.tar *.h *.cpp makefile

final.o: person.h genNode.h pedIterator.h pedigree.h final.cpp
	g++ -c final.cpp -g


clean:
	rm a.out *.o *.tar
all : a.out
