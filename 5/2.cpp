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
        bool bb = false;
        for(auto i : s)
        {
            bool b = true;
            for(int ii = 0; ii < v.size(); ++ii)
            {
                if(m[v[ii]].count(i) == 0 && b)
                {
                    bb = true;
                    b = false;
                    v.insert(next(begin(v), ii), i);
                    ii++;
                }
            }
            if(b)
                v.emplace_back(i);
            //for(auto vv : v)
            //    cout << vv << ",";
            //cout << endl;
        }
        sum += bb * v[v.size() / 2];
    } 
    
    cout << sum << endl;
}