#ifndef WORDFINDER_H
#define WORDFINDER_H

#include <vector>
#include <string>

class WordFinder
{
public:
    WordFinder(void);
    bool setDictionary(const std::string &path);
    std::vector<std::string> findWords(const std::string &letters, const std::string &requiredLetters);
    bool writeConfig(const std::string &path="./WordFinder.cfg");
    std::string readConfig(const std::string &path="./WordFinder.cfg");

private:
    const char *cfgPath = "./WordFinder.cfg";

};

#endif // WORDFINDER_H
