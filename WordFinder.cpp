#include "WordFinder.h"
#include <fstream>
#include <sstream>

WordFinder::WordFinder(void) {
    std::string dictPath = this->readConfig();
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
    std::ifstream t(path);
    std::stringstream buffer;

    printf("setDictionary ... \n");

    // dont remember this dict if it's no good
    if (!t)
        return false;

    // save path to the dictionary we just opened
    std::ofstream cfgOut(this->cfgPath);
    cfgOut << path;

    // read in the dictionary
    buffer << t.rdbuf();

    // TODO: do something with dict word list here, read into a vector<string> ?
    printf("read dict, wrote config\n");


    return true;
}
