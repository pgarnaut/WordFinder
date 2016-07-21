#include "WordFinder.h"

#include <iostream>

using namespace std;

int main(int argc, char **argv) {
    cout << "being" << endl;
    
    WordFinder wordFinder;
    
    for (auto match : wordFinder.solve("abcdefghi", "e"))
        cout << "WORD: " << match << endl;
    
    cout << "done" << endl;
}