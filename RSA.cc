// ECE4122/6122 RSA Encryption/Decryption assignment
// Fall Semester 2015
// C.V. Chaitanya Krishna

#include <iostream>
#include "RSA_Algorithm.h"
#include <math.h>

using namespace std;

int main()
{
  // Instantiate the one and only RSA_Algorithm object
  RSA_Algorithm RSA;
  mpz_class PT, CT, DT;
  // Loop from sz = 32 to 1024 inclusive
  // for each size choose 100 different key pairs
  // For each key pair choose 100 differnt plaintext 
  // messages making sure it is smaller than n.
  // If not smaller then n then choose another
  // For eacm message encrypt it using the public key (n,e).
  // After encryption, decrypt the ciphertext using the private
  // key (n,d) and verify it matches the original message.

  // your code here
  int success_count=0;
  int fail_count=0;
  for (int i=0; i<6; i++)
  {
    size_t sz=pow(2,(5+i));
    for (int j=0; j<100; j++)
    {
      RSA.GenerateRandomKeyPair(sz);
      RSA.PrintNDE();
      for (int k=0; k<100; k++)
      {
        PT=RSA.PlainTextGenerator(sz);
        RSA.PrintM(PT);
        CT=RSA.Encrypt(PT);
        RSA.PrintC(CT);
        DT=RSA.Decrypt(CT);
        //RSA.PrintM(DT);
          if (DT==PT)
            success_count++;
      	  else
      	    fail_count++;
      }
     // cout<<"success count = "<<success_count<<endl;
     // cout<<"fail count = "<<fail_count<<endl;
    }
   }
}