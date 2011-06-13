#include "window.h"


window::window(QWidget *parent) :
    QWidget(parent)

{

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
    lay->addWidget(edit,5,0,1,3);

    b = new QPushButton(tr("Do"));
    lay->addWidget(b,5,3);

    QLabel *label3 = new QLabel(tr("Log: "));
    lay->addWidget(label3,6,0);

    log = new QLabel(tr(""));
    lay->addWidget(log,6,1);

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
        log->setText(q.lastError().text());
        modelSelect->clear();

        return;
    }

    if(q.isSelect()){
        modelSelect->setQuery(q);
    }

    log->setText(tr("Complete successful"));


}

void window::b_slot()
{
   execSQL();
   edit->clear();
   edit->setFocus();

}

window::~window()
{
    db.close();

    delete modelSelect;

}
