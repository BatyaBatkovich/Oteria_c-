#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <map>
#include <cctype>

using namespace std;

// https://stackoverflow.com/questions/3418231/replace-part-of-a-string-with-another-string
void replaceAll(std::string& str, const std::string& from, const std::string& to) {
    if(from.empty())
        return;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}

int main(int argc, char* argv[]){
  if (argc < 2) {
       cout << "Error you need to give argument !" << endl;
       return 1;
    }
   if (argc < 3) {
       cout << "Error you need to give more argument !" << endl;
       return 1;
    }
  ifstream file(argv[1]);
  string line;
  // https://habr.com/ru/companies/otus/articles/532056/
  // vector<string> buffer;
  const regex r(R"((\$[a-zA-Z0-9_]+)\s*=\s*(.*))"); // группа захвата Трататата
  const regex l(R"(^\s*(?!.*=)(.*(\b(and|or|all|any|of|not|at|in)\b|[\(\)]).*))");
  smatch m; // object dans le quel on stock le resultat dans match de regex
  smatch g;
  map<string, string> my_dict_rules;
  vector<string> conditions;

  if (file.is_open()) {
    vector<string> buffer;
    while (getline(file, line)) {
        // auto slashPosition = string.find_first_of('\\');
        // string.erase(string.begin() + slashPosition, string.end());   
            // cout << string << endl;
            //
            if (!line.empty())
            buffer.push_back(line);
            } 

       // map<string, string> my_dict_rules;
        // vector<string> conditions;

        for (string& line : buffer) { // pour modif direceterment le vector
              auto slashPosition = line.find("//"); 
              if (slashPosition != string::npos) { 
              line.erase(line.begin() + slashPosition, line.end());}
             
              if (regex_search(line, m, r)){
                // cout << line << endl; // a mettre dans un dict 
                //cout << m[2] << endl;
                string values = m[2];
                string keys = m[1];
                values.erase(remove(values.begin(),values.end(),' '),values.end()); // https://ru.stackoverflow.com/questions/1071460/%D0%A3%D0%B4%D0%B0%D0%BB%D0%B5%D0%BD%D0%B8%D0%B5-%D0%BF%D1%80%D0%BE%D0%B1%D0%B5%D0%BB%D0%BE%D0%B2-%D0%B8%D0%B7-%D1%81%D1%82%D1%80%D0%BE%D0%BA%D0%B8
                if (values[0] == '/' or values[0] == '{' or values[0] == '"')
                {
                  values.erase(0,1);
                  values.erase(values.length() - 1, 1);
                  // cout << values << endl;
                }
                
                my_dict_rules[keys] = values; // cout << my_dict["$str1"]
              }
               if (regex_search(line, g, l)){
                   // cout << line << endl; // a mettre dans un dict 
                   conditions.push_back(g[1]); 
              }
            }

    // https://www.geeksforgeeks.org/cpp/read-a-file-line
    file.close();
    }

    ifstream fileV2(argv[2]);
    string data;
    vector<string> bufferV2;
    map<string, bool> results;
    vector<string> list_keys;
    vector<string> list_values;
    
    for (auto const& [key, val] : my_dict_rules) 
    {
          list_keys.push_back(key);
          list_values.push_back(val);
          results[key] = false;
    }

   // for (auto el : list_values){
   //   cout << el;
   // }


    if (fileV2.is_open()) {
    while (getline(fileV2, data)) {
            bufferV2.push_back(data);
    }
    //int compt = 0;
    //string substr;

    for (auto el : bufferV2){
        for (int i = 0; i < int(list_values.size()); i++){
        
        string string_to_find = list_values[i];
        //regex rx{ string_to_find } ;
        //smatch sm ;
        if (list_keys[i].find("str") != string::npos)
        {
          if (el.find(string_to_find) !=  string::npos) { 
          results[list_keys[i]] = true;
          }
        }
        else if (list_keys[i].find("reg") != string::npos)
        {
           regex rx{ string_to_find } ;
           smatch sm ;
           if (regex_search(el, sm, rx)) {
             results[list_keys[i]] = true;
           }
        }
        else if (list_keys[i].find("hex") != string::npos) {
          auto to_find = list_values[i];
          string result_convert;
          for (size_t i = 0; i < to_find.length(); i += 2) {
            string byteString = to_find.substr(i, 2);
            char byte = static_cast<char>(std::stoul(byteString, nullptr, 16));
            result_convert.push_back(byte);
          }
          if (el.find(result_convert) != string::npos)
              results[list_keys[i]] = true;
        }
        
        //if(regex_search(el, sm, rx) == true ){
        //      cout << "MAAAAAATCHHHH" << endl;
        //}
         
        // cout << list_values[i] << "|" << i << endl;//string_to_find << endl;
        //compt += 1;
        //substr = 
        //cout << my_dict_rules[compt].Values << endl;
        }
       // cout << el; //<< endl;
       // for (int i = 0; i < el.size(); i++){
         // for (auto const& [key, val] : my_dict_rules){  
           // if (el[i] == podstr[0])
          
          //}
    }
    fileV2.close();
    }
    //for (auto el : bufferV2){
    //  cout << el;
    //}
      //for (auto const& [key, val] : my_dict_rules) {
      //           cout << key << " — " << val << endl;
      //          }
      //for (auto const& [key, val] : my_dict_rules) {
      //           cout << key << " — " << val << endl;
      //          }
      

      //
      //
      //        Logie pour gerer les conditions !!!!!!!!!
      //
      //
      //

//for (auto const& [key, val] : results) {
//                 cout << key << " — " << val << endl;
//              }
string big_string; 
for (auto element : conditions){ 
  big_string += element;
  big_string += " ";
  //cout << element << "@" << endl;
  }
  
  replaceAll(big_string,"and","&");
  replaceAll(big_string,"or","|");
  replaceAll(big_string,"not","!");

  // cout << big_string;
  vector<string> sets = {"all of", "any of"};
  for (const string& set : sets) {
  size_t start_index; // find renvoie ce type 
  string search_target = set + " ($";

  while ((start_index = big_string.find(search_target)) != string::npos) {

    auto last_index = big_string.find(")", start_index);
    string group_prefix = big_string.substr(start_index, last_index - start_index + 1);
    auto start = group_prefix.find("$");
    auto last =  group_prefix.find("*");
    string prefix = group_prefix.substr(start + 1, last - start - 1);
    int total = 0;
    int found = 0;
    for (auto const& [key, val] : my_dict_rules) {
      if (key.find(prefix) != string::npos) {
        total++;
        if (results.count(key) && results[key] == true) {
                      found++;
                  
      }
    }
  }    
  // cout << start_index << "|" << last_index << "|" << prefix;
  bool success = false;
  if (set == "all of") {
        if (total > 0 && found == total) success = true;
    } else if (set == "any of") {
      if (found > 0) success = true;
    }
    string replacement = "0";
    if (success) replacement = "1";
    big_string.replace(start_index, last_index - start_index + 1, replacement);
  }
}
for (auto const& [key, val] : results) {
  if (big_string.find(key) != string::npos) {
    if (val == true) {
      replaceAll(big_string,key,"1");
    }
    if (val == false) {
      replaceAll(big_string,key,"0");
    }
  }
}

//cout << big_string << endl; // (1 & 1) | 1 // 0 & ( (0 & ! 0) | (0 & 0) ) | 0 

// last logical improuve
//string final_result;
  big_string.erase(remove(big_string.begin(),big_string.end(),' '),big_string.end()); // https://ru.stackoverflow.com/questions/1071460/%D0%A3%D0%B4%D0%B0%D0%BB%D0%B5%D0%BD%D0%B8%D0%B5-%D0%BF%D1%80%D0%BE%D0%B1%D0%B5%D0%BB%D0%BE%D0%B2-%D0%B8%D0%B7-%D1%81%D1%82%D1%80%D0%BE%D0%BA%D0%B8

  while (big_string.length() > 1){
   string before = big_string;
  // cout << big_string << endl; 
    replaceAll(big_string, "(1)", "1");
    replaceAll(big_string, "(0)", "0");
    replaceAll(big_string, "!1", "0");
    replaceAll(big_string, "!0", "1");

    replaceAll(big_string, "1&1", "1");
    replaceAll(big_string, "1&0", "0");
    replaceAll(big_string, "0&1", "0");
    replaceAll(big_string, "0&0", "0");

    replaceAll(big_string, "1|1", "1");
    replaceAll(big_string, "1|0", "1");
    replaceAll(big_string, "0|1", "1");
    replaceAll(big_string, "0|0", "0");

    if (before == big_string) break;
  }
  //cout << big_string << endl; 
if (big_string == "1") cout << "YES MATCHED" << endl;
else cout << "NO MATCHED: LOGICAL VALUE(" << big_string << ")" << endl;


  return 0;
}
