### Intro To AI - Assignment 1
# Tree-Based Search -  Robot Navigation Problem

## Project Structure


`/Parsers` - Contains both the command line parser and file parser

`/Search` - Classes and functions relavant to the actual search implementation:

* `Search/Core` - Containers, base classes and the `Environment` type
* `Search/Methods` - All search methods, with the following implemented:
	* `BFS` - Breadth-First search
	* `DFS` - Depth-First search
	* `GBFS` - Greedy Best-First search
	* `AS` - A*
	* `IDDFS` - Iterative-Deepening Depth-First search 
	* `IDA` - Iterative-Deepening A*

`Visualizer` - Code used for the GUI visualizer

## CLI Operation

The command line app provided as `robonav.exe` while also containing the required positional arguments as defined in the assignment spec, has the following optional flags:

* `-v | --visualizer` - Opens the GUI visualizer, does not require any other positional arguments to work
* `-h | --help` - Displays a help message
* `-s | --stats` - Displays other useful statistics such as largest frontier

When reading files in it reads them in as a relative path from the executables directory.

## GUI operation

The GUI visualizer defines the following controls:

* **1-6** - Chooses a search method
* **Left mouse** - Places a wall on a blank cell. Moves the start or goal position when held and dragged over either of them
* **Space** - Clears the search tree and path
* **Escape** - Quits the application
