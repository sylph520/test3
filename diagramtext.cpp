#include "diagramtext.h"
#include "ui_diagramtext.h"
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QVector>
#include <string>
#include <QPainter>
#include <QDebug>
#include <QProcess>
#include <QXmlStreamWriter>

bool have_image_info = false;
using namespace std;
//begin function declaration
QStringList parse_text(QString s);
QStringList filter_text(QStringList qsl);
void parse_image(bool flag);
//void myDrawCircle(QString a);
void getElementList();
vector<imgPointElement> points;
vector<imgCircleElement> circles;
vector<imgLineElement> lines;
QImage *img = new QImage;
QStringList imgElement;


void getElementList(bool flag)
{
    if(!flag)
    {
        imgCircleElement imgele_1 ={"O",87,73,67};
        imgPointElement imgele_2 = {"A",20,73};
        imgPointElement imgele_3 = {"B",154,73};
        imgPointElement imgele_4 = {"C",131,24};
        imgPointElement imgele_5 = {"D",131,124};
        imgPointElement imgele_6 = {"E",131,73};
        circles.push_back(imgele_1);
        points.push_back(imgele_2);
        points.push_back(imgele_3);
        points.push_back(imgele_4);
        points.push_back(imgele_5);
        points.push_back(imgele_6);
    }

}

//slot respondance functions defined below
DiagramText::DiagramText(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DiagramText)
{
    ui->setupUi(this);
}

DiagramText::~DiagramText()
{
    delete ui;
}


void DiagramText::on_actionTextImport_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Import Question Text"),QString(),tr("Text Files(*.txt)"));
    if(!fileName.isEmpty()){
        QFile file(fileName);
        if(!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::critical(this,tr("Error"),tr("Could not open file"));
            return;
        }
        QTextStream in(&file);
        ui->QtextLoc->setText(in.readAll());
        file.close();
    }

}

void DiagramText::on_actionImageImport_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Import Question Image"),QString(),tr("image Files(*.png)"));
    if(!fileName.isEmpty()){
        if(!img->load(fileName))
        {
            QMessageBox::critical(this,tr("Error"),tr("Could not open file"));
            return;
        }
        ui->imageLoc->setPixmap(QPixmap::fromImage(*img));
        //ui->imageLoc->setScaledContents(true);


    }
}

void DiagramText::on_textParseBtn_clicked()
{
    QString QuestionText = ui->QtextLoc->toPlainText();
    QStringList words;
    words = parse_text(QuestionText);
    int wsize = words.size();
    ui->wordObjectList->clear();
    for(int i = 0;i<wsize;i++)
    {
        QString to_add_string = words.at(i);
        ui->wordObjectList->addItem(to_add_string);
    }

}

void DiagramText::on_textFilterBtn_clicked()
{
    QString QuestionText = ui->QtextLoc->toPlainText();
    QStringList words,QWords;
    words = parse_text(QuestionText);
    QWords = filter_text(words);
    int wsize = QWords.size();
    ui->wordObjectList->clear();
    for(int i = 0;i<wsize;i++)
    {
        QString to_add_string = QWords.at(i);
        ui->wordObjectList->addItem(to_add_string);
    }
}



void DiagramText::on_elementFilter_clicked()
{

}

