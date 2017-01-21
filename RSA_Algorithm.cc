// RSA Assignment for ECE4122/6122 Fall 2015
// C.V. Chaitanya Krishna

#include <iostream>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include "RSA_Algorithm.h"

using namespace std;

// Implement the RSA_Algorithm methods here

// Constructor
RSA_Algorithm::RSA_Algorithm()
  : rng(gmp_randinit_default)
{
  // get a random seed for the random number generator
  int dr = open("/dev/random", O_RDONLY);
  if (dr < 0)
    {
      cout << "Can't open /dev/random, exiting" << endl;
      exit(0);
    }
  unsigned long drValue;
  read(dr, (char*)&drValue, sizeof(drValue));
  //cout << "drValue " << drValue << endl;
  rng.seed(drValue);
// No need to init n, d, or e.
}

// Fill in the remainder of the RSA_Algorithm methods
void RSA_Algorithm::GenerateRandomKeyPair(size_t sz)
{
  int flag_pq, chkInv, primeCheckP, primeCheckQ;
  mpz_class p, q, p1, q1, phi, gcd;
  flag_pq=1;
  chkInv=0;

  while (flag_pq==1 || chkInv==0)
  {
    primeCheckP=0;
    while (primeCheckP==0)
    {
      p=rng.get_z_bits(sz);
      primeCheckP=mpz_probab_prime_p (p.get_mpz_t(), 100); 
    }

    primeCheckQ=0;  
    while (primeCheckQ==0)
    {
      q=rng.get_z_bits(sz);
      primeCheckQ=mpz_probab_prime_p (q.get_mpz_t(), 100); 
    }

    if(p==q)
      flag_pq=1;    
    else
      flag_pq=0;
	
    mpz_mul(n.get_mpz_t(),p.get_mpz_t(),q.get_mpz_t());
    p1=p-1;
    q1=q-1;
   
    mpz_mul(phi.get_mpz_t(),p1.get_mpz_t(),q1.get_mpz_t());
    gcd = 0;
    while(gcd!=1 || d>phi)
    {
      d=rng.get_z_bits(sz*2);
      mpz_gcd(gcd.get_mpz_t(), d.get_mpz_t(), phi.get_mpz_t());  
    }
    
    chkInv = mpz_invert(e.get_mpz_t(), d.get_mpz_t(), phi.get_mpz_t());
  }
}

mpz_class RSA_Algorithm::PlainTextGenerator(size_t sz)
{
  mpz_class PT;
  int flag=0;
  while (flag==0)
  {
    PT=rng.get_z_bits(2*sz);
    if (PT<n)
      flag=1;
  }
  return PT;
}

mpz_class RSA_Algorithm::Encrypt(mpz_class M)
{
  mpz_class C;  
  mpz_powm(C.get_mpz_t(), M.get_mpz_t(), e.get_mpz_t(), n.get_mpz_t());
  return C;
}

mpz_class RSA_Algorithm::Decrypt(mpz_class C)
{
  mpz_class MafterC;  
  mpz_powm(MafterC.get_mpz_t(), C.get_mpz_t(), d.get_mpz_t(), n.get_mpz_t());
  return MafterC;
}


void RSA_Algorithm::PrintND()
{ // Do not change this, right format for the grading script
  cout << "n " << n << " d " << d << endl;
}

void RSA_Algorithm::PrintNE()
{ // Do not change this, right format for the grading script
  cout << "n " << n << " e " << e << endl;
}

void RSA_Algorithm::PrintNDE()
{ // Do not change this, right format for the grading script
  cout << "n " << n << " d " << d << " e " << e << endl;
}

void RSA_Algorithm::PrintM(mpz_class M)
{ // Do not change this, right format for the grading script
  cout << "M " << M << endl;
}

void RSA_Algorithm::PrintC(mpz_class C)
{ // Do not change this, right format for the grading script
  cout << "C " << C << endl;
}