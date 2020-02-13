/*
* Написать планировщик запуска приложений по нажатию клавиши. Программа должна
* иметь возможность редактировать кнопки на форме и программу, которая будет
* запускаться по нажатию этих кнопок.
*/
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    currentID = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    button = new QDynamicButton(this);
    button->setText("Кнопочка " + QString::number(button->GetID()));
    ui->formLayout->addWidget(button);
    button->SetFileName(" ");
    button->setContextMenuPolicy(Qt::CustomContextMenu);    
    connect(button, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slotCustomMenuRequested(QPoint)));
    connect(button, SIGNAL(clicked()), this, SLOT(startProgram()));
}

void MainWindow::slotCustomMenuRequested(QPoint pos)
{
    QDynamicButton *pB = qobject_cast<QDynamicButton*>(sender());
    currentID = pB->GetID();
    QMenu *menu = new QMenu(this);
    QAction *dellDevice = new QAction("Удалить", this);
    QAction *editDevice = new QAction("Редактировать задачу", this);
    menu->addAction(editDevice);
    menu->addAction(dellDevice);
    connect(editDevice, SIGNAL(triggered()), this, SLOT(editDevice()));
    connect(dellDevice, SIGNAL(triggered()), this, SLOT(dellDevice()));
    menu->popup(button->mapToGlobal(pos));
}
void MainWindow::dellDevice()
{
    for(int i = 0; i < ui->formLayout->count(); i++){
        QDynamicButton *button = qobject_cast<QDynamicButton*>(ui->formLayout->itemAt(i)->widget());
        if(button->GetID() == currentID){
            button->hide();
            delete button;
        }
    }
}
void MainWindow::editDevice()
{
    window=new QMainWindow(this);
    window->setWindowTitle("Редактор задачи");
    window->setFixedWidth(220);
    window->setFixedHeight(120);
    window->show();
    lbl1 = new QLabel(window);
    lbl1->move(10,0);
    lbl1->setText("Введите название задачи:");
    lbl1->setFixedWidth(window->width()-10);
    lbl1->show();
    txt = new QLineEdit(window);
    txt->move(10, 25);
    txt->setFixedWidth(window->width()-20);
    txt->setFixedHeight(18);
    txt->show();
    lbl2 = new QLabel(window);
    lbl2->move(10,40);
    lbl2->setText("Программа для запуска задачи:");
    lbl2->setFixedWidth(window->width()-10);
    lbl2->show();
    txt2 = new QLineEdit(window);
    txt2->move(10, 65);
    txt2->setFixedWidth(window->width()-70);
    txt2->setFixedHeight(18);
    txt2->show();
    btnFile = new QPushButton(window);
    btnFile->setText("Обзор");
    btnFile->move(window->width()-60,64);
    btnFile->setFixedWidth(50);
    btnFile->setFixedHeight(20);
    btnFile->show();
    connect(btnFile, SIGNAL(clicked()), this, SLOT(pickFile()));

    btnAccept = new QPushButton(window);
    btnAccept->setText("Применить");
    btnAccept->move(10,90);
    btnAccept->show();
    connect(btnAccept, SIGNAL(clicked()), this, SLOT(editBtn()));
    btnCancel = new QPushButton(window);
    btnCancel->setText("Отменить");
    btnCancel->move(110,90);
    btnCancel->show();
    connect(btnCancel, SIGNAL(clicked()), this, SLOT(windowHide()));
}
void MainWindow::windowHide()
{
    window->hide();
    delete window; //нужно удалить все элементы с формы или только этого достаточно?
}
void MainWindow::editBtn()
{
    for(int i = 0; i < ui->formLayout->count(); i++){
        QDynamicButton *button = qobject_cast<QDynamicButton*>(ui->formLayout->itemAt(i)->widget());
        if(button->GetID() == currentID){
            button->setText(txt->text());
            button->SetFileName(txt2->text());
        }
    }
    window->hide();
    delete window; //нужно удалить все элементы с формы или только этого достаточно?
}
void MainWindow::pickFile()
{
    QString filename = QFileDialog::getOpenFileName(this, "Выбрать файл для запуска", NULL, tr("Все файлы (*.*)"));
    txt2->setText(filename);
}
void MainWindow::startProgram()
{
    QDynamicButton *pB = qobject_cast<QDynamicButton*>(sender());
    QProcess proc;
    proc.start(pB->GetFileName());
    proc.waitForFinished();
}

