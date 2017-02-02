/*
    compare_spy.h
    02/01/2017
    Andrew Wood
 
    Defines and implements the predicate class template LessThanSpy<T>
    
    The code is self-documenting.
 
    LessThanSpy<T> is a predicate class that returns true when t1 < t2.  LessThanSpy<T>
    predicate objects also ahve an internal counter that increments each time the object
    is called.  The intention is to check the number of times that comparator object
    (in this case LessThanSpy<T> object) is called when used with a generic algorithm.
*/

#ifndef _COMPARE_SPY_H
#define _COMPARE_SPY_H

namespace fsu  //place compare_spy in the fsu namespace
{
    
    template < typename T >
    class LessThanSpy
    {
    public:
        //default constructor
        LessThanSpy () : counter(0)
        {}
        
        //operator () allows the object to be called by passing arguments
        bool operator () (const T& t1, const T& t2)
        {
            ++counter; //increment call count
            return (t1 < t2);
        }
        
        void Reset() //sets internal counter to zero
        {
            counter = 0;
        }
        
        size_t Count() const //returns current number of calls
        {
            return counter;
        }
        
    private: //private access; only accessed within class
        size_t counter; // holds the number of call counts
    }; // end class LessThanSpy<T>
    
} // end namespace fsu

#endif
