import sys

file = open(sys.argv[1], 'r')
tablet = {}
exec(file.read(), tablet)
del tablet["__builtins__"]

print(tablet)
