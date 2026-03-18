#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
       cout << "Error you need to give argument !" << endl;
       return 1;
    }
    ifstream file(argv[1], ios::binary);

    if (!file.is_open()) {
      cout << "Error to open !!!" << endl; 
      return 1;
    }

    vector<int> v;
    char b;
    int offset = 0; 

    while (file.get(b)) {
        v.push_back((unsigned char)b);
        if (v.size() == 16) {
            // cout << v << endl; -> sort une big error
            cout << hex << setw(8) << setfill('0') <<  offset << " | ";
            offset += 16;
            for (int b_val : v)
            { 
              cout << hex << setw(2) << setfill('0') << b_val << " ";
            }
            cout << "|" << b;
            for (int b_val : v)
            { 
              if (b_val > 32 && b_val <= 126) {
                cout << (char)b_val;
              }
              else { cout << "."; }

        }
        cout << endl;
        v.clear();
        }
    }
    return 0;
}