void DiagramText::on_imageParse_clicked()
{
    //points.clear();circles.clear();
    //import image info
    //    QVector<QPoint> points;
    //    QVector<QLine> lines;
    //    QVector<QPolygon> polys;
    //    QVector<QRect> circles;
    //    int offset = 22;
    //    QPoint A(20,95-offset);QPoint B(154,95-offset);QPoint C(131,46-offset);QPoint D(131,146-offset);QPoint E(131,95-offset);QPoint O(87,95-offset);
    //    QLine l1(A,B);QLine l2(A,C);QLine l3(C,D);
    //    QRect cicle_O(20,6,134,134);
    //show the info
    //    for(int i = 0;i < circles.size();i++)
    //    {
    //        //.....
    //        ui->imgeleListWidget->addItem(temp);
    //    }
    //    for(int i = 0;i < lines.size();i++)
    //    {
    //        //.....
    //        ui->imgeleListWidget->addItem(temp);
    //    }
    ui->imgeleListWidget->clear();
    //QStringList imageElement;
    //imageElement.clear();
    parse_image(have_image_info);
    //    ui->imgeleListWidget->addItem("circle O");
    //    ui->imgeleListWidget->addItem("line AB");
    //    ui->imgeleListWidget->addItem("line AC");
    //    ui->imgeleListWidget->addItem("line CD");
    //    ui->imgeleListWidget->addItem("point A");
    //    ui->imgeleListWidget->addItem("point B");
    //    ui->imgeleListWidget->addItem("point C");
    //    ui->imgeleListWidget->addItem("point D");
    //    ui->imgeleListWidget->addItem("point E");
    //    ui->imgeleListWidget->addItem("point F");
    for(int i = 0;i<imgElement.size();i++)
    {
        ui->imgeleListWidget->addItem(imgElement.at(i));
    }
    imgElement.clear();



}


void DiagramText::on_wordObjectList_itemClicked(QListWidgetItem *item)
{
    //qDebug()<<"test begin"<<endl;
    QString tempQText = item->text();
    //string tempText = tempQText.toStdString();

    QPixmap temp = QPixmap::fromImage(*img);
    QPainter painter(&temp);
    painter.setPen(QPen(Qt::red,5,Qt::SolidLine));
    painter.setFont(QFont("Arial",30));

    //test painting

    //******analyze string content
    QStringList templist = parse_text(tempQText);
    QString tempidx_q = templist.at(0);
    QString tempett_q = templist.at(1);
    //qDebug()<<"1: "<<tempidx_q<<"2: "<<tempett_q<<endl;

    //*****get primitive points elements
    getElementList(have_image_info);

    //*****begin drawing process
    if(tempidx_q == "circle")
    {
        qDebug()<<"circle drawing"<<endl;
        QRect rect;
        for(int i = 0;i < circles.size();i++)
        {
            QString cname;
            string cLetter = circles[i].letter;
            cname = QString::fromStdString(cLetter);
            int _radius = circles[i].radius;
            if(cname == tempett_q)
            {
                int c_x = circles[i].x;
                int c_y = circles[i].y;
                //QPoint center(_x,_y);
                QRect recttemp(c_x - _radius,c_y-_radius,2*_radius,2*_radius);
                rect = recttemp;
                break;
            }
            else
            {
                continue;
            }
        }
        cout<<"test stop"<<endl;
        painter.drawEllipse(rect);
        ui->imageLoc->setPixmap(temp);

    }
    else if(tempidx_q == "line")
    {
        //qDebug()<<"line drawing"<<endl;
        string tempett = tempett_q.toStdString();
        QString firstP_q,secondP_q;
        string firstP = tempett.substr(0,1);
        string secondP = tempett.substr(1,1);
        cout<<firstP<<secondP<<"part"<<endl;
        firstP_q = QString::fromStdString(firstP);
        secondP_q = QString::fromStdString(secondP);
        int l_x1,l_y1,l_x2,l_y2;
        for(int i = 0;i < points.size();i++)
        {
            QString pname;
            string pLetter = points[i].idxletter;
            pname = QString::fromStdString(pLetter);
            if(pname == firstP_q)
            {
                l_x1 = points[i].x;
                l_y1 = points[i].y;

            }
            else if(pname == secondP_q)
            {
                l_x2 = points[i].x;
                l_y2 = points[i].y;
            }
        }
        painter.drawLine(l_x1,l_y1,l_x2,l_y2);
        ui->imageLoc->setPixmap(temp);

    }else if(tempidx_q == "point")
    {
        //qDebug()<<"point drawing"<<endl;
        int p_x,p_y;
        for(int i = 0; i < points.size();i++)
        {
            QString pname;
            string pLetter = points[i].idxletter;
            pname = QString::fromStdString(pLetter);
            if(pname == tempett_q)
            {
                p_x = points[i].x;
                p_y = points[i].y;
                break;
            }
        }
        painter.drawPoint(p_x,p_y);
        ui->imageLoc->setPixmap(temp);
    }
}


