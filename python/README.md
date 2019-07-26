# Python script for processing graphs files
The file processgraph.py can be used to process graph and coordinates files from [here](http://users.diag.uniroma1.it/challenge9/download.shtml).

However, in the graph and coordinates files from the above link contain edges with weight less than its corresponding Euclidean distance. This makes the potential function used in this particular implementation of A* algorithm invalid.