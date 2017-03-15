#include "split.h"

vector<std::string> split(const std::string &s, const char &c) {
   vector<std::string> v;
   std::string::size_type i = 0;
   std::string::size_type j = s.find(c);
   while (j != std::string::npos) {
      v.push_back(s.substr(i, j-i));
      i = ++j;
      j = s.find(c, j);

   }
   v.push_back(s.substr(i, s.length()));
   return v;
}
