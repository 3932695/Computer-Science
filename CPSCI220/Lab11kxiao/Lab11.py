import timeit

# Note: avoiding the use of end="" in print statements. I'd like my code to
# run in both Python2 and Python3 with similar output.
def println(element):
    print("--------\nOUTPUT: ")
    print(element)
    print("--------")

print("\n\t <<< Question 2 demonstrations >>> \n")

print("def func(val1, val2): \n\t y += x")
def func(val1, val2):
    val2 += val1


print("x = 'Hello, '")
x = 'Hello, '



print("y = x ")
y = x

print("print(x) ")
println(x)

print("func(x, y)")
func(x, y)

print("print(x) ")
println(x)

print("print(y) ")
println(y)

print("x and y are not the same. Not a surprise, since our function sets 'y' equal to 'y plus x'. However, if we apply that function to an array...")

print("x = [1, 2, 3]")
x = [1, 2, 3]

print("y = x")
y = x

print("print(x)")
println(x)

print("func(x, y)")
func(x, y)

print("print(x)")
println(x)

print("print(y)")
println(y)

print("See, x and y are the same! y points to the object that x points to because arrays are mutable.")

print("\n\t <<< Question 3 demonstrations >>> \n")

def costly_func():
    return range(2**8)

print("Timing 'range(2**8)', calculating execution time in seconds...")
print(timeit.timeit(costly_func))


