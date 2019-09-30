/***********************************************************************
* Header:
*    PERSON CLASS
* Summary:
*    This file contains the class definition of a Person. It has a string
*    for a last name, a string for given names, a string for the ID number,
*    and a string for the birthdate. Its >, <, =, and == are overloaded to
*    deal with comparisons and assignments. 
* Author
*    Claire Haderlie
************************************************************************/

#ifndef PERSON_H
#define PERSON_H

#include <cassert>
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

/************************************************
 * PERSON
 * Definition of Person class
 ***********************************************/
class Person
{
  public:

//Default constructor
  Person() : idNum(""), givenName(""), 
      lastName(""), birthdate("") {}
  
  //Copy constructor
  Person(const Person & rhs)
  {
    this->lastName = rhs.lastName;
    this->givenName = rhs.givenName;
    this->birthdate = rhs.birthdate;
    this->idNum = rhs.idNum;
  }
      

   //Overload the insertion operator to output the name correctly
   friend ostream & operator<< (ostream & out, const Person & rhs);  

   //Overload the comparison operator to compare two Persons
   bool operator == (const Person & rhs) const; 
   
   //Overload the greater than operator to compare two Persons
   bool operator > (const Person & rhs) const; 
   
   //Overload the smaller than operator to compare two Persons
   bool operator < (const Person & rhs) const; 
   
   //Overload the assignment operator to assign a person
   Person & operator =(const Person & rhs);
   
   string birthdate;   //Birthdate of the person
   string givenName;   //Given names of the person
   string lastName;    //Last name of the pwerson
   string idNum;       //ID number of the person   
  
};

/********************************************************************
 * OPERATOR >
 * This overloaded operator checks to see if THIS person is greater
 * than the RHS. It first compares last names, then first names, then
 * birthdates.
 *******************************************************************/
bool Person :: operator > (const Person & rhs) const 
{
  //If they're the same, we'll just return true
   if(*this == rhs)
    return true;

  //Create a temporary string for both sides of the comparison
    string tempLHS = this->lastName;
   string tempRHS = rhs.lastName;
   
   //Make sure that the first letter of each string is capitalized
     if(!this->lastName.empty())
    tempLHS[0] = toupper(tempLHS[0]);
        
     if(!rhs.lastName.empty())
    tempRHS[0] = toupper(tempRHS[0]);
  
  //If THIS person is greater, return true!
   if (tempLHS > tempRHS)
      return true;
        
   //If they are the same last name, OR they're both empty, compare given names and birthdates     
   else if(tempLHS == tempRHS || (this->lastName.empty() && rhs.lastName.empty()))
   {
     //If THIS given name is greater, return true!
     if(this->givenName > rhs.givenName)
         return true;
        
    //If they have the same given name, check the birthdates 
     else if(this->givenName == rhs.givenName)
      {
         string rhsYear = "";
         string lhsYear = "";
          
          //If the birthday is not empty, get the year from it 
         if(!(this->birthdate.empty()))
         {
           //Start at the beginning of the year
            int i = (this->birthdate.size()) - 5;
          
            //Get each digit of the year
           while (i < this->birthdate.size())
           {
             lhsYear += this->birthdate[i];
             i++;
           }
         }

//If the birthday is not empty, get the year from it
         if(!rhs.birthdate.empty())
         {
         //Start at the beginning of the year
            int i = (rhs.birthdate.size()) - 5;
            
   //Get each digit of the year
            while (i < rhs.birthdate.size())
            {
               rhsYear += rhs.birthdate[i];            
               i++;
            }              
         }

        //If THIS year is greater, return true;
         if (lhsYear > rhsYear)
            return true;
      }     
   }

  //Well. It's not true!
   return false;
}

/*******************************************************************
 * OPERATOR >
 * This overloaded operator checks to see if THIS person is smaller
 * than the RHS. It first compares last names, then first names, then
 * birthdates.
 *******************************************************************/
bool Person :: operator < (const Person & rhs) const 
{
//If they're the same, we'll just return false
if(*this == rhs)
return false;

 //Create a temporary string for both sides of the comparison
   string tempLHS = this->lastName;
   string tempRHS = rhs.lastName;
   
     //Make sure that the first letter of each string is capitalized
     if(!this->lastName.empty())
    tempLHS[0] = toupper(tempLHS[0]);
        
     if(!rhs.lastName.empty())
    tempRHS[0] = toupper(tempRHS[0]);
    
    //If THIS person is smaller, return true!
  if (tempLHS < tempRHS)
    return true;
  
  //If they are the same last name, OR they're both empty, compare given names and birthdates
  else if(tempLHS == tempRHS || (this->lastName.empty() && rhs.lastName.empty()))
   {
   //If THIS given name is greater, return true!
     if (this->givenName < rhs.givenName)
         return true;
      
           
    //If they have the same given name, check the birthdates 
      else if(this->givenName == rhs.givenName)
      {
         string rhsYear = "";
         string lhsYear = "";

          //If the birthday is not empty, get the year from it 
         if(!this->birthdate.empty())
         {
         //Start at the beginning of the year
            int i = this->birthdate.size() - 5;
           
 //Get each digit of the year
            while (this->birthdate[i])
               {
               lhsYear += this->birthdate[i];
               i++;
               }
         }
 //If the birthday is not empty, get the year from it 
         if(!rhs.birthdate.empty())
         {
          //Start at the beginning of the year
            int i = rhs.birthdate.size() - 5;
          
 //Get each digit of the year
            while (rhs.birthdate[i])
               {
               rhsYear += rhs.birthdate[i];
             i++;
           }
         }
   //If THIS year is smaller, return true;
         if (lhsYear < rhsYear)
            return true;

      } 
   }
   
   //Well. It's not true
  return false;
}

/*********************************************************************
* OPERATOR =
* This overloaded operatore takes one Person and copies everything into
* THIS Person
**********************************************************************/
Person & Person :: operator = (const Person & rhs)
{
  //Copy last name
   this->lastName = rhs.lastName;
   
   //Copy given name
   this->givenName = rhs.givenName;
   
   //Copy birthdate
   this->birthdate = rhs.birthdate;
   
   //Copy ID number
   this->idNum = rhs.idNum;
   
   //Return the copied item
  return *this;
}

/*******************************************************************
 * OPERATOR <<
 * This overloaded operator outputs a Person's information in the 
 * following format:
 *       GivenName GivenName LastName, b. Day MONTH Year 
 ******************************************************************/
ostream & operator << (ostream & out, const Person &rhs)
{
  //If they have a given name, output it
   if (!rhs.givenName.empty())
   {
      out << rhs.givenName;
      
      //If they have a last name, they'll need a space
      if (!rhs.lastName.empty())
       out << " ";  
   } 
  
  //If they have a last name, output it
   if(!rhs.lastName.empty())
      out << rhs.lastName;

//If there is a birthday, output it
   if (!rhs.birthdate.empty())
   {    
      out << ", b. " << rhs.birthdate;
   }

//Output an endline
   out << endl;
    
    //Return the output
   return out;
}

/*************************************************************
 * OPERATOR ==
 * This overloaded operator checks to see if two Persons are
 * identical 
 *************************************************************/
bool Person :: operator == (const Person & rhs) const 
{
  return(this->lastName == rhs.lastName 
  && this->givenName == rhs.givenName 
  && this->birthdate == rhs.birthdate
  && this->idNum == rhs.idNum);  
}



#endif // NODE_H

