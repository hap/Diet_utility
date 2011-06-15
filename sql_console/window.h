#ifndef WINDOW_H
#define WINDOW_H

#include <QDebug>
#include <QtGui/QApplication>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSqlDatabase>
#include <QtSql>
#include <QTableView>
#include <QKeyEvent>


class window : public QWidget
{
    Q_OBJECT

public:
    explicit window(QWidget *parent = 0);
    ~window();
private slots:
    void b_slot();
private:
    QSqlDatabase db;
    bool databaseOn(QString);
    QSqlQueryModel *modelSelect;
    QTableView *viewSelect;
    QLineEdit *edit;
    QPushButton *b;
    QLabel *log;

    void execSQL();
protected:
    virtual void timerEvent ( QTimerEvent *   );
    virtual void keyPressEvent ( QKeyEvent *  );

};


class pixDelegate : public QItemDelegate
 {
     Q_OBJECT

 public:
     pixDelegate(QObject *parent = 0): QItemDelegate(parent)
    {
    }

     QWidget  *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                           const QModelIndex &index) const;


     void setModelData(QWidget *editor, QAbstractItemModel *model,
                       const QModelIndex &index) const;

     void  setEditorData(QWidget *editor,const QModelIndex &index) const;


 };

#endif // WINDOW_H
