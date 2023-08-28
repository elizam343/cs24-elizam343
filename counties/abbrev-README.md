### Theory

Graphs in general can be very dense, which requires a full adjency matrix in the average case. But graphs which describe possible ways for contiguous regions to touch each other are much more restricted. The average number of adjacent regions is never going to go above 6, and in additiion the region with fewest neighbors is never going to have 6 or more. In addition, if we remove a node and all of its edges from such a graph (called a planar graph), we get a graph which is still planar.

This means we can convert an adjacency matrix of a planar graph into a different representation with much better asymptotic performance.

### Implementation

When we create one of these graphs, we simply repeatedly find the node with the smallest number of neighbors, and add its neighbors into its adjacency list, removing these edges as we go. We will never have to add more than 5 neighbors.

When we use the result, however, this does require checking both sides of the edge whenever we check for adjacency, but it's still a constant amount of work..
