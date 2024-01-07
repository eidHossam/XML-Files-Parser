#ifndef EDITWIDNOW_H
#define EDITWIDNOW_H

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QTextEdit>
#include <QPushButton> // Added this line

class EditWindow : public QDialog
{
    Q_OBJECT

public:
    EditWindow(QWidget *parent = nullptr);
    void setTextEdit(const QString &text);

signals:
    void textAvailable(const QString &text); // Added this line

private slots:
    void onButtonClicked(); // Added this line

private:
    QTextEdit *resultTextEdit;
    QScrollArea *scrollArea;
    QPushButton *button; // Added this line
};

#endif // EDITWIDNOW_H
