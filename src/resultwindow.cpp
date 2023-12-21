#include "resultwindow.h"

ResultWindow::ResultWindow(QWidget *parent)
    : QDialog(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Create a scroll area
    scrollArea = new QScrollArea(this);
    resultLabel = new QLabel(this);

    // Set the label as the widget for the scroll area
    scrollArea->setWidget(resultLabel);
    scrollArea->setWidgetResizable(true);

    layout->addWidget(scrollArea);
    setLayout(layout);
}

void ResultWindow::setLabelText(const QString &text)
{
    resultLabel->setText(text);
}
