#!/usr/bin/env python3

import argparse
import os
import subprocess
import random as rand
import json
import time
import pandas as pd
from pandas.io.json import json_normalize
import glob
import matplotlib.pyplot as plt
import seaborn as sb
import numpy as np

sb.set(style='darkgrid', palette='Set2')
sb.set_style(style='darkgrid', rc={'grid.color': '.8'})


method_map = {
    'dfs': 'Depth-First',
    'bfs': 'Breadth-First',
    'gbfs': 'Greedy Best-First',
    'as': 'A*',
    'cus1': 'Iterative-Deepening Depth-First',
    'cus2': 'Iterative-Deepening A*'
}


def get_dirs():
    # Get the directory paths for the script and exe
    script_dir = os.path.abspath(os.path.dirname(__file__))
    results_dir = os.path.join(script_dir, 'Results')
    return script_dir, results_dir


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

    stats = dict()
    if 'largest_frontier:' in output:
        largest_frontier = output[output.index('largest_frontier:') + 1]
        stats['largest_frontier'] = int(largest_frontier)

    return pathlen, expanded, stats


def take_sample(method, exe_path):
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

    os.chdir(exe_path)

    # Try and get the results from robonavs stdout, if the exe returns non-zero
    # then return an invalid environment (-1, -1)
    proc = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

    start = time.perf_counter()
    cmdresults, err = proc.communicate()
    end = time.perf_counter()

    execution_time = (end - start) * 1000

    if proc.returncode != 0:
        return -1, -1, {'execution_time': execution_time}

    pathlen, expanded, stats = get_results(cmdresults)
    if stats is None:
        stats = dict()
    stats['execution_time'] = execution_time
    return pathlen, expanded, stats


def generate_test(width, height, start, end, exe_path):
    rand.seed()
    placed = set()
    i = 0
    # Generate a number of randomly placed walls equal to the size
    # of the map with a 20% chance of being placed
    while i != width * height:
        pos = (rand.randint(0, width - 1), rand.randint(0, height - 1))
        wall = (pos[0], pos[1], 1, 1)
        if wall[2] < 0 or wall[3] < 0:
            continue

        if wall not in placed and pos != start and pos != end:
            if rand.random() > 0.85:
                placed.add(wall)

        i += 1

    # Write to a temporary file to be fed into the robonav c++ exe
    with open(os.path.join(exe_path, 'experiment.txt'), 'w+') as f:
        f.write('[{0},{1}]\n'.format(width, height))
        f.write('({0},{1})\n'.format(start[0], start[1]))
        f.write('({0},{1})\n'.format(end[0], end[1]))
        for w in placed:
            f.write('({0},{1},{2},{3})\n'.format(w[0], w[1], w[2], w[3]))
    return len(placed)


def run_experiment(args):
    samples = 1

    if args.samples:
        samples = args.samples

    # Get the directory paths for the script and exe
    script_dir, results_dir = get_dirs()
    exe_path = os.path.realpath(os.path.join(script_dir, '..'))
    exe_path = os.path.join(exe_path, 'cmake-build-debug')

    # The results for the entire experiment will be stored here for
    # JSON serialization
    results = {
        'grid_size': {'x': int(args.width), 'y': int(args.height)}
    }

    for i in range(0, samples):
        print('robonav experiment: sample {0}'.format(i))
        # Generate random start and end positions
        start = (rand.randint(0, args.width), rand.randint(0, args.height))
        end = (rand.randint(0, args.width), rand.randint(0, args.height))

        num_walls = generate_test(args.width, args.height, start, end, exe_path)
        optimal, _, _ = take_sample('as', exe_path)
        for method in method_map.keys():
            pathlen, expanded, stats = take_sample(method, exe_path)
            # Invalid environment, don't store results - only possible when the
            # random generation fails unexpectedly
            if pathlen < 0 or expanded < 0:
                continue

            # Valid environment but goal wasn't found
            if pathlen == 0 or expanded == 0:
                sample = {
                    'solution': False,
                    'path_length': pathlen,
                    'nodes_expanded': expanded,
                    'start': {'x': start[0], 'y': start[1]},
                    'end': {'x': end[0], 'y': end[1]},
                }
            else:
                # Valid environment and the goal was found
                sample = {
                    'solution': True,
                    'path_length': pathlen,
                    'nodes_expanded': expanded,
                    'start': {'x': start[0], 'y': start[1]},
                    'end': {'x': end[0], 'y': end[1]},
                }

            sample['num_walls'] = int(num_walls)
            sample['optimal_path'] = optimal

            if stats is not None:
                sample.update(stats)

            if method not in results:
                results[method] = {}
                results[method]['samples'] = []

            results[method]['samples'].append(sample)
            results[method]['tests_run'] = len(results[method]['samples'])
            results[method]['solutions_found'] = len([
                s for s in results[method]['samples'] if s['solution']
            ])

        # Remove the temp file
        os.remove(os.path.join(exe_path, 'experiment.txt'))

    if len(results) <= 0:
        return

    if not os.path.exists(results_dir):
        os.makedirs(results_dir)

    json_path = os.path.join(results_dir, str(time.time()) + '.json')
    with open(json_path, 'w+') as json_file:
        json.dump(results, json_file, indent=4, sort_keys=False)


