import sys
import random
import argparse


def get_pair(num_vertices):
    seen = set()
    while True:
        pair = tuple(random.choices(range(1, 1 + num_vertices), k=2))
        if pair not in seen:
            seen.add(tuple)
            yield pair


def process(args):
    try:
        with open(args.graph, "r") as graph:
            with open(args.coord, "r") as coord:
                with open(args.output + "_d.txt", "w") as out_d:
                    with open(args.output + "_a.txt", "w") as out_a:
                        for line in graph:
                            if line.startswith("p sp"):
                                num_vertices = int(line.split()[2])
                                out_d.write(" ".join(line.split()[2:]) + "\n")
                                out_a.write(" ".join(line.split()[2:]) + "\n")
                                for coord_line in coord:
                                    if coord_line.startswith("p aux"):
                                        if num_vertices != int(coord_line.split()[4]):
                                            print("Incorrect number of vertices in the coord file!")
                                            return 1
                                    if coord_line.startswith("v "):
                                        out_a.write(" ".join(coord_line.split()[2:]) + "\n")
                            if line.startswith("a "):
                                out_d.write(" ".join(line.split()[1:]) + "\n")
                                out_a.write(" ".join(line.split()[1:]) + "\n")

                        # Generate queries
                        if args.n < 0:
                            args.n = 0
                        if args.n > num_vertices ** 2:
                            args.n = num_vertices ** 2
                        out_d.write(str(args.n) + "\n")
                        out_a.write(str(args.n) + "\n")
                        pair_gen = get_pair(num_vertices)
                        for _ in range(args.n):
                            pair = next(pair_gen)
                            out_d.write(" ".join(map(str, pair)) + "\n")
                            out_a.write(" ".join(map(str, pair)) + "\n")
        return 0
    except IOError as exc:
        print(exc)


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument("graph", type=str, help="graph file")
    parser.add_argument("coord", type=str, help="coord file for the graph")
    parser.add_argument("n", type=int, help="number of random queries to generate")
    parser.add_argument("-o", "--output", type=str, default="output", help="output file name")

    args = parser.parse_args()
    sys.exit(process(args))

