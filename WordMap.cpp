#include <iostream>
#include <map>
#include <string>
#include "WordMap.h"

using namespace std;
using namespace std::chrono;

WordMap::WordMap()
{
}

WordMap::~WordMap()
{
}

map<string, Word>& WordMap::get_data() { return data; }

int WordMap::get_count(const string text) const
{
    if(data.find(text)==data.end())
        return -1;
    else 
        data.find(text)->second.get_count();
}

void WordMap::insert(const string text)
{
    if(data.size()==0){
        Word w(text);
        auto start = chrono::steady_clock::now();
        data.insert(pair<string,Word>(text,w));
        auto end = chrono::steady_clock::now();
        auto diff = end - start;
        increment_elapsed_time(chrono::duration <double, micro> (diff).count());
    }
    
    else if(data.find(text)==data.end()){
        Word w(text);
        auto start = chrono::steady_clock::now();
        data.insert(pair<string,Word>(text,w));
        auto end = chrono::steady_clock::now();
        auto diff = end - start;
        increment_elapsed_time(chrono::duration <double, micro> (diff).count());
        
    }    
    else{
        auto start = chrono::steady_clock::now();
        data.find(text)->second.increment_count();
        auto end = chrono::steady_clock::now();
        auto diff = end - start;
        increment_elapsed_time(chrono::duration <double, micro> (diff).count());
    }   
    
}

map<string, Word>::iterator WordMap::search(const string text) 
{
        auto start = chrono::steady_clock::now();
        map<string, Word>::iterator it=data.find(text);
        auto end = chrono::steady_clock::now();
        auto diff = end - start;
        increment_elapsed_time(chrono::duration <double, micro> (diff).count());
        return it;
        //return data.begin();
}