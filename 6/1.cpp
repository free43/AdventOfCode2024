#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<algorithm>
#include<optional>
#include<math.h>
#include<unordered_set>
#include<valarray>
using namespace std;

using pos = valarray<int>;
const array<char, 4> l{'^', '>', 'v', '<'};

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

int main(int argc, const char** argv)
{
    fstream f(argv[1], ios::in | ios::binary);
    vector<string> m;
    string s;
    int r = 0, c = -1;
    while(getline(f, s))
    {
        const auto it = find(begin(s), end(s), '^');
        if(it != end(s))
        {
            c = distance(begin(s), it);
        }
        m.emplace_back(move(s));
        r += c == -1;
    }
    const pos st({r, c});
    pos nm = st;
    int mi = 0;
    int sum = 1;
    
    while(true)
    {
        pos nnm = nm + get_offset(l[mi]);
        //cout << nnm[0] << "," << nnm[1] << endl;
        const int nr = nnm[0];
        const int nc = nnm[1];
        if(nr < 0 || nc < 0 || nr >= m.size() || nc >= m[nr].size())
            break;
        if(m[nr][nc] == '#')
        {
            mi = (mi + 1) % l.size();
            continue;
        }
        sum += find(begin(l), end(l), m[nr][nc]) == end(l);
        m[nr][nc] = l[mi];
        nm = nnm;

    }
    //for(auto s : m)
    //    cout << s << endl;
    cout << sum << endl;

    
}