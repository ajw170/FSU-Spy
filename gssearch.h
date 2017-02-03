/*
    gssearch.h
    Februay 2, 2017
    Andrew Wood
    FSU ID: ajw14m
 
    Generic Sequential Search Algorithm
 
    This is an implementation of the generic tempalted sequential search algorithm.  The algorithm
    takes parameters of type T, I, and optionally a third parameter of type P.
 
    about I
    =======
    I is a forward iterator that provides no random access.  This type of iterator is used with lists,
    where iterating step-by-step through the list is the only option, as binary search would be impossible
    since there is no random access.
 
    I supports the following operations:
    
    I&  operator++();       //prefix
    I   operator++(int);    //postfix
    
    The bracket operator is not definied since this is not random access.  However, the * operator is
    defined as in
 
    T&  operator*();            //dereference operator
    const T& operator*() const  //const version
 
 
    Examples include: List<T>::Iterator.
 
    about T
    =======
 
    T is the value type of the iterator I
 
 
    about P
    =======
 
    P is the predicate class used for order; an object cmp of class P has the function evaluation
    overloaded with the prototype
 
    bool operator () (const T&, constT&).
 
    Note that P must be used to order the elements so that P can work as a search condition.
 
    If no P is specified, the default "<" operation is used.
 
 
    General Information
    ===================
 
    g_lower_bound() and g_upper_bound() implement sequential search for forward iterators.  It is assumed
    that by the time these functions are called the elements in the List container are in nondecreasing order
    (using operator < or an applicable predicate object).
 
    g_lower_bound() returns an iterator to the first location containing the search value if found;
    if it is not found, it returns the location where it would be.
    g_upper_bound() returns atn iteratorto the first element whos element is greater than the search
    value if it exists, or the end iterator otherwise (one past the last)
 
    Note that sequential search could be fast if the value is found in the beginning of the list but could
    also be very slow; the number of compares could be up to the numbe of items in the list (unlike binary search, where the max value is log2(n)
 
 */

#ifndef gssearch_h
#define gssearch_h

#include <compare.h> //allows for default < predicate if none is specified

namespace seq
{
    template <class I, typename T, class P>
    I g_lower_bound (I low, I hih, const T& val, P& cmp)
    //pre:  I is a forward iterator;  no random access
    //      I has value type T
    //      low + n = hih for some n >= 0
    //      low[0]...low[n-1] are in non-decreasing order
    //post: no state is changed
    //return: itr = lower bound location in range, that is:
    //        itr = low + i, where low[i-1] < val <= low[i] or
    //        itr = hih i fno such i exists
    {
        T item; //initialize item
        
        while (low != hih) //while iterator is pointing to item in list
        {
            item = *low; //set item to low; avoids invalid derefernce within loop
            if (cmp(item, val)) //if the current item is less than searched for value
            {
                ++low;
            }
            else //if current item is equal to or greater than searhed for value
                return low; //return position of iterastor
        }
        return low; //return pointer to one-after the last
    }
    
    
    template <class I, typename T, class P>
    I g_upper_bound (I low, I hih, const T& val, P&cmp)
    // pre:    I is a forward iterator; no random access
    //         I has ValueType T
    //         low + n = hih for some n >= 0
    //         low[0] ... low[n-1] are in non-decreasing order using cmp
    // post:   no state is changed
    // return: itr =  low + i, where low[i-1] <= val < low[i]; or
    //         itr = hih if no such i exists
    {
        T item; //initialize item
        
        while (low != hih)
        {
            item = *low; //set item to lowest item; avoids invalid dereference in loop
            if (cmp(val,item)) //if the value being searched for is less than the item
            {
                return low; //upper bound found, return.
            }
            else
                ++low; //increment iterator
        }
        return low; //maximum value reached in range
    }
    
    
    //functions for if no comparator predicate object is supplied
    
    template <class I, typename T>
    I g_lower_bound (I low, I hih, const T& val)
    {
        fsu::LessThan<T> cmp;
        return seq::g_lower_bound(low, hih, val, cmp);
    }
    
    template <class I, typename T>
    I g_upper_bound (I low, I hih, const T& val)
    {
        fsu::LessThan<T> cmp;
        return seq::g_upper_bound(low, hih, val, cmp);
    }
    
} // end namespace seq

#endif /* gssearch_h */