void DiagramText::on_actionImport_Image_Informations_triggered()
{
    points.clear();circles.clear();imgElement.clear();
    QString fileName = QFileDialog::getOpenFileName(this,tr("Import Image Info"),QString(),tr("image info(*txt)"));
    if(!fileName.isEmpty())
    {
        QFile file(fileName);
        if(!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::critical(this,tr("Error"),tr("could not open file"));
            return;
        }
        else
        {
            ui->imgeleListWidget->clear();
            have_image_info = true;
        }
        while(!file.atEnd())
        {
            QString temp = file.readLine();
            //qDebug()<<temp<<endl
            QStringList templist = parse_text(temp);
            //*****test the templist generation
            //                for(int i = 0;i<templist.size();i++)
            //                {
            //                    qDebug()<<templist.at(i)<<endl;
            //                }
            if(templist.at(0) == "0")
            {
                if(templist.size()==size_t(4))//intend for points infos
                {
                    imgPointElement tempPE;
                    bool flag1,flag2;
                    tempPE.idxletter = templist.at(1).toStdString();
                    tempPE.x = templist.at(2).toInt(&flag1,10);
                    tempPE.y = templist.at(3).toInt(&flag2,10);
                    points.push_back(tempPE);
                }
                else if(templist.size() == size_t(5))//intend for circle infos
                {
                    imgCircleElement tempCE;
                    bool flag1,flag2,flag3;
                    tempCE.letter = templist.at(1).toStdString();
                    tempCE.x = templist.at(2).toInt(&flag1,10);
                    tempCE.y = templist.at(3).toInt(&flag2,10);
                    tempCE.radius = templist.at(4).toInt(&flag3,10);
                    circles.push_back(tempCE);
                }
            }
            else if (templist.at(0) == "1")
            {
                qDebug()<<"wait for relationship infos"<<endl;
                if(templist.size() == size_t(3))
                {
                    QString temp;
                    temp = "line " + templist.at(1)+templist.at(2);
                    imgElement.push_back(temp);
                }
            }

        }

    }
    qDebug()<<"still debuging other things"<<endl;

}

void DiagramText::on_imgeleListWidget_itemClicked(QListWidgetItem *item)
{
    //qDebug()<<"test begin"<<endl;
    QString tempQText = item->text();
    //string tempText = tempQText.toStdString();

    QPixmap temp = QPixmap::fromImage(*img);
    QPainter painter(&temp);
    painter.setPen(QPen(Qt::red,5,Qt::SolidLine));
    painter.setFont(QFont("Arial",30));

    //test painting

    //******analyze string content
    QStringList templist = parse_text(tempQText);
    QString tempidx_q = templist.at(0);
    QString tempett_q = templist.at(1);
    //qDebug()<<"1: "<<tempidx_q<<"2: "<<tempett_q<<endl;

    //*****get primitive points elements
    getElementList(have_image_info);

    //*****begin drawing process
    if(tempidx_q == "circle")
    {
        qDebug()<<"circle drawing"<<endl;
        QRect rect;
        for(int i = 0;i < circles.size();i++)
        {
            QString cname;
            string cLetter = circles[i].letter;
            cname = QString::fromStdString(cLetter);
            int _radius = circles[i].radius;
            if(cname == tempett_q)
            {
                int c_x = circles[i].x;
                int c_y = circles[i].y;
                //QPoint center(_x,_y);
                QRect recttemp(c_x - _radius,c_y-_radius,2*_radius,2*_radius);
                rect = recttemp;
                break;
            }
            else
            {
                continue;
            }
        }
        cout<<"test stop"<<endl;
        painter.drawEllipse(rect);
        ui->imageLoc->setPixmap(temp);

    }
    else if(tempidx_q == "line")
    {
        //qDebug()<<"line drawing"<<endl;
        string tempett = tempett_q.toStdString();
        QString firstP_q,secondP_q;
        string firstP = tempett.substr(0,1);
        string secondP = tempett.substr(1,1);
        cout<<firstP<<secondP<<"part"<<endl;
        firstP_q = QString::fromStdString(firstP);
        secondP_q = QString::fromStdString(secondP);
        int l_x1,l_y1,l_x2,l_y2;
        for(int i = 0;i < points.size();i++)
        {
            QString pname;
            string pLetter = points[i].idxletter;
            pname = QString::fromStdString(pLetter);
            if(pname == firstP_q)
            {
                l_x1 = points[i].x;
                l_y1 = points[i].y;

            }
            else if(pname == secondP_q)
            {
                l_x2 = points[i].x;
                l_y2 = points[i].y;
            }
        }
        painter.drawLine(l_x1,l_y1,l_x2,l_y2);
        ui->imageLoc->setPixmap(temp);

    }else if(tempidx_q == "point")
    {
        //qDebug()<<"point drawing"<<endl;
        int p_x,p_y;
        for(int i = 0; i < points.size();i++)
        {
            QString pname;
            string pLetter = points[i].idxletter;
            pname = QString::fromStdString(pLetter);
            if(pname == tempett_q)
            {
                p_x = points[i].x;
                p_y = points[i].y;
                break;
            }
        }
        painter.drawPoint(p_x,p_y);
        ui->imageLoc->setPixmap(temp);
    }
}

