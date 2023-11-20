<h2 align="center">Project 3 | Implementation and empirical analysis of the Karger algorithm</h2>

In this porject, you must implement, in any programming language, the Karger algorithm
for determining a minimum cut in a simple graph. Your program will read a graph
informed through a text file. The file format is the same as previous works (see [Project 1](https://github.com/WeslleyDeziderio/applied-graph-theory) and [Project 2](https://github.com/WeslleyDeziderio/graph-search)).

**Implementation of the Karger algorithm.** In this first part, you just need to implement the algorithm.
As a reference, I recommend the following material:
<https://www.dropbox.com/s/ari9bf7zlces28j/Lecture16-Stanford-Karger.pdf?dl=0>

**Implementation of a naive randomized approach.** The Karger algorithm, despite taking
randomized decisions, this is not a naive approach, as, as iterations are executed,
ted, the probability of making contractions that remove many edges from the final cut increases (think about
this statement). This will become evident when comparing it to the naive approach that simply partitions randomly.
ally the vertices of the graph into two sets. This second part consists of implementing such an approach
naive.

**Empirical analysis of algorithms.** Examples of graphs and one of theirs will be shared with the class.
respective minimum cuts (a graph can have more than one minimum cut). For each graph, one must construct
a graph with two curves, one for each implemented algorithm. It is important to emphasize that an execution
One of the algorithms has N iterations, and the smallest cut found in these iterations will be returned.
In the graphs in question, the abscissa axis will contain the number of iterations N iter , while the axis
ordinates will present the probability p of the respective algorithm finding the minimum cut. This probability will be estimated by running the algorithm N exec times. It is suggested N exec = 10000. The range of values considered
for N iter it must be calibrated by the student. The tip is to stop increasing the value as soon as the probability
is very close to 100%.

Test cases. <https://www.dropbox.com/sh/b9vcwq0u3rj516o/AAAlvn2_ONQ7srmq5s2KaVwla?dl=0>