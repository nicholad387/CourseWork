#Lab2
import math

# Name: Nicholas Mohamed
# Pledge: I pladge my honor that I have abided by the stevens honor board

# All of the functions with the solve prefix are to be implemented using four fours and
# basic math operations to equal the number in the function title. The basic operations are
# +, -, *, /, and parentheses.
# To fill the function out, replace the 0 with your expression so that the function will return
# the number in the function title

# As an example the solution for 12 and a way to test it is given below
# If your output has a decimal in the solution, it will not be counted against you,
# but if you'd like to remove it use // for division


def solve_12():
	return 4 * (4 - 4 // 4)

print(solve_12())  # Will print 12

def solve_0():
	return 4+4-4-4
print(solve_0())

def solve_1():
	return (4/4)*(4/4)
print(solve_1())

def solve_2():
	return (4/4)+(4/4)
print(solve_2())

def solve_3():
	return (4*4-4)/4
print(solve_3())

def solve_4():
	return 4+((4-4)*4)
print(solve_4())

def solve_5():
	return (4*4+4)/4
print(solve_5())

def solve_6():
	return 4+((4+4)/4)
print(solve_6())

def solve_7():
	return (44/4)-4
print(solve_7())

def solve_8():
	return 4+4%44
print(solve_8())

def solve_9():
	return (4+4)+(4/4)
print(solve_9())


# To solve this one you're allowed to use any operation you'd like
# This includes factorials, square roots, and concatenation (Using two 4s to make 44)
# The math library has already been imported so you can use math.sqrt(n) for square roots
# and math.factorial(n) for factorials
def solve_10():
	return int(4+4+(math.sqrt(4)))
print(solve_10())

# The following problems are to act as introductions to lists.
# All of them will use a list, titled lst, in the function which
# you can assume will not produce an error

# Simple tests are given below each function
example_lst = [1, 2, 3, 4, 5]

# Returns the first element of a list


def get_first(lst):
	return lst[0]

print(get_first(example_lst))  # Prints 1

# Returns the last element of a list
def get_last(lst):
	return lst[len(lst)-1]

print(get_last(example_lst))  # Prints 5

# Returns a list containing all elements except the first
# Hint: use list slices
def remove_first(lst):
	lst.pop(0)
	return lst

print(remove_first(example_lst))  # Prints [2, 3, 4, 5]
