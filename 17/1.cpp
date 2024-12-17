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
    vector<int> codes;
    array<int, 3> registers{};
    int k = 0;
    while(getline(f, s))
    {
        if(s.empty() || s.size() == 1)
            break;
        auto it = find_if(begin(s), end(s), [](char c){
            return isdigit(c);
        });
        registers[k++] = stoi(string(it, end(s)));
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

    auto get_combos = [&registers](int a){
        if(a >= 0 && a <= 3)
            return a;
        return registers[a - 4];
    };
    int i = 0;
    auto do_opcode = [&](int opcode, int operand){
        switch (opcode)
        {
        case 0:
            registers[0] /= (1 << get_combos(operand));
            break;
        case 1:
            registers[1] ^= operand;
            break;
        case 2:
            registers[1] = get_combos(operand) % 8;
            break;
        case 3:
            if(registers[0] != 0)
                return operand;
            break;
        case 4:
            registers[1] ^= registers[2];
            break;
        case 5:
            cout << get_combos(operand) % 8 << ",";
            break;
        case 6:
            registers[1] = registers[0] / (1 << get_combos(operand));
            break;
        case 7:
            registers[2] = registers[0] / (1 << get_combos(operand));
            break;
        default:
            break;
        }
        return i + 2;
    };

    while(i < codes.size())
    {
        i = do_opcode(codes[i], codes[i + 1]);
    }
    cout << endl;
}