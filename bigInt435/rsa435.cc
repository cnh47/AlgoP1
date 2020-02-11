// You need to complete this program for a part of your first project.

// Standard libraries
#include <string>
#include <iostream>
#include <stdlib.h>
#include <fstream>

// 'BigIntegerLibrary.hh' includes all of the library headers.
#include "BigIntegerLibrary.hh"

BigInteger findE (BigUnsigned &p, BigUnsigned &q, BigUnsigned &mod);
BigUnsigned AssignBigInt ();
BigUnsigned RandomBigInt ();
bool isPrime (BigUnsigned n);

int main(){
    /* The library throws 'const char *' error messages when things go
     * wrong.  It's a good idea to catch them using a 'try' block like this
     * one.  Your C++ compiler might need a command-line option to compile
     * code that uses exceptions. */
    try {
        // Find primes for P and Q
        BigUnsigned P = AssignBigInt();
        BigUnsigned Q = AssignBigInt();


        // Calculate N
        BigUnsigned N = P * Q;

		// Calculate thetaN
        BigUnsigned thetaN = ( P - 1 ) * (Q - 1);

		// Calculate E
        BigInteger E = findE(P, Q, thetaN);

		// Calculate D
        BigUnsigned D = modinv(E, thetaN);

		//Open Files
		std::ofstream PQ;
		std::ofstream EN;
		std::ofstream DN;
		PQ.open("p_q.txt");
		EN.open("e_n.txt");
		DN.open("d_n.txt");

		//Store Variables
		PQ << P << "\n";
        PQ << Q;
		EN << E << "\n";
        EN << N;
		DN << D << "\n";
        DN << N;

		//Close Files
		PQ.close();
		EN.close();
		DN.close();
        std::cout << "Keys Created & Stored\n";

    } catch(char const* err) {
        std::cout << "The library threw an exception:\n"
            << err << std::endl;
    }
    return 0;
}

BigUnsigned AssignBigInt () {
    while (true) {
        BigUnsigned bigInt = RandomBigInt();
        if (isPrime(bigInt))
            return bigInt;
    }
}

BigInteger findE (BigUnsigned &p, BigUnsigned &q, BigUnsigned &mod) {
    BigUnsigned e;
    while (true) {
        e = rand()%90 + 10;
        if (gcd (e, mod) == 1) {
            return e;
        }
    }
}

BigUnsigned RandomBigInt () {
    BigUnsigned bigIntHolder = BigUnsigned(1);
    for (int i = 0; i < 155; i++) {
        bigIntHolder = bigIntHolder * 10 + rand();
    }
    return bigIntHolder;
}
bool isPrime (BigUnsigned n) {
    BigUnsigned a = BigUnsigned(3);
    for (a; a <= 9; a++) {
        // Verify that a and n are co-prime
        if (gcd(n, a) != 1) {
            return false;
        }
        if (modexp(a, n-1, n) != 1)
            return false;
    }
    return true;
}
