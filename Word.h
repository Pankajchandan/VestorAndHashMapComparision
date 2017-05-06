#ifndef WORD_H_
#define WORD_H_

/***** Modify this file as needed. *****/

#include <string>
using namespace std;

class Word
{
public:
    Word();
    Word(string text);
    virtual ~Word();

    string get_text() const;
    int get_count() const;

    void increment_count();
    friend bool operator !=(Word& w1,Word& w2);
     

private:
    string text;
    int count;
};

#endif /* WORD_H_ */
