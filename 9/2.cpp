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

int main(int argc, const char** argv)
{
    fstream f(argv[1], ios::in | ios::binary);
    string s;
    getline(f, s);
    int j = s.size() - 1;
    int i = 0;
   
    int sid = 0;
   
    long long sum = 0;
    vector<vector<int>> lu(s.size());
    for(int ii = 0; ii < s.size(); ii++)
    {
        int k = s[ii] - '0';
        lu[ii].emplace_back(k);
        if((ii & 1) == 0) 
        {
            lu[ii].emplace_back(ii / 2);
        }
        else
        {
        }
    }

    for(int j = lu.size() - 1; j >= 0; j -= 2)
    {
        int sp = lu[j][0];
        int id = lu[j][1];
        for(int i = 1; i < j; i += 2)
        {
            if(lu[i][0] >= sp)
            {
                lu[i].emplace_back(id);
                lu[i].emplace_back(sp);
                lu[i][0] -= sp;

                lu[j][1] = 0;
                break; 
            }
        }
    }

    for(const auto& v : lu)
    {
        if(v.size() == 1)
        {
            sid += v.front();
        }
        else if(v.size() == 2)
        {
            int sp = v.front();
            int id = v.back();
            for(int k = 0; k < sp; ++k)
                sum += static_cast<long long>(id * sid++);
        }
        else
        {
            for(int i = 1; i < v.size(); i += 2)
            {
                int sp = v[i + 1];
                int id = v[i];
                for(int k = 0; k < sp; ++k)
                    sum += static_cast<long long>(id * sid++);
            }
            sid += v[0];
        }
    }
    
    cout << sum << endl;

}