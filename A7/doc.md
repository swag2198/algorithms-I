#### My thoughts on this assignment!
- Though this assignment was on Binary Search Trees, I felt it is more focused on some recusrsive sequence generation problem as in Assignment- 2.
- Today I happened to face something very intriguing about compilers. There is something called **undefined behaviour** of 
compilers that brings in some very beautiful but otherwise irritating behaviour in your code.
- So it is like this, I declared some counting variables `c0` and `c1` to count the no. of zeros and ones in an array containing
0s and 1s (a *bitstring* actually). Unfortunately, I forgot to initialise the variables to `zero` before starting the `c0++` thing.
- The function `void findallhelper(vector<vector<int> > &seq, vector<int> &AL, vector<int> &AR, int n, vector<int> B)` which had the
counting part basically populating some vector with `AL` and `AR` based on an `n-1` length-ed binary string. Before pushing back 
the vector to the 2D vector `seq` (which is passed by reference to *fool* the recursion in my terms!) I was printing the vector
there itself.
- Now here comes the magic part! With the printing part on, the function was working correctly,and I was getting all the expressions
correctly in the `main`. But the moment I commented the mere printing statements, no error shows up but all on a sudden my code 
just fails to do what it was supposed to do!
- All this happened with `gcc` compiler on the lab PC and on my own PC as well. However, after I spotted the initialisation error, 
and found out about this weird error, I tried to run the (original) code in an online C++ compiler, where it *failed* every time.
- Later when I googled, I found that this is the **undefined behaviour** of a compiler when deleting seemingly unrelated segments
of code affects another region. I am quoting from [here](https://www.learncpp.com/cpp-tutorial/uninitialized-variables-and-undefined-behavior/) 
below.

```
Using the value from an uninitialized variable is our first example of undefined behavior. 
Undefined behavior is the result of executing code whose behavior is not well defined by the C++ language. 
In this case, the C++ language doesn’t have any rules determining what happens if you use the value of a variable that
has not been given a known value. 
Consequently, if you actually do this, undefined behavior will result.

Code implementing undefined behavior may exhibit any of the following symptoms:

- Your program produces different results every time it is run.
- Your program consistently produces the same incorrect result.
- Your program behaves inconsistently (sometimes produces the correct result, sometimes not).
- Your program seems like its working but produces incorrect results later in the program.
- Your program crashes, either immediately or later.
- Your program works on some compilers but not others.
- Your program works until you change some other seemingly unrelated code.

Or, your code may actually produce the correct behavior anyway. 
The nature of undefined behavior is that you never quite know what you’re going to get, 
whether you’ll get it every time, and whether that behavior will change when you make other changes.
```
> I really wish to learn in detail about **Compilers** and **Programming Languages** some day! Till then let me *Call it magic!*
