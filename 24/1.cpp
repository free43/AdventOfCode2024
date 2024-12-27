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
#include<map>
#include<numeric>
using namespace std;

char solve(const auto& o2i, const auto& i2op, auto& m, const auto& s)
{
    if(m.contains(s))
        return m[s];
    const auto& [a, b] = o2i.at(s);
    const auto& op = i2op.at(make_tuple(a, b, s));
    return m[s] = op(solve(o2i, i2op, m, a), solve(o2i, i2op, m, b));
}

int main(int argc, const char** argv)
{
    fstream f(argv[1], ios::in | ios::binary);
    unordered_map<string, char> m;
    unordered_map<string, pair<string, string>> o2i;
    map<tuple<string, string, string>, function<char(const char, const char)>> i2op;

    struct ops
    {
        pair<string, string> inputs;
        string output;
        function<char(string a, string b)> op;
    };
    auto a = [](const auto a, const auto b){
        return a & b;
    };
    auto o = [](const auto a, const auto b){
        return a | b;
    };
    auto x = [](const auto a, const auto b){
        return a ^ b;
    };
    vector<ops> os;
    
    string s;
    while(getline(f, s))
    {
        if(s.empty() || s.size() == 1)
            break;
        auto it = find(begin(s), end(s), ':');
        auto ns = string(begin(s), it);
        m[ns] = (*next(it, 2)) - '0';
    }
    priority_queue<string, vector<string>, greater<string>> pq;
    while (getline(f,s))
    {
        auto e = [](auto& i, auto s, auto e){
            auto ne = find(s, e, ' ');
            i = string(s, ne);
            return ne;
        };
        string s0, s1, op, oo;
        auto it = e(s0, begin(s), end(s));
        advance(it, 1);
        it = e(op, it, end(s));
        advance(it, 1);
        it = e(s1, it, end(s));
        advance(it, 1);
        it = e(oo, it, end(s));
        advance(it, 1);
        it = e(oo, it, end(s));
        if(find(begin(oo), end(oo), '\r') != end(oo))
            oo.pop_back();
        auto ip = make_pair(s0, s1);
        auto tp = make_tuple(s0, s1, oo);
        o2i[oo] = ip;
        if(op == "AND")
        {
            i2op[tp] = a;
        }
        if(op == "OR")
        {
            i2op[tp] = o;
        }
        if(op == "XOR")
        {
            i2op[tp] = x;
        }
        if(oo[0] == 'z')
        {
            pq.push(oo);
        }
    }
    unsigned long long res = 0;
    int c = 0;
    while(!pq.empty())
    {
        auto t = pq.top();
        pq.pop();
        unsigned long long ii = solve(o2i, i2op, m, t);
        res |= (ii << c);
        c++;
    }
    cout << res << endl;        
}