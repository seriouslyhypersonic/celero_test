/*
 * Copyright (c) Nuno Alves de Sousa 2019
 *
 * Use, modification and distribution is subject to the Boost Software License,
 * Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */
#include <random>

#include <celero/Celero.h>

CELERO_MAIN

std::random_device randomDevice;
std::uniform_int_distribution<int> uniformIntDistribution(0, 1024);

BASELINE(DemoSimple, Baseline, 30, 1000000)
{
    celero::DoNotOptimizeAway(static_cast<float>
        (sin(fmod(uniformIntDistribution(randomDevice), 3.14159265))));
}

// Since the sample size is equal to 0, celero will compute a number to use for
// both samples and iterations.
BENCHMARK(DemoSimple, Complex32, 0, 0)
{
    celero::DoNotOptimizeAway(static_cast<float>
        (sin(fmod(uniformIntDistribution(randomDevice), 3.14159265))));
}