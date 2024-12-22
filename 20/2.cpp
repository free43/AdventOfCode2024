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
#include<set>
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

int solve(const pos& s, auto& m, auto& path, auto& dp)
{
    if(s[0] < 0 || s[1] < 0 || s[0] >= m.size() || s[1] >= m.front().size())
        return numeric_limits<int>::max();
    if(m[s[0]][s[1]] == 'X')
        return numeric_limits<int>::max();
    if(m[s[0]][s[1]] == '#')
        return numeric_limits<int>::max();
    path.emplace_back(s);
    if(m[s[0]][s[1]] == 'E')
    {
        return dp[s[0]][s[1]] = 0;
    }
    int mn = numeric_limits<int>::max();
    char tmp = m[s[0]][s[1]];
    m[s[0]][s[1]] = 'X';
    for(auto c : lu)
    {
        int r = solve(s + get_offset(c), m, path, dp);
        if(r == numeric_limits<int>::max())
            continue;
        mn = min(r + 1, mn);
    }
    m[s[0]][s[1]] = tmp;
    return dp[s[0]][s[1]] = mn;
}


int main(int argc, const char** argv)
{
    fstream f(argv[1], ios::in | ios::binary);
    string s;
    vector<string> m;
    int r = 0;
    pos st;
    pos e;
    while(getline(f, s))
    {
        auto it  = find(begin(s), end(s), 'S');
        if(it != end(s))
        {
            int c = distance(begin(s), it);
            st = pos({r, c});
        }
        it = find(begin(s), end(s), 'E');
        if(it != end(s))
        {
            int c = distance(begin(s), it);
            e = pos({r, c});
        }
        if(find(begin(s), end(s), '\r') != end(s))
            s.pop_back();
        m.emplace_back(move(s));
        r++;
    }
    vector<vector<int>> dp(m.size(), vector<int>(m.front().size(), -1));
    vector<pos> path;
    const int sv = solve(st, m, path, dp);
    int cnt = 0;
    for(int i = 0; i < path.size(); ++i)
    {
        const pos& c = path[i];
        vector<vector<bool>> visited(m.size(), vector<bool>(m.front().size(), false));
        for(int r = 2; r <= 20; ++r)
        {
            for(int dr = 0; dr <= r; ++dr)
            {
                int dc = r - dr; 
                int acc = dr + dc;
                pos offset = pos({dr, dc});
                for(auto fak : {pos({1,1}), pos({-1, 1}), pos({1, -1}), pos({-1, -1})})
                {
                    pos np = c + fak * offset;
                    if(np[0] < 0 || np[1] < 0 || np[0] >= m.size() || np[1] >= m.front().size())
                        continue;
                    if(m[np[0]][np[1]] == '#')
                        continue;
                    if(visited[np[0]][np[1]]) 
                        continue;
                    visited[np[0]][np[1]] = true;
                    int dtg = dp[np[0]][np[1]];
                    cnt += sv - (dtg + acc + i) >= 100;
                }
            }
        }
    }
    cout << cnt << endl;
    return 0;
}