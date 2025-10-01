#pragma once
#include <vector>
#include <random>
#include <stdexcept>
#include <algorithm>

class RandomByFrequency {
    std::vector<int> values_;
    mutable std::discrete_distribution<std::size_t> dist_;
    mutable std::mt19937_64 gen_;

    static void validate(const std::vector<int>& vals, const std::vector<std::size_t>& freq) {
        if (vals.empty() || vals.size() != freq.size())
            throw std::invalid_argument("Empty data or array sizes differ.");
        if (std::all_of(freq.begin(), freq.end(), [](std::size_t w) { return w == 0; }))
            throw std::invalid_argument("All frequencies are zero.");
        std::vector<int> t = vals;
        std::sort(t.begin(), t.end());
        if (std::adjacent_find(t.begin(), t.end()) != t.end())
            throw std::invalid_argument("Values must be pairwise distinct.");
    }

public:
    RandomByFrequency(const std::vector<int>& values, const std::vector<std::size_t>& freqs, std::uint64_t seed = std::random_device{}())
        : values_(values), dist_(freqs.begin(), freqs.end()), gen_(seed)
    {
        validate(values_, freqs);
    }

    int operator()() const {
        std::size_t idx = dist_(gen_);
        return values_[idx];
    }

};
