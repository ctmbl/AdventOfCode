import logging

LOGGER = logging.getLogger()

def get_input_lines(filename):
    lines = None
    with open(filename, "r") as f:
        lines = f.readlines()
    return lines


def main(lines):
    dial = 50
    direction = ""
    part1 = 0
    part2 = 0
    for l in lines:
        old_direction = direction
        old_dial = dial
        direction = l[0]

        _dial = dial + int(l.replace("L", "-").replace("R", "+"))
        clicks, dial = divmod(_dial, 100)
        # but clicks is not enough, we must take care to edge cases where we land exactly on 0
        correction = int(old_dial == 0) * (old_direction != direction) * ((direction == "R") - (direction == "L") )

        part1 += int(dial == 0)
        part2 += abs(clicks) + correction
        logging.debug("  %2s + %3s = %4s | %2s | P1: %s P2: %s", old_dial, l.strip("\n"), _dial, dial, part1, part2)
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
