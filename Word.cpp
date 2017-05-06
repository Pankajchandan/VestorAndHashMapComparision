#include <string>
#include "Word.h"
using namespace std;

/***** Modify this file as needed. *****/

Word::Word() : text(""), count(0)
{
}

Word::Word(string text) : text(text), count(1)
{
}

Word::~Word()
{
}

string Word::get_text()  const { return text; }
int    Word::get_count() const { return count; }

void   Word::increment_count() { count++; }

//overload operator
bool operator !=(Word& w1,Word& w2){
    if(w1.text==w2.text)
        return false;
    else
        return true;
}