#include <algorithm>
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;

// Add prototypes of helper functions here
void search(int blank, std::string &in, const std::string &floating, const std::set<std::string> &dict, std::set<std::string> &fin, int pos);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string &in,
    const std::string &floating,
    const std::set<std::string> &dict)
{
  // Add your code here
  int cnt = 0; // count how many blank spaces
  for (unsigned int i = 0; i < in.length(); i++)
  {
    if (in[i] == '-')
      cnt++; // blank location
  }
  std::set<std::string> final;                // set of words that fit conditions
  std::string cur = in;                       // current guess
  search(cnt, cur, floating, dict, final, 0); // find all possible words
  if (in == "")
    return final; // no words
  return final;   // return set of words matching conditions
}

// Define any helper functions here
void search(int blank, std::string &in, const std::string &floating, const std::set<std::string> &dict, std::set<std::string> &fin, int pos)
{
  int l = in.size();       // size of current guess word
  int f = floating.size(); // size of total letters that works in string in
  if (pos == l)
  { // at the end of string in (guess)
    if (dict.find(in) != dict.end())
    {
      fin.insert(in); // finds word in dictionary, insert word in set
    }
    return; // stop
  }
  if (in[pos] != '-')
  {                                                  // correct letter in location already
    search(blank, in, floating, dict, fin, pos + 1); // go to next index
    return;                                          // stop
  }
  else if (in[pos] == '-')
  { // blank position
    if (blank > f)
    {                                                  // more blank letters than knowing letters
      std::string alph = "abcdefghijklmnopqrstuvwxyz"; // alphabet
      int s = alph.size();                             // size of alphabet
      for (int i = 0; i < s; i++)
      {                              // goes through the entire alphabet
        char b = alph[i];            // current letter
        in[pos] = b;                 // insert current letter in guess (in) to make combinations
        std::string make = floating; // creates string to maybe modify known guessed letters
        if ((signed int)floating.find(b) != -1)
        {                                  // letter is present in guessed letters
          make.erase(floating.find(b), 1); // modify, erase that letter once only
        }
        search(blank - 1, in, make, dict, fin, pos + 1); // one less guessed letter and go next index
      }
    }
    else if (blank == f)
    { // same amount of blank spaces as guessed letters
      for (int i = 0; i < f; i++)
      {                                                  // go through guessed letters
        in[pos] = floating[i];                           // replaced blank space with letter in guesed letter
        std::string make = floating;                     // modify const string
        make.erase(floating.find(floating[i]), 1);       // erase used guessing letter, duplicate = erase one only
        search(blank - 1, in, make, dict, fin, pos + 1); // find combinations with current word
      }
    }
    in[pos] = '-'; // go back to previous for new combinations
  }
}
