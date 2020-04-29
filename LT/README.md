### From O(N<sup>6</sup>) to O(N<sup>2</sup>): Dynamic programming to the rescue!
- I really liked the way the question of the lab test is presented. The problem at the core is very simple. It just asked to
find the *largest possible rectangular region in a binary matrix which satisfies the chessboard pattern*.
- The problem had two main parts, where we optimise the incredibly slow exhaustive search solutions to a practical solution
using dynamic programming for *square* and *rectangular* regions separately.
- Note that since a square is basically a rectangle with all sides having equal length, all solutions proposed to find rectangular
regions can be modified to find sqaure chessboards as well. However, because of the _added symmetry_ of a square, sometimes more
beautiful and optimised solutions can be found by exploiting its inherent properties.

**Exhaustive search algorithms**
 - If the given binary matrix is of dimensions `m`x`n`, then the largest square that can be inscribed in it has side length `L = min(m, n)`.
 Also take `N = max(m, n)` for complexity bounds.
 For searching square chessboard regions, we visit each `(i, j)`th location and start looking for squares with side length `l`
 where `1 <= l <= L` and top-left corner situated at `(i, j)`. In the worst case we have to check for all `L` values till we
 end up with a `1`x`1` chessboard at location at `(i, j)`. Checking if a `l`x`l` square is a chessboard takes O(N<sup>2</sup>)
 time anyway and there are `L` (worst case `N` if `m = n`) such values of `l`. So we spend **O(N<sup>3</sup>)** effort at each
 location and since there are O(N<sup>2</sup>) possible locations, the total time complexity becomes **O(N<sup>5</sup>)**. Of
 course we have do bound checks appropriately.
 - Searching for rectangular chessboards exhaustively just incorporates an extra nesting of loop accounting for the added breadth
 dimension. We have to check for all `k`x`l` rectangles at each `(i, j)` where `1 <= k <= m` and `1 <= l <= n`. So we end up doing
 **O(N<sup>4</sup>)** work at each location resulting in a final complexity of **O(N<sup>6</sup>)**.
 
**Dynamic programming algorithm for square**
 - This algorithm is explained in detail in the [assignment](https://github.com/swag2198/DSA/blob/master/LT/LT.pdf) document itself.
 This one is pretty neat and clever as it reduces the time complexity down to **O(N<sup>2</sup>)** straight! The solution builds
 the table from the location `(m-1, n-1)` to `(0, 0)`th location with ease just by exploiting the color-coding property of the
 chessboard and the property that any square/ rectangle inside any chessboard is also a chessboard. (We can think of it as the
 *optimal substructure* of the chessboard.)
 
**Dynamic programming algorithm for rectangle**
 - If we try to modify the above algorithm for square to work for rectangle as well we have to take into account numerous cases
 considering the different overlapping patterns for two rectangles at `(i, j+1)` and `(i+1, j)` considering the order relations of
 the lengths and breadths of the 2 rectangles. Also, in case of square we were left with only **one cell** to match the color and
 extend the chessboard if possible (*see `l1`=`l2` case for the square*). Here we are forced to check whether **an entire 
 region** is chessboard if we try to expand the rectangle.
 - So how do we start *approaching* this problem? Well as with most 2D dynamic programming problems, we first consider a simpler
 **1D variant** of the problem. This is analogous to the problem of finding the longest alternating 0-1 subarray in an array containing
 only 0s and 1s. This problem has a classic recurrence formulation as follows
 ```c
 LongestAlternatingSubarray(A[0...n-1])
 {
    /* T[i] = Longest alternating 0-1 subarray in range [0...i] */
    /* A single element is always a valid pattern */
    T[0] = 1;
    
    for i = 1 to n-1
       if A[i] != A[i-1]
          T[i] = 1 + T[i-1]; /* Extension possible */
       else
          T[i] = 1; /* Starts a new chain */
          
    return T[n-1]; /* Stores the answer */
 }
 ```
 - Now in the 2D variant, we pre-compute two `m`x`n` matrices `K` and `L` using the above algorithm carefully which stores the
 following. The only difference from the above formulation is that we populate for arrays (rows and columns) from the *last element* to the *first element*.
 Filling up these takes **O(N<sup>2</sup>)** time.
 ```python
 K[i][j] = length of longest vertical alternating 0-1 sequence starting from (i, j)
 Hence all cells in the last row will have K[i][j] = 1.
 
 L[i][j] = length of longest horizontal alternating 0-1 sequence starting from (i, j)
 Hence all cells in the last column will have L[i][j] = 1.
 ```
 - Now we define the table T as follows
 ```python
 T[i][j] = area of the maximal chessboard rectangle whose top-left corner is at (i, j)
 ```
 - However, the most important part to realise is that we do not need any dynamic programming to fill this table at all! The
 dynamic programming part of the problem is already over with calculations for `K` and `L`. To fill the table, we just go to
 location `(i, j)` and find the maximum height of possible rectangles starting at `(i, j)` as `K[i][j]`. Now we start visiting
 cells vertically below `(i, j)` within distance `K[i][j]` and find the **cumulative minimum** of `L[i+k-1][j]` till that value of `k`. This minimum
 gives the *breadth* of the rectangle with height =  `k`. We maximise `k*l` over `1 <= k <= K[i][j]`. This maximum area is stored
 at `T[i][j]`.
 - In fact the table `T` is not at all necessary if our only aim was to find the maximum area of the rectangle and where it
 occurs. Since at each location we only spend **O(N)** time, the total complexity becomes **O(N<sup>3</sup>)**.
 - I consider this a beautiful example of reducing a problem to a seemingly easier version and then use some extra manipulations
 to arrive at the solution!
 
  **Further improvements**
  - If you give the above algorithm some more thought, you will realise it pleasantly resembles the algorithm for finding the
  *maximum area rectangule in a bar histogram*! Basically here the histogram bases are located at each column and the heights
  are given by `L[i][j]` values. There are `n` such columns and if suffices to maximise over the maximum rectangles for each
  such histogram.
  - An **O(N)** time algorithm exists for finding the [maximum area rectangle](https://www.geeksforgeeks.org/largest-rectangle-under-histogram/) in a histogram using a *stack*. Using that we can
  reduce the complexity of the problem to **O(N<sup>2</sup>)** as there are `n` such histograms or columns!
 
 **My thoughts on this problem!**
 - Unfortunately, I could not implement the `dprectangle` algorithm as I spent most of my time during the exam trying to
 extend the given algorithm for square. Though during the last few minutes, I did give a thought on the 1D version of the
 problem but all I was able to do was to initialise the last row and last column! `:(`
 - I personally liked the dynamic programming algorithm for square boards the most as it seemed *trickier* to come up with!
 The assignment could have given hints for the **O(N<sup>3</sup>)** dp algorithm for rectangles instead and asked us to implement
 a different algorithm that runs in **O(N<sup>2</sup>)** time for squares to make it more difficult!
