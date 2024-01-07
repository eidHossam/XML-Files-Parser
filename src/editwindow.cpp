#include "editwindow.h"
#include <QPushButton>

EditWindow::EditWindow(QWidget *parent)
    : QDialog(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Create a scroll area
    scrollArea = new QScrollArea(this);
    resultTextEdit = new QTextEdit(this);

    // Set the label as the widget for the scroll area
    scrollArea->setWidget(resultTextEdit);
    scrollArea->setWidgetResizable(true);

    // Create a button
    button = new QPushButton("Get Text", this);
    connect(button, &QPushButton::clicked, this, &EditWindow::onButtonClicked);

    layout->addWidget(scrollArea);
    layout->addWidget(button);  // Add the button to the layout
    setLayout(layout);
}

void EditWindow::setTextEdit(const QString &text)
{
    resultTextEdit->setText(text);
}

void EditWindow::onButtonClicked()
{
    emit textAvailable(resultTextEdit->toPlainText());
}
