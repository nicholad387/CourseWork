import random
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Name    : Nicholas Mohamed
# Pledge  : I pledge my honor that i have abided by the stevens honor system 
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def shuffledNumbers(n):
    if n == 0:
        return  []
    out = list()
    for i in range(n):
        out.append(i)
    for i in range(n-1,1,-1):
        rand = random.randint(0,i)
        if(rand < i):
            out[i],out[rand] = out[rand],out[i]
    return out

print(shuffledNumbers(5))
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def string_times(str, n):
    return str * n

print(string_times("hi", 5))
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def count_evens(nums):
    cnt = 0
    for i in nums:
        if i % 2 == 0:
            cnt+=1
    return cnt
exp = [1,2,3,4,5,6,7,8,9]
print(count_evens(exp))
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def front_times(str, n):
    return str[:3] * n

print(front_times("hello", 3))
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def has22(nums):
    for i in range(len(nums)-1):
        if nums[i] == nums[i+1]:
            return True
    return False

exp2 = [1,2,3,4,2]
print(has22(exp2))
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def centered_average(nums):
    avg = 0
    nums.sort()
    nums[1:]
    nums[:1]
    for i in nums:
        avg = i + avg
    return avg / len(nums)
    
exp3 = shuffledNumbers(8)
print(centered_average(exp3))
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
