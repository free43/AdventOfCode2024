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
   
    int eid = s.size() / 2;
    int sid = 0;
   
    long long sum = 0;


    for(int ii = 0; ii < s.size(); ii++)
    {
        int k = s[ii] - '0';
        if((ii & 1) == 0) 
        {
            for(int ll = 0; ll < k; ++ll)
                sum += static_cast<long long>( sid * (i++));
            sid++;
        }
        else
        {
            while(k > 0)
            {
                int ls = s[j] - '0';
                for(int ll = 0; ll < min(k, ls); ++ll)
                    sum += static_cast<long long>(eid * (i++));
                k -= ls;
                if(k >= 0)
                {
                    j -= 2;
                    eid--;
                    if(sid > eid)
                        break;
                }
                else
                {
                    s[j] = abs(k) + '0';
                }
            }
        }
        if(sid > eid)
            break;
    }
    
    cout << sum << endl;

}