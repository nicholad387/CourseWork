####################################################################################
# Name: Nicholas H Mohamed
# Pledge: I pledge my honor that i have abided by the stevens honor system
####################################################################################


# The binary format you'll be working with for this assignment is called R2L,
# as it is a right-to-left representation.
####################################################################################
## Ex: 8 in decimal is 1000 in standard binary (2^3),
## and represented as a list [0, 0, 0, 1] in our R2L representation.
####################################################################################

# Notice that this makes it very easy to work with binary,
# by using num[0] to grab the least significant bit (2^0)!
#
# Please fill out the following 4 functions below using recursion, as specified.

# Given an integer x >= 0, convert it to the R2L binary format.
# Take note that both [] and [0] are used to represent 0 in R2L
def decimalToBinary(x):
   lst = []
   if x == 0:
      return [0]
   n = x%2
   return [n] + decimalToBinary(x//2) if x//2 != 0 else [n]
print(decimalToBinary(8))

# Given an R2L formatted number, return the integer it is equivalent to.
# The function should function with both [] and [0] returning 0.
def binaryToDecimal(num):
   if len(num) == 0:
      return 0
   return num[-1] + 2 * binaryToDecimal(num[:-1])
print(binaryToDecimal([1,0,0,0]))
# Given an R2L formatted number, return an R2L equivalent to num + 1
# If you need to increase the length, do so. Again, watch out for 0
def incrementBinary(num):
   if num == []:
      return [1]
   if num[0] == 0:
      return [1] + num[1:]
   return [0] + incrementBinary(num[1:])
print(incrementBinary([1,1,1]))
# Given 2 R2L numbers, return their sum.
## You MUST implement recursively the algorithm for bit-by-bit addition as taught in class,
## you may NOT do something like decimalToBinary( binaryToDecimal(num1) + binaryToDecimal(num2) ).
# Make sure to figure out what to do when num1 and num2 aren't of the same length!
# (and be sure you can add [] and [0])
## Tip: Try this on paper before typing it up
def buf(bin,numLen):
   if numLen > 0:
      return buf(bin + [0], numLen -1)
   return len
def addBinary(num1, num2):
   if num1 == []:
      return num2
   if num2 == []:
      return num1
   c = num1[0] and num2[0]
   b = num1[0] ^ num2[0]
   a = addBinary(num1[1:], num2[1:])
   if c == 1:
      a = incrementBinary(a)
   return [b] + a
   
print(addBinary([1,0,0,0,1], [0,0,1]))
