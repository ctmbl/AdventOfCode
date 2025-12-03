import logging
import re

LOGGER = logging.getLogger()

def get_input_lines(filename):
    lines = None
    with open(filename, "r") as f:
        lines = f.readlines()
    return lines


def main(lines):
    part1 = 0
    part2 = 0
    ranges = [re.findall(r"\d+", _range) for _range in lines[0].split(",")]
    for a, b in ranges:
        ids = list(range(int(a), int(b)+1))
        for id_nb in ids:
            id_str = str(id_nb)
            invalid = []
            half = len(id_str)//2
            if len(id_str) % 2 != 1 and id_str[:half] == id_str[half:]:
                part1 += id_nb
            if re.match(r"(?P<x>\d+)(?P=x)+$", id_str):
                part2 += id_nb
                invalid.append(id_str)
        LOGGER.debug("In %s-%s, invalid ids (part2) are %s", a, b, invalid)
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