def generate_statistics(args):
    script_dir, results_dir = get_dirs()
    if not os.path.exists(results_dir):
        print('robonav experiment: no results found')
        return

    stats_dir = os.path.join(script_dir, 'Stats')
    if not os.path.exists(stats_dir):
        os.makedirs(stats_dir)

    experiments = {}
    for experiment in glob.glob(os.path.join(results_dir, '*.json')):
        with open(experiment, 'r') as file:
            json_obj = json.load(file)
            size_str = str(json_obj['grid_size']['x']) + 'x' + str(json_obj['grid_size']['y'])
            experiments[size_str] = json_obj

    data_frames = {}
    for size, e in experiments.items():
        frames = []
        for key, method in e.items():
            if 'samples' not in method:
                continue
            df = json_normalize(method['samples'])
            df.index.name = 'sample'
            df.reset_index(level=0, inplace=True)
            extra = pd.read_json(json.dumps(method))
            df = df.join(extra[['tests_run', 'solutions_found']])
            df['method'] = method_map[key]
            df.set_index('method', inplace=True)
            frames.append(df)
        data_frames[size] = pd.concat(frames)
        data_frames[size]['grid_size'] = int(e['grid_size']['x']) * int(e['grid_size']['y'])

    padding = 2.0
    for size, df in data_frames.items():
        df.reset_index(level=0, inplace=True)
        ax = sb.stripplot(data=df, x='method', y='execution_time', jitter=True)
        ax.set(ylabel='Time (ms)', xlabel='Search method')
        plt.setp(ax.get_xticklabels(), rotation=30)
        plt.title(size + ' - runtime distribution')
        plt.tight_layout(pad=padding)
        plt.savefig(os.path.join(stats_dir, size + 'execution.pdf'))
        plt.close()

        median = df.groupby('method').median()

        ax = sb.barplot(data=median, x=median.index, y='execution_time')
        ax.set(ylabel='Time (ms)', xlabel='Search method')
        plt.setp(ax.get_xticklabels(), rotation=30)
        plt.tight_layout(pad=padding)
        plt.title(size + ' - runtime medians')
        plt.savefig(os.path.join(stats_dir, size + 'execution_median.pdf'))
        plt.close()

        ax = sb.stripplot(data=df, x='method', y='path_length', jitter=True)
        ax.set(ylabel='Path length (number of nodes)', xlabel='Search method')
        plt.setp(ax.get_xticklabels(), rotation=30)
        plt.title(size + ' - Path length distribution')
        plt.tight_layout(pad=padding)
        plt.savefig(os.path.join(stats_dir, size + 'path_length.pdf'))
        plt.close()

    concat = pd.concat(data_frames)
    for m in method_map.values():
        method = concat.loc[concat['method'].isin([m, 'A*'])]

        # Do a boxplot of runtimes
        ax = sb.boxplot(data=method, x='method', y='execution_time', linewidth=1.5)
        plt.setp(ax.get_xticklabels(), rotation=30)
        ax.set(ylabel='Runtime (ms)', xlabel='Search method')
        plt.tight_layout(pad=padding)
        plt.title('A* - {0}: Runtime distribution'.format(m))
        plt.savefig(os.path.join(stats_dir, m + '-total_execution_time.pdf'))
        plt.close()

        # And a histogram
        sb.set(font_scale=0.5)
        ax = sb.FacetGrid(method, hue='method', legend_out=True)
        ax.map(plt.hist, 'execution_time', histtype='bar', align='mid',
               alpha=0.6, bins=50)
        ax.add_legend()
        plt.tight_layout(pad=padding)
        plt.title('A* - {0}: Runtime distribution'.format(m))
        plt.savefig(os.path.join(stats_dir, m + '-hist-total_execution_time.pdf'))
        plt.close()

        # Do a boxplot of path lengths
        sb.set(font_scale=1.0)
        ax = sb.boxplot(data=method[method['solution']], x='method', y='path_length', linewidth=1.5)
        plt.setp(ax.get_xticklabels(), rotation=30)
        ax.set(ylabel='Path length (# nodes)', xlabel='Search method')
        plt.tight_layout(pad=padding)
        plt.title('A* - {0}: Path-length distribution'.format(m))
        plt.savefig(os.path.join(stats_dir, m + '-total_path_length.pdf'))
        plt.close()

        # And a histogram
        sb.set(font_scale=0.5)
        ax = sb.FacetGrid(method[method['solution']], hue='method', legend_out=True)
        ax.map(plt.hist, 'path_length', histtype='bar', align='mid',
               alpha=0.6, bins=50)
        ax.add_legend()
        plt.tight_layout(pad=padding)
        plt.title('A* - {0}: Path-length distribution'.format(m))
        plt.savefig(os.path.join(stats_dir, m + '-hist-total_path_length.pdf'))
        plt.close()

        # Hist of nodes expanded comparing method with A*
        sb.set(font_scale=1.0)
        ax = sb.stripplot(x='method', y='nodes_expanded', data=method, jitter=True)
        ax.set(ylabel='Nodes expanded', xlabel='Search method')
        plt.tight_layout(pad=padding)
        plt.title('Distribution of number of nodes expanded per search')
        plt.savefig(os.path.join(stats_dir, m + '-nodes_expanded.pdf'))
        plt.close()

        # Bar plot of nodes expanded comparing method with A*
        sb.set(font_scale=1.0)
        ax = sb.barplot(x='method', y='nodes_expanded', data=method, palette='Set2')
        ax.set(ylabel='Mean nodes expanded', xlabel='Search method')
        plt.tight_layout(pad=padding)
        plt.title('Mean number of nodes expanded per search')
        plt.savefig(os.path.join(stats_dir, m + '-bar-nodes_expanded.pdf'))
        plt.close()

        # Bar plot of execution time comparing method with A*
        sb.set(font_scale=1.0)
        ax = sb.barplot(x='method', y='execution_time', data=method, palette='Set2')
        ax.set(ylabel='Mean runtime (ms)', xlabel='Search method')
        plt.tight_layout(pad=padding)
        plt.title('Mean runtime in ms per search')
        plt.savefig(os.path.join(stats_dir, m + '-bar-execution_time.pdf'))
        plt.close()

        # Bar plot of path length comparing method with A*
        sb.set(font_scale=1.0)
        ax = sb.barplot(x='method', y='path_length', data=method[method['solution']], palette='Set2')
        ax.set(ylabel='Mean path length (# nodes)', xlabel='Search method')
        plt.tight_layout(pad=padding)
        plt.title('Mean path length per search')
        plt.savefig(os.path.join(stats_dir, m + '-bar-path_length.pdf'))
        plt.close()

        # Hist of nodes expanded for method
        sb.set(font_scale=1.0)
        ax = sb.distplot(method.loc[method['method'] == m]['nodes_expanded'], bins=50, kde=False)
        ax.set(ylabel='Occurances', xlabel='Nodes expanded')
        plt.tight_layout(pad=padding)
        plt.title('{0}: Distribution of number of nodes expanded'.format(m))
        plt.savefig(os.path.join(stats_dir, m + '-hist-nodes_expanded.pdf'))
        plt.close()

        # And a histogram
        sb.set(font_scale=1.0)
        ax = sb.distplot(method.loc[method['method'] == m]['path_length'], bins=50, kde=False)
        ax.set(ylabel='Occurances', xlabel='Path length (# nodes)')
        plt.tight_layout(pad=padding)
        plt.title('{0}: Distribution of path length per search'.format(m))
        plt.savefig(os.path.join(stats_dir, m + '-hist-path_length.pdf'))
        plt.close()

        # And a histogram
        sb.set(font_scale=1.0)
        ax = sb.distplot(method.loc[method['method'] == m]['execution_time'], bins=50, kde=False)
        ax.set(ylabel='Occurances', xlabel='Runtime (ms)')
        plt.tight_layout(pad=padding)
        plt.title('{0}: Runtime distribution'.format(m))
        plt.savefig(os.path.join(stats_dir, m + '-hist-runtime.pdf'))
        plt.close()

    # Plot runtime relationships
    ax = sb.lmplot(x='grid_size', y='execution_time',
                   data=concat[concat['method'].isin(['A*', 'Depth-First', 'Breadth-First', 'Greedy Best-First'])],
                   hue='method', col='method', col_wrap=2, x_jitter=0.5)
    ax.set_axis_labels('Total nodes in grid', 'Runtime (ms)')
    plt.tight_layout(pad=padding)
    plt.savefig(os.path.join(stats_dir, 'runtime_relationship.pdf'))
    plt.close()

    # Plot space relationships
    ax = sb.lmplot(x='grid_size', y='nodes_expanded',
                   data=concat[concat['method'].isin(['A*', 'Depth-First', 'Breadth-First', 'Greedy Best-First'])],
                   hue='method', col='method', col_wrap=2, x_jitter=0.5)
    ax.set_axis_labels('Total nodes in grid', 'Number of nodes expanded')
    plt.tight_layout(pad=padding)
    plt.savefig(os.path.join(stats_dir, 'expanded_relationship.pdf'))
    plt.close()

    # Plot wall relationships
    ax = sb.lmplot(x='num_walls', y='execution_time',
                   data=concat[concat['method'].isin(['A*', 'Depth-First', 'Breadth-First', 'Greedy Best-First'])],
                   hue='method', col='method', col_wrap=2, x_jitter=0.8)
    ax.set_axis_labels('Number of walls in grid', 'Run-time (ms)')
    plt.tight_layout(pad=padding)
    plt.savefig(os.path.join(stats_dir, 'walls_relationship.pdf'))
    plt.close()

    # Plot wall relationships
    ax = sb.lmplot(x='num_walls', y='execution_time',
                   data=concat[concat['method'].isin(['Iterative-Deepening Depth-First', 'Iterative-Deepening A*'])],
                   hue='method', col='method', col_wrap=2, x_jitter=0.8)
    ax.set_axis_labels('Number of walls in grid', 'Run-time (ms)')
    plt.tight_layout(pad=padding)
    plt.savefig(os.path.join(stats_dir, 'walls_relationship_custom.pdf'))
    plt.close()

    # Plot wall relationships nodes expanded
    ax = sb.lmplot(x='num_walls', y='nodes_expanded',
                   data=concat[concat['method'].isin(['A*', 'Depth-First', 'Breadth-First', 'Greedy Best-First'])],
                   hue='method', col='method', col_wrap=2, x_jitter=0.8)
    ax.set_axis_labels('Number of walls in grid', 'Number of nodes expanded')
    plt.tight_layout(pad=padding)
    plt.savefig(os.path.join(stats_dir, 'walls_nodes_relationship.pdf'))
    plt.close()

    # Plot wall relationships nodes expanded
    ax = sb.lmplot(x='num_walls', y='nodes_expanded',
                   data=concat[concat['method'].isin(['Iterative-Deepening Depth-First', 'Iterative-Deepening A*'])],
                   hue='method', col='method', col_wrap=2, x_jitter=0.8)
    ax.set_axis_labels('Number of walls in grid', 'Number of nodes expanded')
    plt.tight_layout(pad=padding)
    plt.savefig(os.path.join(stats_dir, 'walls_nodes_relationship_custom.pdf'))
    plt.close()

    # Plot runtime bars
    ax = sb.barplot(x='method', y='execution_time',
                    data=concat[concat['method'].isin(['A*', 'Depth-First', 'Breadth-First', 'Greedy Best-First'])])
    ax.set(ylabel='Mean runtime (ms)', xlabel='Method')
    plt.setp(ax.get_xticklabels(), rotation=30)
    plt.tight_layout(pad=padding)
    plt.savefig(os.path.join(stats_dir, 'runtime_bars.pdf'))
    plt.close()

    # Plot expanded bars
    ax = sb.barplot(x='method', y='nodes_expanded',
                    data=concat[concat['method'].isin(['A*', 'Depth-First', 'Breadth-First', 'Greedy Best-First'])])
    ax.set(ylabel='Mean # nodes expanded', xlabel='Method')
    plt.setp(ax.get_xticklabels(), rotation=30)
    plt.tight_layout(pad=padding)
    plt.savefig(os.path.join(stats_dir, 'expanded_bars.pdf'))
    plt.close()


def parse():
    """
    Parses the command line input, running robonav over a randomly generated 
    problem environment using the specified search method and environment size
    """
    parser = argparse.ArgumentParser(description='runs experiments on the '
                                                 'Robot Navigation Problem')
    subparsers = parser.add_subparsers()
    run = subparsers.add_parser('run', help='Executes the experiment')
    run.set_defaults(func=run_experiment)
    run.add_argument('width', type=int,
                        help='The width of the test environment')
    run.add_argument('height', type=int,
                        help='The height of the test environment')
    run.add_argument('-s', '--samples', type=int,
                        help='The number of samples to take for the test')

    stats = subparsers.add_parser('generate',
                                  help='Generates statistic data from results')
    stats.set_defaults(func=generate_statistics)

    args = parser.parse_args()
    args.func(args)


if __name__ == '__main__':
    parse()
