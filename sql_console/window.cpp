#include "window.h"


window::window(QWidget *parent) :
    QWidget(parent)

{
   // qDebug()<<QSqlDatabase::drivers();
    if (!databaseOn(QString("test.db"))) {qDebug()<<db.lastError().text(); QApplication::exit(-1);}
    else {qDebug()<<"Database is on now!"<<endl;}

    modelSelect = new QSqlQueryModel;


    QGridLayout *lay = new QGridLayout;

    viewSelect = new QTableView;
    viewSelect->setModel(modelSelect);
    lay->addWidget(viewSelect,1,0,3,3);

    QLabel *label1 = new QLabel(tr("Enter query string: "));
    lay->addWidget(label1,4,0);

    QLabel *label2 = new QLabel(tr("Output: "));
    lay->addWidget(label2,0,0);

    edit = new QLineEdit;
    lay->addWidget(edit,5,0);

    b = new QPushButton(tr("Do"));
    lay->addWidget(b,5,3);

    this->setLayout(lay);

    connect(b,SIGNAL(clicked()),this,SLOT(b_slot()));

}

bool window::databaseOn(QString dbname){
    db = QSqlDatabase::addDatabase("QSQLITE") ;

    db.setDatabaseName(dbname);
    db.open();
    return db.isValid();
}

void window::execSQL()
{
    QSqlQuery q;
    if(!q.exec((edit->text()))){
        qDebug()<<q.lastError().text();
        modelSelect->clear();
        return;
    }

    if(q.isSelect()){
        modelSelect->setQuery(q);
    }
    // QRegExp reg("^(select|SELECT|sElect|Select|seLect|selEct|seleCt|selecT)");
  //  QString str(&edit->text()) ;
  //  if(str.trimmed().contains(reg)){

  //  }


}

void window::b_slot()
{
   execSQL();
   edit->clear();

}

window::~window()
{
    db.close();
    //delete db;
    delete modelSelect;

}
