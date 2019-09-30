/***********************************************************************
* Header:
*   PEDIGREE CLASS
* Summary:
*   This program holds the implementation of the Pedigree class. It is a
*   a linked list / binary tree hybrid. It has all the functions needed
*   to sort and insert Persons into the linked list by storing them in
*   Geneology Nodes.
* Author
*   Claire Haderlie
************************************************************************/

#ifndef PEDIGREE_H
#define PEDIGREE_H

#include <cassert>
#include <iostream>
using namespace std;

#include "genNode.h"
#include "pedIterator.h"
#include "person.h"


/************************************************
 * Pedigree
 ***********************************************/
class Pedigree
{
  public:
   
   //Default constructor to set everything up.
  Pedigree(): numItems(0), pHead(NULL), pTail(NULL) {}
   
   //Copy constructor to copy over a Pedigree.
   Pedigree(const Pedigree & rhs) throw (const char *);
   
   //Destructor to delete the info variable.
   ~Pedigree()    {  if (pHead) clear(); }
   
   //The Pedigree is empty, true or false?
   bool empty() const { return (pHead == NULL);}
   
   //Clear out everything that was allocated
   void clear();
   
   //Let us see how many items we have.
   int size() const { return numItems;}
   
   //Let us insert something! We will insert it BEFORE the place that the iterator has
   PedIterator insert(PedIterator insertBefore, const Person & newPerson) throw (const char *);

   //This function finds where a Person should go and calls insert()
   void sortAndInsert(const Person & newPerson);
   
   //Return the last item in the Pedigree
   Person & back() throw (const char *);
   
   //Return the first item in the Pedigree
   Person & front() throw (const char *);

   //Add the new info onto the back of the Pedigree
   void push_back(const Person & newPerson);

   //Add the new info onto the front of the Pedigree
   void push_front(const Person & newPerson);

   //Remove and properly delete a node in the Pedigree
   void remove(PedIterator pedIter) throw (const char *);

   //Return an iterator to the beginning of the Pedigree
   PedIterator  begin() const { return PedIterator(pHead); }
  
   //Return an iterator to the end of the Pedigree
   PedIterator  end() const { return PedIterator(NULL);}

   //Return an iterator to the beginning of the Pedigree
   PedIterator  rbegin() const { return PedIterator(pTail); }

   //Return an iterator to the end of the Pedigree
   PedIterator  rend() const { return PedIterator(NULL); }
 
   //Overload the equals operator
   Pedigree & operator = (const Pedigree & rhs);
  
  private:
   int numItems;  //How many items we have   
   GenNode * pHead; //Where the Pedigree begins
   GenNode * pTail; //Where the Pedigree ends
};

/***************************************************
 * Pedigree :: back
 * Return the last info item in the Pedigree
 **************************************************/
Person & Pedigree :: back() throw (const char *) 
{
   //Check to make sure we have at least one node
   if (pTail)
      return pTail->info;
   
   //Nope, no node
   else
      throw "ERROR: unable to remove from an empty Pedigree";
}

/***************************************************
 * Pedigree :: front
 * Return the last info in the Pedigree.
 **************************************************/
Person & Pedigree  :: front() throw (const char *)
{
   //Check to make sure we have at least one node
   if (pHead)
      return pHead->info;
   
   //Nope, no node
   else
      throw "ERROR: unable to remove from an empty Pedigree";
}

/***************************************************
 * Pedigree :: clear
 * This function deallocates the memory for each
 * node in the Pedigree;
 **************************************************/
void Pedigree :: clear()
{
   //Remove each item
   for(PedIterator pedIter = begin(); pedIter != end(); pedIter++)
   {
      remove(pedIter);
   }
   
   //Now we have no items!
   numItems = 0;
   
   //Set them to NULL, just in case.
   pTail = NULL;
   pHead = NULL;
   
   return;
}

/***************************************************
 * Pedigree :: push_back
 * Add the new item to the end of the Pedigree.
 **************************************************/
void Pedigree :: push_back(const Person & newPerson)
{
   //Insert at the end
   insert(end(), newPerson);
}

/***************************************************
 * Pedigree :: push_front
 * Add the new item to the end of the Pedigree.
 **************************************************/
void Pedigree :: push_front(const Person & newPerson)
{
   //Insert at the front
   insert(begin(), newPerson);
}

/***************************************************
 * Pedigree :: Remove
 * Remove an item from the Pedigree
 **************************************************/
void Pedigree :: remove(PedIterator pedIter) throw (const char *)
{
   //If it's null, we cannot remove it.
   if (pedIter == end())
   {
      throw "ERROR: unable to remove from an invalid location in a Pedigree";
   }
   
   //We removeth something!
   numItems--;
   
   //If we only have one thing, we only delete the one thing
   if (pHead == pTail)
   {
      delete pHead;
      pHead = NULL;
      pTail = NULL;
      return;
   }
   
   //Reassign the pointers so that we have our new pHead
   if (pedIter.pointer == pHead)
   {
      pedIter.pointer->pNext->pPrev = NULL;   
      pHead = pedIter.pointer->pNext;
      return;
   }
   
   //Reassign the pointers so that we have our new pTail
   else if(pedIter.pointer == pTail)
   {
      pedIter.pointer->pPrev->pNext = NULL;
      pTail = pedIter.pointer->pPrev;
      return;
      
   }
   
   //We're in the middle, so we will reassign pointers accordingly
   else
   {
      pedIter.pointer->pNext->pPrev = pedIter.pointer->pPrev;
      pedIter.pointer->pPrev->pNext = pedIter.pointer->pNext;
      return;
   }
   
   //Delete, the last of all!
   delete pedIter.pointer;
}

