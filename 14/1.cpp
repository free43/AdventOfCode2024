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
    while(getline(f, s))
    {
        d.emplace_back();
        auto emplace_n = [&s](auto& a, int i){
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
            s = string(nit, end(s));
        };
        emplace_n(d.back(), 0);
        emplace_n(d.back(), 1);
    }

    const int width = 101;
    const int height = 103;

    for(int i = 0; i < 100; ++i)
    {
        for(auto& a : d)
        {
            auto& p = a[0];
            const auto& v = a[1];
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
        }
    }
    const pr first_quad_low = pr({0, 0});
    const pr first_quad_high = pr({width / 2, height / 2});
    const pr second_quad_low = pr({width / 2 + 1, 0});
    const pr second_quad_high = pr({width, height / 2});
    const pr third_quad_low = pr({0, height / 2 + 1});
    const pr third_quad_high = pr({width / 2, height});
    const pr fourth_quad_low = pr({width / 2 + 1, height / 2 + 1});
    const pr fourth_quad_high = pr({width, height});

    const array checks = {
        make_pair(first_quad_low, first_quad_high),
        make_pair(second_quad_low, second_quad_high),
        make_pair(third_quad_low, third_quad_high),
        make_pair(fourth_quad_low, fourth_quad_high),
    };

    int prod = 1;;
    for(const auto& [l, h] : checks)
    {
        int sum = 0;
        for(const auto& a : d)
        {
            const auto& p = a[0];
            if((p >= l).min() && (p < h).min())
                sum++;
        }
        prod *= sum;
    }
    cout << prod << endl;

}