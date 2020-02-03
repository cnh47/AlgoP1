// You need to complete this program for a part of your first project.

// Standard libraries
#include <string>
#include <iostream>
#include <stdlib.h>
#include <fstream>


// 'BigIntegerLibrary.hh' includes all of the library headers.
#include "BigIntegerLibrary.hh"

int main(){
	/* The library throws 'const char *' error messages when things go
	 * wrong.  It's a good idea to catch them using a 'try' block like this
	 * one.  Your C++ compiler might need a command-line option to compile
	 * code that uses exceptions. */
	try {

      std::cout << "a couple of test cases for 3460:435/535 Algorithms!!!\n";
      BigUnsigned p = BigUnsigned(1);
      for (int i=0;i<400;i++) {
         p = p*10 +rand();
      }
      std::cout << "my big1 !!!\n";
      std::cout << p << std::endl;
	  std::ofstream pq;
	  pq.open("p_q.txt");
	  pq << p << std::endl;

      BigUnsigned q = BigUnsigned(1);
      for (int i=0;i<400;i++) {
         q = q*10 +rand();
      }
      std::cout << "my big2 !!!\n";
      std::cout << q << std::endl;
	   pq << q << std::endl;

      std::cout << "my big3 = big1*big2 !!!\n";
      BigUnsigned n = p*q;
      std::cout << n << std::endl;
	  std::ofstream en;
	  en.open("e_n.txt");
	  std::ofstream dn;
	  dn.open("d_n.text");
	  en << n << std::endl;
	  dn << n << std::endl;

      std::cout << "my big3/big2 !!!\n";
      std::cout << n/q << std::endl;

	} catch(char const* err) {
		std::cout << "The library threw an exception:\n"
			<< err << std::endl;
	}

	return 0;
}
