#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char* argv[]){
  if (argc < 2) {
       cout << "Error you need to give argument !" << endl;
       return 1;
    }
  ifstream file(argv[1]);

  if (!file.is_open()) {
   cout << "Error to open !!!" << endl; 
   return 1;
  }

  char b;// char 1 byte , int 4 byte 
  string my_str;
  while (file.get(b)) {
          int code =(unsigned char)b; // man ascii 
          
          if (code > 32 && code <= 126) { 
          my_str += b;
          } else { 
           if (my_str.length() >= 8) { 
             cout << my_str << endl;
             my_str.clear();

           }
          } 
           
         
  }
  
  file.close();

  return 0;
  }
