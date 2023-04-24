Nicholas DeFilippis
HPC Assignment 4

1. Running the ping pong example, we get

Rank 1/2 running on cs489.hpc.nyu.edu.
Rank 0/2 running on cs488.hpc.nyu.edu.
pingpong latency: 9.950549e-04 ms
pingpong bandwidth: 6.602681e+00 GB/s

which clearly shows that the process wsa run on two different nodes.

2. Running with N=10, we get the following result
Rank 0/6 running on cs515.hpc.nyu.edu
Rank 4/6 running on cs519.hpc.nyu.edu
Rank 2/6 running on cs517.hpc.nyu.edu
Rank 5/6 running on cs520.hpc.nyu.edu
Rank 3/6 running on cs518.hpc.nyu.edu
Rank 1/6 running on cs516.hpc.nyu.edu
Message received, expected: 150, 150
Time: 7.585051e-01 ms
Latency: 1.264175e-01 ms

For N=100000, we get
Rank 0/6 running on ga010.hpc.nyu.edu
Rank 5/6 running on ga015.hpc.nyu.edu
Rank 1/6 running on ga011.hpc.nyu.edu
Rank 3/6 running on ga013.hpc.nyu.edu
Rank 2/6 running on ga012.hpc.nyu.edu
Rank 4/6 running on ga014.hpc.nyu.edu
Message received, expected: 1500000, 1500000
Time: 7.987421e-03 ms
Latency: 1.331237e-03 ms

To measure bandwith, we now send a 2MB message instead of a single number, we get the following results
Rank 0/6 running on cs364.hpc.nyu.edu
Rank 3/6 running on cs367.hpc.nyu.edu
Rank 5/6 running on cs369.hpc.nyu.edu
Rank 1/6 running on cs365.hpc.nyu.edu
Rank 2/6 running on cs366.hpc.nyu.edu
Rank 4/6 running on cs368.hpc.nyu.edu
Message received, expected: 1500000, 1500000
Time: 9.527667e-01 ms
Latency: 1.587944e-01 ms
Bandwith: 4.373229e-02 Gb/s

3. See mpi-scan.cpp for the parallel scan implementation. For example, we get a sample run of N=10000000
Rank 0/10 running on ga010.hpc.nyu.edu.
Rank 3/10 running on ga013.hpc.nyu.edu.
Rank 1/10 running on ga011.hpc.nyu.edu.
Rank 8/10 running on ga018.hpc.nyu.edu.
Rank 7/10 running on ga017.hpc.nyu.edu.
Rank 6/10 running on ga016.hpc.nyu.edu.
Rank 5/10 running on ga015.hpc.nyu.edu.
Rank 4/10 running on ga014.hpc.nyu.edu.
Rank 9/10 running on ga019.hpc.nyu.edu.
Rank 2/10 running on ga012.hpc.nyu.edu.
sequential-scan = 0.014556s
parallel-scan   = 0.009185s
error = 0

when running on 10 nodes
