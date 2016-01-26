#include "diagramtext.h"
using namespace std;
void parse_image(bool flag)
{

    if(!flag)
    {
        imgElement<<"circle O"<<"line AB"<<"line AC"<<"line CD"<<"point A"<<"point B"<<"point C"<<"point D"<<"point E"<<"point F";
    }
    else
    {
        for(int i = 0;i<circles.size();i++)
        {
            string temp = "circle " + circles[i].letter;
            QString tempq = QString::fromStdString(temp);
            imgElement<<tempq;
        }
        for(int j = 0;j<points.size();j++)
        {
            string temp = "point " + points[j].idxletter;
            QString tempq = QString::fromStdString(temp);
            imgElement<<tempq;
        }

    }
    //return imgElement;
}


