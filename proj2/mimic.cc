#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "treap.h"

using namespace std;

Treap *treap = new Treap;

// Replace all characters except letters (A-Z,a-z) in line with ' ',
// except keep '-' or '\'' if they are between letters.
void lowercaseWords(string & line) {
  for( string::iterator it = line.begin(); it != line.end(); ++it ) {
    if( !isalpha(*it) ) {
      if( (*it != '-' && *it != '\'') ||
	  it == line.begin() || it+1 == line.end() ||
	  !isalpha(*(it-1)) || !isalpha(*(it+1)) ) {
	*it = ' ';
      }
    } else {
      *it = tolower(*it);
    }
  }
}
/**
 * Insert a TreapNode to the Treap using treap function in Treap.cc
 */
bool insertToTreap(const string& key, int value) {
  bool isFound = true;
  
  // If the key is not found in the Treap, create a TreapNode with the key and value and insert into Treap
  if (treap->find(key) == -1) {
    treap->insert(key, value);
    isFound = false;
  }
  return isFound;
}


int main(int argc, char *argv[]) {
  
  if( argc < 2 || argc > 4 ) {
    cerr << "Usage: " << argv[0] << " n book.txt (optional 1 or 0 flag)" << endl;
    exit(1);
  }
  int flag = 0;
  int n = atoi(argv[1]);
  if (argv[3] != NULL)
    flag = atoi(argv[3]); 
  ifstream fin;
  fin.open(argv[2]);
  if( !fin.is_open() ) {
    cerr << "Unable to open " << argv[1] << endl;
    exit(2);
  }

  string line;
  string word;
  int count = 0;
    
  vector<string> vector_word; 
  vector<int> all_word_ranks;
  vector<vector<int> > follower_ranks;
    
  int val;
  while( !fin.eof() ) {
    getline(fin,line);
    lowercaseWords(line);
    istringstream iss(line, istringstream::in);
    while( iss >> word ) {
        if(!insertToTreap(word, count)) {
            count++;
        }
        bool found = false;
        for(int i = 0, max_size = vector_word.size(); i < max_size; i++){
            if(vector_word[i] == word){
                found = true;
                break;
            }
        }
        if(!found){
            vector_word.push_back(word);
        }
        // Use treap to find value of each word
        val =  treap->find(word);
        all_word_ranks.push_back(val);
      
    }
  }
  fin.close();
    
     // initializing the array with empty vectors
    for(int i = 0, max_size = vector_word.size(); i < max_size; i++) {
        vector<int> tmpv;
        follower_ranks.push_back(tmpv);
    }
    // Creating the nested vector
    for(int k = 0, max_size = all_word_ranks.size(); k < max_size - 1; k++){
        int currWord = all_word_ranks[k];
        int nextVal = all_word_ranks[k+1];
        // adding onto the vector the nextVal;
        follower_ranks.at(currWord).push_back(nextVal);
        
    }
    // Argument cannot be less than 0
    if( n < 0){
        cout<< "Incorrect Argument" << endl;
    }
    // Print unique words with words that follow it
    else if( n == 0){
        for(int currIndex = 0, max_size = vector_word.size(); currIndex < max_size ; currIndex++ ){
            vector<int> follower_vect = follower_ranks.at(currIndex);
            cout<< vector_word.at(currIndex) << " : ";
            //printing the contents of the follower vector
            for(int it = 0, max_size = follower_vect.size(); it < max_size; it++){
                cout<< vector_word[follower_vect[it]] << " ";
            }
            cout<<endl;
        }
    }
    // When n is greater than 0, print however many words specified randomly generated using structure from n == 0
    else{
        srand(time(0));
        int firstWord = rand() % vector_word.size();
        cout << vector_word[firstWord] << " ";
        for(int m = 1; m < n; m++ ){
            vector<int> tmp = follower_ranks.at(firstWord);
            // If a word has no followers, select the word according to how we selected the first word.
            if (tmp.empty()) {
              firstWord = rand() % vector_word.size();
              cout << vector_word[firstWord] << " ";
            } 
            // Else pick a word from a word's follower's at random, with each word given equal probability 
            else {
              int k = tmp.at(rand() % tmp.size());
              cout<< vector_word.at(k) << " ";
              firstWord = k;
            }
        }
    }
    if (flag == 1) {
      TreapNode *root = treap->getRoot();
      treap->printTreap(root);
    }
  return 0;
}
