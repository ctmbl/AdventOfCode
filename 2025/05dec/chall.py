from copy import copy
import logging

LOGGER = logging.getLogger()

def get_input_lines(filename):
    lines = None
    with open(filename, "r") as f:
        lines = f.readlines()
    return lines


def sort_and_merge_ranges(ranges):
    ranges.sort() # ranges is a list of tuple, will be sorted based on the first member
    i = 0
    while i < len(ranges)-1:
        if ranges[i][1] >= ranges[i+1][0]:
            ranges[i][1] = max(ranges[i][1], ranges[i+1][1])
            ranges.pop(i+1)
            continue
        i += 1
    return ranges


def main(lines):
    part1 = 0
    part2 = 0

    sep = lines.index("\n")
    ranges = [list(map(int, lines[i].strip().split("-"))) for i in range(0, sep)]
    ids = [int(lines[i].strip()) for i in range(sep+1, len(lines))]
    LOGGER.debug("ranges %s", ranges)
    LOGGER.debug("ids %s", ids)

    ranges = sort_and_merge_ranges(ranges)

    for idx in ids:
        for a, b in ranges:
            if idx >= a and idx <= b:
                part1 += 1
                LOGGER.debug("%s in (%s, %s)", idx, a, b)
                break

    part2 = sum([b - a +1 for a, b in ranges])

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
