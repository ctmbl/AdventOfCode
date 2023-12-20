import sys
import time
import logging
logging.basicConfig(level=logging.INFO)

file_name = "input.txt" if len(sys.argv) < 2 else sys.argv[1]
lines = None
with open(file_name, "r") as f:
    text = f.read()
    lines = text.split("\n")
n = len(lines)
for i in range(n):
    lines[i] = "." + lines[i] + "."
m = len(lines[0])
lines.insert(0, "."*m)
lines.append("."*m)
n+=2

def _map(x, y):
    return lines[x][y]

def move(a, x, y, old):
    match a:
        case '|':
            d = (old[0] < x)*2-1 # +1 if coming from top -1 otherwise
            return (x + d, y)
        case '-':
            d = (old[1] < y)*2-1 # +1 if coming from left -1 otherwise
            return (x    , y + d)
        case 'L':
            if old[1] == y: # coming from top
                return (x, y + 1)
            return (x-1, y)
        case 'J':
            if old[1] == y: # coming from top
                return (x, y - 1)
            return (x-1, y)
        case '7':
            if old[1] == y: # coming from below
                return (x, y - 1)
            return (x+1, y)
        case 'F':
            if old[1] == y: # coming from below
                return (x, y + 1)
            return (x+1, y)
        case '.':
            return (x, y)

def get_neighbors(x, y):
    return [(x-1, y), (x+1, y), (x, y-1), (x, y+1)]


x, y = 0, 0
for i in range(n):
    logging.debug("%s", lines[i])
    if "S" in lines[i]:
        x = i
        y = lines[i].index("S")
path = [(x, y)]

if _map(x-1, y) in ['|', 'F', '7']:   # above
    path.append((x-1,y))
elif _map(x+1, y) in ['|', 'J', 'L']: # below
    path.append((x+1,y))
elif _map(x, y-1) in ['-', 'F', 'L']: # left
    path.append((x,y-1))
elif _map(x, y+1) in ['-', 'J', '7']: # right
    path.append((x,y+1))
else:
    raise Exception("Next step after S not found")
logging.info("found %s", path)


while _map(*path[-1]) != 'S':
    next_tile = move(_map(*path[-1]), *path[-1], path[-2])
    path.append(next_tile)
    logging.debug("next tile: %s", next_tile)
    #time.sleep(1)
logging.debug("The whole circuit is %s", path)


dist = (len(path)-1)/2 # should be an int
print("part1:", dist)

