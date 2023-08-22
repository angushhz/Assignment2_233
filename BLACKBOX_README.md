```
# Graph Algorithms

This repository contains implementations of various graph algorithms in C++.

## Algorithms

The following algorithms are implemented:

* Depth-first traversal
* Breadth-first traversal
* Topological sort (depth-first and breadth-first)
* Minimum spanning tree

## Usage

To use the algorithms, first create an instance of the `Graph` class and pass the number of vertices and the type of graph (directed or undirected) to the constructor.

```
Graph graph(5, UNDIRECTEDGRAPH);
```

To add a vertex to the graph, use the `addVertex()` method.

```
graph.addVertex("A");
graph.addVertex("B");
graph.addVertex("C");
graph.addVertex("D");
graph.addVertex("E");
```

To add an edge to the graph, use the `addEdge()` method.

```
graph.addEdge("A", "B", 10);
graph.addEdge("A", "C", 20);
graph.addEdge("B", "C", 30);
graph.addEdge("B", "D", 40);
graph.addEdge("C", "D", 50);
graph.addEdge("D", "E", 60);
```

Once the graph has been created, you can use the following methods to perform the different algorithms:

* `depthFirstTraversal()`
* `breadthFirstTraversal()`
* `topologicalSort()`
* `minSpanTree()`

For example, the following code prints the results of the depth-first traversal of the graph:

```
string result = graph.depthFirstTraversal("A");
cout << result << endl;
```

The output of the above code will be:

```
A B C D E
```

## License

The code in this repository is licensed under the MIT License.
```