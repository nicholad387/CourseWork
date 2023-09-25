from importlib import reload as Rfrsh
import hmmm

# Fibonacci! You've already done it in Lab 9
# Now however, you are to do hmmmonacci with
# recursion, & you MUST do so for any credit
# The tests are still the same as from Lab 9
# Tests: f(2) = 1, f(5) = 5, f(9) = 34
RecFibSeq = """ 
00 read r1
01 setn r2 0
02 setn r3 1
03 setn r15 42
04 calln r14 7
05 write r2 
06 halt
07 jnezn r1 10
08 setn r13 0
09 jumpr r14
10 pushr r1 r15
11 pushr r14 r15
12 addn r1 -1
13 calln r14 7
14 popr r14 r15
15 popr r1 r15
16 copy r4 r3
17 add r3 r2 r3
18 copy r2 r4
19 jumpr r14
"""

# Change doDebug to false to turn off debugs
runThis = RecFibSeq
doDebug = False

# Note: main() in the shell to easily reload
def main(runArg=runThis,  debugArg=doDebug):
    Rfrsh(hmmm); hmmm.main(runArg, debugArg)

if __name__ == "__main__" :
    main()
