// $Id: main.cpp,v 1.11 2018-01-25 14:19:29-08 - - $

#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>
#include <unistd.h>
#include <cassert>

using namespace std;

#include "listmap.h"
#include "xpair.h"
#include "util.h"
#include <regex>


using str_str_map = listmap<string, string>;
using str_str_pair = str_str_map::value_type;

int main(int argc, char** argv) {
     sys_info::execname(argv[0]);
     str_str_map map;
     regex comment_regex{ R"(^\s*(#.*)?$)" };
     regex key_value_regex{ R"(^\s*(.*?)\s*=\s*(.*?)\s*$)" };
     regex trimmed_regex{ R"(^\s*([^=]+?)\s*$)" };
     for (;;) {
          string line;
          getline(cin, line);
          if (cin.eof()) break;
          cout << endl << "input: \"" << line << "\"" << endl;
          smatch result;
          if (regex_search(line, result, comment_regex)) {
               continue;
          }
          if (regex_search(line, result, key_value_regex)) {

               cout << "key  : \"" << result[1] << "\"" << endl;
               cout << "value: \"" << result[2] << "\"" << endl;
          }
          else if (regex_search(line, result, trimmed_regex)) {
               auto i = map.find(result[1]);
               if (i == map.end()) {
                    cout << result[1] << ": key not found\n";
               }
               else {
                    cout << "key  : \"" << i->first << '\n';
                    cout << "value: \"" << i->second << '\n';
               }
          }
     }
     cout << "EXIT_SUCCESS" << endl;
     return EXIT_SUCCESS;
}

