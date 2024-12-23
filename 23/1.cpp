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

int main(int argc, const char** argv)
{
    fstream f(argv[1], ios::in | ios::binary);
    unordered_map<string, unordered_set<string>> m;
    string s;
    int cnt = 0;
    unordered_set<string> cs;
    while(getline(f, s))
    {
        auto it = find(begin(s), end(s), '-');
        auto ns = string(begin(s), it);
        auto nns = string(next(it), end(s));
        m[ns].emplace(nns);       
        m[nns].emplace(ns);
        const bool swt = ns.front() == 't' || nns.front() == 't';
        for(const auto& s : m[ns])
        {
            if(m[nns].contains(s))
            {
                if(swt || s.front() == 't')
                {
                    array a{
                        ns, 
                        nns, 
                        s
                    };
                    sort(begin(a), end(a));
                    auto r = accumulate(begin(a), end(a), ""s);
                    if(!cs.contains(r))
                        cs.emplace(move(r));
                }
            }
        }
    }
    
    cout << cs.size() << endl;
    
}