import os
import subprocess
def isPalin(x):
    return x == x[::-1]
def isPrime(x):
    x = str(x)
    myout = subprocess.Popen(['factor', x], stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    stdout, stderr = myout.communicate()
    return str(stdout).count(' ') == 1 and x != '1'

movex = {"D": 1, "U": -1, "L": 0, "R": 0}
movey = {"D": 0, "U": 0, "L": -1, "R": 1}

def genxy(x, y, op):
    xs = []
    ys = []
    for c in op:
        xs.append(x)
        ys.append(y)
        x += movex[c]
        y += movey[c]
    return x, y, xs, ys

def solve10():
    digit = []
    with open("game10.in") as f:
        a = f.readline().strip()
        digit.append(f.readline().strip().split())
        digit.append(f.readline().strip().split())
        digit.append(f.readline().strip().split())
    getStr = lambda a, xs, ys: ''.join([a[x][y] for (x, y) in zip(xs, ys)])
    xs = []
    ys = []
    x1, y1 = 0, 0
    for i in range(999//3):
        x1, y1, tx, ty = genxy(x1, y1, "RDLDRRUUR")
        xs += tx
        ys += ty
    print(len(getStr(digit, xs, ys)))
    print(isPalin(getStr(digit, xs, ys)))
    with open("game10.out","w") as f:
        f.write("1\n")
        f.write("2997 ")
        for x, y in zip(xs, ys):
            f.write("{} {} ".format(x + 1, y + 1))
        f.write('\n')
solve10()