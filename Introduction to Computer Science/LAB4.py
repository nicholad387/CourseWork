############################################################
# CS115 Lab 4
# Name: Nicholas Mohamed
# Pledge: I pledge my honor that i have abided by the stevens honor system 
############################################################

from functools import reduce
import math
# Task 1: Use reduce to add up all elements in a list
"""
Input: A list of numbers
Output A number representing the sum
Example: add_all([1, 2, 3]) = 6
"""
nums = [1,2,3]
def add_all(lst):
		return reduce(lambda a,b: a+b, lst)
print(add_all(nums))
# Task 2: Use map to evaluate a given polynomial at a specific x-value
"""
Input:
	p: A list of coefficients for increasing powers of x
	x: The value of x to evaluate
Output: Number representing the value of the evaluated polynomial
Example: poly_eval([1, 2, 3], 2) = 1(2)^0 + 2(2)^1 + 3(2)^2 = 17
"""
def poly_eval(p, x):
	lst2 = map(lambda i: x**p.index(i),p)
	p = map(lambda x,y: x*y ,p,lst2)
	return reduce(lambda a,b: a+b,p)
print(poly_eval(nums, 2))