#include <QApplication>
#include <bits/stdc++.h>
#include "mainwindow.h" // Make sure this path is correct

using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow w;
    w.show();

    return app.exec();
}
