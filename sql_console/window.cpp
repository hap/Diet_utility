#include "window.h"


window::window(QWidget *parent) :
    QWidget(parent)

{

    if (!databaseOn(QString("test.db"))) {qDebug()<<db.lastError().text(); QApplication::exit(-1);}
    else {qDebug()<<"Database is on now!"<<endl;}

    modelSelect = new QSqlQueryModel;
    modelSelect->setQuery("");

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

    QSqlQuery q;
    if(!q.exec("create table if not exists photo (id integer primary key autoincrement, body blob);")){
        log->setText(q.lastError().text());
        modelSelect->setQuery("");
        this->startTimer(10000);
        qDebug()<<"11";
        return;
    }



    QPixmap pix("/home/vadim/Diet_utility/Diet_utility/sql_console/Nokia-QtCreator-64.png");

    QByteArray bytes;
    QBuffer buffer(&bytes);
    buffer.open(QIODevice::WriteOnly);
    pix.save(&buffer, "PNG");


   // QPixmap p;
 //     p.loadFromData(bytes,"PNG");
  //  label1->setPixmap(p);

    QString str="insert into photo(body) values('%1');";

    str=str.arg(bytes.data() );
    qDebug()<<bytes ;

    if(!q.exec(str)){
        log->setText(q.lastError().text());
        modelSelect->setQuery("");
        this->startTimer(10000);
        qDebug()<<"12";
        return;
    }


    if(!q.exec("select * from photo;")){
        log->setText(q.lastError().text());
        modelSelect->setQuery("");
        this->startTimer(10000);
        qDebug()<<"13";
        return;
    }





    if(q.isSelect()){
        viewSelect->setItemDelegateForColumn(1,new pixDelegate(this));
        modelSelect->setQuery(q);


    }

    log->setText(tr("Complete successful"));
    this->startTimer(10000);




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
        modelSelect->setQuery("");
        this->startTimer(10000);
        return;
    }

    if(q.isSelect()){
        modelSelect->setQuery(q);
    }

    log->setText(tr("Complete successful"));
    this->startTimer(10000);

}

void window::b_slot()
{
   execSQL();
   edit->clear();
   edit->setFocus();

}

void window::keyPressEvent( QKeyEvent *event )
{


    if(this->focusWidget()==qobject_cast<QWidget*>(edit)){

        if( event->key()+1 == Qt::Key_Enter ){
           qDebug()<<"enter";
           this->b_slot();return;
         }

        if( event->key() == Qt::Key_Down ){
           qDebug()<<"down";
           edit->undo();
           return;
        }

        if( event->key() == Qt::Key_Up ){
           qDebug()<<"Up";
           edit->redo();
           return;
        }

  }

    QWidget::keyPressEvent(event);
}

void window::timerEvent ( QTimerEvent * event )
{
    log->clear();
    this->killTimer(event->timerId());
    return;
}

window::~window()
{
    db.close();

    delete modelSelect;

}

/*
QWidget* pixDelegate::createEditor(QWidget *parent,
     const QStyleOptionViewItem &  option  ,
     const QModelIndex &  index  )   const
 {
     QLabel *editor = new QLabel(parent);
 qDebug()<<"11";
    //QMessageBox::critical(editor,QString("!!"),QString("sss"));
     this->setEditorData(editor,index);


     return editor;
 }

  void pixDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                    const QModelIndex &index) const
 {
     QLabel *edit = static_cast<QLabel*>(editor);

         const QPixmap *p=edit->pixmap();

         QByteArray bytes;
         QBuffer buffer(&bytes);
         buffer.open(QIODevice::WriteOnly);
         p->save(&buffer, "PNG");





         model->setData(index, bytes.data() , Qt::DecorationRole);
 }

 void pixDelegate::setEditorData(QWidget *editor,
                                     const QModelIndex &index) const
 {
     QByteArray value = index.model()->data(index, Qt::DisplayRoleQt::DecorationRole/).toByteArray() ;

         QPixmap p;
           p.loadFromData(value,"PNG");
           QMessageBox::critical(editor,QString("!!"),QString(value));

     QLabel *edit = static_cast<QLabel*>(editor);
         edit->setPixmap(p);;


 }

 */

 void pixDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                             const QModelIndex &index) const
  {

      QByteArray value = index.data(Qt::DisplayRole) .toByteArray() ;
    // qDebug()<<index.data(Qt::DisplayRole).toByteArray();

     QPixmap p;
       p.loadFromData( value ,"PNG");


    QApplication::style()->drawItemPixmap(painter,option.rect,Qt::AlignHCenter,p );




  }

