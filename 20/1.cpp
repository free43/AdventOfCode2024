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


void cheat(auto& m, const pos& s, int& cnt, const auto& dp, int cheatcnt, int acc, int sd)
{
    if(cheatcnt > 2)
        return;
    if(s[0] < 0 || s[1] < 0 || s[0] >= m.size() || s[1] >= m.front().size())
        return;
    if(m[s[0]][s[1]] == 'X')
        return; 
    if(cheatcnt > 2 && m[s[0]][s[1]] == '#')
        return;
    if(dp[s[0]][s[1]] != -1)
    {
        cnt += sd - (acc + dp[s[0]][s[1]] + cheatcnt) >= 100;
    }
    char tmp = m[s[0]][s[1]];
    m[s[0]][s[1]] = 'X';
    for(auto c : lu)
    {
        cheat(m, s + get_offset(c), cnt, dp, cheatcnt + 1, acc, sd);
    }
    m[s[0]][s[1]] = tmp;

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
    int sv = solve(st, m, path, dp);
    int cnt = 0;
    for(int i = 0; i < path.size(); ++i)
    {
        pos c = path[i];
        cheat(m, c, cnt, dp, 0, i, sv);
        m[c[0]][c[1]] = 'X';
    }
    cout << cnt << endl;
    return 0;
}