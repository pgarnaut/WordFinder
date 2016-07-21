#ifndef WORDFINDER_H
#define WORDFINDER_H

#include <vector>
#include <string>

class WordFinder
{
public:
    WordFinder(void);
    bool setDictionary(const std::string &path="word_list.txt");
    bool writeConfig(const std::string &path="./WordFinder.cfg");
    std::string readConfig(const std::string &path="./WordFinder.cfg");
    std::vector<std::string> solve(const std::string &possible, const std::string &required);
private:
    bool wordExists(const std::string &word);
    const char *cfgPath = "./WordFinder.cfg";
    std::vector<std::string> dict;
};

#endif // WORDFINDER_H
