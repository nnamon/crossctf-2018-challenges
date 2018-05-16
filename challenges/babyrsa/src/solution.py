def chinese_remainder(n, a):
    sum = 0
    prod = reduce(lambda a, b: a*b, n)

    for n_i, a_i in zip(n, a):
        p = prod / n_i
        sum += a_i * mul_inv(p, n_i) * p
    return sum % prod


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

def findroot(n,mod):
    low = 1
    high = int("9"*800)
    ans = -1
    while low <= high:
        mid = (low + high)/2
        if pow(mid,mod) <= n:
            ans = mid
            low = mid + 1
        else:
            high = mid - 1
    return ans

def decod(k):
    o = ""
    while k > 0 :
        o = chr(k%256) + o
        k /= 256
    print (o)

if __name__ == '__main__':
    n = []
    a = []
    for i in range(257):
        a.append(int(raw_input().split()[-1]))
        raw_input()
        n.append(int(raw_input().split()[-1]))
        raw_input()
    l = chinese_remainder(n, a)
    k = findroot(l, 257)
    decod(k)
