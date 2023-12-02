print(sorted([sum(list(map(int, s.strip("\n").split("\n")))) for s in (open("input.txt","r").read().split("\n\n"))])[-1])
