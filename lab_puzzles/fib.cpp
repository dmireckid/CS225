/**
 * @file fib.cpp
 * Contains Fibonacci-number generating functions both utilizing and not
 * utilizing memoization.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "fib.h"

#include <map>

using std::map;

/**
 * Calculates the nth Fibonacci number where the zeroth is defined to be
 * 0.
 * @param n Which number to generate.
 * @return The nth Fibonacci number.
 */
unsigned long fib(unsigned long n)
{
    /* Your code goes here! */
    if(n==0){
      return 0;
    }
    else if(n==1){
      return 1;
    }
    else{
      return fib(n-1)+fib(n-2);
    }
    //return 0;
}

/**
 * Calculates the nth Fibonacci number where the zeroth is defined to be
 * 0. This version utilizes memoization.
 * @param n Which number to generate.
 * @return The nth Fibonacci number.
 */
unsigned long memoized_fib(unsigned long n)
{
    /* Your code goes here! */
    static map<unsigned long, unsigned long> memoization1 = {
      {1,1}
    };
    static map<unsigned long, unsigned long> memoization2 = {
      {0,0}
    };
    map<unsigned long, unsigned long>::iterator find1 = memoization1.find(n);
    map<unsigned long, unsigned long>::iterator find2 = memoization2.find(n);

    if(find1 != memoization1.end()){
      return find1->second;
    }
    else if(find2 != memoization2.end()){
      return find2->second;
    }
    else{
      unsigned long temp = memoized_fib(n-1) + memoized_fib(n-2);
      memoization1[n] = temp;
      return temp;
    }
    //return 0;
}
