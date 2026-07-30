#include <benchmark/benchmark.h>
#include "sort.h"
#include <vector>
#include <random>

static void BMSortInsertion(benchmark::State& state) {
    int n = state.range(0);
    srand(80);
    std::vector<int> data(n);
    for (int i = 0; i < n; ++i) data[i] = rand() % 10000;

    for (auto _ : state) {
        state.PauseTiming();
        LinkedList list = LinkedList::from_vector(data);
        state.ResumeTiming();
        sort_insertion(list);
    }
}

BENCHMARK(BMSortInsertion)->Arg(100)->Arg(1000)->Arg(10000)->Arg(50000)->Arg(100000) -> Unit(benchmark::kMillisecond);

static void BMSortMerge(benchmark::State& state) {
    int n = state.range(0);
    srand(80);
    std::vector<int> data(n);
    for (int i = 0; i < n; ++i) data[i] = rand() % 10000;

    for (auto _ : state) {
        state.PauseTiming();
        LinkedList list = LinkedList::from_vector(data);
        state.ResumeTiming(); //to measure the sort time not the rebuild of the list
        sort_merge(list);
    }
}

BENCHMARK(BMSortMerge)->Arg(100)->Arg(1000)->Arg(10000)->Arg(50000)->Arg(100000) -> Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();