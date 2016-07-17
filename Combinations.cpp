#include "Combinations.h"

#include <functional>
#include <algorithm>


// def combinations_bigger_than(inp, k):
// res = set()
// 
// def _combinations(inp, this):
// #print this
// 
// if len(this) >= k:
//     res.add(''.join(sorted(this)))
//     
//     if len(inp) == 0 :
//         return
//         else:
//             _combinations(inp[1:], this + inp[0]) # with current char
//             _combinations(inp[1:], this) # without current char
//             
//     start = ""
//     _combinations(inp, start)
//     return res #sorted(res)
// //       

static void _combinations(std::string inp, std::string cur, std::vector<std::string> &res, unsigned int k) {
    if (cur.length() == k)
        res.push_back(cur);
    else if (inp.length() == 0 || cur.length() > k)
        return;
    else {
        _combinations(inp.substr(1), cur + inp.at(0), res, k);
        _combinations(inp.substr(1), cur, res, k);
    }
}

std::vector<std::string> Combinations::combinations(const std::string &input, unsigned int k) {
    std::vector<std::string> res;
    res.reserve(fact(input.length()) / (fact(k) * fact(input.length() - k)));
    _combinations(input, std::string(), res, k);
    return res;
}


// def combinations(inp, k):
//     res = set()
// 
//     def _combinations(inp, n, this):
//         if len(this) == k:
//             res.add(''.join(sorted(this)))
//         elif n == 0 or len(inp) == 0 or len(this) > k:
//             return
//         else:
//             _combinations(inp[1:], n-1, this + inp[0]) # with current char
//             _combinations(inp[1:], n, this) # without current char
//     
//     start = ""
//     _combinations(inp, k, start)
//     return res #sorted(res)
//     


static void _combinationsBiggerThan(std::string inp, std::string cur, std::vector<std::string> &res, unsigned int k) {
    if (cur.length() >= k)
        res.push_back(cur);
    
    if (inp.length() == 0)
        return;
    else {
        _combinationsBiggerThan(inp.substr(1), cur + inp.at(0), res, k);
        _combinationsBiggerThan(inp.substr(1), cur, res, k);
    }
}

std::vector<std::string> Combinations::combinationsBiggerThan(const std::string &input, unsigned int k) {
    std::vector<std::string> res;
    // TODO: how big will this be? we should reserve space for this too
    _combinationsBiggerThan(input, std::string(), res, k);
    return res;
}


std::vector<std::string> Combinations::nPk(const std::string& input, unsigned int k) {
    std::vector<std::string> npk;
    npk.reserve(fact(input.length() / fact(input.length() - k)));
    std::vector<std::string> combs = combinations(input, k);

    for (auto comb : combs) {
        do {
            npk.push_back(comb);
        } while(std::next_permutation(comb.begin(), comb.end()));
    }
    return npk;

}


