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

auto get(const auto& m, auto& q, const pos& cp, char mdir, auto& visited, bool coupled = false)
{
    if(visited[cp[0]][cp[1]] != -1)
        return visited[cp[0]][cp[1]];
    if(m[cp[0]][cp[1]] == '#')
    {
        return 0;
    }
    if(m[cp[0]][cp[1]] == '.')
        return 1;
    if(coupled)
    {
        return visited[cp[0]][cp[1]] = get(m, q, cp + get_offset(mdir), mdir, visited);
    }
    if(m[cp[0]][cp[1]] == '[')
    {
        auto b = get(m, q, cp + pos({0, 1}), mdir, visited, true) && get(m, q, cp + get_offset(mdir), mdir, visited);
        if(b)
        {
            q.push_back(cp);
            q.push_back(cp + pos({0,1}));
        }
        return visited[cp[0]][cp[1]] = b;
    }
    if(m[cp[0]][cp[1]] == ']')
    {
        auto b = get(m, q, cp + pos({0, -1}), mdir, visited, true) && get(m, q, cp + get_offset(mdir), mdir, visited);
        if(b)
        {
            q.push_back(cp);
            q.push_back(cp + pos({0,-1}));
        }
        return visited[cp[0]][cp[1]] = b;
    }
    return 1;
}

void move(auto& m, pos& rp, char mdir)
{
    pos np = rp + get_offset(mdir);
    if(m[np[0]][np[1]] == '#')
        return;
    const auto nchar = m[np[0]][np[1]];
    deque<pos> ps{};
    if(mdir == '<' || mdir == '>')
    {
        ps.push_front(rp);
        while(true)
        {
            if(m[np[0]][np[1]] == '#')
                return;
            if(m[np[0]][np[1]] == '.')
                break;
            if(m[np[0]][np[1]] == '[' || m[np[0]][np[1]] == ']')
            {
                ps.push_front(np);
            }
            np += get_offset(mdir);
        }
    }
    else
    {
        vector<vector<int>> visited(m.size(), vector<int>(m.front().size(), -1));
        if(!get(m, ps, np, mdir, visited))
            return;
        ps.push_back(rp);
    }
    for(const auto& p : ps)
    {
        const pos tmp = p + get_offset(mdir);
        m[tmp[0]][tmp[1]] = m[p[0]][p[1]];
        m[p[0]][p[1]] = '.';
    }

    
    //m[rp[0]][rp[1]] = '.';
    //m[np[0]][np[1]] = '@';
    rp += get_offset(mdir);
}


int main(int argc, const char** argv)
{
    fstream f(argv[1], ios::in | ios::binary);
    string s;
    vector<string> m;
    int r = 0;
    pos st;
    while(getline(f, s))
    {
        if(s.empty() || s.size() == 1)
            break;
        string ns;
        for(auto c : s)
        {
            if(c == '#')
                ns += "##";
            if(c == '.')
                ns += "..";
            if(c == 'O')
                ns += "[]";
            if(c == '@')
            {
                st = pos({r, static_cast<int>(ns.size())});
                ns += "@.";
            }
        }
        m.emplace_back(move(ns));
        r++;
    }
    char c;
    while(f >> c)
    {
        auto it = find(begin(lu), end(lu), c);
        if(it == end(lu))
            continue;           
        move(m, st, c);
        //for(auto s : m)
        //{
        //    cout << s << endl;
        //}
    }
    long long sum = 0;
    for(int i = 0; i < m.size(); ++i)
    {
        for(int j = 0; j < m.front().size(); ++j)
        {
            if(m[i][j] == '[')
            {
                sum += i * 100 + j;
            }
        }
    }
    cout << sum << endl;;
}