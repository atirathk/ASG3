// $Id: main.cpp,v 1.11 2018-01-25 14:19:29-08 - - $

#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>
#include <unistd.h>

using namespace std;

#include "listmap.h"
#include "xpair.h"

 using str_str_map = listmap<string, string>;
 using str_str_pair = str_str_map::value_type;

int main(int argc, char** argv) {
     str_str_map map;
     str_str_pair pair("key", "value");
     map.insert(pair);
     str_str_map::iterator it = map.find("key");
     cout << it->second << '\n';
     return 0;
}

