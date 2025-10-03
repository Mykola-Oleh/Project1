#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <numeric>
#include <algorithm>
#include <string>
#include <locale>
#include "RandomByFrequency.h"

using namespace std;

bool readInput(const string& filename,
    int& n,
    vector<int>& nums,
    vector<size_t>& freqs,
    int& m)
{
    ifstream fin(filename);
    if (!fin) {
        cerr << "Помилка: не вдалося відкрити файл " << filename << "\n";
        return false;
    }

    if (!(fin >> n) || n <= 0) {
        cerr << "Помилка: некоректне n\n";
        return false;
    }

    nums.resize(n);
    freqs.resize(n);

    for (int i = 0; i < n; i++) {
        if (!(fin >> nums[i])) {
            cerr << "Помилка: не вдалося зчитати число\n";
            return false;
        }
    }

    for (int i = 0; i < n; i++) {
        int f;
        if (!(fin >> f) || f < 0) {
            cerr << "Помилка: некоректна частота\n";
            return false;
        }
        freqs[i] = static_cast<size_t>(f);
    }

    if (!(fin >> m) || m <= 0) {
        cerr << "Помилка: некоректне значення m\n";
        return false;
    }

    return true;
}

vector<int> generateFrequencies(const RandomByFrequency& rnd,
    const vector<int>& nums,
    int m)
{
    vector<int> counts(nums.size(), 0);
    for (int i = 0; i < m; i++) {
        int x = rnd();
        auto it = find(nums.begin(), nums.end(), x);
        if (it != nums.end()) {
            counts[it - nums.begin()]++;
        }
    }
    return counts;
}

void printResults(const vector<int>& nums,
    const vector<size_t>& freqs,
    const vector<int>& counts,
    int m)
{
    int totalFreq = accumulate(freqs.begin(), freqs.end(), 0ull);
    double maxDiff = 0.0;

    cout << setw(10) << "Число"
        << setw(15) << "Задана частота"
        << setw(15) << " Отримана частота"
        << setw(15) << "Різниця\n";

    for (size_t i = 0; i < nums.size(); i++) {
        double expected = static_cast<double>(freqs[i]) / totalFreq;
        double actual = static_cast<double>(counts[i]) / m;
        double diff = abs(expected - actual);
        maxDiff = max(maxDiff, diff);

        cout << setw(10) << nums[i]
            << setw(15) << expected
                << setw(15) << actual
                << setw(15) << diff << "\n";
    }

    cout << "\nНайбільша розбіжність: " << maxDiff << "\n";
}

int main() {
	locale::global(locale("ukr"));
    try {
        int n, m;
        vector<int> nums;
        vector<size_t> freqs;

        if (!readInput("input.txt", n, nums, freqs, m)) {
            return 1;
        }

        RandomByFrequency rnd(nums, freqs);
        auto counts = generateFrequencies(rnd, nums, m);
        printResults(nums, freqs, counts, m);
    }
    catch (const exception& e) {
        cerr << "Виняток: " << e.what() << "\n";
        return 1;
    }

    return 0;
}