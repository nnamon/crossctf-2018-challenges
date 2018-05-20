def mod_inv(a, b):
    b0 = b
    x0, x1 = 0, 1
    if b == 1: return 1
    while a > 1:
        q = a // b
        a, b = b, a%b
        x0, x1 = x1 - q * x0, x0
    if x1 < 0: x1 += b0
    return x1

# Returns (g, x, y) s.t. ax+by = g = gcd
def xgcd(b, a):
    x0, x1, y0, y1 = 1, 0, 0, 1
    while a != 0:
        q, b, a = b // a, a, b % a
        x0, x1 = x1, x0 - q * x1
        y0, y1 = y1, y0 - q * y1
    return  b, x0, y0

def decod(k):
    o = ""
    while k > 0 :
        o = chr(k%256) + o
        k = k // 256
    print (o)

def broadcast(elist, clist):
    oute = []
    outc = []
    for i in range (len(elist)-1):
        g, x, y = xgcd(elist[i], elist[i+1])
        if (x > 0):
            invy = mod_inv(clist[i+1], n)
            newc = (pow(clist[i], x, n)*pow(invy, -y, n))%n
            newe = g
        else:
            invy = mod_inv(clist[i], n)
            newc = (pow(clist[i+1], y, n)*pow(invy, -x, n))%n
            newe = g
        outc.append(newc)
        oute.append(newe)

    return oute, outc

def main():
    global n
    n = int(input().split()[-1])
    e1 = []
    c1 = []
    for _ in range(5):
        input()
        inc = int(input().split()[-1])
        ine = int(input().split()[-1])
        e1.append(ine)
        c1.append(inc)

    for _ in range(4):
        e1, c1 = broadcast(e1, c1)

    print(decod(c1[0]))

if __name__ == '__main__':
    main()
