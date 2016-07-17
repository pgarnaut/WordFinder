#ifndef COMBINATIONS_H
#define COMBINATIONS_H

#include <vector>
#include <string>

class Combinations {
public:
    static std::vector<std::string> combinations(const std::string &input, unsigned int k);
    static std::vector<std::string> combinationsBiggerThan(const std::string &input, unsigned int k);
    static std::vector<std::string> nPk(const std::string &input, unsigned int k);

    static unsigned long long fact(int n) {
        return (n == 1 || n == 0) ? 1 : fact(n - 1) * n;
    }
};

#endif // COMBINATIONS_H
