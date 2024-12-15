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

void move(auto& m, pos& rp, char mdir)
{
    const pos np = rp + get_offset(mdir);
    if(m[np[0]][np[1]] == '#')
        return;
    if(m[np[0]][np[1]] == 'O')
    {
        pos tmp = np;
        while (true)
        {
            tmp += get_offset(mdir);
            const auto c = m[tmp[0]][tmp[1]];
            if(c == '#')
            {
                return;
            }
            if(c == '.')
            {
                m[tmp[0]][tmp[1]] = 'O';
                break;
            }
        }
    }
    m[rp[0]][rp[1]] = '.';
    m[np[0]][np[1]] = '@';
    rp = np;
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
        const auto it = find(begin(s), end(s), '@');
        if(it != end(s))
        {
            int c = distance(begin(s), it);
            st = pos({r, c});
        }
        r++;
        m.emplace_back(move(s));
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
            if(m[i][j] == 'O')
            {
                sum += i * 100 + j;
            }
        }
    }
    cout << sum << endl;;
}