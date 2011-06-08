#include "window.h"


window::window(QWidget *parent) :
    QWidget(parent)

{
    lay = new QGridLayout;
    this->setLayout(lay);
        panel = new QLabel;
        panel->setText(tr("Enter query string: "));
    lay->addWidget(panel);
        edit = new QLineEdit;
    lay->addWidget(edit);
        b = new QPushButton;
        b->setText(tr("Do"));
    lay->addWidget(b);
    if (!databaseOn(QString("test.db"))) {qDebug()<<"Error at database connection!"<<endl; QApplication::exit(-1);}
    else {qDebug()<<"Database is on now!"<<endl;}

}
bool window::databaseOn(QString dbname){
    db = new QSqlDatabase;
    db->addDatabase("QSQLITE");
    db->setDatabaseName(dbname);
    db->open();
    return db->isValid();
}
void window::b_press(){
    QSqlQuery q;

}
window::~window()
{
    db->close();
}
