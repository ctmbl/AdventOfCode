from copy import copy
import logging

LOGGER = logging.getLogger()

def get_input_lines(filename):
    lines = None
    with open(filename, "r") as f:
        lines = f.readlines()
    return lines


def wrap_puzzle(lines):
    width = len(lines[0])
    lines.insert(0, "."*width)
    lines.append("."*width)
    return ["."+line+"." for line in lines]


def iterate_on_neighbours(i, j):
    for di in [-1, 0, 1]:
        for dj in [-1, 0, 1]:
            if di != 0 or dj != 0:
                yield i+di, j+dj


def remove_rolls(puzzle, width, height):
    n = 0
    for x in range(1, height+1):
        for y in range(1, width+1):
            if puzzle[x][y] != "@":
                continue
            neighbours = 0
            for i, j in iterate_on_neighbours(x, y):
                neighbours += (puzzle[i][j] == "@")
            if neighbours < 4:
                n += 1
                puzzle[x] = puzzle[x][:y]+"."+puzzle[x][y+1:]
        logging.debug("After line %s we have n at %s", x, n)
    return puzzle, n


def main(lines):
    part1 = 0
    part2 = 0
    lines = [line.strip("\n") for line in lines]
    width = len(lines)
    height = len(lines[0])
    puzzle = wrap_puzzle(lines)
    logging.debug("Shape lines: %s %s ; Shape puzzle %s %s", width, height, len(puzzle), len(puzzle[0]))
    # Part1
    for x in range(1, height+1):
        line = lines[x]
        for y in range(1, width+1):
            if puzzle[x][y] != "@":
                continue
            neighbours = 0
            for i, j in iterate_on_neighbours(x, y):
                neighbours += (puzzle[i][j] == "@")
            part1 += (neighbours < 4)
        logging.debug("After line %s we have part1 at %s", x, part1)

    #Part2
    puzzle, n = remove_rolls(puzzle, width, height)
    while n:
        part2 += n
        LOGGER.debug("Now add %s", n)
        puzzle, n = remove_rolls(puzzle, width, height)

    LOGGER.info("Part1: %s", part1)
    LOGGER.info("Part2: %s", part2)


if __name__ == "__main__":
    import argparse
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "-x",
        "--example",
        action="store_true",
        help="Run on input.ex.txt",
    )
    parser.add_argument(
        "-i",
        "--input",
        default="input.txt",
        help="Pass a custom file as input",
    )
    parser.add_argument(
        "-d",
        "--debug",
        action="store_true",
        help="Change logging level to debug",
    )
    ARGS = parser.parse_args()
    input_filename = "input.ex.txt" if ARGS.example else ARGS.input
    level = logging.DEBUG if ARGS.debug else logging.INFO

    logging.basicConfig(level = level)

    main(get_input_lines(input_filename))
