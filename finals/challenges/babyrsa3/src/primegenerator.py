import random
import math
import sys

def rabinMiller(n):
    s = n-1
    t = 0
    while s&1 == 0:
        s = s/2
        t +=1
    k = 0
    while k<128:
        a = random.randint(2,n-1)
        #a^s is computationally infeasible.  we need a more intelligent approach
        #v = (a**s)%n
        #python's core math module can do modular exponentiation
        v = pow(a,s,n) #where values are (num,exp,mod)
        if v != 1:
            i=0
            while v != (n-1):
                if i == t-1:
                    return False
                else:
                    i = i+1
                    v = (v**2)%n
        k+=1
    return True

def isPrime(n):
    #lowPrimes is all primes (sans 2, which is covered by the bitwise and operator)
    #under 1000. taking n modulo each lowPrime allows us to remove a huge chunk
    #of composite numbers from our potential pool without resorting to Rabin-Miller
    lowPrimes =   [3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97
                   ,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179
                   ,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269
                   ,271,277,281,283,293,307,311,313,317,331,337,347,349,353,359,367
                   ,373,379,383,389,397,401,409,419,421,431,433,439,443,449,457,461
                   ,463,467,479,487,491,499,503,509,521,523,541,547,557,563,569,571
                   ,577,587,593,599,601,607,613,617,619,631,641,643,647,653,659,661
                   ,673,677,683,691,701,709,719,727,733,739,743,751,757,761,769,773
                   ,787,797,809,811,821,823,827,829,839,853,857,859,863,877,881,883
                   ,887,907,911,919,929,937,941,947,953,967,971,977,983,991,997]
    if (n >= 3):
        if (n&1 != 0):
            for p in lowPrimes:
                if (n == p):
                    return True
                if (n % p == 0):
                    return False
            return rabinMiller(n)
    return False

# Takes a threshold and generates a number that is prime
def generate_prime(seed):
    while True:
        if isPrime(seed):
            return seed
        else:
            seed += 2

def generate_large_prime(threshold, factorlow, factorhigh, bigboy):
    attempt = 0
    while True:
        randompowertwo = 1
        attempt += 1

        factors = [2] * randompowertwo
        out = 2**randompowertwo
        while out < threshold:
            randomseed = random.randint(factorlow, factorhigh)
            if (randomseed % 2 == 0):
                randomseed += 1
            smallprime = generate_prime(randomseed)
            factors.append(smallprime)
            out *= smallprime

        if bigboy:
            factors.append (bigprime)
            out *= bigprime

        print("Trying out attempt number + " + str(attempt))
        print("Prime is " + str(out + 1))
        if isPrime(out+1):
            print ('Success!')
            return factors

bigprime = generate_prime(2**350 + 97)

def get_phin():
    pfactors = generate_large_prime (2**550, 5*10**8, 10**13, False)
    print ("p ready")
    qfactors = generate_large_prime (2**200, 5*10**8, 10**13, True)
    print ("q ready")

    p = 1
    for i in pfactors:
        p *= i
    p += 1

    q = 1
    for i in qfactors:
        q *= i
    q += 1

    print ("p = ", pfactors)
    print ("q = ", qfactors)
    print ("Numfactors ", len(pfactors + qfactors))
    print ("n = " + str(p*q))
    print ("phin = " + str((p-1)*(q-1)))

get_phin()
