#Nicholas Mohamed
# I pledge my Honor that I have abided by the stevens honor system.
from functools import reduce
l = [1,2,3]
k = [4,5,6]

def dotProduct(l,k):
	if not l:
		return 0
	return l[0]*k[0] + dotProduct(l[1:],k[1:])
print(dotProduct(l,k))

def removeAll(e,L):
	if e in L:
		if e == L[0]:
			x = [L[1]] + removeAll(e,L[2:])
		else:
			x = [L[0]] + removeAll(e, L[1:])
		return x
	return L
print(removeAll(1, l))

def geometricSeq(n,f,b):
	if n < 1:
		return b
	else:
		return (b * (int)(f**(n-1)))
print(geometricSeq(3, 2, 10))

def deepReverse(L):
	if not L:
		return []
	elif isinstance(L[0], list) == True:
		return deepReverse(L[1:]) + [deepReverse(L[0])]
	return deepReverse(L[1:]) + [L[0]]
	
lst2 = [1,[2,3],4]
print(deepReverse(lst2))