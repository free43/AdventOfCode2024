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

vector<vector<unordered_map<char, int>>> mp;

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

void cnt(int& s, auto& m, const auto& lst_state, const auto& v, auto& visited)
{
    for(const auto& [e, c] : lst_state)
    {
        if(visited[e[0]][e[1]].contains(c))
            continue;
        visited[e[0]][e[1]].emplace(c);
        s+= m[e[0]][e[1]] != 'O';
        m[e[0]][e[1]] = 'O';
        if(!v[e[0]][e[1]].contains(c))
            continue;
        cnt(s, m, v[e[0]][e[1]].at(c), v, visited);
    }
}

bool is_opposite(char a, char b, bool bb = false)
{
    if(a == '>' && b == '<')
        return true;
    if(a == '^' && b == 'v')
        return true;
    if(!bb)
        return is_opposite(b, a, true);
    return false;
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
    mp = vector<vector<unordered_map<char, int>>>(
        m.size(), 
        vector<unordered_map<char, int>>(m.front().size(), {
            {'>', numeric_limits<int>::max()},
            {'<', numeric_limits<int>::max()},
            {'^', numeric_limits<int>::max()},
            {'v', numeric_limits<int>::max()},
        } ));
    mp[st[0]][st[1]]['>'] = 0;
    auto cmp = [](const auto& p0, const auto& p1)
    {
        auto [c0, pp0, dir0] = p0;
        auto [c1, pp1, dir1] = p1;
        return c0 > c1;
    };
    priority_queue<tuple<int, pos, char>, vector<tuple<int, pos, char>>, decltype(cmp)> pq(cmp);
    pq.push(make_tuple(0, st, '>'));
    vector<vector<unordered_map<char, vector<pair<pos, char>> >>> prevs(m.size(), vector<unordered_map<char, vector<pair<pos, char>> >>(m.front().size()));
    int lowest_cost = numeric_limits<int>::max();
    vector<pair<pos, char>> end_states;
    while(!pq.empty())
    {
        auto [cost, t, cdir] = pq.top();
        pq.pop();
        auto current = mp[t[0]][t[1]][cdir];
        if(cost > current)
            continue;        
        if((t == e).min())
        {
            if(cost > lowest_cost)
                break;
            end_states.emplace_back(t, cdir);
            lowest_cost = cost;
        }

        for(auto c : lu)
        {
            if(is_opposite(cdir, c))
                continue;
            pos n = t + get_offset(c);
            if(m[n[0]][n[1]] == '#')
                continue;
            auto ncnt = mp[n[0]][n[1]][c];
            auto nncnt = cost + 1 + 1000 * (c != cdir);
            if(nncnt > ncnt)
                continue;
            if(nncnt < ncnt)
            {
                prevs[n[0]][n[1]][c].clear();
                mp[n[0]][n[1]][c] = nncnt;
            }
            prevs[n[0]][n[1]][c].emplace_back(t, cdir);
            pq.push({nncnt, n, c});  
        }
    }
    int ss = 0;
    vector<vector<unordered_set<char>>> visited(m.size(), vector<unordered_set<char>>(m.front().size()));
    cnt(ss, m, end_states, prevs, visited);
    //auto [turns, i, _] = mp[e[0]][e[1]];
    for(auto s : m)
        cout << s << endl;
    cout << ss << endl;
    cout << lowest_cost << endl;
}