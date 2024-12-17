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

vector<vector<pair<int, char>>> mp;

int score(auto& m, const pos& st, const pos& e, const char dir, int s)
{
    if(m[st[0]][st[1]] == '#')
        return numeric_limits<int>::max();
    if((st == e).min())
        return s;
    int mn = numeric_limits<int>::max();
    for(auto c : lu)
    {
        const pos& np = st + get_offset(c);
        char tmp = m[st[0]][st[1]];
        m[st[0]][st[1]] = '#';
        mn = min(mn, score(m, np, e, c, s + 1 + (c != dir) * 1000));
        m[st[0]][st[1]] = tmp;
    }
    return mn;
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
        auto it = find(begin(s), end(s), 'S');
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
        r++;
        m.emplace_back(move(s));
    }
    mp = vector<vector<pair<int, char>>>(m.size(), vector<pair<int, char>>(m.front().size(), make_pair(numeric_limits<int>::max(), '-')));
    mp[st[0]][st[1]] = make_pair(0, '>');
    auto cmp = [](const auto& p0, const auto& p1)
    {
        return mp[p0[0]][p0[1]].first > mp[p1[0]][p1[1]].first;
    };
    priority_queue<pos, vector<pos>, decltype(cmp)> pq(cmp);
    vector<vector<bool>> visited(m.size(), vector<bool>(m.front().size(), false));
    pq.push(st);

    while(!pq.empty())
    {
        auto t = pq.top();
        pq.pop();
        if((t == e).min())
            break;
        if(visited[t[0]][t[1]])
            continue;
        visited[t[0]][t[1]] = true;
        auto [current_dst, current_dir] = mp[t[0]][t[1]];
        for(auto c : lu)
        {
            pos n = t + get_offset(c);
            if(m[n[0]][n[1]] == '#')
                continue;
            if(visited[n[0]][n[1]])
                continue;
            auto ndst = mp[n[0]][n[1]].first;
            auto nndst = current_dst + 1 + 1000 * (current_dir != c);
            if(ndst > nndst)
            {
                mp[n[0]][n[1]] = make_pair(nndst, c);
            }
            pq.push(n);  
        }
    }
    cout << mp[e[0]][e[1]].first << endl;
}