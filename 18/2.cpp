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
const array lu = {'^', '>', 'v', '<'};
using pos = valarray<int>;


pos get_offset(char c)
{
    switch (c)
    {
    case '^':
        return {-1, 0};
        break;
    case '>':
        return {0,1};
    case 'v':
        return {1,0};
    case '<':
        return {0, -1};
    default:
        break;
    }
    return {0,0};
}

int main(int argc, const char** argv)
{
    fstream f(argv[1], ios::in | ios::binary);
    string s;
    vector<string> m(71, string(71, '.'));
    vector<pos> nps;
    int r = 0;
    pos st;
    const pos e({static_cast<int>(m.size()) - 1, static_cast<int>(m.size()) - 1});
    while(getline(f, s))
    {
        int a,b;
        char c;
        istringstream ss(move(s));
        ss >> a >> c >> b;
        if(r < 1024)
        {
            m[b][a] = '#';
        }
        else
        {
            nps.emplace_back(pos({b,a}));
        }
        r++;
    }
    
    auto cmp = [](const auto& p0, const auto& p1)
    {
        return p0.first > p1.first;
    };
    r = 0;
    while(r < nps.size())
    {
        vector<vector<bool>> visited(m.size(), vector<bool>(m.front().size(), false));
        priority_queue<pair<int,pos>, vector<pair<int,pos>>, decltype(cmp)> pq(cmp);
        pq.push(make_pair(0, pos({0,0})));
        bool reachable = false;
        const auto nnp = nps[r];
        m[nnp[0]][nnp[1]] = '#';
        while(!pq.empty())
        {
            auto [cost, t] = pq.top();
            pq.pop();
            if((t == e).min())
            {
                reachable = true;
                break;
            }
            if(visited[t[0]][t[1]])
                continue;
            visited[t[0]][t[1]] = true;
            for(auto c : lu)
            {
                pos n = t + get_offset(c);
                if(n[0] < 0 || n[1] < 0 || n[0] >= m.size() || n[1] >= m.front().size())
                    continue;
                if(m[n[0]][n[1]] == '#')
                    continue;
                auto nc = cost + 1;
                pq.push(make_pair(nc,n));  
            }
        }
        //m[nnp[0]][nnp[1]] = '.';
        if(!reachable)
        {
            cout << nnp[1] << "," << nnp[0] << endl;
            break;
        }
        cout << r << endl;
        r++;
    }

}