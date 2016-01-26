#include <QString>
#include <QStringList>
#include <algorithm>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <sys/types.h>
#include <cctype>
#include <iterator>
#include <string>
using namespace std;
struct str_and_idx
{
    string str;
    int idx;
};


bool is_prefix(string abc)
{
    vector<string> filter;
    bool flag = false;
    //***** prepare the prefix set for matching
    //  filter.push_back("diameter");
    //  filter.push_back("chord");
    //  filter.push_back("median");
    //  filter.push_back("altitude");
    filter.push_back("point");
    filter.push_back("line");
    filter.push_back("angle");
    filter.push_back("circle");
    filter.push_back("triangle");
    filter.push_back("square");
    //***** matching

    for(size_t i = 0; i < filter.size(); i++)
    {
        const char* temp1 = abc.c_str();
        const char* temp2 = filter[i].c_str();
        //if(strcasecmp(abc.c_str(),(filter[i]).c_str()))
        if(!_strcmpi(temp1,temp2))
        {
            flag = true;
            break;
        }
    }
    return flag;

}

bool is_entity(string abc)
{
    int strsize = abc.size();
    for(int i = 0; i < strsize; i++)
    {
        if(islower(abc[i]))
        {
            return false;
        }
        else if(isdigit(abc[i]))
        {
            return false;
        }
    }
    return true;

}

//bool in_ettSet(string abc)
//{

//}

QStringList filter_text(QStringList qsl)
{
    QStringList to_return;
    //vector<str_and_idx> prefixSet,entitySet;
    //begin
    int size = qsl.size();
    for(int i = 0;i < size;i++)
    {
        string temp = (qsl.at(i)).toStdString();
        if(is_prefix(temp))
        {
            if((i != size - 1)&&(is_entity((qsl.at(i+1)).toStdString())))
            {
                string newStr = temp +" "+ qsl.at(i+1).toStdString();
                QString newQStr = QString::fromStdString(newStr);
                to_return.append(newQStr);
                ++i;
            }
            else
            {
                QString qtemp_show;
                qtemp_show.fromStdString(temp);
                to_return.append(qtemp_show);
            }
        }
        else if(is_entity(temp))
        {
            int temp_size = (qsl.at(i)).size();
            string temp_toshow;
            switch (temp_size) {
            case 1:
                temp_toshow = "point " + temp;
                break;
            case 2:
                temp_toshow = "line " + temp;
                break;
            case 3:
                temp_toshow = "triangle "+ temp;
            case 4:
                temp_toshow = "rectangle " + temp;
                break;
            default:
                break;
            }
            QString qtemp_toshow = QString::fromStdString(temp_toshow);
            to_return.append(qtemp_toshow);
        }

    }
    //end
    return to_return;
}

