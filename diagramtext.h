#ifndef DIAGRAMTEXT_H
#define DIAGRAMTEXT_H

#include <QMainWindow>
#include <QListWidgetItem>
#include "geometry.h"
#include <stdio.h>
#include <iostream>
namespace Ui {
class DiagramText;
}

class DiagramText : public QMainWindow
{
    Q_OBJECT

public:
    explicit DiagramText(QWidget *parent = 0);
    ~DiagramText();

private slots:

    void on_actionTextImport_triggered();

    void on_actionImageImport_triggered();

    void on_textParseBtn_clicked();

    void on_textFilterBtn_clicked();

    void on_elementFilter_clicked();

    void on_imageParse_clicked();

    void on_wordObjectList_itemClicked(QListWidgetItem *item);

    void on_actionImport_Image_Informations_triggered();

    void on_imgeleListWidget_itemClicked(QListWidgetItem *item);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::DiagramText *ui;
    QListWidgetItem *item;
};

#endif // DIAGRAMTEXT_H
