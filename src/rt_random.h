#pragma once
#include <random>

namespace trace {

inline double mt_random() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    static std::function<double()> rand_generator =
      std::bind(distribution, generator);
    return rand_generator();
  }


}