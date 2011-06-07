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


class window : public QWidget
{
    Q_OBJECT

public:
    explicit window(QWidget *parent = 0);
    ~window();

private:
    QSqlDatabase *db;
    bool databaseOn(QString);
    QGridLayout *lay;
    QLabel *panel;
    QLineEdit *edit;
    QPushButton *b;
    void b_press();

};

#endif // WINDOW_H
