#include <iostream>
#include <vector>
#include <string>
#include "WordVector.h"

using namespace std;
using namespace std::chrono;

WordVector::WordVector()
{
}

WordVector::~WordVector()
{
}

vector<Word>& WordVector::get_data() { return data; }

int WordVector::get_count(const string text) const
{
    int i=find(text,0,data.size()-1);
    if(i!=-1)
        return data[i].get_count();
    else
        return -1;
}

void WordVector::insert(const string text)
{
    
    if(data.size()==0){
        auto start = chrono::steady_clock::now();
        data.push_back(Word(text));
        auto end = chrono::steady_clock::now();
        auto diff = end - start;
        increment_elapsed_time(chrono::duration <double, micro> (diff).count());
    }
    else{
        int i = find(text,0,data.size()-1);
        if(i==-1){
            auto start = chrono::steady_clock::now();
            vector<Word>::iterator it = data.begin();
           /* vector<Word>::reverse_iterator r_it=data.rbegin();
            if (i<=data.size()/2)
            {  
                int index=i;
                while(index!=0){
                    it++;
                    index--;
                }
                //it = data.erase(it);
            }
            else
            {
                int index=data.size()-index-1;
                while(index!=0){
                    r_it++;
                    index--;
                }
                it = r_it.base();
                --it;
                //it1=data.erase(it1);
            } */
            while(it!=data.end()){
            if(text>(*it).get_text())
                it++;
            else
                break;
            }
            if(it!=data.end())
                it=data.emplace(it,Word(text));
            else
                data.push_back(Word(text));
            auto end = chrono::steady_clock::now();
            auto diff = end - start;
            increment_elapsed_time(chrono::duration <double, micro> (diff).count());
        }
        else{
            (*search(text)).increment_count();
        }
    }
       
}

vector<Word>::iterator WordVector::search(const string text)
{
    vector<Word>::iterator it = data.begin();
    auto start = chrono::steady_clock::now();
    int i=find(text,0,data.size()-1);
    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    increment_elapsed_time(chrono::duration <double, micro> (diff).count());
    if(i>=0){
        while(i>0){
            auto start = chrono::steady_clock::now();
            it++;
            auto end = chrono::steady_clock::now();
            auto diff = end - start;
            increment_elapsed_time(chrono::duration <double, micro> (diff).count());
            i--;
        }
    
    return it;
    }
    else
    {
        auto start = chrono::steady_clock::now();
        it=data.end();
        auto end = chrono::steady_clock::now();
        auto diff = end - start;
        increment_elapsed_time(chrono::duration <double, micro> (diff).count());
        return it;
    }
}

int WordVector::find(const string text, int low, int high) const
{
    while (low <= high) {
            int middle = (low + high) / 2;
           // cout<<"middle="<<middle<<endl;
            if (data[middle].get_text() == text)
                  return middle;
            else if (data[middle].get_text() > text)
                  high = middle - 1;
            else
                  low = middle + 1;
      }
      return -1;
}
