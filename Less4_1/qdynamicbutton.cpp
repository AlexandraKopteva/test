#include "qdynamicbutton.h"

QDynamicButton::QDynamicButton(QWidget *parent) : QPushButton(parent)
{
    ButId++;
    buttonID = ButId;
}
int QDynamicButton::GetID() const
{
    return buttonID;
}
QString QDynamicButton::GetFileName() const
{
    return fileName;
}
void QDynamicButton::SetFileName(QString atr)
{
    fileName = atr;
}
int QDynamicButton::ButId = 0;
