#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;
int main(int argc, const char** argv)
{
    fstream f(argv[1], ios::in);
    int n0;
    int n1;
    vector<int> n1s;
    unordered_map<int, int> m;
    unordered_map<int, int> m1;
    while(f >> n0 >> n1)
    {
        m[n0] = 0;
        m1[n0]++;
        n1s.emplace_back(n1);
    }
    
    for(auto v : n1s)
    {
        if(m.contains(v))
            m[v]++;
    }
    int d = 0;
    for(auto [k, v] : m)
    {
        d += m1[k] * k*v;
    }
    cout << d << '\n';
}