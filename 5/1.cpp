#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<algorithm>
#include<optional>
#include<math.h>
#include<unordered_set>
using namespace std;
int main(int argc, const char** argv)
{
    fstream f(argv[1], ios::in | ios::binary);
    unordered_map<int, unordered_set<int>> m;
    string s;
    while(getline(f, s))
    {
        cout << s.size() << endl;
        if(s.size() == 1 || s.empty())
            break;
        int p = 0;
        auto it = find(begin(s), end(s), '|');;
        auto k = stoi(string(begin(s), it));
        auto v = stoi(string(next(it), end(s)));
        m[k].emplace(v);
    }
    vector<vector<int>> seq;
    while(getline(f, s))
    {
        istringstream ss(move(s));
        int i;
        seq.emplace_back();
        while(ss >> i)
        {
            seq.back().emplace_back(i);
            char c;
            ss >> c;
        }
    }
    
    int sum = 0;
    for(auto& s : seq)
    {
        vector<int> v;
        bool b = true;
        for(auto& i : s)
        {
            for(auto& ii : v)
            {
                b = b && m[ii].count(i) > 0;
                if(!b)
                    break;
            }
            v.emplace_back(i);

        }
        sum += b * v[v.size() / 2];
    } 
    
    cout << sum << endl;
}