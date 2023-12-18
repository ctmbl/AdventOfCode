lines = None
with open("input.txt", "r") as f:
    lines = f.readlines()
n = len(lines)

for i in range(n):
    lines[i] = [int(x) for x in lines[i].split(" ")]

tot1 = 0
tot2 = 0
for l in lines:
    L = [l]
    while any(L[-1]):
        L.append([L[-1][i+1] - L[-1][i] for i in range(0,len(L[-1])-1)])

    def extrapolate_forward(L):
        if not any(L[0]):
            return 0
        return L[0][-1] + extrapolate_forward(L[1:])
    def extrapolate_backward(L):
        if not any(L[0]):
            return 0
        return L[0][0] - extrapolate_backward(L[1:])
    tot1 += extrapolate_forward(L)
    tot2 += extrapolate_backward(L)

print("part1:", tot1)
print("part2:", tot2)