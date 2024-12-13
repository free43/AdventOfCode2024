#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<algorithm>
#include<optional>
#include<math.h>
#include<unordered_set>
#include<valarray>
using namespace std;

using pos = valarray<int>;

auto dst(const auto& p0, const auto& p1)
{
    return sqrt(pow(p0 - p1, 2).sum());
}

void set(auto& m, const pos& p, const pos& off)
{
    if(p[0] < 0 || p[1] < 0 || p[0] >= m.size() || p[1] >= m[0].size())
        return;
    m[p[0]][p[1]] = '#';
    set(m, p + off, off);
}

int main(int argc, const char** argv)
{
    fstream f(argv[1], ios::in | ios::binary);
    unordered_map<char, vector<pos>> m;
    vector<string> mp;
    string s;
    int r = 0;
    while(getline(f, s))
    {
        for(int c = 0; c < s.size(); ++c)
        {
            if(s[c] != '.' && s[c] != '\r')
            {
                m[s[c]].push_back(pos({r,c}));
            }
        }
        r++;
        mp.emplace_back(move(s));
    }
    int sum = 0;
    vector<vector<char>> mmp(mp.size(), vector<char>(mp[0].size(), '.'));
    for(auto [k, v] : m)
    {
        //cout << k << ":";
        for(int i = 0; i < v.size(); ++i)
        {
            for(int j = 0; j < v.size(); ++j)
            {
                if(i == j)
                    continue;
                //auto d = dst(v[i], v[j]);
                const pos diff = v[i] - v[j];
                const pos nd = v[i] + diff;
                set(mmp, v[i], diff);
            }
        }
    }
    for(auto s : mmp)
    {
        sum += count(begin(s), end(s), '#');
    }
    cout << sum << endl;
}