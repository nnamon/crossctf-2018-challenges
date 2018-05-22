#!/usr/bin/python2.7
from fractions import gcd
import random

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

def isNotPrime(n):
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
    for i in lowPrimes:
        if n % i == 0:
            return True
    return False

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

def pollards_rho(n):
    x = 2; y = 2; d = 1
    f = lambda x: (x**2 + 1) % n
    while d == 1:
        x = f(x); y = f(f(y))
        d = gcd(abs(x-y), n)
    if d != n: return d

def factor(n):
    if isPrime(n):
        factors.append(n)
        return

    print n
    p = pollards_rho(n)
    print p
    if isPrime(p):
        factors.append(p)
    else:
        factor(p)

    if isPrime(n/p):
        factors.append(n/p)
    else:
        factor(n/p)

factors = []

c = int((raw_input().split())[2])
d = int((raw_input().split())[2])
phin = int((raw_input().split())[2])
#factor(phin)

factors = [4754509728797, 6579600728639, 9566431650679, 4065711354007, 6938103821809, 2293498615990071511610820895302086940796564989168281123737588839386922876088484808070018553110125686555051, 3680247726403, 6545600536253, 7265658595571, 6060693342503, 1984419944251, 2767687179787, 3639128890921, 6672422609813, 9220079755217, 7230980905199, 1973804930501, 6438418759151, 8313722160551, 333600482773]

factors.sort()

def decod(k):
    o = []
    while k > 0 :
        o.append(chr(k%256))
        k /= 256
    o.reverse()
    return (''.join(o))

def mul_inv(a, b):
    b0 = b
    x0, x1 = 0, 1
    if b == 1: return 1
    while a > 1:
        q = a / b
        a, b = b, a%b
        x0, x1 = x1 - q * x0, x0
    if x1 < 0: x1 += b0
    return x1

loopcount = 0
top = 2 ** (len(factors)-1)
while loopcount < top:
    if (loopcount % 50000 == 0):
        print loopcount
    bitmask = loopcount
    p = 2
    q = 2
    count = 0
    while (count < len(factors)):
        if (bitmask % 2):
            p *= factors[count]
        else:
            q *= factors[count]
        bitmask /= 2
        count += 1

    p += 1
    q += 1

    if isNotPrime(p) or isNotPrime(q):
        loopcount += 1
        continue

    n = p*q
    e = 1000000007
    d = mul_inv(e, phin)
    m = pow(c, d, n)

    message = decod(m)
    if "CrossCTF" in message:
        print message

    loopcount += 1
