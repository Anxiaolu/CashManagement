#ifndef CALCULATOR_DIALOG_H
#define CALCULATOR_DIALOG_H

#include <QDialog>
#include <QLabel>
#include <QAction>
#include <QTextEdit>
#include <QPushButton>
#include <QMainWindow>

namespace Ui {
class calculator_dialog;
}

class calculator_dialog : public QMainWindow
{
    Q_OBJECT
    QAction *action1 ;
        QAction *action2 ;
        QAction *action3 ;
        QAction *action4 ;
        QAction *action5 ;
        QAction *action6 ;
        QAction *action7 ;
        QAction *action8 ;

        QLabel *label1;
        QLabel *label2;

        QTextEdit *showEdit;
        QTextEdit *resultEdit;

        QPushButton *backBt;
        QPushButton *removeBt;
        QPushButton *clearBt;
        QPushButton *sumBt;

        QPushButton *sevenBt;
        QPushButton *eightBt;
        QPushButton *nineBt;
        QPushButton *decBt;

        QPushButton *fourBt;
        QPushButton *fiveBt;
        QPushButton *sixBt;
        QPushButton *starBt;

        QPushButton *oneBt;
        QPushButton *twoBt;
        QPushButton *threeBt;
        QPushButton *divBt;

        QPushButton *_Bt;
        QPushButton *zeroBt;
        QPushButton *pointBt;
        QPushButton *equalBt;

        void mylayout();
        void addMenu();
        void addMenuAction();

public:
    explicit calculator_dialog(QWidget *parent = 0);
    ~calculator_dialog();
private:
    Ui::calculator_dialog *ui;
};

#endif // CALCULATOR_DIALOG_H
