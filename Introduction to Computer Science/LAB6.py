####################################################################################
# Name: Nicholas Mohamed
# Pledge: I pledge my honor that i have abided by the stevens honor 
####################################################################################
# Lab 6: Recursion 2
# Demonstrate recursion as an algorithm design technique for the problem of 
# computing the (length of the) longest common subsequence of two given strings
#
# Note: Using anything other than recursion will result in a penalty
#####################################################################################

##############################################################################
# Example: The longest common subsequence of "helllowo_rld" and "!helloabcworld!"
# is "helloworld", and it has a length of 10.
#
# Therefore LLCS("helllowo_rld", "!helloabcworld!") returns 10, and
# LCS("helllowo_rld", "!helloabcworld!") returns "helloworld"
##############################################################################

def LLCS(S1, S2):
    if not S1 or not S2:
        return 0
    elif S1[0] == S2[0]:
        return 1 + LLCS(S1[1:], S2[1:])
    a = LLCS(S1[1:], S2)
    b = LLCS(S1, S2[1:])
    if a > b:
        return a
    return b
print(LLCS("helllowo_rld", "!helloabcworld!"))
##############################################################################
# Instead of returning the length of the longest common substring, this task
# asks you to return the string itself.
##############################################################################
# Tip: You may find it helpful to copy your solution to LLCS and edit it
# to solve this problem
##############################################################################

def LCS(S1, S2):
    if not S1 or not S2:
        return ""
    elif S1[0] == S2[0]:
        return (S1[0] + LCS(S1[1:], S2[1:]))
    a = LCS(S1[1:], S2)
    b = LCS(S1, S2[1:])
    if len(a) > len(b):
        return a
    return b
print(LCS("helllowo_rld", "!helloabcworld!"))