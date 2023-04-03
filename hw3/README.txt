Question 1. OpenMP warm-up

For simplicity, I am assuming that n is even

(a) The first loop splits into two chunks, one that runs from 1 to n/2, and the other from n/2+1 to n-1. Thus, the first chunk runs in 1 + 2 + ... + n/2 milliseconds, which reduces to n^2/8 + n/4 milliseconds.

Then, the second chunk runs in (n/2+1) + ... + (n-1) milliseconds, which reduces to 3n^2/8 - 3n/4 milliseconds.

This means the first thread waits (3n^2/8 - 3n/4) - (n^2/8 + n/4) = n^2/4 - n milliseconds for the second thread in the first for loop.

In the second loop, we also have two chunks, split in the same way. However, now the first thread takes (n-1) + (n-2) + ... + (n-n/2), which is equal to 3n^2/8-n/4 milliseconds

The second chunk goes from i=n/2+1 to n-1, which takes a total of (n-(n/2+1)) + ... + (n- (n-1)) = n^2/8-n/4.

This means that the second thread waits (3n^2/8 - n/4) - (n^2/8-n/4) = n^2/4 milliseconds for the first thread.

Thus, the total time for the first loop is limited by the second thread, for a total of 3n^2/8 - 3n/4 milliseconds, while the second loop is limited by the first thread for a total of 3n^2/8 - n/4 milliseconds. Therefore, the total time spent to execute the parallel region is 3n^2/4 - n milliseconds

Therefore, the total amount of time spent waiting for the other threads is n^2/2 - n milliseconds.

(b) If we use schedule(static, 1) for both loops, then the chunks become size 1. This means that the first thread will be assigned i=1, 3, 5, ..., n-1, while the second thread will be assigned i=2, 4, ... n-2.

In the first loop, the first thread will take 1 + 3 + 5 + ... + (n-1) = n^2/4 milliseconds, and the second thread will take 2 + 4 + ... + n-2 = n^2/4 - n/2 milliseconds.

In the first loop, the first thread will take (n-1) + (n-3) + ... + (n-(n-1)) = n^2/4 milliseconds while the second thread will take (n-2) + (n-4) + ... + (n-(n-2)) = n^2/4 - n/2 milliseconds.

Therefore, the total time spent to execute the parallel region is n^2/4 + n^2/4 = n^2/2 milliseconds.

(c) Yes, the execution time would improve if we used schedule(dynamic, 1). This is because as soon as one chunk finished executing, it will be assigned the next available chunk. Since the amount of execution time changes drastically for different values of i, using dynamics scheudling will allow for efficient use of thread time, similar to the schedule(static, 1) case.

(d) Yes, this would be the nowait clause. This would eliminate the waiting time between loops. Thus, the first thread would take a total of n^2/8 + n/4 + 3n^2/8 - n/4 = n^2/2 milliseconds, while the second thread would take 3n^2/8 - 3n/4 + n^2/8 - n/4 = n^2/2 - n milliseconds. Therefore, the overall program is limited by the first thread, so the whole program takes n^2/2 milliseconds to run.

Question 2.
This question was run on a AMD EPYC Processor with 4 cores @ 2.89 MhZ

I ran this with N = 10000000
Note that the serial time for this test is: 0.074000s
num_thread, total time
01,0.017261
02,0.011664
03,0.009990
04,0.010304
05,0.012885
06,0.009994
07,0.010945
08,0.009181
