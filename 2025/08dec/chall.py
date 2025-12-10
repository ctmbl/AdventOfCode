import bisect
import logging
import math

LOGGER = logging.getLogger()

def get_input_lines(filename):
    lines = None
    with open(filename, "r") as f:
        lines = f.readlines()
    return lines


def dist(A, B):
    return math.sqrt(sum([(A[i] - B[i])**2 for i in range(len(A))]))


def find_closest(jboxes):
    dists = []
    for i in range(1, len(jboxes)):
        for j in range(i):
            A, B = jboxes[i], jboxes[j]
            bisect.insort(dists, (dist(A, B), A, B), key = lambda x: x[0])
    return dists


def main(lines):
    part1 = 0
    part2 = 0

    jboxes = {tuple(map(int, line.strip().split(","))) : None for line in lines}
    dists = find_closest(list(jboxes.keys()))
    circuits = []

    limit = 10 if ARGS.example else 1000
    for i in range(limit):
        _, A, B = dists[i]
        A_id = jboxes.get(A)
        B_id = jboxes.get(B)
        if A_id is None and B_id is None:
            circuits.append([A, B])
            jboxes[A] = len(circuits) - 1
            jboxes[B] = len(circuits) - 1
        elif A_id is not None and B_id is not None:
            if A_id == B_id:
                continue
            c = circuits[B_id]
            circuits[A_id].extend(c)
            for jb in c:
                jboxes[jb] = jboxes[A]
            circuits[B_id] = None
        else:
            A, B = A if A_id is not None else B, A if A_id is None else B
            A_id, B_id = jboxes.get(A), None
            circuits[A_id].append(B)
            jboxes[B] = jboxes[A]

    cir_len = [len(c) for c in circuits if c is not None]
    cir_len.sort(reverse = True)
    part1 = cir_len[0] * cir_len[1] * cir_len[2]

    last_two = False
    i = limit
    while last_two is False:
        _, A, B = dists[i]
        LOGGER.debug("Inspecting %s - %s", A, B)
        A_id = jboxes.get(A)
        B_id = jboxes.get(B)
        if A_id is None and B_id is None:
            circuits.append([A, B])
            jboxes[A] = len(circuits) - 1
            jboxes[B] = len(circuits) - 1
        elif A_id is not None and B_id is not None:
            if A_id == B_id:
                i += 1
                continue
            c = circuits[B_id]
            circuits[A_id].extend(c)
            for jb in c:
                jboxes[jb] = jboxes[A]
            circuits[B_id] = None
        else:
            A, B = A if A_id is not None else B, A if A_id is None else B
            A_id, B_id = jboxes.get(A), None
            circuits[A_id].append(B)
            jboxes[B] = jboxes[A]

        last_two = all([val is not None for val in jboxes.values()]) and circuits.count(None) + 2 >= len(circuits)
        i += 1

    if circuits.count(None) + 2 > len(circuits):
        i -= 1
    _, A, B = dists[i]
    part2 = A[0] * B[0]

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
