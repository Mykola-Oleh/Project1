#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <algorithm>
#include <array>
#include "RandomByFrequency.h"

using namespace std;

int main()
{
	std::vector<int> vals{ 1, 2, 3 };
	std::vector<std::size_t> freqs{ 2, 2, 2 };
	RandomByFrequency pick(vals, freqs);

	const int N = 6000;
	std::array<int, 3> cnt{ 0,0,0 };

	for (int i = 0; i < N; ++i) {
		int x = pick();
		if (x == 1) ++cnt[0];
		else if (x == 2) ++cnt[1];
		else if (x == 3) ++cnt[2];
	}

	std::cout << "1: " << cnt[0] << "\n"
		<< "2: " << cnt[1] << "\n"
		<< "3: " << cnt[2] << "\n";

	return 0;
}
