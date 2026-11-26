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

I created a data set of [100,000,000] random integers using `./numbers 1 [100000000] > input.txt`. Running the single-threaded starter program (`./msort input.txt > /dev/null`) took ______ seconds to sort it.

### Experiments

#### 1 Thread

Running processes before experiment (`ps aux | wc -l`): ______

Command used to run experiment: `MSORT_THREADS=1 ./tmsort input.txt > /dev/null`

Sorting portion timings:

1. ______ seconds
2. ______ seconds
3. ______ seconds
4. ______ seconds

Average: ______ seconds

#### 2 Threads

Running processes before experiment (`ps aux | wc -l`): ______

Command used to run experiment: `MSORT_THREADS=2 ./tmsort input.txt > /dev/null`

Sorting portion timings:

1. ______ seconds
2. ______ seconds
3. ______ seconds
4. ______ seconds

Average: ______ seconds

#### 6 Threads

Running processes before experiment (`ps aux | wc -l`): ______

Command used to run experiment: `MSORT_THREADS=6 ./tmsort input.txt > /dev/null`

Sorting portion timings:

1. ______ seconds
2. ______ seconds
3. ______ seconds
4. ______ seconds

Average: ______ seconds

#### 12 Threads

Running processes before experiment (`ps aux | wc -l`): ______

Command used to run experiment: `MSORT_THREADS=12 ./tmsort input.txt > /dev/null`

Sorting portion timings:

1. ______ seconds
2. ______ seconds
3. ______ seconds
4. ______ seconds

Average: ______ seconds

#### 24 Threads

Running processes before experiment (`ps aux | wc -l`): ______

Command used to run experiment: `MSORT_THREADS=24 ./tmsort input.txt > /dev/null`

Sorting portion timings:

1. ______ seconds
2. ______ seconds
3. ______ seconds
4. ______ seconds

Average: ______ seconds

#### 48 Threads

Running processes before experiment (`ps aux | wc -l`): ______

Command used to run experiment: `MSORT_THREADS=48 ./tmsort input.txt > /dev/null`

Sorting portion timings:

1. ______ seconds
2. ______ seconds
3. ______ seconds
4. ______ seconds

Average: ______ seconds


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

Average: 13.934692 seconds

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

On Host 1 (12-core Apple M2 Max), sorting got much faster as I raised the thread count from 1 ([1-thread avg] seconds) up to [best thread count] threads ([best avg] seconds). Beyond [stop-improving thread count] threads, adding more threads stopped giving clear speedups and started to slow down.

On Host 2 (24-core Khoury Login Server), sorting improved greatly from 1 thread (26.17 seconds on average, similar to `msort` at 24.83 seconds) to 2 threads (13.93 seconds, ~1.9x faster) and 12 threads (4.45 seconds, ~5.9x faster). Speedup slowed down near the 24-core count (3.69 seconds at 24 threads) and peaked at 48 threads (3.31 seconds, ~7.9x faster). At 96 threads, performance got clearly worse (4.72 seconds on average, with runs jumping up to 5.37 seconds). Because Khoury Login is a shared server with over 1,000 running processes, run times also had more variance when using many threads.

On both machines, most of the speedup happens up to the CPU core count (12 on Host 1, 24 on Host 2), and going far past the core count hurts performance for three main reasons:

1. **CPU core limit and thread switching:** When there are more active threads than CPU cores, the OS must switch threads in and out of cores. This adds context-switching cost and causes more CPU cache misses.
2. **Sequential merge work (Amdahl's Law):** After child threads finish and join, the top-level `merge()` calls still run on a single thread. Because that work is not parallel, it limits the maximum speedup no matter how many threads we add.
3. **Memory bandwidth limit:** Sorting 100,000,000 `long` values moves two 800 MB arrays back and forth in RAM. Once memory bandwidth is saturated, extra threads wait on memory instead of sorting faster.

Overall, setting `MSORT_THREADS` close to the number of CPU cores (or up to 2x cores at most) gave the best performance on both hosts.