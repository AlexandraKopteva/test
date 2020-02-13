#ifndef QDYNAMICBUTTON_H
#define QDYNAMICBUTTON_H

#include <QPushButton>

class QDynamicButton : public QPushButton
{
    Q_OBJECT
public:
    QDynamicButton(QWidget *parent = nullptr);
    ~QDynamicButton(){}

    static int ButId;
    int GetID() const;
    QString GetFileName() const;
    void SetFileName(QString atr);
public slots:
private:
    int buttonID = 0;
    QString fileName;
};

#endif // QDYNAMICBUTTON_H
