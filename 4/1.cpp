#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<algorithm>
#include<optional>
#include<math.h>
using namespace std;
int main(int argc, const char** argv)
{
    fstream f(argv[1], ios::in | ios::binary);
    vector<string> m;
    string_view l = "XMAS";
    string_view rl = "SAMX";
    string s;
    while(f >> s)
    {
        m.emplace_back(move(s));
    }
    int c = 0;
    for(int i = 0; i < m.size(); ++i)
    {
        for(int j = 0; j < m[i].size(); ++j)
        {
            if(m[i][j] == 'X' || m[i][j] == 'S')
            {
                auto set = [&](const auto& v){
                    for(auto [ii, jj] : v)
                        m[ii][jj] = '.';
                };
                auto r = [&](const auto &ll)
                {
                    int ii = 0;
                    vector<pair<int,int>> v;
                    for(int jj = j; jj < m[i].size() && ii < ll.size(); ++jj)
                    {
                        if(m[i][jj] == ll[ii])
                        {
                            ++ii;
                            v.emplace_back(i, jj);
                        }
                        
                    }
                    bool b = ii == ll.size();
                    //if(b)
                    //    set(v);
                    return b;
                };
                auto u = [&](const auto &ll)
                {
                    int ii = 0;
                    vector<pair<int,int>> v;
                    for(int jj = i; jj < m.size() && ii < ll.size(); ++jj)
                    {
                        if(m[jj][j] == ll[ii])
                        {
                            v.emplace_back(jj, j);
                            ++ii;
                        }
                        
                    }
                    bool b = ii == ll.size();
                    //if(b)
                    //    set(v);
                    return b;
                };
                auto dl = [&](const auto &ll)
                {
                    int c = 0;
                    vector<pair<int,int>> v;
                    for(int jj = j, ii = i; jj >= 0 && c < ll.size() && ii < m.size(); --jj, ii++)
                    {
                        if(m[ii][jj] == ll[c])
                        {
                            v.emplace_back(ii, jj);
                            ++c;
                        }
                        
                    }
                    bool b = c == ll.size();
                    //if(b)
                    //    set(v);
                    return b;
                };
                auto dr = [&](const auto &ll)
                {
                    int c = 0;
                    vector<pair<int,int>> v;
                    for(int jj = j, ii = i; jj < m[i].size() && c < ll.size() && ii < m.size(); ++jj, ii++)
                    {
                        if(m[ii][jj] == ll[c])
                        {
                            v.emplace_back(ii, jj);
                            ++c;
                        }
                        
                    }
                    bool b = c == ll.size();
                    //if(b)
                    //    set(v);
                    return b;
                };
                if(m[i][j] == 'X')
                {
                    c += r(l) + u(l) + dl(l) + dr(l);
                }
                if(m[i][j] == 'S')
                {
                    c += r(rl) + u(rl) + dl(rl) + dr(rl);
                }
                cout << i << "," << j << " " << c << endl;
            }
        }
    }
    cout << c << endl;
}