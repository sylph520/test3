#ifndef GEOMETRY
#define GEOMETRY

#endif // GEOMETRY
#include <string>
#include <QPainter>
using namespace std;

struct imgPointElement
{
    string idxletter;
    int x,y;
};
struct imgCircleElement
{
    string letter;
    int x,y;
    int radius;
};
struct imgLineElement
{
    string letter;
    int x,y,a,b;
};

extern vector<imgPointElement> points;
extern vector<imgCircleElement> circles;
//prepare the platform for painting
extern QPainter painter;
extern QStringList imgElement;
