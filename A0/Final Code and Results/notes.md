#### Some Notes

- The crux of the assignment was to develop the underlying mesh/ grid structure using nodes and pointers. Here a node correspond to a single day in the year.
- The calendar is of dimensions 20 x 21 (nodes). `(20 = 5 (weeks/ month) * 4 (months/ big column) and 21 = 7 (days/ week) * 3 (months/ big row).`
- It is to be noted that the nodes need *not* be placed contiguously in memory. Nodes can reside in the memory in arbitrary locations, but the pointers should be appropriately connected. (Just like nodes in a Graph!)
- I created the mesh using pointer to pointer to pointer to a node! Basically the helper `gridptr give_grid(int r, int c)` function creates a 2D array, each element of which is a pointer to a node.
- Exploiting the indexing if the 2D array `all`, the function `mesh initcal()` iteratively adjusts the pointers among the nodes. Now, we do not need the `all` matrix and we will have the base pointer `C` as `all[0][0]`.
- The function `void print_calendar(mesh C)` recursively prints the raw mesh. It first stores the down pointer of the current node, and prints the nodes in the right linked list consecutively. Finally, a recursive call is made on the (stored) down pointer to print the raw calendar mesh in a row by column format.
- The function `int storemonth(mesh C, int month, int start, int year)` calculates where the *block* of the `month` starts using pointer calculations and fills up the date field of the nodes. Sometimes the last row needs to be adjusted to the starting row of the month.
- Initially I started with a recursive implementation to create the mesh (can be found in the file `A0.cpp` commented), but some nodes were getting created multiple times and there was no way (?) to join the pointers to the same node!
>I tend to forget quickly what I coded even the day before! I hope maintaining this document will help in future for my reference. This was the warm-up (not to be graded) assignment of Spring 2020 Algorithms Laboratory.
