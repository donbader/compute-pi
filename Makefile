CC = gcc
CFLAGS = -O0 -std=gnu99 -Wall -fopenmp -mavx
EXECUTABLE = \
	time_test_baseline time_test_openmp_2 time_test_openmp_4 \
	time_test_avx time_test_avxunroll \
	benchmark_clock_gettime \
	benchmark_clock_gettime_95 \
	benchmark_formula_iter_times \
	benchmark_formula_time \
	benchmark_compare_omp_threads \
	benchmark_compare_omp_simd_threads

CSV = \
	result_clock_gettime.csv \
	result_clock_gettime_95.csv \
	result_formula_iter_times.csv \
	result_formula_time.csv \
	result_compare_omp_threads.csv \
	result_compare_omp_simd_threads.csv

GIT_HOOKS := .git/hooks/pre-commit

$(GIT_HOOKS):
	@scripts/install-git-hooks
	@echo

default: $(GIT_HOOKS) computepi.o
	$(CC) $(CFLAGS) computepi.o time_test.c -DBASELINE -o time_test_baseline -lm -lOpenCL
	$(CC) $(CFLAGS) computepi.o time_test.c -DOPENMP_2 -o time_test_openmp_2 -lm -lOpenCL
	$(CC) $(CFLAGS) computepi.o time_test.c -DOPENMP_4 -o time_test_openmp_4 -lm -lOpenCL
	$(CC) $(CFLAGS) computepi.o time_test.c -DAVX -o time_test_avx -lm -lOpenCL
	$(CC) $(CFLAGS) computepi.o time_test.c -DAVXUNROLL -o time_test_avxunroll -lm -lOpenCL

.PHONY: clean default

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

check: default
	time ./time_test_baseline
	time ./time_test_openmp_2
	time ./time_test_openmp_4
	time ./time_test_avx
	time ./time_test_avxunroll

gencsv: computepi.o
	$(CC) $(CFLAGS) computepi.o benchmark_clock_gettime.c -o benchmark_clock_gettime -lm -lOpenCL
	for i in `seq 512 512 512000`; do \
		printf "%d," $$i;\
		./benchmark_clock_gettime $$i; \
	done > result_clock_gettime.csv	

gencsv95: computepi.o
	$(CC) $(CFLAGS) computepi.o benchmark_clock_gettime_95.c -o benchmark_clock_gettime_95 -lm -lOpenCL
	for i in `seq 512 512 512000`; do \
		printf "%d," $$i;\
		./benchmark_clock_gettime_95 $$i; \
	done > result_clock_gettime_95.csv	

gencsv_formula_iter_times: pi_formula.o
	$(CC) $(CFLAGS) pi_formula.o benchmark_formula_iter_times.c -o benchmark_formula_iter_times -lm
	for i in `seq 1 1 7`; do \
		printf "%d," $$i;\
		./benchmark_formula_iter_times $$i; \
	done > result_formula_iter_times.csv	

gencsv_formula_time: pi_formula.o result_formula_iter_times.csv
	$(CC) $(CFLAGS) pi_formula.o benchmark_formula_time.c -o benchmark_formula_time -lm
	./benchmark_formula_time > result_formula_time.csv

gencsv_compare_omp_threads: computepi.o
	$(CC) $(CFLAGS) computepi.o benchmark_compare_omp_threads.c -o benchmark_compare_omp_threads -lm -lOpenCL
	./benchmark_compare_omp_threads 512 512 512000 > result_compare_omp_threads.csv

gencsv_compare_omp_simd_threads: computepi.o
	$(CC) $(CFLAGS) computepi.o benchmark_compare_omp_simd_threads.c -o benchmark_compare_omp_simd_threads -lm -lOpenCL
	./benchmark_compare_omp_simd_threads 512 512 512000 > result_compare_omp_simd_threads.csv


gencsv_all: gencsv gencsv95 gencsv_formula_iter_times gencsv_formula_time gencsv_compare_omp_threads gencsv_compare_omp_simd_threads

clean:
	rm -f $(EXECUTABLE) *.o *.s $(CSV)
