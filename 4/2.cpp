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
    string s;
    string_view l = "MAS";
    string_view rl = "SAM";
    while(f >> s)
    {
        m.emplace_back(move(s));
    }
    int c = 0;
    for(int i = 0; i < m.size(); ++i)
    {
        for(int j = 0; j < m[i].size(); ++j)
        {
            if(m[i][j] == 'A')
            {
                auto dl = [&m](const auto &ll, int i, int j)
                {
                    int c = 0;
                    for(int jj = j, ii = i; jj >= 0 && c < ll.size() && ii < m.size(); --jj, ii++)
                    {
                        if(m[ii][jj] == ll[c])
                        {
                            ++c;
                        }
                        else
                            return false;
                        
                    }
                    return c == ll.size();
                };
                auto dr = [&m](const auto &ll, int i, int j)
                {
                    int c = 0;
                    for(int jj = j, ii = i; jj < m[i].size() && c < ll.size() && ii < m.size(); ++jj, ii++)
                    {
                        if(m[ii][jj] == ll[c])
                        {
                            ++c;
                        }
                        else
                            return false;
                        
                    }
                    return c == ll.size();
                };
                
                bool b1 = i - 1 >= 0 && j - 1 >= 0 && (dr(l, i - 1, j - 1) || dr(rl, i - 1, j - 1));
                bool b2 = i - 1 >= 0 && j + 1 < m[i].size() && (dl(l, i - 1, j + 1) || dl(rl, i - 1, j + 1));
                c += b1 && b2;
            }
        }
    }
    cout << c << endl;
}