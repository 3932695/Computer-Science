def plus(*list):
    sum = 0
    for e in list:
        sum += e
    return sum


total = plus(1, 2, 3, 4, 5)

print(total)
