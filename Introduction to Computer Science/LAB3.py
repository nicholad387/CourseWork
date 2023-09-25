##########################################
# Name: Nicholas Mohamed    
# Pledge: I pladge my honor that I have abided by the stevens honor system 
##########################################

# Import reduce from the functools package
from functools import reduce

#######################################################################################
# Task 1: Use reduce to determine if all elements in a boolean list are true
lst = [False,False,False,True,False]

def is_true(a,b):
    return a and b
def all_true(lst):
    return reduce(is_true,lst)

print(all_true(lst))
#######################################################################################
# Task 1.1: Use reduce to determine if AT LEAST one element in a boolean list is true
# Hint: Should be very similar to the above function
def true_present(a,b):
    return a or b == True
def one_true(lst):
    if reduce(true_present,lst) is True:
        return True
print(one_true(lst))

#######################################################################################
# Task 2: Use map and reduce to return how many elements are True in a boolean list
def count_true(lst):
    cnt = sum(lst)
    return cnt
print(count_true(lst))

# This function is provided for you
# Gets a list of strings through the command line
# Input is accepted line-by-line
def getInput():
    lst = []
    txt = input()
    
    while(len(txt) != 0):
        lst.append(txt)
        txt = input()
        
    return lst
# Task 3: Get the longest string in the list using map and reduce, and print it out
# 'strings' is a list of input strings e.g. [ 'hello', 'world' ]
# Hint: The 'map' part of your program should take a string s into a length-2 list [len(s), s].

def getLongestString():
    strings = getInput()
    longest = max(strings,key = len)
    return strings
print(getLongestString())