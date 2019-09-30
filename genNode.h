/***********************************************************************
* Header:
*    Gen(eology) Node Class
* Summary:   
*    This file contains the class definition of a Geneology Node (GenNode)
*    which is used in a Pedigree (linked list/tree implementation). The GenNode
*    has a pointer to the next thing in the list, the last thing in the list
*    and pointers to a "Dad" and "Mom" (left and right in the tree). It also
*    has a displayByLevel function that displays the pedigree by generations.
* Author
*    Claire Haderlie
************************************************************************/

#ifndef GENNODE_H
#define GENNODE_H

#include <cassert>
#include <iostream>
#include <iomanip>

#include "person.h"
using namespace std;

/************************************************
 * Gen(eology) Node
 * This is the class used for building a Pedigree 
 ***********************************************/
class GenNode
{
  public:
   
   //Default constructor
  GenNode() : pPrev(NULL), pNext(NULL), pDad(NULL),
      pMom(NULL) {}
   
   //Non-default constructor--like above
  GenNode(const Person & newData) : pPrev(NULL), pNext(NULL),
      pDad(NULL), pMom(NULL), info(newData), numItems(1) {}
   
   //Set the info of the GenNode
   void setData(Person & newData) {info = newData;}
   
   //The GenNode already exists, but just make the parent equal to the one we have
   GenNode * addMom(GenNode * newMom);
   
   //Create new Mom node and add it.
   GenNode * addMom(const Person & newMom)  throw (const char *);
      
   //The GenNode already exists, but just make the parent equal to the one we have
   GenNode * addDad(GenNode * newMom);
   
   //Create new node and add it.
   GenNode * addDad(const Person & newDad)  throw (const char *);
      
   //Display the GenNodes by level-order traversal
   void displayByLevel();
    
   //Return the number of nodes in the tree
   int size();
   
   
   int numItems;      //Number of items in the list

   Person info;       //Information of the person
   GenNode * pDad;    //Pointer to the father of the tree
   GenNode * pMom;    //Pointer to the mother of the tree
   GenNode * pNext;   //Pointer to the next thing in the list
   GenNode * pPrev;   //Pointer to the previous thing in the list
};

/*****************************************************
* DISPLAY BY LEVEL
* This function uses level-order traversal to output
* the GenNode and its parents.
*****************************************************/
void GenNode :: displayByLevel()
{
   //We will have, at most, 149 people in our queue. 200 just in case!
   const int MAX = 200;
   
   //Make a queue
   GenNode *queue[MAX];
   
   //Make a temporary 
   GenNode *temp;

   //Set front, back, savedBack, and number of generations
   int front = 0;
   int back = 0;
   int numGens = 0;
   int savedBack = 1; 
   
   //Set the first thing in the queue to be the node we have
   queue[back++] = this;
   
   //While we're not at the end of the queue
   while (front != back)
   {
      //Get the first item from the queue and increment the front
      temp = queue[front];
      front = (front + 1) % MAX;
      
      if(front == savedBack)
      {
         //Get the line where the next generation starts
         savedBack = back + 1;
         
         //Put the correct generation header
         switch(numGens)
         {
            case 0:
               cout << "The Ancestors of ";
               break;
            case 1:
               cout << "Parents:\n";
               break;
            case 2:
               cout << "Grandparents:\n";
               break;
            case 3:
               cout << "Great Grandparents:\n";
               break;
            case 4:
               cout << "2nd Great Grandparents:\n";
               break;
            case 5:
               cout << "3rd Great Grandparents:\n";
               break;
            case 6:
            case 7:
               cout << numGens - 2 << "th Great Grandparents:\n";
               break;
            default:
               break;
         }

         //Increment the number of generations
         numGens++;
      } 
      
         
      if (temp != NULL)
      {     
         
         //If it is the first person in the tree, we output the header
         if(temp->info.idNum == "1")
         {  
            cout << temp->info.givenName 
                 << " " 
                 << temp->info.lastName
                 << ":" 
                 << endl;
         }
         
         //Otherwise, just output the information
         else
         {
            //The cout.width(4) thing was not working, so spaces it is!
            cout << "        " 
                 << temp->info; 
         }
         
         //Put the temp's dad into the queue and increment the back 
         queue[back] = temp->pDad;
         back = (back + 1) % MAX;
         
         //Put the temp's mom into the queue and increment the back
         queue[back] = temp->pMom;
         back = (back + 1) % MAX;            
      }         
   }
}

/***************************************************
 * GEN NODE :: SIZE
 * This function returns the size of the family 
 ***************************************************/ 
int GenNode :: size()
{
   if (this)
   {
      return (numItems + pDad->size() + pMom->size());
   }
   
   else
      return 0;
}

/***************************************************
 * GEN NODE :: Add Dad
 * This function takes in a GenNode pointer and
 * sets THIS pDad to point to it.
 ***************************************************/
GenNode * GenNode :: addDad(GenNode * newDad)
{
   //Even if this is NULL, it's okay
   this->pDad = newDad;
      
   return this;
}

/***************************************************
 * GEN NODE :: Add Dad
 * This function takes in a Person. It creates a new
 * GenNode, sets its info to be the Person, and sets
 * THIS GenNode's pDad to point to it
 ***************************************************/
GenNode * GenNode :: addDad(const Person & newDad) throw (const char *)
{
   GenNode * newGenNode;

   //Attempt to allocate
   try
   {
      newGenNode = new GenNode;
   }

   //Well, that didn't work
   catch(std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a node";
   }

   //Add in the info
   newGenNode->info = newDad;

   //Reassign the pointer
   this->pDad = newGenNode;

   return this;
}

/***************************************************
 * GEN NODE :: Add Mom
 * This function takes in a GenNode pointer and
 * sets THIS pMom to point to it.
 ***************************************************/
GenNode * GenNode :: addMom(GenNode * newMom)
{
   //Add it the mum! Even if she's NULL
   this->pMom = newMom;
   
   return this;
}

/***************************************************
 * GEN NODE :: Add Mom
 * This function takes in a Person. It creates a new
 * GenNode, sets its info to be the Person, and sets
 * THIS GenNode's pMom to point to it
 ***************************************************/
GenNode * GenNode :: addMom(const Person & newMom) throw (const char *)
{
   GenNode * newGenNode;
   
   //Attempt to allocate
   try
   {
      newGenNode = new GenNode;
   }
   
   //Attempt failed
   catch(std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a node";
   }

   //Add in the info
   newGenNode->info = newMom;

   //Reassign the pointers
   this->pMom = newGenNode;
   //newGenNode->pPrev = this;


   return this;
}
  
/**************************************************
 * Delete Binary Tree
 * This function correctly deletes an entire Binary
 * Tree. It uses recursion to go through each node
 * in postfix traversal.
 **************************************************/
void deleteBinaryTree(GenNode * & genNode)
{
   //If it exists, we shall go through some recursion
   if(genNode)
   {
      //Left first!
      deleteBinaryTree(genNode->pDad);

      //Right second!
      deleteBinaryTree(genNode->pMom);

      //Visit and delete!
      delete genNode;

      //Aaaaand it's gone
      genNode = NULL;

   }
   
   return;
}

#endif // NODE_H

