# Power Station Network Pathfinding Algorithms

This repository contains two C programs that demonstrate graph-based pathfinding algorithms—**Dijkstra's** and **Bellman-Ford**—applied to power station networks. These tools help compute the shortest paths and detect connectivity or negative cycles in the graph.

## 📁 Contents

- `matrix_dijkstra.c` — Uses an adjacency matrix and Dijkstra's algorithm.
- `edge_bellmanford.c` — Uses an edge list and Bellman-Ford algorithm.
- `input.txt` (Not included) — A text file containing the graph in the format:
```

V E
src dest weight
...

````

## 🧮 Algorithms Used

### Dijkstra's Algorithm (`matrix_dijkstra.c`)
- Input format: Adjacency matrix from a `.txt` file
- Finds the shortest distances from a single source node to all others.
- Handles only non-negative edge weights.

### Bellman-Ford Algorithm (`edge_bellmanford.c`)
- Input format: Edge list from a `.txt` file
- Detects negative weight cycles.
- Computes shortest path between a given source and target node.

## 🛠️ How to Compile and Run

```bash
gcc matrix_dijkstra.c -o dijkstra
./dijkstra

gcc edge_bellmanford.c -o bellmanford
./bellmanford
````

## ⏱ Performance

Both programs measure and display execution time to assess efficiency.

## 📄 Sample Input File Format

```txt
5 7
0 1 4
0 2 1
1 2 2
1 3 5
2 3 8
3 4 3
2 4 10
```

## 📌 Notes

* Ensure the input file ends with `.txt`
* Vertex IDs must be 0-indexed
* Make sure the input is well-formed; otherwise, parsing will fail.

---
