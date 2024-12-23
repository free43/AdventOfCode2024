#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<algorithm>
#include<optional>
#include<math.h>
using namespace std;
int main(int argc, const char** argv)
{
    fstream f(argv[1], ios::in | ios::binary);
    char c;
    long long s = 0LL;
    int i = 0;
    int aa = 0, bb = 0; 
    int cnt = 0;
    auto reset = [&](){
        aa = 0;
        bb = 0;
        cnt = 0;
        i = 0;
    };
    const array<function<bool(char)>, 8> m{
        [](char a){
            return a == 'm';
        },
        [](char a){
            return a == 'u';
        },
        [](char a){
            return a == 'l';
        },
        [](char a){
            return a == '(';
        },
        [&cnt, &aa](char a){
            bool b = isdigit(a) && cnt < 3;
            if(b)
                aa = aa * 10 + static_cast<int>(a - '0');
            return b;
        },
        [](char a){
            return a == ',';
        },
        [&cnt, &bb](char a){
            bool b = isdigit(a) && cnt < 3;
            if(b)
                bb = (bb * 10 + static_cast<int>(a - '0'));
            return b;
        },
        [](char a){
            return a == ')';
        }
    };
    while(f.get(c))
    //while(f >> c)
    {
        bool b = m[i](c);
        //cout << i << endl;
        if(i == 4 || i == 6)
        {
            if(b)
                cnt++;
            else
            {
                b = m[i+1](c); 
                if(b && cnt > 0)
                {
                    cnt = 0;
                    i+=2;
                }
            }
        }
        if(b && i == m.size())
        {
            //cout << aa << " " << bb << endl;
            s += aa * bb;
            b = false;
        }
        if(!b)
        {
            reset();
        }
        if(i != 4 && i != 6)
            i += b;
        
    }
    cout << s << endl;
}