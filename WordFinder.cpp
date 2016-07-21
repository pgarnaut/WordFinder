#include <fstream>
#include <sstream>
#include <functional>
#include <algorithm>
#include <iterator>
#include <cctype>
#include <locale>
#include <iostream>

#include <unistd.h>

#include "WordFinder.h"
#include "Combinations.h"

#define MIN_WORD_SIZE 4


using namespace std;

// trim from start
static inline std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
            std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
            std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}

WordFinder::WordFinder(void) {
    std::string dictPath = this->readConfig();
    trim(dictPath);
    this->setDictionary(dictPath);
}

std::string WordFinder::readConfig(const std::string &path) {
    std::ifstream t(path);
    std::stringstream buffer;
    if (!t)
        return "";

    buffer << t.rdbuf();

    return buffer.str();
}

bool WordFinder::setDictionary(const std::string &path) {
    this->dict.clear();
    std::ifstream dictFile(path);
    std::stringstream buffer;
    printf("setDictionary: %s \n", path.c_str());

    // dont remember this dict if it's no good
    if (!dictFile)
        return false;

    printf("reading dict  ... \n");
    // save path to the dictionary we just opened
    std::ofstream cfgOut(this->cfgPath);
    cfgOut << path;

    // read it in line by line
    std::copy(std::istream_iterator<std::string>(dictFile),
              std::istream_iterator<std::string>(),
              std::back_inserter(this->dict));

    cout << "n words in dict: " << this->dict.size() << endl;

    std::sort(this->dict.begin(), this->dict.end());

    cout << "read dict, wrote config" << endl;

    return true;
}

std::vector<std::string> WordFinder::solve(const std::string &possible, const std::string &required) {
    if (possible.length() <= MIN_WORD_SIZE || required.size() >= possible.length())
        return {};
    
    auto containsAllChars = [](const std::string &haystack, const std::string &needles) -> bool {
        for (auto c : needles)
            if (haystack.find(c) == std::string::npos)
                return false;
        return true;
    };
    
    if (!containsAllChars(possible, required))
        return {};


    std::vector<std::string> combos = Combinations::combinationsBiggerThan(possible, MIN_WORD_SIZE);
    cout << "NUMBER OF COMBINATIONS: " << combos.size() << endl;
    std::vector<std::string> res;
    //res.reserve(combos.size() * Combinations::fact(possible.size()));

    for (auto combo : combos) {
        do {
            if (containsAllChars(combo, required) && std::binary_search(this->dict.begin(), this->dict.end(), combo))
                res.push_back(combo);
        } while(std::next_permutation(combo.begin(), combo.end()));
    }
    //cout << "NUMBER OF PERMUTATIONS: " << res.size() << endl;
    return res;

}

bool WordFinder::wordExists(const std::string &word) {
    return std::binary_search(this->dict.begin(), this->dict.end(), word);
}
