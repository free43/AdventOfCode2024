#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<algorithm>
#include<optional>
#include<math.h>
#include<unordered_set>
#include<valarray>
#include<stack>
#include<queue>
#include<map>
#include<numeric>
using namespace std;

void check(vector<string>& cs, const auto& m, const auto& v, int i, unordered_set<string>& visited)
{
    if(i >= v.size())
    {
        return;
    }
    auto cc = cs;
    sort(begin(cc), end(cc));
    auto ns = accumulate(begin(cc), end(cc), ""s);
    if(visited.contains(ns))
    {
        return;
    }
    visited.emplace(move(ns));
    const auto& s = v[i];
    bool b = true;
    for(const auto& ss : cs)
    {
        b = b && m.at(ss).contains(s);
        if(!b)
            break;
    }
    if(b)
    {
        cs.emplace_back(s);
        check(cs, m, v, i + 1, visited);
        cs.pop_back();
    }
    check(cs, m, v, i + 1, visited);
}


int main(int argc, const char** argv)
{
    fstream f(argv[1], ios::in | ios::binary);
    unordered_map<string, unordered_set<string>> m;
    string s;
    int cnt = 0;
    while(getline(f, s))
    {
        auto it = find(begin(s), end(s), '-');
        auto ns = string(begin(s), it);
        auto nns = string(next(it), end(s));
        m[ns].emplace(nns);       
        m[nns].emplace(ns); 
    }
    vector<string> acc;
    unordered_set<string> visited;
    for(const auto& [k, v] : m)
    {
        vector<string> cs{k};
        vector<string> vv(begin(v), end(v));
        check(cs, m, vv, 0, visited);
    }
    auto it = max_element(begin(visited), end(visited), [](const auto& a, const auto& b){
        return a.size() < b.size();
    });
    auto ss = *it;
    for(int i = 0; i < it->size(); ++i)
    {
        cout << it->at(i);
        if(i > 0 && ((i & 1) == 1) && i + 1 < it->size())
            cout << ","; 
    }
    cout << endl;
}