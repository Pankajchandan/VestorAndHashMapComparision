#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <ctime>
#include <stdlib.h>
#include <sstream>
#include "Word.h"
#include "WordVector.h"
#include "WordMap.h"

using namespace std;

const string INPUT_FILE_NAME = "C:\\Users\\pankaj\\Desktop\\USConstitution.txt";
const int    MAX_SEARCHES    = 100000;

void time_word_insertions(ifstream& in, WordVector& v, WordMap& m);
void make_spot_checks(WordVector& v, WordMap& m) throw(string);
void check_concordances(WordVector& v, WordMap& m) throw(string);
void time_word_searches(WordVector& v, WordMap& m) throw(string);
string commafy(const long n);

int main()
{
    ifstream in;
    in.open(INPUT_FILE_NAME);
    if (in.fail())
    {
        cout << "Failed to open " << INPUT_FILE_NAME << endl;
        return -1;
    }

    WordVector v;
    WordMap    m;

    try {
        time_word_insertions(in, v, m);
        make_spot_checks(v, m);
        check_concordances(v, m);
        time_word_searches(v, m);
    }
    catch (string& msg)
    {
        cout << endl << endl << "***** " << msg << endl;
    }

    return 0;
}

void time_word_insertions(ifstream& in, WordVector& v, WordMap& m)
{
    string line;
    int line_count = 0;
    int character_count = 0;
    int word_count = 0;

    cout << "Timed insertions ..." << endl;

    // Loop once per line of the input file.
    while (getline(in, line))
    {
        int i=0;
        while(line[i]){
                    line[i]=tolower(line[i]); //convert to lower case
                    i++;
                    character_count++;
                }
        
        istringstream iss(line);
        string word;
        while(iss >> word) {
                     
            //filter the word based on the 1st letter and last letter, discard any special char
            if(!((word[0]>='a'&&word[0]<='z')||(word[0]>='A'&&word[0]<='Z')||(word[0]=='(')||(word[0]=='"'))){
               continue; 
            }
                
            else{
                word_count++;
                if(!((word[word.size()-1]>='a'&&word[word.size()-1]<='z')||(word[word.size()-1]>='A'&&word[word.size()-1]<='Z'))){
                    word.pop_back();
                }
                if(!((word[word.size()-1]>='a'&&word[word.size()-1]<='z')||(word[word.size()-1]>='A'&&word[word.size()-1]<='Z'))){
                    word.pop_back();
                }
                if(!((word[0]>='a'&&word[0]<='z')||(word[0]>='A'&&word[0]<='Z'))){
                    word=word.substr(1);
                }
                if(word=="vice-president"){
                    v.insert("vice");
                    m.insert("vice");
                    v.insert("president");
                    m.insert("president");
                    word_count++;
                }
                else{
                    v.insert(word);
                    m.insert(word);
                }
            } 
        }
        line_count++;
    }
 

    cout << "          Lines: " << setw(6) << commafy(line_count) << endl;
    cout << "     Characters: " << setw(6) << commafy(character_count) << endl;
    cout << "          Words: " << setw(6) << commafy(word_count) << endl;
    cout << endl;
    cout << "    Vector size: " << commafy(v.get_data().size()) << endl;
    cout << "       Map size: " << commafy(m.get_data().size()) << endl;
    cout << endl;
    cout << "    Vector total insertion time: " << setw(8)
         << commafy(v.get_elapsed_time()) << " usec" << endl;
    cout << "       Map total insertion time: " << setw(8)
         << commafy(m.get_elapsed_time()) << " usec" << endl;
    
}

//to make spotchecks
void make_spot_checks(WordVector& v, WordMap& m) throw(string)
{
    cout << endl << "Spot checks of word counts ..." << endl;

    vector<Word>&      vdata = v.get_data();
    map<string, Word>& mdata = m.get_data();

    vector<string> texts = {
        "amendment", "article", "ballot", "citizens", "congress",
        "constitution", "democracy", "electors", "government", "law",
        "legislature", "people", "president", "representatives",
        "right", "trust", "united", "vice", "vote"
    };

    for (string text : texts)
    {
        cout << "    " << text << ": ";

        vector<Word>::iterator      itv = v.search(text);
        map<string, Word>::iterator itm = m.search(text);
        if(itm==mdata.end()){
            cout<<"vecor:(not found)"<<" map:(not found)"<<endl;
        }
        else{
          cout<<"vecor:"<<(*itv).get_count()<<" map:"<<itm->second.get_count()<<endl;
        }
        
    }
}
//check validity of table
void check_concordances(WordVector& v, WordMap& m) throw(string)
{
    cout << endl << "Checking concordances ... ";  cout.flush();

    vector<Word>&      vdata = v.get_data();
    map<string, Word>& mdata = m.get_data();

    int vsize = vdata.size();
    int msize = mdata.size();

    if (vsize == 0) throw("Empty vector.");
    if (msize == 0) throw("Empty map.");

    if (vsize != msize ) throw(string("Size mismatch: ") + to_string(vsize) +
                                                 " and " + to_string(msize));

    vector<Word>::iterator      itv = vdata.begin();
    map<string, Word>::iterator itm = mdata.begin();

    while (itv != vdata.end())
    {
        if (*itv != itm->second)
        {
            
            throw string(string("Data mismatch: ")
                    + (*itv).get_text() + ":" + to_string((*itv).get_count())
                    + " and " + itm->second.get_text() + ":"
                    + to_string(itm->second.get_count()));
        }

        ++itv;
        ++itm;
    }

    cout << "both match!" << endl;
}

//make random searches
void time_word_searches(WordVector& v, WordMap& m) throw(string)
{
    cout << endl << "Timed searches (" << commafy(MAX_SEARCHES)
                 << " searches) ..." << endl;
    v.reset_elapsed_time();
    m.reset_elapsed_time();
    for (int i = 1; i <= MAX_SEARCHES; i++)
    {
        int size=v.get_data().size();
        int index = rand()%size;
        
        string text = v.get_data()[index].get_text();
        v.search(text);
        m.search(text);
        
    }

    cout << endl;
    cout << "    Vector total search time: " << setw(8)
         << commafy(v.get_elapsed_time()) << " usec" << endl;
    cout << "       Map total search time: " << setw(8)
         << commafy(m.get_elapsed_time()) << " usec" << endl;
}

/**
 * Convert a number to a string with commas.
 * @param n the number.
 */
string commafy(const long n)
{
    string str = to_string(n);
    int pos = str.length() - 3;

    while (pos > 0)
    {
        str.insert(pos, ",");
        pos -= 3;
    }

    return str;
}
