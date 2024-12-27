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
    const auto& [op, ops] = i2op.at(make_tuple(a, b, s));
    char ret = m[s] = op(solve(o2i, i2op, m, a), solve(o2i, i2op, m, b));
    cout << "(" << a << " " <<  ops << " " << b << ") -> " << s << endl;
    return ret;
}

int main(int argc, const char** argv)
{
    fstream f(argv[1], ios::in | ios::binary);
    unordered_map<string, char> m;
    unordered_map<string, pair<string, string>> o2i;
    map<tuple<string, string, string>, pair<function<char(const char, const char)>, string>> i2op;

    auto a = [](const auto a, const auto b){
        return a & b;
    };
    auto o = [](const auto a, const auto b){
        return a | b;
    };
    auto x = [](const auto a, const auto b){
        return a ^ b;
    };
    
    string s;
    unsigned long long x0 = 0;
    unsigned long long y0 = 0;
    int ix = 0, iy = 0;
    while(getline(f, s))
    {
        if(s.empty() || s.size() == 1)
            break;
        auto it = find(begin(s), end(s), ':');
        auto ns = string(begin(s), it);
        m[ns] = (*next(it, 2)) - '0';
        if(ns.front() == 'x')
        {
            x0 |= static_cast<unsigned long long>(m[ns]) << ix;
            ix++;
        }
        if(ns.front() == 'y')
        {
            y0 |= static_cast<unsigned long long>(m[ns]) << iy;
            iy++;
        }
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
            i2op[tp] = {a, op};
        }
        if(op == "OR")
        {
            i2op[tp] = {o, op};
        }
        if(op == "XOR")
        {
            i2op[tp] = {x, op};
        }
        if(oo[0] == 'z')
        {
            pq.push(oo);
        }
    }
    //swap(o2i["gmt"], o2i["z07"]);
    unsigned long long res = x0 + y0;
    unsigned long long res2 = 0;
    int c = 0;

    while(!pq.empty())
    {
        auto t = pq.top();
        pq.pop();
        char expected = res & 1;
        char ii = solve(o2i, i2op, m, t);
        if(expected != ii)
            break;
        res >>= 1;
        res2 |= static_cast<unsigned long long>(ii) << c;
        cout << endl;
        c++;
    }
    cout << boolalpha << (res2 ==(x0+y0))   << endl;  

    array ss ={
        "z07"sv,
        "gmt"sv,
        "qjj"sv,
        "cbj"sv,
        "dmn"sv,
        "z18"sv,
        "cfk"sv,
        "z35"sv
    };
    sort(begin(ss), end(ss));
    for(auto s : ss)
        cout << s << ",";       
}