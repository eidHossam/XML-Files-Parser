#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <iostream>
#include "XML_Parser.h"
#include "XML_to_json.h"
#include "Huffman_Coding.h"
#include "resultwindow.h"

using namespace std;

HuffmanCoding huffman;
string compressedData;

void saveToCompressedFile(QString extension, string data) {
    QString filter = "Binary File (*." + extension + ")"; // create filter from extension
    QString filename = QFileDialog::getSaveFileName(0, "Save file", QDir::currentPath(), filter);

    if (!filename.isEmpty()) {
        QFile file(filename);
        if (file.open(QIODevice::WriteOnly)) {
            QDataStream stream(&file);
            QByteArray byteArray;

            // Convert string of '0's and '1's to binary
            for (int i = 0; i < data.size(); i += 8) {
                string byteString = data.substr(i, 8);
                char byte = static_cast<char>(bitset<8>(byteString).to_ulong());
                byteArray.append(byte);
            }

            stream.writeRawData(byteArray.data(), byteArray.size());
            file.close();
        } else {
            // handle error
        }
    } else {
        // handle error
    }
}


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

    QDataStream in(&file);
    QByteArray byteArray = file.readAll();
    string data;

    // Convert binary data to string of '0's and '1's
    for (int i = 0; i < byteArray.size(); ++i) {
        bitset<8> bits(byteArray[i]);
        data += bits.to_string();
    }

    file.close();

    return data;
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



void MainWindow::on_decompress_button_clicked()
{
    string data =huffman.decompress(compressedData);
    QString fileName = ui->address_label->text();
    XML_Parser parser= parseData(fileName);
    string formattedData =parser.get_formatted_xml_data();
    ResultWindow *resultWindow = new ResultWindow(this);
    resultWindow->setLabelText(QString::fromStdString(formattedData));
    resultWindow->exec();

}


void MainWindow::on_fix_data_button_clicked()
{
    QString fileName = ui->address_label->text();
    XML_Parser parser = parseData(fileName);
    string data=parser.fix_xml_data();
    saveToFile("xml",data);
}


void MainWindow::on_locate_button_clicked()
{
    ui->fix_data_button->setEnabled(false);
    ui->show_errors_button->setEnabled(false);
    ui->decompress_button->setEnabled(false);
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open File"), "/home", tr("Files (*.xml)"));
    XML_Parser parser = parseData(fileName);
    if(parser.has_errors()){
        ui->error_label->setText("Has errors");
        ui->fix_data_button->setEnabled(true);
        ui->show_errors_button->setEnabled(true);
    }
    else{
        ui->error_label->setText("No errors");
    }
    ui->address_label->setText(fileName);
    ui->json_button->setEnabled(true);
    ui->compress_button->setEnabled(true);
}




void MainWindow::on_json_button_clicked()
{
    QString fileName = ui->address_label->text();
    XML_Parser parser = parseData(fileName);
    XML_to_json jsonParser(parser);
    string data = jsonParser.json_string();
    saveToFile("json",data);
}


void MainWindow::on_compress_button_clicked()
{
    QString fileName = ui->address_label->text();
    XML_Parser parser = parseData(fileName);
    string data = parser.get_raw_xml_data();
    compressedData = huffman.compress(data);

    ResultWindow *resultWindow = new ResultWindow(this);
    resultWindow->setLabelText(QString::fromStdString(compressedData));
    resultWindow->exec();

    //saveToCompressedFile("bin",compressedData);
    ui->decompress_button->setEnabled(true);
}


void MainWindow::on_show_errors_button_clicked()
{


    QString fileName = ui->address_label->text();
    XML_Parser parser = parseData(fileName);

    //Ysta Htgyb El data bta3tk String w
    //To7otha mkan el parser.get_fixed_xml_data()


    ResultWindow *resultWindow = new ResultWindow(this);
    resultWindow->setLabelText(QString::fromStdString( parser.get_fixed_xml_data()  ));
    resultWindow->exec();

}

