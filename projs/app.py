is_hot = True

weight = int(input("weight: "))
unit = input("(L)bs or (K)g: ")
x = unit.upper()
if x == 'L':
    print(weight * 0.45)
elif x == 'K':
    print(weight/0.45)
else:
    print("not a valid unit")
