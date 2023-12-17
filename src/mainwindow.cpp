#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <iostream>
#include "XML_Parser.h"
#include "XML_to_json.h"
#include "XML_Compressor.h"
#include "XML_Decompressor.h"

using namespace std;



void saveToFile(QString extension, string data) {
    QString filter = "Text File (*." + extension + ")"; // create filter from extension
    QString filename = QFileDialog::getSaveFileName(0, "Save file", QDir::currentPath(), filter);

    if (!filename.isEmpty()) {
        QFile file(filename);
        if (file.open(QIODevice::WriteOnly)) {
            QTextStream stream(&file);
            stream << QString::fromStdString(data);
            file.close();
        } else {
            // handle error
        }
    } else {
        // handle error
    }
}

string readFromFile(QString filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        // handle error
        return "";
    }

    QTextStream in(&file);
    QString data = in.readAll();
    file.close();

    return data.toStdString();
}

XML_Parser parseData(QString fileName){
    string _xml_data;
    XML_Parser parser(fileName.toStdString());

    return parser;

}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

        QString fileName = QFileDialog::getOpenFileName(this,tr("Open File"), "/home", tr("Files (*.*)"));
    XML_Parser parser = parseData(fileName);
        if(parser.has_errors()){
        ui->label_2->setText("Has errors");
            ui->fix_data_button->setEnabled(true);
    }
        else{
            ui->label_2->setText("No errors");
        }
    ui->label->setText(fileName);
        ui->pushButton_3->setEnabled(true);
        ui->pushButton_2->setEnabled(true);




}


void MainWindow::on_pushButton_2_clicked()
{
    // Get the file name from the label
    QString fileName = ui->label->text();
    XML_Parser parser = parseData(fileName);
    XML_to_json jsonParser(parser);
    string data = jsonParser.json_string();
    saveToFile("json",data);

    // Call your function
}

void MainWindow::on_pushButton_3_clicked()
{
    QString fileName = ui->label->text();
    XML_Parser parser = parseData(fileName);
    string data = parser.get_raw_xml_data();
    Compressor compressor;
    string compressedData = compressor.compress(data);
    saveToFile("txt",compressedData);
}


void MainWindow::on_decompress_button_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open File"), "/home", tr("Files (*.*)"));
    string compressedData = readFromFile(fileName);
    cout<<compressedData<<endl<<endl<<"--------------------------------------------------------";
    Decompressor decompressor;
    string data =decompressor.decompress(compressedData);
    cout<<data<<endl;
    saveToFile("xml",data);

}


void MainWindow::on_fix_data_button_clicked()
{
    QString fileName = ui->label->text();
    XML_Parser parser = parseData(fileName);
    string data=parser.fix_xml_data();
    saveToFile("xml",data);
}

