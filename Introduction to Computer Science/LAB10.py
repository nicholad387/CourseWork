# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Name    : Nicholas Mohamed
# Pledge  : I pledge my honor that i have abided by the stevens honor system 
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Max:
#  Write a hmmm function that gets two numbers,
#   then prints the larger of the two.
#  Assumptions: Both inputs are any integers
Max = """
00 read r1
01 read r2
02 addn r5,1
03 copy r3,r1
04 copy r4,r2
05 jeqzn r4,10
06 jeqzn r3,12
07 sub r3,r3,r5
08 sub r4,r4,r5
09 jumpn 05
10 write r1
11 halt
12 write r2
13 halt 
"""

# Power:
#  Write a hmmm function that gets two numbers,
#   then prints (No.1 ^ No.2).
#  Assumptions: No.1 is any integer, No.2 >= 0
Power = """
00 read r1
01 read r2
02 addn r4,1
03 sub r2,r2,r4
04 copy r3,r1
05 sub r2,r2,r4
06 mul r1,r1,r3
07 jnezn r2,5
08 write r1
09 halt
"""


# Fibonacci
#  Write a hmmm function that gets one number,
#   then prints the No.1st fibonacci number.
#  Assumptions: No.1 >= 0
#  Tests: f(2) = 1
#         f(5) = 5
#         f(9) = 34
Fibonacci = """
00 read r1
01 jeqzn r1, 8
02 setn r2, 0
03 setn r3, 1
04 addn r1, -1
05 add r4, r2, r3
06 copy r2, r3
07 copy r3, r4
08 addn r1, -1
09 jnezn r1, 5
10 write r4
11 halt
"""


# ~~~~~ Running ~~~~~~
import hmmm
import importlib

runThis = Fibonacci # Change to the function you want to run
doDebug = False # Change to turn debug mode on/off

# call main() from the command line to run the program again
def main(runArg = runThis, debugArg = doDebug):
    importlib.reload(hmmm)
    hmmm.main(runArg, debugArg)

if __name__ == "__main__" : 
    main()


    