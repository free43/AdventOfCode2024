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

bool foo(int i, const auto& code, const long long current)
{
    if(i < 0) 
    {
        cout << current << endl;
        return true;
    }
    for(long long ii = 0; ii <= 7; ++ii)
    {
        const auto n = (current << 3) | ii;
        const long long a = ((((n & 7) ^ 5) ^ (n >> ((n & 7)^ 5))) ^ 6) & 7;
        if(code[i] == a)
        {
            if(foo(i - 1, code, n))
                return true;
        }
    }
    return false;
}

int main(int argc, const char** argv)
{
    fstream f(argv[1], ios::in | ios::binary);
    string s;
    vector<int> codes;
    array<long long, 3> registers{};
    int k = 0;
    while(getline(f, s))
    {
        if(s.empty() || s.size() == 1)
            break;
        auto it = find_if(begin(s), end(s), [](char c){
            return isdigit(c);
        });
        registers[k++] = stoll(string(it, end(s)));
    }
    getline(f, s);
    auto it = begin(s);
    do{
        it = find_if(it, end(s), [](char c){
            return isdigit(c);
        });
        auto nit = find_if_not(it, end(s), [](char c){
            return isdigit(c);
        });
        codes.emplace_back(stoi(string(it, nit)));
        it = nit;
    }while(it != end(s));

    foo(codes.size()- 1, codes, 0LL);
    
}