All tests were run on a Linux Machine with a 6 core Intel(R) Core(TM) i7-8700 CPU @ 3.20GHz processor

1. See val_test01_solved.cpp and val_test02_solved.cpp

2. Timings for blocked version of code using a BLOCK_SIZE of 24, found by experimentation to be the fastest:

 Dimension       Time    Gflop/s       GB/s        Error
        24   0.425853   4.696457  75.143315 0.000000e+00
        72   0.431575   4.635606  74.169691 0.000000e+00
       120   0.432198   4.629883  74.078126 0.000000e+00
       168   0.434489   4.605334  73.685342 0.000000e+00
       216   0.440886   4.571569  73.145104 0.000000e+00
       264   0.444837   4.549914  72.798619 0.000000e+00
       312   0.441403   4.541224  72.659579 0.000000e+00
       360   0.453722   4.524495  72.391913 0.000000e+00
       408   0.451786   4.509922  72.158755 0.000000e+00
       456   0.463730   4.498336  71.973368 0.000000e+00
       504   0.457151   4.480767  71.692266 0.000000e+00
       552   0.449579   4.489439  71.831028 0.000000e+00
       600   0.480712   4.493332  71.893310 0.000000e+00
       648   0.487250   4.467486  71.479773 0.000000e+00
       696   0.451702   4.478440  71.655039 0.000000e+00
       744   0.552423   4.472993  71.567882 0.000000e+00
       792   0.661802   4.504001  72.064021 0.000000e+00
       840   0.527238   4.496668  71.946681 0.000000e+00
       888   0.622521   4.499302  71.988835 0.000000e+00
       936   0.730273   4.491613  71.865806 0.000000e+00
       984   0.852467   4.470619  71.529899 0.000000e+00
      1032   0.488761   4.497515  71.960243 0.000000e+00
      1080   0.559642   4.501849  72.029589 0.000000e+00
      1128   0.639648   4.487623  71.801971 0.000000e+00
      1176   0.731902   4.444254  71.108056 0.000000e+00
      1224   0.819808   4.473652  71.578427 0.000000e+00
      1272   0.921463   4.466973  71.471562 0.000000e+00
      1320   1.031477   4.459564  71.353028 0.000000e+00
      1368   1.151919   4.444943  71.119087 0.000000e+00
      1416   1.280386   4.434848  70.957567 0.000000e+00
      1464   1.413859   4.438613  71.017801 0.000000e+00
      1512   1.559898   4.431891  70.910260 0.000000e+00
      1560   1.714143   4.429520  70.872320 0.000000e+00
      1608   1.886068   4.408906  70.542496 0.000000e+00
      1656   2.076245   4.374541  69.992649 0.000000e+00
      1704   2.249393   4.399197  70.387156 0.000000e+00
      1752   2.486345   4.325844  69.213511 0.000000e+00
      1800   2.751131   4.239712  67.835385 0.000000e+00
      1848   2.925061   4.315201  69.043215 0.000000e+00
      1896   3.161222   4.312111  68.993776 0.000000e+00
      1944   3.396760   4.325676  69.210814 0.000000e+00
      1992   3.655993   4.324069  69.185100 0.000000e+00


Timings for the OpenMP version of the code are as follows:

Dimension       Time    Gflop/s       GB/s        Error
        24   0.260458   7.678796 122.860735 0.000000e+00
        72   0.128162  15.609961 249.759379 0.000000e+00
       120   0.110626  18.088258 289.412121 0.000000e+00
       168   0.101292  19.754476 316.071619 0.000000e+00
       216   0.098870  20.385733 326.171732 0.000000e+00
       264   0.095864  21.112843 337.805484 0.000000e+00
       312   0.092728  21.616986 345.871774 0.000000e+00
       360   0.093391  21.981422 351.702746 0.000000e+00
       408   0.091549  22.255971 356.095543 0.000000e+00
       456   0.093544  22.299866 356.797855 0.000000e+00
       504   0.091394  22.412809 358.604938 0.000000e+00
       552   0.088822  22.723546 363.576743 0.000000e+00
       600   0.094547  22.845724 365.531586 0.000000e+00
       648   0.095527  22.787098 364.593564 0.000000e+00
       696   0.087350  23.158836 370.541384 0.000000e+00
       744   0.108838  22.703265 363.252244 0.000000e+00
       792   0.128364  23.221177 371.538824 0.000000e+00
       840   0.102520  23.125497 370.007947 0.000000e+00
       888   0.122721  22.823342 365.173467 0.000000e+00
       936   0.141924  23.111638 369.786206 0.000000e+00
       984   0.164679  23.142383 370.278134 0.000000e+00
      1032   0.094784  23.191796 371.068738 0.000000e+00
      1080   0.107732  23.386072 374.177144 0.000000e+00
      1128   0.122997  23.337897 373.406347 0.000000e+00
      1176   0.138826  23.430494 374.887898 0.000000e+00
      1224   0.159303  23.022331 368.357301 0.000000e+00
      1272   0.176770  23.285343 372.565492 0.000000e+00
      1320   0.197169  23.329875 373.277999 0.000000e+00
      1368   0.220443  23.226904 371.630461 0.000000e+00
      1416   0.242707  23.395742 374.331878 0.000000e+00
      1464   0.267808  23.433073 374.929173 0.000000e+00
      1512   0.296075  23.349838 373.597416 0.000000e+00
      1560   0.328863  23.088155 369.410473 0.000000e+00
      1608   0.358194  23.215049 371.440782 0.000000e+00
      1656   0.391518  23.198475 371.175598 0.000000e+00
      1704   0.423670  23.356679 373.706861 0.000000e+00
      1752   0.460682  23.347020 373.552318 0.000000e+00
      1800   0.526360  22.159732 354.555706 0.000000e+00
      1848   0.535963  23.550531 376.808498 0.000000e+00
      1896   0.581558  23.439708 375.035320 0.000000e+00
      1944   0.626711  23.445061 375.120978 0.000000e+00
      1992   0.675078  23.417691 374.683058 0.000000e+00
	  
