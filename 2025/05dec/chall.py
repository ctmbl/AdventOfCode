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

    sep = lines.index("\n")
    ranges = [tuple(map(int, lines[i].strip().split("-"))) for i in range(0, sep)]
    ids = [int(lines[i].strip()) for i in range(sep+1, len(lines))]
    LOGGER.debug("ranges %s", ranges)
    LOGGER.debug("ids %s", ids)

    for idx in ids:
        for a, b in ranges:
            if idx >= a and idx <= b:
                part1 += 1
                LOGGER.debug("%s in (%s, %s)", idx, a, b)
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
