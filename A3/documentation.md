#### My thoughts on this assignment!
- This is the first time I implemented a *geometric algorithm*. Previously, I have tried to venture into this amazing genre of algorithms, but some way or the other never coded one.
- Before describing what I coded, let me first mention the (data) structures that were used in the problem. I will be using various terms from the [assignment.](https://github.com/swag2198/DSA/blob/master/A3/A3.pdf)

| Name | Data Members | Use |
| --- | --- | --- |
| `line` | `index`, `m` (slope) and `c` (intercept). | Stores one single line and the index is assigned while taking the user input. |
| `point` | `x` and `y` coordinates along with a `lineno`. | In **method1**, while finding the intersection point between the *chosen* line and the rest, the `lineno` stores the `index` of the latter line to update the *chosen* line for the next iteration. |
| `boundary` | `lineno` as the index of the line and `begin` and `end` (`point`s) of the segment in the boundary. | This element is used to define a line segment in the boundary of the *visible region*. One line with two end points define a *segment*. |
| `stnode` | `ln` (a `line`) and `b1` (a `boundary` element i.e. a segment). | In **method2**, a stack of these elements are used. `ln` becomes necessary to keep track of the original line `index` as lines are rearranged after sorting according to their slopes. |

- Now let me describe briefly the functions associated with **method1** and **method2**.

| Functions in Method 1 | Description |
| --- | --- |
| `void printlines(vector<line> &lines)` | Prints the lines from a `vector` of `line` elements along with their index. |
| `int smallest_slope_line(vector<line> &lines)` | Returns the index of the line having the smallest (steepest negative) slope. |
| `point intersection_point(line &l1, line &l2)` | Returns the intersection `point` of two lines in slope intercept form i.e., `y = mx + c`. |
| `int give_appropriate_point(vector<point> &sol, point &Q)` | Takes the vector of intersection points of rest of the lines with the current line and returns the point with minimum `x` coordinate, which is also greater than the `x` coordinate of the last point on the border (`Q`). |
| `void print_boundary(vector<boundary> &contour)` | Takes a vector of `boundary` elements and prints the line segments numbers along with the `begin` and `end` coordinates. |
| `void method1(vector<line> &lines)` | Implements an O(n<sup>2</sup>) algorithm that finds the visible region. The main `while` loop breaks when all lines are marked `visited`. The algorithm is described in detail in the assignment. |

| Functions in Method 2 | Description |
| --- | --- |
| `void merge(vector<line> &lines, int start, int mid, int end)` and `void mergesort(vector<line> &lines, int start, int end)` | Implements mergesort algorithm to sort the vector of `line`s in increasing order of their slopes. |
| `void method2(vector<line> &lines)` | Implements an O(nlogn) time algorithm (described below and also in the assignment) that solves the problem. |

- **Method 2 Algorithm Description**

First we should understand that the line with steepest negative slope will be the *leftmost* element of the border. Now we can initialise a stack of `stnode`s with the steepest negative line with `begin` and `end` points as points having x coordinate as minus and plus infinity respectively. Note that while pushing a node into the stack, we only have the `begin` point as a finite coordinate and we have to extend the the `end` point's `x` coordinate to positive infinity.
Now suppose we fetch the next line from the vector and find its intersection point with the current top segment in the stack.
If the `x` coordinate of the solution lies to the **right of the `begin` point of the top segment**, that means we have added another
segment to the border and we can continue with the next line. However, if the `x` coordinate happens to fall left to that of the
`begin` of top segment, that means **some previous segment** intersects with the current line much earlier and **overshadows the current top line segment**. Hence we have to pop the stack nodes until
we have found a segment which satisfies the criterion i.e., `Sol(x)` > `begin(x)`. Since the problem assumes that no three lines are concurrent and no line is vertical or no two lines have same slope, this method will work.
Here every line gets pushed into the stack or popped from the stack exactly once. So an extra `O(n)` overhead gets added to the sorting cost of `O(nlogn)`.

- **What I did in the lab!**

I completed the first method but failed to fully implement the **method 2** owing to a pretty frustrating bug! While popping out the boundary elements of the stack, I used `S.size()` as the `for` loop check condition! So stupid of me as I did not realise that stack size was dynamically changing as I was popping things out of it.
Later at hall, I corrected this mistake with a `while(!S.empty())` loop and got the second method working. It really hurts to lose points by such close margins!

- **Some other points**
  - I took the maximum and minimum values of the `double` datatype as plus and minus infinities. Had to `#include <limits>` and `const double inf = numeric_limits<double>::max();` this line of code gave the value of max double.
  - In some of the structure definitions, I had tried to define a constructor having values of the variables but somehow the g++ compiler in the lab PC displayed some error. May be some older version of C++ did not support such constructors inside structures.
