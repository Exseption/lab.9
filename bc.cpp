#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cmath>
using namespace std;

int bin2dec(const char* str) {
 int n = 0;
 int size = strlen(str) - 1;
        int count = 0;
 while ( *str != '\0' ) {
  if ( *str == '1' ) 
      n = n + pow(2, size - count );
  count++; 
  str++;
 }
 return n;
}

int main() {
 const char* bin_str = "1100100";
 cout << bin2dec(bin_str) << endl;
}