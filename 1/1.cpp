#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
using namespace std;
int main(int argc, const char** argv)
{
    fstream f(argv[1], ios::in);
    int n0;
    int n1;
    vector<int> n0s;
    vector<int> n1s;
    while(f >> n0 >> n1)
    {
        n0s.emplace_back(n0);
        n1s.emplace_back(n1);
    }
    sort(begin(n0s), end(n0s));
    sort(begin(n1s), end(n1s));
    int d = 0;
    for(int i = 0; i < n0s.size(); ++i)
    {
        d += abs(n0s[i] - n1s[i]);
    }
    cout << d << '\n';
}