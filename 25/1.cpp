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

using cs = valarray<int>;

int main(int argc, const char** argv)
{
    fstream f(argv[1], ios::in | ios::binary);

    vector<cs> k;
    vector<cs> l;
    
    
    string s;
    bool n = true;
    vector<string> v;
    const int height = 7;
    while(true)
    {
        bool b = static_cast<bool>(getline(f,s));
        if(s.empty() || s.size() == 1 || !b)
        {
            
            vector<int> vv(v.front().size(), 0);
            bool isk = true;
            for(int j = 0; j < v.size(); ++j)
            {
                const auto& s = v[j]; 
                for(int i = 0; i < s.size(); ++i)
                {
                    if(j == 0)
                    {
                        isk = isk && s[i] == '.';
                    }
                    vv[i] += s[i] == '#';
                }
            }
            auto add = [](auto& m, const auto& v){
                m.push_back(cs({v[0], v[1], v[2], v[3], v[4]}));
            };
            if(isk)
            {
                add(k, vv);
            }
            else
            {
                add(l, vv);
            }
            v.clear();
            if(!b)
                break;
            continue;   
        }
        if(find(begin(s), end(s), '\r') != end(s))
            s.pop_back();
        v.emplace_back(move(s));
        
            
    }
    int sum = 0;
    for(const auto& v0 : k)
    {   
        for(const auto& v1 : l)
        {
            sum += ((v0 + v1) <= height).min();
        }
    }
    cout << sum << endl;

}