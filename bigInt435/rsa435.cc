// You need to complete this program for a part of your first project.

// Standard libraries
#include <string>
#include <iostream>
#include <stdlib.h>
#include <fstream>

// 'BigIntegerLibrary.hh' includes all of the library headers.
#include "BigIntegerLibrary.hh"

bool isPrime(const BigUnsigned& number);
BigUnsigned AssignBigInt();
void sha256();

int main(){
	/* The library throws 'const char *' error messages when things go
	 * wrong.  It's a good idea to catch them using a 'try' block like this
	 * one.  Your C++ compiler might need a command-line option to compile
	 * code that uses exceptions. */
	try {

	//Make random number by time
	srand(time(NULL));

	//get P prime
	BigUnsigned P = BigUnsigned(1);
	P = AssignBigInt();
	while(!isPrime(P)){
	  P = AssignBigInt();
	}

	//get Q prime
	BigUnsigned Q = BigUnsigned(1);
	Q = AssignBigInt();
	while(!isPrime(P)){
	  Q = AssignBigInt();
	}

	//get N
	BigUnsigned N = (P - 1) * (Q - 1);

	//get e
	BigUnsigned E = AssignBigInt(), two = 2, remainder = E, q;
	remainder.divideWithRemainder(two, q);
	BigUnsigned gcdV = gcd(N, E);
	// while the gcd is not 1 or the E is not negative
	while ((gcdV != 1) || (remainder != 1)){
	    E = AssignBigInt();
	    remainder = E;
	    remainder.divideWithRemainder(two, Q);
	    gcdV = gcd(N, E);
	}


	//get D
	BigUnsigned D = modinv(E, N);

	//Open Files
	std::ofstream PQ;
	std::ofstream EN;
	std::ofstream DN;

	PQ.open("p_q.txt");
	EN.open("e_n.txt");
	DN.open("d_n.txt");

	//Store Variables
	PQ << P << std::endl;
	PQ << Q << std::endl;

	EN << E << std::endl;
	EN << N << std::endl;

	DN << D << std::endl;
	DN << N << std::endl;

	//Display Values
	std::cout << "This is your P: \n" << P << std::endl;
	std::cout << "This is your Q: \n" << Q << std::endl;
	std::cout << "This is your E: \n" << E << std::endl;
	std::cout << "This is your N: \n" << N << std::endl;
	std::cout << "This is your D: \n" << D << std::endl;

	/* MESSAGE ENCRYPTION */
	std::ofstream sha256;
	sha256.open("file.txt");

	sha256 << "Decrypted";
	


	} catch(char const* err) {
		std::cout << "The library threw an exception:\n"
			<< err << std::endl;
	}

}

bool isPrime(const BigUnsigned& number){
	// the a value in Fermat's test - (a ^ ( p - 1)) % p
    BigInteger a1 = 2;
	BigInteger a2 = 3;

    BigUnsigned Test1 = modexp(a1, (number - 1), number);
    BigUnsigned Test2 = modexp(a2, (number - 1), number);

    if ((Test1 == 1) && (Test2 == 1))
        return true;
    else
        return false;
}

BigUnsigned AssignBigInt(){
	BigUnsigned n = BigUnsigned(1);
	while(n.bitLength() < 100){
		 n = n * 10 +rand();
	}
	return n;

}

void sha256(){

}
