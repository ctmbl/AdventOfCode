import bisect
import logging
import math

LOGGER = logging.getLogger()

def get_input_lines(filename):
    lines = None
    with open(filename, "r") as f:
        lines = f.readlines()
    return lines


def area(A, B):
    return (abs(A[0] - B[0]) + 1) * (abs(A[1] - B[1]) + 1) 


def add_middle_points(corners):
    c = []
    for i in range(len(corners)):
        A, B = corners[i-1], corners[i]
        middle_point = ((A[0] + B[0]) // 2, (A[1] + B[1]) // 2)
        c.append(middle_point)
        c.append(B)
    return c


def main(lines):
    part1 = 0
    part2 = 0

    corners = [tuple(map(int, line.strip().split(","))) for line in lines]
    squares = []
    for i in range(1, len(corners)):
        for j in range(i):
            A, B = corners[i], corners[j]
            bisect.insort(squares, (area(A, B), A, B), key = lambda x: x[0])

    part1 = squares[-1][0]

    corners_with_middle_point = add_middle_points(corners)
    for a, A, B in squares[::-1]:
        contains = [C[0] < max(B[0], A[0]) and C[0] > min(B[0], A[0]) and C[1] < max(B[1], A[1]) and C[1] > min(B[1], A[1]) for C in corners_with_middle_point]
        LOGGER.debug("%s x %s contains %s", A, B, contains)
        if any(contains):
            continue
        LOGGER.debug("No tile is contained in %s x %s", A, B)
        part2 = a
        break

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
