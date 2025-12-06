from copy import copy
import logging

LOGGER = logging.getLogger()

def get_input_lines(filename):
    lines = None
    with open(filename, "r") as f:
        lines = f.readlines()
    return lines


def main(lines):
    part1 = 0
    part2 = 0

    table = list(map(lambda l : list(map(int, l)), [lines[i].strip().split() for i in range(len(lines)-1)]))
    operations = lines[-1].strip().split()

    for i in range(len(table[0])):
        n = None
        if operations[i] == '+':
            n = 0
            for j in range(len(table)):
                n += table[j][i]
        elif operations[i] == '*':
            n = 1
            for j in range(len(table)):
                n *= table[j][i]
        else:
            raise NotImplemented
        part1 += n

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
