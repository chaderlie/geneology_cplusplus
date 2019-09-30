#ifndef PEDITERATOR_H
#define PEDITERATOR_H

#include "genNode.h"
#include <iostream>
#include <cassert>
using namespace std;




//template <class PedIterator>
/*PedIterator operator++ (const PedIterator & iter, int postfix)
{
  PedIterator tmp(iter.pointer);
  iter.pointer = iter.pointer->pNext;
  return tmp;
}*/


/**************************************************
 * PEDIGREE ITERATOR
 * An iterator that works with the Pedigree.
 *************************************************/
class PedIterator
{
public:
PedIterator() : pointer(NULL) {}
PedIterator(GenNode * pointer) : pointer(pointer) {}

PedIterator(const PedIterator & rhs)
{ 
   *this = rhs;
}

PedIterator operator++(int postfix)
{
      PedIterator tmp(*this);
      
      pointer = pointer->pNext;
      
      return tmp;
}
   
//friend PedIterator operator++ (const PedIterator & iter, int postfix);

PedIterator & operator = (const PedIterator & rhs)
{
  this->pointer = rhs.pointer;
  return *this;
}

  bool operator == (const PedIterator & rhs) const
   {
      return (this->pointer == rhs.pointer);
   }
   
Person & operator *()
{
return pointer->info;
}

  bool operator != (const PedIterator & rhs) const
   {
      return (rhs.pointer != this->pointer);
   }
   
   GenNode * pointer;
};




/*}
  public:
  
   //Default constructor
  PedIterator() : pointer(NULL) {}
  
   //Initialize to direct pointer to some item
  PedIterator(GenNode * pointer) : pointer(pointer) {}
  
   //Copy constructor
   PedIterator(const PedIterator & rhs)
   {
      *this = rhs;
   }
  
   //Assignment operator
   PedIterator & operator = (const PedIterator & rhs)
      {
         this->pointer = rhs.pointer;
         return *this;
      }
  
   //Overloaded equals operator
 
  
   //Overloaded not-equals operator
 
  
   //Overloaded dereference operator to return the info
   Person & operator * ()
   {
      return (pointer->info);
   }
  
   //Overloaded prefix increment
   PedIterator & operator ++ ()
   {
      pointer = pointer->pNext;
      return *this;
   }

   //Overloaded postfix increment


   //Overloaded prefix decrement
   PedIterator & operator -- ()
   {
      pointer = pointer->pPrev;
      return *this;
   }
   //Overloaded postfix decrement
   PedIterator operator--(int postfix)
   {
      PedIterator tmp(*this);
      pointer = pointer->pPrev;
      return tmp;
   }
   
//  private:
  
   GenNode * pointer;   //Our pointer to our node
    //Let the Pedigree see our private things
};
*/
#endif  //PEDITERATOR_H