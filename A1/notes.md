#### Few thoughts on this assignment!

- This assignment was fairly easy. Now if I am saying it easy, that means a hell lot of people have found out it easy as well! There was only one tricky part in this one and as expected I could not do it!
- In the recursion problem, the only point worth mentioning is the *coupled recurrence equation* that was given.

>H <sub>0</sub> = 1, L <sub>0</sub> = 0, Hn = 2H<sub>n−1</sub> + L<sub>n−1</sub> for n > 1, Ln = H<sub>n−1</sub> + L<sub>n−1</sub> for n > 1

- So here I tried initially to derive the explicit recurrences for H<sub>n</sub> and L<sub>n</sub> only to realise that things were getting dirtier. Finally, I ended up writing the very straightforward recursive functions `double hirec(int n);` and `double lorec(int n);` which are dependent on one another for computation.
- Another interesting part was where we were asked to simultaneously compute (H<sub>n</sub>, L<sub>n</sub>) by a function having a single argument n. I **feel** that this is only possible because H<sub>n</sub> and L<sub>n</sub> are only functions of H<sub>n-1</sub> and L<sub>n-1</sub>. Had they been something like An = 2A<sub>n−1</sub> + **B<sub>n−2</sub>**, this implementation of simultaneous recursion won't be feasible!
- The next problem was deceivingly simple and the straightforward brute-force strategies were also easy to implement. I got stuck at the fourth part which called for a `O(n)` time implementation for the problem. I was thinking to use current-min, current-max strategy but that was failing for some cases.
- The actual solution uploaded by AD involved the use of stacks and stacky permutations of `1, 2, 3,. . ., n` which I am yet to understand fully!

>And let me mention the dumbest mistake I made today! In the first program, there were 3 functions to compute the values. I called the first function once and updated variable values and printed them on the terminal. However, for the other two functions, I called them but forgot to update the variable values and printed the same old variables! In the commit `corrected problem1 code in main function` I updated the same. Luckily, the code worked and hopefully the TA (who will grade the assignment) would also understand my intentions. My bad! :( 

