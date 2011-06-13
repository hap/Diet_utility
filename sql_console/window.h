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
    virtual void keyPressEvent ( QKeyEvent *  );

};

#endif // WINDOW_H
