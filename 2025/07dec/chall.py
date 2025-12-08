from copy import copy
import logging

LOGGER = logging.getLogger()

def get_input_lines(filename):
    lines = None
    with open(filename, "r") as f:
        lines = f.readlines()
    return lines


def add_or_set(d, key, val):
    if key in d:
        d[key] += val
    else:
        d[key] = val


def main(lines):
    part1 = 0
    part2 = 0

    js = {lines[0].index("S") : 1}
    for line in lines[1:]:
        new_js = dict()
        for j, occ in js.items():
            if line[j] == ".":
                add_or_set(new_js, j, occ)
            elif line[j] == "^":
                add_or_set(new_js, j-1, occ)
                add_or_set(new_js, j+1, occ)
                part1 += 1
            else:
                raise NotImplemented
        LOGGER.debug("Split on %s in %s", new_js, line.strip())
        js = new_js
    part2 = sum(js.values())

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
