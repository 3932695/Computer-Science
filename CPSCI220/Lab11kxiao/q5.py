# import struct
import time

# I've commented out my first attempt at 'packing' variables. 
# A classmate taught me that I just had to put a * next to the x in memoize...
# ...to pass in a variable amount of parameters.

def memoize(f):
	memo = {}
	def helper(*x):
		if x not in memo:
			memo[x] = f(*x)
		return memo[x]
	return helper

def fib(n):
	if n == 0:
		return 0
	elif n ==1:
		return 1
	else:
		return fib(n-1) + fib(n-2)

def pascalc(i, j):
	# i, j = struct.unpack('hh1', params)
	if j == 0 or (j == i):
		return 1
	else:
		# params1 = struct.pack('hh1', i-1, j)
		# params2 = struct.pack('hh1', i-1, j-1)
		# return pascalc(params1) + pascalc(params2)
		return pascalc(i-1, j) + pascalc(i-1, j-1)
					


def pascal(rows):
	array = []
	for i in range(rows):
		row = [0]*(i+1)
		for j in range(i+1):
			# params = struct.pack('hh1', i, j)
			row[j] = pascalc(i, j)
		
		array.append(row)

	for line in array:
		print(line)
	
start = time.time()
pascal(25)
end = time.time()

time1 = end - start

pascalc = memoize(pascalc)

start = time.time()
pascal(25)
end = time.time()

time2 = end - start

print("Original execution time: ")
print(time1)

print("Memoized execution time: ")
print(time2)
