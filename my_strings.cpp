#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]){
  if (argc < 2) {
       cout << "Error you need to give argument !" << endl;
    }
  ifstream file(argv[1]);

  if (!file.is_open()) {
    cout << "Error to open :" << argv[1] << "!!!" << endl; 
  }

  string line;

  while (getline(file, line)) {
   cout << line << "\n";
  }
  file.close();

  return 0;
  }
