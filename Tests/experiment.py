#!/usr/bin/env python3

import argparse
import os
import subprocess
import random as rand
import json
import time


def get_results(results):
    """
    Gets the pathlength and number of nodes expanded for a result.
    Returns zero if no solution was found
    :param results: stdout from the robonav executable
    :type results: bytes
    :return: The path length and the number of expanded nodes
    :rtype: tuple(int int)
    """
    decoded = results.decode('ascii')
    filtered = ''.join(char for char in decoded if ord(char) > 31 or ord(char) == 91)
    if 'No solution found' in filtered:
        return 0, 0, None

    output = filtered.split()
    path = [action for action in output if ';' in action]
    pathlen = len(path)
    expanded = int(output[2])

    stats = {}
    if 'largest_frontier:' in output:
        stats['largest_frontier'] = output[output.index('largest_frontier:') + 1]

    if len(stats) <= 0:
        stats = None

    return pathlen, expanded, stats


def run_sample(width, height, start, end, method, exe_path):
    """
    Runs a single test returning a sample of the data from the 
    search algorithm
    :param width: The width of the environment
    :type width: int
    :param height: The height of the environment
    :type height: int
    :param start: The starting position
    :type start: tuple(int, int)
    :param end: The goal position 
    :type end: tuple(int, int)
    :param method: The search method being used
    :type method: str
    :param exe_path: The absolute path to the robonav executable
    :type exe_path: str
    :return: Tuple containing the path length and the number of nodes expanded
    :rtype: tuple(int, int)
    """
    cmd = ['./robonav', 'experiment.txt', method.upper(), '-s']
    placed = set()
    i = 0
    # Generate a number of randomly placed walls equal to the size
    # of the map with a 10% chance of being placed
    while i != width:
        pos = (rand.randint(0, width), rand.randint(0, height))
        wall = (pos[0], pos[1], rand.randint(0, width) - pos[0],
                rand.randint(0, height) - pos[1])
        if wall[2] < 0 or wall[3] < 0:
            continue

        if wall not in placed and (not pos == start or not pos == end):
            if rand.random() > 0.9:
                placed.add(wall)

        i += 1

    # Write to a temporary file to be fed into the robonav c++ exe
    with open(os.path.join(exe_path, 'experiment.txt'), 'w+') as f:
        f.write('[{0},{1}]\n'.format(width, height))
        f.write('({0},{1})\n'.format(start[0], start[1]))
        f.write('({0},{1})\n'.format(end[0], end[1]))
        for w in placed:
            f.write('({0},{1},{2},{3})\n'.format(w[0], w[1], w[2], w[3]))

    os.chdir(exe_path)

    # Try and get the results from robonavs stdout, if the exe returns non-zero
    # then return an invalid environment (-1, -1)
    proc = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    results, err = proc.communicate()
    if proc.returncode != 0:
        return -1, -1, None

    return get_results(results)


def parse():
    """
    Parses the command line input, running robonav over a randomly generated 
    problem environment using the specified search method and environment size
    """
    parser = argparse.ArgumentParser(description='runs experiments on the '
                                                 'Robot Navigation Problem')
    parser.add_argument('width', type=int,
                        help='The width of the test environment')
    parser.add_argument('height', type=int,
                        help='The height of the test environment')
    parser.add_argument('method', type=str,
                        help='The search method to test')
    parser.add_argument('-s', '--samples', type=int,
                        help='The number of samples to take for the test')

    args = parser.parse_args()

    samples = 1

    if args.samples:
        samples = args.samples

    # Get the directory paths for the script and exe
    script_dir = os.path.dirname(__file__)
    results_dir = os.path.join(script_dir, 'Results')
    exe_path = os.path.realpath(os.path.join(script_dir, '..'))
    exe_path = os.path.join(exe_path, 'cmake-build-debug')

    # Generate random start and end positions
    start = (rand.randint(0, args.width), rand.randint(0, args.height))
    end = (rand.randint(0, args.width), rand.randint(0, args.height))

    # The results for the entire experiment will be stored here for
    # JSON serialization
    results = {
        'method': args.method,
        'num_samples': samples,
        'samples': []
    }

    for i in range(0, samples):
        pathlen, expanded, stats = run_sample(
            args.width, args.height, start, end, args.method, exe_path
        )

        # Invalid environment, don't store results - only possible when the
        # random generation fails unexpectedly
        if pathlen < 0 or expanded < 0:
            continue

        # Valid environment but goal wasn't found
        if pathlen == 0 or expanded == 0:
            results['samples'].append({
                'solution': False,
                'path_length': pathlen,
                'nodes_expanded': expanded,
                'start': {'x': start[0], 'y': start[1]},
                'end': {'x': end[0], 'y': end[1]},
            })
        else:
            # Valid environment and the goal was found
            results['samples'].append({
                'solution': True,
                'path_length': pathlen,
                'nodes_expanded': expanded,
                'start': {'x': start[0], 'y': start[1]},
                'end': {'x': end[0], 'y': end[1]},
            })

        if stats is not None:
            results['samples'][i].update(stats)

        # Remove the temp file
        os.remove(os.path.join(exe_path, 'experiment.txt'))

    results['tests_run'] = len(results['samples'])
    results['solutions_found'] = len([
        s for s in results['samples'] if s['solution']
    ])

    if len(results['samples']) <= 0:
        return

    if not os.path.exists(results_dir):
        os.makedirs(results_dir)

    json_path = os.path.join(results_dir, str(time.time()) + '.json')
    with open(json_path, 'w+') as json_file:
        json.dump(results, json_file, indent=4, sort_keys=False)


if __name__ == '__main__':
    parse()
