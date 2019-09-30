# geneology_cplusplus

This program reads in a .ged file from the command line.

It inserts the information into Persons objects and puts the Persons into Gen(eology) Nodes. 

The nodes are put into a Pedigree, which is a doubly linked list / binary tree implementation.

The Persons are inserted into the list in alphabetical order first by last name, then first name, 
then by birthdate. 

The sorted list is written into the sorted.dat file. 

After the alphabetizing is completed and writen, the family section of the .ged file is read in. 
The program assembles the families by linking the pMom and pDad pointers to the appropriate Person objects.

The program then outputs each generation of ancestors to the screen.
