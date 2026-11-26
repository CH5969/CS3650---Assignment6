# Threaded Merge Sort Experiments


## Host 1: MacBook Pro (Apple M2 Max)

- CPU: Apple M2 Max
- Cores: 12
- Cache size (if known):
  - Performance cores: L1i 192 KB, L1d 128 KB, L2 16 MB
  - Efficiency cores: L1i 128 KB, L1d 64 KB, L2 4 MB
- RAM: 32 GB
- Storage (if known): 926 GiB SSD (588 GiB available)
- OS: macOS 26.6.2 (Build 25G83)

### Input data

I created a data set of 200,000,000 random integers using `./numbers 1 200000000 > input.txt`. Running the single-threaded starter program (`./msort input.txt > /dev/null`) took 34.404213 seconds to sort it.

### Experiments

#### 1 Thread

Running processes before experiment (`ps aux | wc -l`): 862

Command used to run experiment: `MSORT_THREADS=1 ./tmsort input.txt > /dev/null`

Sorting portion timings:

1. 34.315732 seconds
2. 34.698532 seconds
3. 34.881147 seconds
4. 34.998644 seconds

Average: 34.723514 seconds

#### 2 Threads

Running processes before experiment (`ps aux | wc -l`): 859

Command used to run experiment: `MSORT_THREADS=2 ./tmsort input.txt > /dev/null`

Sorting portion timings:

1. 18.346531 seconds
2. 18.361988 seconds
3. 18.379284 seconds
4. 18.361165 seconds

Average: 18.362242 seconds

#### 6 Threads

Running processes before experiment (`ps aux | wc -l`): 858

Command used to run experiment: `MSORT_THREADS=6 ./tmsort input.txt > /dev/null`

Sorting portion timings:

1. 7.697483 seconds
2. 7.694393 seconds
3. 7.706530 seconds
4. 7.692398 seconds

Average: 7.697701 seconds

#### 12 Threads

Running processes before experiment (`ps aux | wc -l`): 860

Command used to run experiment: `MSORT_THREADS=12 ./tmsort input.txt > /dev/null`

Sorting portion timings:

1. 5.632905 seconds
2. 5.613879 seconds
3. 5.604183 seconds
4. 5.570613 seconds

Average: 5.605395 seconds

#### 24 Threads

Running processes before experiment (`ps aux | wc -l`): 859

Command used to run experiment: `MSORT_THREADS=24 ./tmsort input.txt > /dev/null`

Sorting portion timings:

1. 5.534159 seconds
2. 5.520199 seconds
3. 5.496418 seconds
4. 5.608113 seconds

Average: 5.539722 seconds

#### 48 Threads

Running processes before experiment (`ps aux | wc -l`): 861

Command used to run experiment: `MSORT_THREADS=48 ./tmsort input.txt > /dev/null`

Sorting portion timings:

1. 5.581804 seconds
2. 5.535327 seconds
3. 5.519938 seconds
4. 5.520510 seconds

Average: 5.539395 seconds


## Host 2: Khoury Login Server (login-students)

- CPU: Intel(R) Xeon(R) Silver 4214R CPU @ 2.40GHz
- Cores: 24
- Cache size (if known): L1d 32 KB, L1i 32 KB, L2 1 MB, L3 16.5 MB
- RAM: 156 GiB
- Storage (if known): 3.0 TB NFS home volume (670 GB available)
- OS: Rocky Linux 8.10 (Green Obsidian), Linux 4.18.0-553.154.1.el8_10.x86_64

### Input data

I created a data set of 100,000,000 random integers using `./numbers 1 100000000 > /tmp/a6_input.txt`. Running the single-threaded starter program (`./msort /tmp/a6_input.txt > /dev/null`) took 24.834895 seconds to sort it.

### Experiments

#### 1 Thread

Running processes before experiment (`ps aux | wc -l`): 1062

Command used to run experiment: `MSORT_THREADS=1 ./tmsort /tmp/a6_input.txt > /dev/null`

Sorting portion timings:

1. 26.182761 seconds
2. 25.862500 seconds
3. 26.590492 seconds
4. 26.050120 seconds

