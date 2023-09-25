
# Stevens Institute of Technology, 2021

##########################################
# Name: Nicholas Mohamed
# Pledge: I pledge my Honor that i have abided by the stevens honor board
# resubmitting
##########################################
from math import floor    # E.g., floor(5.3) -> 5, floor(3.9) -> 3
from functools import reduce

######################################################################
# Task 1: Given an 8-digit decimal number representing the date,
#         calculate the day of the week using Zeller's congruence:
#
#           https://en.wikipedia.org/wiki/Zeller%27s_congruence
#
# Input:  8-digit decimal number in the format of YYYYMMDD
#
# Output: Weekday as a [0-6] number, where 
#         0: Saturday, 1: Sunday, 2: Monday, ..., 6: Friday  
######################################################################
date = 20211008
week = ['Saturday','Sunday','Monday','Tuesday','Wednsday','Thursday',"Friday"]
q = date % 100
m = (date/100)%100
k = (date/10000)%100
j = (date/1000000)
if m <= 2:
	m+=12
	k-=1
h = (int)(q + (floor((13*(m+1))/5)) + k + (floor(k/4)) + (floor(j/4))-2*j) % 7
def getWeekday(date):
	return week[h]
print(getWeekday(date))
######################################################################
# Task 2: Create two functions, an encoder and a decoder for the
#         Caesar cipher:
#
#           https://en.wikipedia.org/wiki/Caesar_cipher
#
# Note: You can try out this cipher at the link below:
#
#           https://cryptii.com/pipes/caesar-cipher
######################################################################
	
######################################################################
# This provided helper function may be useful
# Input:  List of ASCII values (Ex: [72, 69, 76, 76, 79])
# Output: String (Ex. 'HELLO')       'H   E   L   L   O'
######################################################################
#def asciiToString(asciiList):
	#return ''.join(map(chr, asciiList))
######################################################################
# Caesar Encoder
#
# Input: A string (assume all-caps: leave everything else as-is),
#        and a shift value       (Ex. 'HELLO WORLD', 3)
#
# Output: An encoded string      (Ex. 'KHOOR ZRUOG')
#
# Hint: The ord() function converts single-character strings to ASCII
#       (Its inverse, the chr() function, is used in the provided helper)
######################################################################
def caesarEncoder(str, shift):
	ascii_val = map(ord, str)
	ascii_val = map(lambda x: (((x-65)+shift) % 26) + 65 , ascii_val)
	str = map(chr, ascii_val)
	code = ""
	return code.join(str)
print(caesarEncoder("HELLOWORLD", 3))
######################################################################
# Decoder
# Input: A string value with all capital letters (leave everything
#        else as-is) and a shift value (Ex. KHOOR ZRUOG, 3)
# Output: A decoded string             (Ex. HELLO WORLD)
# Hint: The chr() function converts ASCII to a single-character string
######################################################################
def caesarDecoder(str, shift):
	ascii_val = map(ord, str)
	ascii_val = map(lambda x: (((x-65)-shift) % 26) + 65 , ascii_val)
	str = map(chr, ascii_val)
	code = ""
	return code.join(str)
print(caesarDecoder("KHOORZRUOG", 3))
	

