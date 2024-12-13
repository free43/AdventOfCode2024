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
#include<list>
using namespace std;




int main(int argc, const char** argv)
{
    fstream f(argv[1], ios::in | ios::binary);
    string s;
    list<long long> ll;
    while(getline(f, s))
    {
        long long l;
        stringstream ss(move(s));
        while(ss >> l)
        {
            ll.emplace_back(l);
        }
    }
    for(int i = 0; i < 25; ++i)
    {
        list<long long> nl;
        while(!ll.empty())
        {
            auto v = ll.front();
            auto s = to_string(v);
            if(v == 0)
            {
                nl.emplace_back(1);
            }
            else if((s.size() & 1)== 0)
            {
                string fh(begin(s), next(begin(s), s.size() / 2));
                nl.emplace_back(stoll(fh));
                string sh(next(begin(s), s.size() / 2), end(s));
                nl.emplace_back(stoll(sh));
            }
            else
            {
                nl.emplace_back(v * 2024);
            }
            ll.pop_front();
        }
        ll = move(nl);
    }
    
    cout << ll.size() << endl;

}