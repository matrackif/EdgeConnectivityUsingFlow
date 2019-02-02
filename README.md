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
The output will be two comma separated values text files described below.
#### Argument description
`n` is an positive integer greater than 1 which is the number of vertices to be generated.
And `p` is a double in the range `[0.0, 1.0]` which represents the probability of any vertex i being connected to vertex j.

Each test generates a file with the same format, a header `NumVertices,Probability,ExecTimeMicrosec`, then `MAX_ITERS` amount of rows (lines) with comma-separated values corresponding to the header.

Note that for now `MAX_ITERS` is hardcoded to be `50`.

#### Vertex Count Test
Randomly generates graphs with fixed probability equal to `p`.
The number of vertices is spread evenly  from `n / MAX_ITERS` to `n`. Outputs to file `num_vertices_test.txt`.
#### Probability Test
Second test randomly generates graphs with `n` vertices with varying probabilities evenly spaced from `1 / MAX_ITERS` to `1`.
Outputs to file `probability_test.txt`