/*******************************************
 * Pedigree :: COPY CONSTRUCTOR
 *******************************************/
Pedigree :: Pedigree(const Pedigree  & rhs) throw (const char *)
{
   
   //Set everything to be empty at the beginning
   numItems = 0;
   pHead = NULL;
   pTail = NULL;
   
   //If the rhs is NULL, that's all we need.
   if (rhs.begin() == NULL)
   {
      return;
   }
   
   //Push each item in the rhs onto the new Pedigree. 
   for(PedIterator pedIter = rhs.begin(); pedIter != rhs.end(); pedIter++)
   {
      push_back(*pedIter);
   }
   
   //Set the number of items to be the same
   numItems = rhs.numItems;
   
}

/***************************************************
 * Pedigree :: INSERT
 * Insert an item on the end of the Pedigree
 * return iterator to the item just inserted
 **************************************************/
PedIterator Pedigree :: insert(PedIterator insertBefore, 
                               const Person & newPerson) throw (const char *)
{
   GenNode * newGenNode;
   
   try
   {
      newGenNode = new GenNode;
   }
   
   //Well, that didn't work
   catch(bad_alloc)
   {
      throw "ERROR: unable to allocate a new node for a Pedigree";
   }
   
   newGenNode->info = newPerson;
   
   //If we don't have a head or a tail, our new node IS our Pedigree
   if (pHead == NULL || pTail == NULL)
   {
      pHead = newGenNode;
      pTail = newGenNode;
      numItems = 1;
      return insertBefore;
   }
   
   //If it's NULL, that means we have to put it on the end
   else if (insertBefore == end())
   {
      pTail->pNext = newGenNode;
      
      newGenNode->pPrev = pTail;
      
      pTail = newGenNode;
      
   }
   
   //Not the end? Middle or head it is!
   else
   {
      newGenNode->pNext = insertBefore.pointer;
      newGenNode->pPrev = insertBefore.pointer->pPrev;
      insertBefore.pointer->pPrev = newGenNode;
      
      //If it's the head, we just reassign the pHead pointer
      if(insertBefore == begin())
         pHead = newGenNode;
      
      //No head? Reassign the previous's pNext
      else
         newGenNode->pPrev->pNext = newGenNode;
   }
   
   //Reset the iterator
   insertBefore.pointer = newGenNode;
   
   //We added a thing!
   numItems++;
   
   //Return the iterator
   return insertBefore;
}

/***********************************************************
* PEDIGREE :: SORT AND INSERT
* This function finds where the Person should go and it 
* inserts it into the Pedigree
************************************************************/
void Pedigree :: sortAndInsert(const Person & newPerson)
{ 
   //If there is nothing in the list, we shall insert at the beginning
   if(empty())
   {
      insert(begin(), newPerson);
      return;   
   }   
   
   //Go through the list and see where we should go
   for (GenNode * pNode = pHead; pNode != NULL; pNode = pNode->pNext)
   {
      
      PedIterator it = PedIterator(pNode);
      
      //If the next Node pointer is NULL and the array value
      //is greater than the current data value, insert it at the end
      if (!pNode->pNext && newPerson > pNode->info)
      {              
         insert(end(), newPerson);
         break;
      }
      
      //If the array value is greater than the current data value
      //and the next data value, continue through the array.
      else if (newPerson > pNode->info && newPerson > pNode->pNext->info)
      {
         continue;
      }
      
      //If the array value is less than the data value, insert at the head 
      else if(newPerson < pNode->info)
      {
         insert(it, newPerson);
         break;            
      }
      
      //Let's just put it in then!
      else
      {
         it = PedIterator(pNode->pNext);
         insert(it, newPerson);
         break;
      }   
      
   }
}

/***************************************************
 * Pedigree :: operator =
 * Overload the assignment operator to copy an entire
 * linked Pedigree.
 **************************************************/
Pedigree & Pedigree :: operator = (const Pedigree & rhs)
{
   
   //If our lhs has things, we need to clear them out and reset everything
   if(pHead != NULL)
   {
      //Clear it out
      clear();
      
      //Reset!
      numItems = 0;
      pHead = NULL;
      pTail = NULL;
      
   }
   
   //Go through the rhs and add everything to our lhs
   for(PedIterator pedIter = rhs.begin(); pedIter != rhs.end(); pedIter++)
   {
      push_back(*pedIter);
   }
   
   //Set the number of items
   numItems = rhs.numItems;
   
   //Return our Pedigree!
   return (*this);
}
   
#endif // PEDIGREE_H
