#### Few important notes!
- DFS traversal of an undirected graph results in 3 kinds of edges- tree edges, backward edges and forward edges.
- To Detect cycles, we need to identify the back edges. For that we can use vertex coloring approach (*white, gray, black*) as 
implemented in my code or one may keep counting levels during DFS traversal as suggested in the assignment.
- #### Vertex Coloring Method-
We color each vertex according to its state in the *implicit* DFS (recursion) stack. If a vertex is currently in the stack, 
then we mark it as 1 gray); an unvisited vertex gets the color white (0) and a vertex which has *all its neighbors visited* gets popped of
the stack and is colored black (2). During DFS traversal, we update the `visited` and the `color` array (to 1) in the beginning and
at the end of the function we set the color of that node as 2 (black). We also maintain parent pointers to store the **DFS Forest**.

During recursive calls on neighbors of the current vertex, say `u` (top of stack) if we find a visited neighbor `v`, then we 
first check if parent of `u` in the DFS forest is `v`. That will mean the edge `v---u` was marked as tree edge by `v` and while
DFS was called on `u`, we again encounter the edge, so this cannot be a back edge. The edge `u---v` will be a back edge only if
the vertex `v` is still in the stack i.e, colored *gray*. In that case we follow parent pointers to reach from `u` to `v` and print
the *cycle*!

- An interesting point to note here is that DFS traversal may not identify all possible cycles in graph if the cycles share 
common paths. Consider the graph in the shape of `8` in 7- segment display. It has 3 cycles (The big outer one and two inner 
loops). However, any DFS traversal will identify 2 of them! That is why based on the sequence of neighbors in the adjacency 
lists of nodes, we may get different cycles. However, the no. of cycles we get should remain the same. Check the FAQ txt file
to see what Prof. Abhijit Das has said about it.



> Graphs and their properties are really surprising!
