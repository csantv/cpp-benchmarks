#include <benchmark/benchmark.h>
#include <random>
#include <array>
#include <iostream>
#include <execution>

void func() {
    int xxx = 1;
}

namespace {
    auto get_engine() -> std::mt19937_64 {
        static std::random_device rng;
        std::array<unsigned int, std::mt19937_64::state_size> seed;
        std::generate_n(std::execution::par_unseq, seed.begin(), seed.size(), std::ref(rng));
        std::seed_seq seq(std::begin(seed), std::end(seed));
        std::mt19937_64 engine;
        engine.seed(seq);
        return engine;
    }

    void even_bench(benchmark::State& state) {
        auto engine = get_engine();
        for (auto ign : state) {
            const auto num = engine();
            bool even = (num & 1) == 0;
            benchmark::DoNotOptimize(even);
        }
    }

    void even_bench_2(benchmark::State& state) {
        auto engine = get_engine();
        for (auto ign: state) {
            const auto num = engine();
            bool even = num % 2 == 0;
            benchmark::DoNotOptimize(even);
        }
    }
} // end namespace

BENCHMARK(even_bench);
BENCHMARK(even_bench_2);

auto main(int argc, char *argv[]) -> int {
    benchmark::Initialize(&argc, argv);
    benchmark::RunSpecifiedBenchmarks();
    benchmark::Shutdown();
    return 0;
}
