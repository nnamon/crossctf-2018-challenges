BabyRSA3
---------

Realise that phi(n) that is given can be factorised. Run pollard rho's on it, and using
a bitmask, try all possible combination of p and q. Speed ups are highly necessary as
this is a computationally intensive challenge.

Note: There are 22 factors, 2 of which are 2s. Once of each belongs to p and q. Then
use a bitmask to generate the multiples of numbers for p and q. Total possible number
of p / q: `(2^20)/2 = 2^19 ~ 500K`.

# Question Text

```
So I heard that you can flip the private and public information for RSA...
```

*Creator -- prokarius (@prokarius)*

# Setup Guide

1. All RSA ciphertexts are given in outNerfed.txt

# Exploit Details

Working exploit is in src/solution.py.
Exploit has Pollard Rho's implemented (it runs in 10 minutes on my computer),
however it might be faster to use online factorisation tools such as
[this ECM factorisation][ECM] calculator.

1 more speedup to consider:
p and q should ideally have approximately equal length, so
instead of considering all possible bit masks, you only consider masks that
allows p and q to not differ by too many bits initially.

[ECM]: https://www.alpertron.com.ar/ECM.HTM
