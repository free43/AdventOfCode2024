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
using pr = valarray<int>;


int cnt(int a, int b, const pr& A, const pr& B, const pr& current, auto& lu)
{
    if((current < 0).min() || a >= 100 || b >= 100)
        return numeric_limits<int>::max();
    valarray<bool> bb = current == 0;
    if(bb[0] && bb[1])
        return a * 3 + b * 1;
    if(lu[a][b] != -1)
    {
        return lu[a][b];
    }
    return lu[a][b] = min(cnt(a + 1, b, A, B, current - A, lu), cnt(a, b + 1, A, B, current - B, lu));
    
}



int main(int argc, const char** argv)
{
    fstream f(argv[1], ios::in | ios::binary);
    string s;
    vector<array<pr, 3>> d;
    while(getline(f, s))
    {
        d.emplace_back();
        auto emplace_n = [&s](auto& a, int i){
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
            a[i] = pr({x, y});
        };
        emplace_n(d.back(), 0);
        getline(f, s);
        emplace_n(d.back(), 1);
        getline(f, s);
        emplace_n(d.back(), 2);
        getline(f, s);
    }
    int sum = 0;
    for(int i = 0; i < d.size(); ++i)
    {
        vector<vector<int>> lu(100, vector<int>(100, -1));
        int l = cnt(0, 0, d[i][0], d[i][1], d[i][2], lu);
        if(l != numeric_limits<int>::max())
            sum += l;
    }
    cout << sum << endl;

}