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
const array lu = {'l', 'r', 'u', 'd'};
using pos = valarray<int>;


pos get_offset(char c)
{
    switch (c)
    {
    case 'u':
        return {-1, 0};
        break;
    case 'r':
        return {0,1};
    case 'd':
        return {1,0};
    case 'l':
        return {0, -1};
    default:
        break;
    }
    return {0,0};
}

void set(char dir, char cdir, char cchar, auto& m, auto& check, const pos& p)
{
    if(p[0] < 0 || p[1] < 0 || p[0] >= m.size() || p[1] >= m.front().size())
        return;
    if(tolower(m[p[0]][p[1]]) != cchar)
        return;
    if(check[p[0]][p[1]].contains(cdir))
        return;
    pos cp = p + get_offset(cdir);
    if(cp[0] < 0 || cp[1] < 0 || cp[0] >= m.size() || cp[1] >= m.front().size() || tolower(m[cp[0]][cp[1]]) != cchar)
    {
        check[p[0]][p[1]].emplace(cdir);
        set(dir, cdir, cchar, m, check, p + get_offset(dir));
    }
}

bool cnt(const pos& p, auto& m, const char searched, int& area, auto& check, int& sides)
{
    if(p[0] < 0 || p[1] < 0 || p[0] >= m.size() || p[1] >= m.front().size())
    {
        return true;
    }
    if(m[p[0]][p[1]] == tolower(searched))
    {
        return false;
    }
    if(m[p[0]][p[1]] != searched)
    {
        return true;
    }
    m[p[0]][p[1]] = tolower(searched);
    area++;
    for(auto c : lu)
    {
        if(cnt(p + get_offset(c), m, searched, area, check, sides))
        {
            if(!check[p[0]][p[1]].contains(c))
            {
                sides++;
                if(c == 'u' || c== 'd')
                {
                    set('l', c, m[p[0]][p[1]], m, check, p + get_offset('l'));
                    set('r', c, m[p[0]][p[1]], m, check, p + get_offset('r'));
                }
                if(c == 'l' || c == 'r')
                {
                    set('u', c, m[p[0]][p[1]], m, check, p + get_offset('u'));
                    set('d', c, m[p[0]][p[1]], m, check, p + get_offset('d'));
                }
                check[p[0]][p[1]].emplace(c);
            }
        }
    }
    return false;
}


int main(int argc, const char** argv)
{
    fstream f(argv[1], ios::in | ios::binary);
    string s;
    vector<string> m;
    while(getline(f, s))
    {
        m.emplace_back(move(s));
    }
    long long sum = 0;
    vector<vector<unordered_set<char>>> ll(m.size(), vector<unordered_set<char>>(m.front().size()));
    for(int i = 0; i < m.size(); ++i)
    {
        for(int j = 0; j < m.front().size(); ++j)
        {
            int area = 0;
            int sides = 0;
            if(islower(m[i][j]))
                continue;
            cnt(pos({i, j}), m, m[i][j], area, ll, sides);
            sum += area * sides;
        }
    }
    
    cout << sum << endl;

}