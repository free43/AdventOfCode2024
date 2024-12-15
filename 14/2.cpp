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
#include<numeric>
using namespace std;
using pr = valarray<int>;

int main(int argc, const char** argv)
{
    fstream f(argv[1], ios::in | ios::binary);
    string s;
    vector<array<pr, 2>> d;
    vector<vector<char>> m(101, vector<char>(103, ' '));
    while(getline(f, s))
    {
        d.emplace_back();
        auto emplace_n = [&s, &m](auto& a, int i){
            auto it = find_if(begin(s), end(s), [](const auto c){
                return isdigit(c) || c == '-';
            });
            auto nit = find_if_not(it, end(s), [](const auto c){
                return isdigit(c) || c == '-';
            });
            const int x = stoi(string(it, nit));
            it = find_if(nit, end(s), [](const auto c){
                return isdigit(c) || c == '-';
            });
            nit = find_if_not(it, end(s), [](const auto c){
                return isdigit(c) || c == '-';
            });
            const int y = stoi(string(it, nit));
            a[i] = pr({x, y});
            if(i == 0)
                m[x][y] = '#';
            s = string(nit, end(s));
        };
        emplace_n(d.back(), 0);
        emplace_n(d.back(), 1);
    }

    const int width = 101;
    const int height = 103;

    for(int i = 0; i < 10'000; ++i)
    {
        for(auto& a : d)
        {
            auto& p = a[0];
            const auto& v = a[1];
            m[p[0]][p[1]] = ' ';
            p += v;
            if(p[0] >= width)
            {
                p[0] %= (width);
            }
            if(p[0] < 0)
            {
                p[0] = width + p[0];
            }
            if(p[1] >= height)
            {
                p[1] %= height;
            }
            if(p[1] < 0)
            {
                p[1] = height + p[1];
            }
            m[p[0]][p[1]] = '#';
        }
        for(const auto& vv : m)
        {
            for(const auto c : vv)
                cout << c;
            cout << endl;
        }
        cout << endl;
        cout << i << endl;
        //getchar();
    }
    

}