#include <fstream>
#include <sstream>
#include <functional>
#include <algorithm>
#include <iterator>
#include <cctype>
#include <locale>


#include <unistd.h>

#include "WordFinder.h"
#include "Combinations.h"

#define MIN_WORD_SIZE 4

using std::istream_iterator;



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

    printf("n words in dict: %lu\n", this->dict.size());

    std::sort(this->dict.begin(), this->dict.end());

    // TODO: do something with dict word list here, read into a vector<string> ?
    printf("read dict, wrote config\n");

    return true;
}

std::vector<std::string> WordFinder::solve(const std::string &possible, const std::string &required) {
    if (possible.length() <= MIN_WORD_SIZE || required.size() >= possible.length())
        return {};


    std::vector<std::string> combos = Combinations::combinationsBiggerThan(possible, MIN_WORD_SIZE);
    std::vector<std::string> res;
    //res.reserve(combos.size() * Combinations::fact(possible.size()));

    for (auto combo : combos) {
        do {
            res.push_back(combo);
        } while(std::next_permutation(combo.begin(), combo.end()));
    }
    return res;

}

bool WordFinder::wordExists(const std::string &word) {
    return std::binary_search(this->dict.begin(), this->dict.end(), word);
}
