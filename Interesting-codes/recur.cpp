// author: dalmeidanishan@gmail.com
// github: https://github.com/Nishan212

/*
  Case: consider a string encoding such that each alphabet character is mapped
  to a number between 1 and 26
  ex: A = 1, J = 10, Y = 25, Z = 26
  so: ABC = 123, XYZ = 242526

  Problem Statement: Given a encoded string print all the possible decodings associated
  ex: 123 can be 1 2 3 = ABC or 1 23 = AW or 12 3 = LC

  Note: This solution was coded on C++ compiler below C++11 hence there are some
  redundant code blocks
*/

#include <iostream>
#include <cstring>
#include <sstream>
#include <bits/stdc++.h>

using namespace std;

// stacks used for displaying purposes
stack<string> s1, s2;

// This function converts a string to integer (inbuilt function in C++11 or above)
int stoi(string str) {
  stringstream ss;
  int integer;
  ss << str;
  ss >> integer;
  return integer;
}

// This function maps numbers to alphabets (ex : 1 -> A, 10 -> J, 26 -> Z)
// Note: If you want to map to lower case replace '64' with '96'
char mapper(string str) {
  return 64 + stoi(str);
}

/*
  This is a recursive function that does the actual logic implementation

  Subproblem: From the remaining string,
  (i) display character encoding of one character and recurse or
  (ii) display character encoding of two characters and recurse

  ex: "...12...", where "..." can be any integers and any number of them
  (i) "...AB..." <- one character coding, 1 -> A, 2 -> B
  (ii) "...L..." <- two chracters coding, 12 -> L

  Idea behind logic: atmost two characters from the encoded string
  can be mapped since mapping is from 1 -> A to 26 -> Z and 26 is two characters

*/
int rec(char str[], int i) {
  string ans = "";

  if (str[i] != '\0') {           // end of string not reached
    ans.push_back(str[i]);        // one character encoding

    s1.push(ans);
    rec(str, i + 1);              // recursive call to the rest of the string
    s1.pop();                     // backtracking

    if (str[i + 1] != '\0') {     // second character from current character
      ans = "";                   // not null
      ans.push_back(str[i]);
      ans.push_back(str[i + 1]);  // two character encoding

      s1.push(ans);
      rec(str, i + 2);            // recursive call to the rest of the string
      s1.pop();                   // backtracking
    }
  }
  else {                          // end of string reached - hence display
    ans = "";
    while(!s1.empty()) {
      s2.push(s1.top());
      s1.pop();
    }

    while(!s2.empty()) {          // if character encoding > 26 print "__"
      if (stoi(s2.top()) > 26) cout << "__";
      else cout << mapper(s2.top());
      s1.push(s2.top());
      s2.pop();
    }
    cout << endl;
  }
}

int main(int argc, char const *argv[]) {
  char str[] = "1213625";

  /*
  cout << "Enter the encoded string";
  cin >> str;
  */

  rec(str, 0);
  return 0;
}
