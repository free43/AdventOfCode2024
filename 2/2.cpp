#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<algorithm>
#include<optional>
using namespace std;


auto check(const auto& v, int i)
{
    optional<bool> increase;
    for(int j = i; j < v.size() - 1; ++j)
    {
        int n = v[j + 1];
        if(n == -1)
        {
            if(j + 2 < v.size())
            {
                n = v[j + 2];
            }
            else
                break;
        }
        int c = v[j];
        if(c == -1)
        {
            if(j > 0)
            {
                c = v[j - 1];
            }
            else
                continue;
        }
        int diff = n - c; 
        if(!increase.has_value())
        {
            increase = diff > 0;
        }
        if(!(abs(diff) >= 1 && abs(diff) <= 3 && increase.value() == diff > 0))
            return make_pair(false, increase);
    }
    return make_pair(true, increase);
}
int main(int argc, const char** argv)
{
    fstream f(argv[1], ios::in);
    string s;
    int c = 0;
    vector<vector<int>> vs;
    while(getline(f, s))
    {
        istringstream ss(move(s));
        vs.emplace_back();
        int n;
        while(ss >> n)
        {
            vs.back().emplace_back(n);
        }
    }

    for(auto& v : vs)
    {
        optional<bool> increase;
        bool b = true;
        for(int j = 0; j < v.size() - 1; ++j)
        {
            int diff = v[j + 1] - v[j];
            if(!increase.has_value())
            {
                increase = diff > 0;
            }
            bool b1 = abs(diff) >= 1 && abs(diff) <= 3; 
            bool b2 = increase.has_value() && increase.value() == diff > 0;
            //cout << boolalpha << b1 << " " << b2 << endl;
            if(!b1 || !b2)
            {
                int tmp = v[j];
                v[j] = -1;
                auto [p0, _] = check(v, 0);
                v[j] = tmp;
                tmp = v[j + 1];
                v[j + 1] = -1;
                auto [p1, __] = check(v, 0);
                v[j + 1] = tmp;
                v[0] = -1;
                auto [p2, ___] = check(v, 0);
                b = p0 || p1 || p2;

                //cout << p0 << " " << p1 << endl;             
                break;
            }

            

        }
        cout << endl;
        c += b;
    }
    cout << c << endl;
}