Average: 26.171468 seconds

#### 2 Threads

Running processes before experiment (`ps aux | wc -l`): 1061

Command used to run experiment: `MSORT_THREADS=2 ./tmsort /tmp/a6_input.txt > /dev/null`

Sorting portion timings:

1. 13.547118 seconds
2. 14.014011 seconds
3. 14.021468 seconds
4. 14.156169 seconds

Average: 13.934691 seconds

#### 12 Threads

Running processes before experiment (`ps aux | wc -l`): 1074

Command used to run experiment: `MSORT_THREADS=12 ./tmsort /tmp/a6_input.txt > /dev/null`

Sorting portion timings:

1. 4.119988 seconds
2. 4.777922 seconds
3. 4.691037 seconds
4. 4.194190 seconds

Average: 4.445784 seconds

#### 24 Threads

Running processes before experiment (`ps aux | wc -l`): 1069

Command used to run experiment: `MSORT_THREADS=24 ./tmsort /tmp/a6_input.txt > /dev/null`

Sorting portion timings:

1. 3.827849 seconds
2. 3.623616 seconds
3. 3.744280 seconds
4. 3.577513 seconds

Average: 3.693315 seconds

#### 48 Threads

Running processes before experiment (`ps aux | wc -l`): 1065

Command used to run experiment: `MSORT_THREADS=48 ./tmsort /tmp/a6_input.txt > /dev/null`

Sorting portion timings:

1. 3.387424 seconds
2. 3.269719 seconds
3. 3.289471 seconds
4. 3.299156 seconds

Average: 3.311443 seconds

#### 96 Threads

Running processes before experiment (`ps aux | wc -l`): 1042

Command used to run experiment: `MSORT_THREADS=96 ./tmsort /tmp/a6_input.txt > /dev/null`

Sorting portion timings:

1. 5.369781 seconds
2. 4.118800 seconds
3. 4.049247 seconds
4. 5.337056 seconds

Average: 4.718721 seconds


## Observations and Conclusions

On Host 1 (MacBook Pro, 12 cores, 200,000,000 numbers), sorting got much faster as I added more threads up to 12. The average time dropped from 34.72 seconds with 1 thread (close to `msort` at 34.40 seconds) to 18.36 seconds with 2 threads, 7.70 seconds with 6 threads, and 5.61 seconds with 12 threads (about 6.2x faster). After 12 threads, adding more threads did not really help. Both 24 threads and 48 threads took 5.54 seconds on average. Since this is my own laptop with steady background processes (around 860), the four runs for each test had very similar times.

On Host 2 (Khoury Login Server, 24 cores, 100,000,000 numbers), sorting also got much faster at first. The average time dropped from 26.17 seconds with 1 thread (similar to `msort` at 24.83 seconds) to 13.93 seconds with 2 threads and 4.45 seconds with 12 threads. At 24 threads, the time was 3.69 seconds, and at 48 threads it reached its fastest time of 3.31 seconds (about 7.9x faster). However, at 96 threads, it got slower again at 4.72 seconds on average. Because Khoury is a shared server with over 1,000 processes running, the times changed more from run to run than on my MacBook.

On both machines, most of the speedup stopped near the number of CPU cores (12 cores on Host 1, 24 cores on Host 2). On Host 2, 48 threads was still a little faster than 24 threads, likely because the server handled the smaller splits well on busy cores, but going to 96 threads clearly made it slower.

Adding too many threads stops helping for three main reasons:

1. **Core limit:** A CPU can only run as many threads at the same time as it has cores. When there are too many threads, the OS has to keep switching between them, which wastes time.
2. **Single-thread merge step:** Even when the halves are sorted in parallel, the final top-level `merge()` calls still run on one thread after joining. Because this part is not parallel, the speedup cannot reach 12x or 24x.
3. **Memory limit:** Sorting 100M to 200M `long` numbers copies two huge arrays in RAM. Once memory gets busy, extra threads just wait for memory instead of working faster.

In short, setting `MSORT_THREADS` close to the number of CPU cores gave the best results on both machines.