void DiagramText::on_pushButton_clicked()
{
    ui->imgeleListWidget->clear();
    //QStringList imageElement;
    //imageElement.clear();
    parse_image(have_image_info);
    //    ui->imgeleListWidget->addItem("circle O");
    //    ui->imgeleListWidget->addItem("line AB");
    //    ui->imgeleListWidget->addItem("line AC");
    //    ui->imgeleListWidget->addItem("line CD");
    //    ui->imgeleListWidget->addItem("point A");
    //    ui->imgeleListWidget->addItem("point B");
    //    ui->imgeleListWidget->addItem("point C");
    //    ui->imgeleListWidget->addItem("point D");
    //    ui->imgeleListWidget->addItem("point E");
    //    ui->imgeleListWidget->addItem("point F");
    for(int i = 0;i<imgElement.size();i++)
    {
        ui->imgeleListWidget->addItem(imgElement.at(i));
    }
    imgElement.clear();
}
void grammer_read()
{

}

//void grammer_generation()
//{
//    QFile xml_file("ertest.xml");
//    if(!file.open(QFile::WriteOnly | QFile::Text))
//    {
//        std::cerr <<"Error: Can not write file"
//                 <<qPrintable("ertest.xml")<<": "
//                <<qPrintable(xml_file.errorString()) <<std::endl;
//    }
//    QXmlStreamWriter xmlWriter(&xml_file);
//    xmlWriter.setAutoFormatting(true);
//    xmlWriter.writeStartDocument();

//    xmlWriter.writeStartElement("GRAMMAR");
//    xmlWriter.writeAttribute("LANGID","804");

//    xmlWriter.writeStartElement("DEFINE");
//    xmlWriter.writeStartElement("ID");
//    xmlWriter.writeAttribute("NAME","CMD");
//    xmlWriter.writeAttribute("VAL","8");
//    xmlWriter.writeEndElement();//match for define


//// start generate rule
//    xmlWriter.writeStartElement("RULE");
//    xmlWriter.writeAttribute("NAME","COMMAND");
//    xmlWriter.writeAttribute("ID","CMD");
//    xmlWriter.writeAttribute("TOPLEVEL","ACTIVE");

//// start
//    xmlWriter.writeStartElement("L");
//// bring in the parse result to generate a grammer xml
//    for (int i = 0; i < count; i++)
//    {
//        xmlWriter.writeTextElement("P","");
//    }
//    xmlWriter.writeEndElement();//match for L

//    xmlWriter.writeEndElement();//match for RULE

//    xmlWriter.writeEndElement();//match for GRAMMER



//}

void DiagramText::on_pushButton_2_clicked()
{
    QString speech_exe = "SRTest.exe";
    QProcess *speech_process = new QProcess;
    speech_process->startDetached(speech_exe);

}
