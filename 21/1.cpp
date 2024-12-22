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

void ff(char cp, const auto& lu, int i, const string& seq, string acc, vector<string>& sols)
{
    if(i >= seq.size())
    {
        sols.emplace_back(move(acc));
        return;
    }
    
    char g = seq[i];
    for(const auto& p : lu.at(cp).at(g))
    {
        ff(g, lu, i + 1, seq, acc + p + 'A', sols);
    }
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
    array<string_view, 4> m = {"789",
                               "456",
                               "123",
                               " 0A"};

    array<string_view, 2> mm = {
        " ^A",
        "<v>"
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
    auto ft = [](const auto& v){
        vector<string> r;
        auto it = min_element(begin(v), end(v), [](const auto& s0, const auto& s1){
            return s0.size() < s1.size();
        });
        copy_if(begin(v), end(v), back_inserter(r), [&](const auto& s){
            return s.size() == it->size();
        });
        return r;
    };
    int sum = 0;
    for(const auto& s : d)
    {
        vector<string> sols, sols2;
        ff('A', num_lu, 0, s, "", sols);
        sols = ft(sols);
        for(const auto& s : sols)
        {
            ff('A', dis_lu, 0, s, "", sols2);
            sols2 = ft(sols2);
        }
        sols.clear();
        for(const auto& s : sols2)
        {
            ff('A', dis_lu, 0, s, "", sols);
            sols = ft(sols);
        }
        
        int n = stoi(string(begin(s), prev(end(s))));
        int p = sols.front().size();
        sum += n * p;
    }
    cout << sum << endl;
    
}