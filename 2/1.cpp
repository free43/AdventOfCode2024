#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<algorithm>
#include<optional>
using namespace std;
int main(int argc, const char** argv)
{
    fstream f(argv[1], ios::in);
    string s;
    int c = 0;
    while(getline(f, s))
    {
        //cout << s << ":";
        istringstream ss(move(s));
        int pn = -1;
        int n = 0;
        bool b = true;
        optional<bool> increase;
        while(ss >> n)
        {
            if(pn != -1)
            {
                if(!increase.has_value())
                {
                    increase = n > pn;
                }
                const int diff = abs(n - pn);
                b = b && diff >= 1 && diff <= 3 && (increase.value() && n > pn || !increase.value() && n < pn);
                //cout << n <<" " << pn << " " << diff << endl;
                if(!b)
                    break;
            }
            pn = n;
        }
        c += b;
    }
    cout << c << endl;
}