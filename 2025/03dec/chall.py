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
    for line in lines:
        # Part1:
        line = line.strip()
        d = max(line[:-1])
        u = max(line[line.index(d)+1:])

        # Part2:
        max_joltage = ""
        index = 0
        _line = copy(line)
        # for the 11 first digits:
        for i in range(11, 0, -1):
            max_n = max(_line[:-i])
            index = _line.index(max_n)
            _line = _line[index+1:]
            max_joltage += max_n
        # and the last one:
        max_joltage += max(_line)
        LOGGER.debug("Max joltage (part2) is %s", max_joltage)

        part1 += int(d+u)
        part2 += int(max_joltage)
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