3. I chose to optimize the SSE/AVX part of the sin4_intrin() function, which gave the following timings/accuracy:
Reference time: 12.7191
Taylor time:    1.4351      Error: 6.928125e-12
Intrin time:    0.6257      Error: 6.928125e-12
Vector time:    0.4543      Error: 2.454130e-03

4. (b)

i. compute.cpp

For the mutliply add instruction with -O3 compiler flag, we get
0.090994 seconds
2.913021 cycles/eval
2.196911 Gflop/s


with the -O0 optimization flag, we get
0.291925 seconds
9.342718 cycles/eval
0.684978 Gflop/s

The theoretical latency is 4 for this operation, so it is interesting that the -O3 compilation flag gives a lower latency for this operation

For the division operation, we get with the -O3 flag
0.326244 seconds
10.440887 cycles/eval
0.612964 Gflop/s

and with the -O0 flag,
0.424798 seconds
13.594614 cycles/eval
0.470751 Gflop/s

while the theoretical latency of the operation is 14.

For the sqrt operation, and -O3, we get
0.313612 seconds
10.036625 cycles/eval
0.637653 Gflop/s
 
 
and for -O0, we get
0.600856 seconds
19.228758 cycles/eval
0.332823 Gflop/s

while the theoretical latency is 18

Finally, for sin, we get for -O3
1.092598 seconds
34.964203 cycles/eval
0.183041 Gflop/s

and for -O0,
1.383507 seconds
44.273298 cycles/eval
0.144554 Gflop/s

but this does not have a theoretical latency as it is a sequence of operations.

ii. compute-vec.cpp

When we run the code, we get the following timings:
compute_fn0
time = 0.890295
flop-rate = 8.985434 Gflop/s

compute_fn1
time = 1.776572
flop-rate = 4.503034 Gflop/s

compute_fn2
time = 1.778577
flop-rate = 4.497955 Gflop/s

It appears that the implicitly vectorized code is running 2 times faster than the explicitly vectorized code
This factor is likely due to the fact that the compiler is further optimizing the vectorization process in the autovectorization case.
This is further evidenced because when we compile with the -O0 flag (with different n), we get
time = 0.967099
flop-rate = 0.827182 Gflop/s

time = 0.997751
flop-rate = 0.801797 Gflop/s

time = 2.079047
flop-rate = 0.384790 Gflop/s

This means that the compiler is doing even more optimization in the autovectorization case than the explicit vectorization that allows for further speed up.

iii. compute-vec-pipe.cpp

For M=1, we get
time = 0.895347
flop-rate = 8.934587 Gflop/s

time = 1.779513
flop-rate = 4.495573 Gflop/s

time = 1.777471
flop-rate = 4.500750 Gflop/s

For M=8, we get

time = 2.221003
flop-rate = 28.815338 Gflop/s

time = 2.020859
flop-rate = 31.669540 Gflop/s

time = 2.033867
flop-rate = 31.466927 Gflop/s

For M=12, we get
time = 0.360234
flop-rate = 26.646805 Gflop/s

time = 0.279145
flop-rate = 34.389949 Gflop/s

time = 0.278578
flop-rate = 34.459879 Gflop/s

For M=16, we get
time = 7.541139
flop-rate = 16.973393 Gflop/s

time = 3.782839
flop-rate = 33.836922 Gflop/s

time = 3.782858
flop-rate = 33.836744 Gflop/s

For M=24, we get
time = 2.128750
flop-rate = 9.019215 Gflop/s

time = 2.123586
flop-rate = 9.041268 Gflop/s

time = 2.123807
flop-rate = 9.040329 Gflop/s

Thus, clearly, setting M in the range of 12 to 16 is optimal for bandwith. 
Below this range, we can still increase the amount of parallelism in the problem.
Above this range, the data begins to exceed the size of the registers, so the performance gains are lost
