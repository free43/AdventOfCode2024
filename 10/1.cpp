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


int cnt(const pos& p, auto& m,const int prev_c)
{
    if(p[0] < 0 || p[1] < 0 || p[0] >= m.size() || p[1] >= m.front().size())
        return 0;
    if(m[p[0]][p[1]] != prev_c + 1)
        return 0;
    if(m[p[0]][p[1]] == 9)
    {
        m[p[0]][p[1]] = -1;
        return 1;
    }
    int s = 0;
    for(auto c : lu)
    {
        s += cnt(p + get_offset(c), m, m[p[0]][p[1]]);
    }
    return s;
}



int main(int argc, const char** argv)
{
    fstream f(argv[1], ios::in | ios::binary);
    string s;
    vector<vector<int>> m;
    int r = 0;
    vector<pos> ss;
    while(getline(f, s))
    {
        m.emplace_back();
        for(auto c : s)
            m.back().emplace_back(c - '0');
        auto it = begin(m.back());
        while(it != end(m.back()))
        {
            it = find(it, end(m.back()), 0);
            if(it != end(m.back()))
            {
                int c = distance(begin(m.back()), it);
                ss.push_back(pos({r, c}));
            }
            it = it != end(m.back()) ? next(it) : it;
        }
        r++;
    }
    int sum = 0;
    for(const auto& p : ss)
    {
        auto cm = m;
        sum += cnt(p, cm, -1);
    }
    
    cout << sum << endl;

}