import numpy as np


solutions = []


# this method checks whether a pair of solutions are symmetric or not
def checkSymmetry(p, q, width):
    p1 = np.array(p)
    q.reverse()
    q1 = np.array(q)
    q.reverse()
    r1 = p1 + q1
    if np.sum(r1)/r1.shape == width:
        return True
    return False


# this method repeatedly calls the method "checkSymmetry" to check whether a
# solution is symmetric with rest of the solutions or not
def checkSymmetryList(p, qs, width):
    for q in qs:
        if checkSymmetry(p, q, width):
            return True
    return False


# this method parses the input to a multi-set in the desired form
def getList(l):
    L = list()
    ls = l.split(',')
    for s in ls:
        sub = s.split('(')
        L += [int(sub[0])]*int(sub[1][:-1])
    return L


# this method calculates whether "y" satisfies "L" using the D(y, X) function
def diff(y, X, L):
    diffs = [np.abs(i - y) for i in X]
    for d in diffs:
        if d not in L:
            return False, None
    return True, diffs


# this is the Place(L, X) method as written in the book
def place(L, X, width):
    if len(L) == 0:
        if X not in solutions[-1] and not checkSymmetryList(X, solutions[-1], width):
            solutions[-1].append(X.copy())
        return
    y = L[-1]
    check, diffs = diff(y, X, L)
    if check:
        X.append(y)
        X.sort()
        for d in diffs:
            L.remove(d)
        place(L, X, width)
        X.remove(y)
        X.sort()
        for d in diffs:
            L.append(d)
        L.sort()
    check, diffs = diff(width - y, X, L)
    if check:
        X.append(width - y)
        X.sort()
        for d in diffs:
            L.remove(d)
        place(L, X, width)
        X.remove(width - y)
        X.sort()
        for d in diffs:
            L.append(d)
        L.sort()
    return


# this is the PartialDigest(L) method as written in the book
def partialDigest(L):
    solutions.append([])
    width = L[-1]
    L.remove(width)
    X = [0, width]
    place(L, X, width)


# the three test datasets are provided through the input1.txt file
f = open("input1.txt", "r")
while True:
    l = f.readline().strip()
    if not l:
        break
    L = getList(l[1:-1])
    partialDigest(L)
    print("The number of distinct solution(s):", len(solutions[-1]))
    print(solutions[-1][:3])
