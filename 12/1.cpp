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


void cnt(const pos& p, auto& m, const char searched, int& area, int& delmiter)
{
    if(p[0] < 0 || p[1] < 0 || p[0] >= m.size() || p[1] >= m.front().size())
    {
        delmiter++;
        return;
    }
    if(m[p[0]][p[1]] == tolower(searched))
    {
        return;
    }
    if(m[p[0]][p[1]] != searched)
    {
        delmiter++;
        return;
    }
    m[p[0]][p[1]] = tolower(searched);
    area++;
    for(auto c : lu)
    {
        cnt(p + get_offset(c), m, searched, area, delmiter);
    }
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
    for(int i = 0; i < m.size(); ++i)
    {
        for(int j = 0; j < m.front().size(); ++j)
        {
            int area = 0;
            int delimeter = 0;
            if(islower(m[i][j]))
                continue;
            cnt(pos({i, j}), m, m[i][j], area, delimeter);
            sum += area * delimeter;
        }

    }

    

    cout << sum << endl;

}