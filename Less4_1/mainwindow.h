#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include "qdynamicbutton.h"
#include <QLabel>
#include <QFileDialog>
#include <QProcess>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:    
    void on_pushButton_clicked();
    void slotCustomMenuRequested(QPoint pos);
    void dellDevice();
    void editDevice();
    void windowHide();
    void editBtn();
    void pickFile();
    void startProgram();
signals:

private:   
    Ui::MainWindow *ui;
    QDynamicButton *button;
    QMainWindow *window;
    QLineEdit *txt, *txt2;
    QPushButton *btnAccept, *btnCancel, *btnFile;
    QLabel *lbl1, *lbl2;
    int currentID;

};
#endif // MAINWINDOW_H
