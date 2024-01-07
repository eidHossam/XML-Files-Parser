#ifndef RESULTWINDOW_H
#define RESULTWINDOW_H

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QScrollArea>

class ResultWindow : public QDialog
{
    Q_OBJECT

public:
    ResultWindow(QWidget *parent = nullptr);
    void setLabelText(const QString &text);

private:
    QLabel *resultLabel;
    QScrollArea *scrollArea;
};

#endif // RESULTWINDOW_H
