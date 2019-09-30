#include "pedigree.h"



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
   insert(end(), newPerson);
}

/***************************************************
 * Pedigree :: push_front
 * Add the new item to the end of the Pedigree.
 **************************************************/

void Pedigree :: push_front(const Person & newPerson)
{
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
   }

   //Reassign the pointers so that we have our new pTail
   else if(pedIter.pointer == pTail)
   {
      pedIter.pointer->pPrev->pNext = NULL;
      pTail = pedIter.pointer->pPrev;

   }

   //We're in the middle, so we will reassign pointers accordingly
   else
   {
      pedIter.pointer->pNext->pPrev = pedIter.pointer->pPrev;
      pedIter.pointer->pPrev->pNext = pedIter.pointer->pNext;

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

PedIterator Pedigree :: insert(PedIterator insertBefore, const Person & newPerson) throw (const char *)
{
   GenNode * newNode;

   //Let's allocate!
   try
   {
      newNode = new GenNode;
   }
  
   //Well, that didn't work
   catch(bad_alloc)
   {
      throw "ERROR: unable to allocate a new node for a Pedigree";
   }

   //Add the info
   newNode->info = newPerson;

   //If we don't have a head or a tail, our new node IS our Pedigree
   if (pHead == NULL || pTail == NULL)
   {
      pHead = newNode;
      pTail = newNode;
      numItems = 1;
      return insertBefore;
   }

   //If it's NULL, that means we have to put it on the end
   else if (insertBefore == end())
   {
      pTail->pNext = newNode;
   
      newNode->pPrev = pTail;
   
      pTail = newNode;
   
   }

   //Not the end? Middle or head it is!
   else
   {
      newNode->pNext = insertBefore.pointer;
      newNode->pPrev = insertBefore.pointer->pPrev;
      insertBefore.pointer->pPrev = newNode;

      //If it's the head, we just reassign the pHead pointer
      if (insertBefore.pointer == pHead)
         pHead = newNode;

      //No head? Reassign the previous's pNext
      else
         newNode->pPrev->pNext = newNode;
   }

   //Reset the iterator
   insertBefore.pointer = newNode;

   //We added a thing!
   numItems++;

   //Return the iterator
   return insertBefore;
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
  