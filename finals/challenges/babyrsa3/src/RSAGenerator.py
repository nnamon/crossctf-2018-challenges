import random

def bti(bytes):
    result = 0
    for b in bytes:
        result = result * 256 + int(b)
    return result

gcd = lambda m,n: m if not n else gcd(n,m%n)

plaintext = "CrossCTF{Pub7ic_prIv4te_K3ys_4_R5A_t33ns}slightlylessshittypaddingslightlylessshittypaddingslightlylessshittypaddingslightlylessshittypadding"
plain = plaintext.encode()
m = bti(plain)
#### ^ Helpers ^ ####

def bestow(c, d, phin):
    print ("c = " + str(c))
    print ("d = " + str(d))
    print ("phi(n) = " + str(phin))
    print (" ")

def mul_inv(a, b):
    b0 = b
    x0, x1 = 0, 1
    if b == 1: return 1
    while a > 1:
        q = a // b
        a, b = b, a%b
        x0, x1 = x1 - q * x0, x0
    if x1 < 0: x1 += b0
    return x1

def give(p, q):
    phin = (p-1)*(q-1)
    n = p*q
    e = 1000000007
    d = mul_inv(e, phin)
    if phin%e == 0:
        give(p, q)
        return
    else:
        c = pow(m, e, n)
        bestow(c, d, phin)
        return

p = 664848864185708098444377647643581430245214287651391623925058075365913647882855344532853450417155918855615341333204491495614874825613938388765639002844418865196705650611887599907

q = 38722293136428790154252843057248301003956727074949529577199456045867697108322483530078386035415819596731525703830806512587046507522321691571685703379119439599767387969283

give(p,q)
