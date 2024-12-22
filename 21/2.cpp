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
using namespace std;
const array lu = {'^', '>', 'v', '<'};
using pos = valarray<int>;


pos get_offset(char c)
{
    switch (c)
    {
    case '^':
        return {-1, 0};
        break;
    case '>':
        return {0,1};
    case 'v':
        return {1,0};
    case '<':
        return {0, -1};
    default:
        break;
    }
    return {0,0};
}

void compute_lookup(const auto& m, auto& ll)
{
    for(int i = 0; i < m.size(); ++i)
    {
        for(int j = 0; j < m.front().size(); ++j)
        {
            pos st({i, j});
            if(m[i][j] == ' ')
                continue;
            unordered_map<char, vector<string>> l;
            l[m[st[0]][st[1]]].emplace_back("");
            deque<pos> q;
            q.push_back(st);
            while (!q.empty())
            {
                auto t = q.front();
                char cc = m[t[0]][t[1]];
                q.pop_front();
                for(auto c : lu)
                {
                    pos n = t + get_offset(c); 
                    if(n[0] < 0 || n[1] < 0 || n[0] >= m.size() || n[1] >= m.front().size())
                        continue;
                    auto nc = m[n[0]][n[1]];
                    if(nc == ' ')
                        continue;
                    if(l.contains(nc))
                    {
                        for(auto& s : l[cc])
                        {
                            string ns = s + c;
                            if(ns.size() <= l[nc].front().size())
                            {
                                l[nc].emplace_back(ns);
                            }
                        }
                    }
                    else
                    {
                        if(l.contains(cc))
                        {
                            for(auto& s : l[cc])
                            {
                                if(!l[nc].empty())
                                {
                                    string ns = s +c;
                                    if(ns.size() <= l[nc].front().size())
                                        l[nc].emplace_back(ns);
                                }
                                else
                                    l[nc].emplace_back(s + c);
                            }
                        }
                        q.push_back(n);
                    }
                }
            
            }
            ll[m[st[0]][st[1]]] = l;
        }
    }
}

long long ff(char cp, const auto& num_lu, const auto& dis_lu, int i, const string& seq, auto& dp)
{
    long long sum = 0;
    for(auto g : seq)
    {
        long long mn = numeric_limits<long long>::max();
        if(dp[i].contains(cp) && dp[i][cp].contains(g))
            mn = dp[i][cp][g];
        else
        {
            for(const auto& p : num_lu.at(cp).at(g))
            {
                if(i == 25)
                {
                    mn = min(static_cast<long long>(p.size() + 1), mn);
                }
                else
                {
                    mn = min(ff('A', dis_lu, dis_lu, i + 1, p + 'A', dp), mn);
                }
            }
        }
        dp[i][cp][g] = mn;
        sum += mn;
        cp = g;
    }
    return sum;
}

int main(int argc, const char** argv)
{
    fstream f(argv[1], ios::in | ios::binary);
    string s;
    vector<string> d;
    while(getline(f, s))
    {
        if(find(begin(s), end(s), '\r') != end(s))
            s.pop_back();
        d.emplace_back(move(s));
    }
    array m = { "789"sv,
                "456"sv,
                "123"sv,
                " 0A"sv};

    array mm = {
        " ^A"sv,
        "<v>"sv
    };
    unordered_map<char, unordered_map<char, vector<string>>> num_lu;
    unordered_map<char, unordered_map<char, vector<string>>> dis_lu;

    compute_lookup(m, num_lu);
    compute_lookup(mm, dis_lu);
    
    #if 0
    for(const auto& [k, v] : dis_lu)
    {
        cout << k << "-> ";
        for(const auto& [kk, vv] : v)
        {
            cout << kk << ": ";
            for(const auto& s : vv)
                cout << s << ", ";
            cout << endl;   
        }
    }
    #endif
    long long sum = 0;
    vector<unordered_map<char, unordered_map<char, long long>>> dp(26);
    for(const auto& s : d)
    {   
        long long p = ff('A', num_lu, dis_lu, 0, s, dp);
        long long n = stoi(string(begin(s), prev(end(s))));
        sum += n * p;
    }
    cout << sum << endl;
    
}