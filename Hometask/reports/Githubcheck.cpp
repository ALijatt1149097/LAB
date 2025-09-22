// Githubcheck.cpp
// Simple utility "sdoe" - parse integer arguments, print sum and mean.
// Build: g++ -std=c++17 -O2 Githubcheck.cpp -o sdoe

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <numeric>
#include <iomanip>

class Sdoe {
public:
    // Parse integer arguments from argv. Non-integer tokens are ignored.
    static std::vector<long long> parseArgs(int argc, char** argv) {
        std::vector<long long> out;
        for (int i = 1; i < argc; ++i) {
            std::istringstream iss(argv[i]);
            long long v;
            if (iss >> v) out.push_back(v);
        }
        return out;
    }

    static void printHelp(const std::string& prog) {
        std::cout << "Usage: " << prog << " [integers...]\n"
                  << "Example: " << prog << " 10 20 30\n"
                  << "Outputs sum, count and mean of provided integers.\n";
    }

    static void run(int argc, char** argv) {
        if (argc <= 1) {
            printHelp(argv[0]);
            return;
        }
        auto vals = parseArgs(argc, argv);
        if (vals.empty()) {
            std::cerr << "No valid integers provided.\n";
            return;
        }
        long long sum = std::accumulate(vals.begin(), vals.end(), 0LL);
        double mean = static_cast<double>(sum) / vals.size();
        std::cout << "count: " << vals.size() << "\n"
                  << "sum:   " << sum << "\n"
                  << "mean:  " << std::fixed << std::setprecision(4) << mean << "\n";
    }
};

int main(int argc, char** argv) {
    Sdoe::run(argc, argv);
    return 0;
}