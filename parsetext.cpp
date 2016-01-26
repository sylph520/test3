#include <QString>
#include <QStringList>
#include <algorithm>
#include <stdio.h>
#include <iostream>
using namespace std;

bool notNeed(char c)
{
    //    if(c == '=')
    //        return false;
    //    else
    return ispunct(c);
}
QStringList parse_text(QString str)
{
    QStringList words;
    //string s = q2s(str);
    string s = str.toStdString();
    //****begin split question sentence into  words
    typedef string::size_type string_size;
    string_size i = 0;
    s.erase(remove_if(s.begin(),s.end(),notNeed),s.end());
    cout<<s;
    // invariant: we have processed characters [original value of i, i)
    while (i != s.size())
    {
        // ignore leading blanks
        // invariant: characters in range [original i, current i) are all spaces
        while (i != s.size() && isspace(s[i])){
            ++i;
        }
        // find end of next word
        string_size j = i;
        // invariant: none of the characters in range [original j, current j)is a space
        while (j != s.size() && !isspace(s[j])){
            j++;
        }
        // if we found some nonwhitespace characters
        if (i != j)
        {
            // copy from s starting at i and taking j - i chars
            //QString tempqs = s2q(string(i,j-i));
            QString to_add_qs;string to_add_s;
            to_add_s = s.substr(i,j-i);
            cout<<to_add_s<<endl;
            to_add_qs=QString::fromStdString(to_add_s);
            words.append(to_add_qs);
            i = j;
        }
    }

    //qWords = filter_text(words);
    return words;
}

