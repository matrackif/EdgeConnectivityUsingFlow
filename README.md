# Edge connectivity using flow

## Building and running the tests

```
make all test
```

## Usage
### Find edge connectivity of a graph from input file
```
./EdgeConnectivity/EdgeConnectivity input_graph.txt
```
See `test/*.in` for some example inputs.
### Run program in test mode:
```
./EdgeConnectivity/EdgeConnectivity n p
```
In test mode, the program will measure the execution time of finding the edge connectivity in microseconds.
The output will be a comma separated values text file called `exec_time_results.txt`.

Where `n` is an positive integer greater than 1 which is the number of vertices to be generated.
And `p` is a double in the range [0.0, 1.0] which represents the probability of any vertex i being connected to vertex j.

2 tests will be run, first run fixes the probability to be equal to `p` and checks execution time for randomly generated graphs
with number of vertices from 2 to n.
Second test randomly generates graphs with `n` vertices with varying probabilities 0.05, 0.1, 0.15, ..., 1.0.
