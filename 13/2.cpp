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
using pr = valarray<long long>;




int main(int argc, const char** argv)
{
    fstream f(argv[1], ios::in | ios::binary);
    string s;
    vector<array<pr, 3>> d;
    while(getline(f, s))
    {
        d.emplace_back();
        auto emplace_n = [&s](auto& a, int i, const pr& offset){
            auto it = find_if(begin(s), end(s), [](const auto c){
                return isdigit(c);
            });
            auto nit = find_if_not(it, end(s), [](const auto c){
                return isdigit(c);
            });
            const int x = stoi(string(it, nit));
            it = find_if(nit, end(s), [](const auto c){
                return isdigit(c);
            });
            const int y = stoi(string(it, end(s)));
            a[i] = pr({x, y}) + offset;
        };
        emplace_n(d.back(), 0, {0,0});
        getline(f, s);
        emplace_n(d.back(), 1, {0, 0});
        getline(f, s);
        emplace_n(d.back(), 2, {10'000'000'000'000LL, 10'000'000'000'000LL});
        getline(f, s);
    }
    unsigned long long sum = 0;
    for(int i = 0; i < d.size(); ++i)
    {
        const auto& A = d[i][0];
        const auto& B = d[i][1];
        const auto& r = d[i][2];
        
        long long n = A[0] * r[1] - r[0] * A[1]; 
        long long d = A[0] * B[1] - B[0] * A[1];
        long long rem = n % d;
        if(rem != 0)
            continue;
        long long b = n / d;
        n = r[0] - B[0] * b;
        d = A[0];
        rem = n % d;
        if(rem != 0)
            continue;
        long long a = n / d;
        sum += a * 3 + b; 
    }
    cout << sum << endl;

}