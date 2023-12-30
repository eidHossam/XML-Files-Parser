#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include "XML_Parser.h"
#include "XML_to_json.h"
#include "Huffman_Coding.h"
#include "resultwindow.h"
#include "editwindow.h"
#include "GraphType.h"
#include "NetworkAnalysis.h"
#include <fstream>
using namespace std;



HuffmanCoding huffman;
string compressedData;
XML_Parser parser;
string currentData;
QString fileName;
stack<string> undoStack;
stack<string> redoStack;
GraphType *graph;
NetworkAnalysis *netAnalysis;


void MainWindow::initButtons(){
    ui->fix_data_button->setEnabled(false);
    ui->show_errors_button->setEnabled(false);
    ui->edit_data_button->setEnabled(false);
    ui->save_current_button->setEnabled(false);
    ui->decompress_button->setEnabled(false);
    ui->see_file_data_button->setEnabled(false);
    ui->json_button->setEnabled(false);
    ui->compress_button->setEnabled(false);
    ui->undo_button->setEnabled(false);
    ui->redo_button->setEnabled(false);
    ui->save_minified_button->setEnabled(false);
    ui->search_word_button->setEnabled(false);
}

void MainWindow::checkFile(){
    graph=NULL;
    netAnalysis=NULL;
    if(parser.has_errors()){
        ui->error_label->setText("Has errors");
        ui->fix_data_button->setEnabled(true);
        ui->show_errors_button->setEnabled(true);
    }
    else{
        ui->error_label->setText("No errors");
    }

    ui->address_label->setText(fileName);
    ui->edit_data_button->setEnabled(true);
    ui->save_current_button->setEnabled(true);
    ui->json_button->setEnabled(true);
    ui->compress_button->setEnabled(true);
    ui->see_file_data_button->setEnabled(true);
    ui->save_minified_button->setEnabled(true);
    ui->search_word_button->setEnabled(true);
    currentData = parser.get_fixed_xml_data();
}

void MainWindow::open_result_window(string info){
    ResultWindow *resultWindow = new ResultWindow(this);
    resultWindow->setLabelText(QString::fromStdString( info ));
    resultWindow->exec();
}

NetworkAnalysis *getNetworkAnalysis(){
    XML_Tree *file_tree = parser.build_xml_tree();
    vector<TreeNode *> users = file_tree->root->no_Of_Users_Vector();
    if(!graph){
        graph=new GraphType(users.size());
        graph->build_Graph(file_tree);
    }

    if(!netAnalysis){
        netAnalysis=new NetworkAnalysis(*graph);
    }

    return netAnalysis;
}

bool canOpenFile(string filePath) {

    ifstream file(filePath.c_str());

    if (file.is_open()) {
        return true;
        file.close();
    } else {
        return false;
    }

    return 0;
}


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
     parser= parseData(fileName);
    string formattedData =parser.get_formatted_xml_data();
     open_result_window(formattedData);

}


void MainWindow::on_fix_data_button_clicked()
{
    parser = parseData(fileName);
    string data=parser.fix_xml_data();
    saveToFile("xml",data);
}


void MainWindow::on_locate_button_clicked()
{
    initButtons();
    fileName = QFileDialog::getOpenFileName(this,tr("Open File"), "/home", tr("Files (*.xml)"));
    parser = parseData(fileName);
    checkFile();
}




void MainWindow::on_json_button_clicked()
{
    parser = parseData(fileName);
    XML_to_json jsonParser(parser);
    string data = jsonParser.json_string();
    saveToFile("json",data);
}


void MainWindow::on_compress_button_clicked()
{
    parser = parseData(fileName);
    string data = parser.get_raw_xml_data();
    compressedData = huffman.compress(data);

    open_result_window(compressedData);

    saveToCompressedFile("bin",compressedData);
    ui->decompress_button->setEnabled(true);
}


void MainWindow::on_show_errors_button_clicked()
{
    //Ysta Htgyb El data bta3tk String w
    //To7otha mkan el parser.get_fixed_xml_data()
    vector<string> errors = parser.highlight_errors();
    string errorLines="";
    for(int i=0;i<errors.size();i++){
        errorLines+=errors[i];
        errorLines+="\n\n";
    }

    open_result_window(errorLines);

}


void MainWindow::on_locate_address_button_clicked()
{

    initButtons();
    fileName = ui->address_edit->toPlainText();
    if(canOpenFile(fileName.toStdString())){     parser = parseData(fileName);
        checkFile();}
    else{
        ui->address_label->setText("File can't be opened");
        ui->error_label->setText("File extention is wrong or no file detected");
    }

}


void MainWindow::on_see_file_data_button_clicked()
{


    open_result_window(currentData);
}


void MainWindow::on_save_current_button_clicked()
{

    saveToFile("xml",currentData);
}


void MainWindow::on_edit_data_button_clicked()
{
    EditWindow *editWindow = new EditWindow(this);
    editWindow->setTextEdit(QString::fromStdString(currentData));

    // Connect the textAvailable signal to the updateData slot
    connect(editWindow, &EditWindow::textAvailable, this, &MainWindow::updateData);

    editWindow->exec();
}

void MainWindow::updateData(const QString &text)
{
    undoStack.push(currentData);
    while (!redoStack.empty()) {
        redoStack.pop();
    }
    currentData = text.toStdString();
    ui->undo_button->setEnabled(true);
}


void MainWindow::on_undo_button_clicked()
{
    if (!undoStack.empty()) {

        redoStack.push(currentData);
        ui->redo_button->setEnabled(true);

        currentData=undoStack.top();
        undoStack.pop();
    }

    if(undoStack.empty()){
        ui->undo_button->setEnabled(false);
    }
}


void MainWindow::on_redo_button_clicked()
{
    if (!redoStack.empty()) {

        undoStack.push(currentData);
         ui->undo_button->setEnabled(true);

        currentData=redoStack.top();
        redoStack.pop();
    }

    if(redoStack.empty()){
        ui->redo_button->setEnabled(false);
    }
}


void MainWindow::on_save_minified_button_clicked()
{
    open_result_window(parser.get_raw_xml_data());
    saveToFile("xml",parser.get_raw_xml_data());
}


void MainWindow::on_search_word_button_clicked()
{
    string found= "";
    vector<string> posts = parser.findPosts(ui->search_word_text_edit->toPlainText().toStdString());
    for (const auto& post : posts) {
        found= found + post+"\n";
    }

    open_result_window(found);
}







void MainWindow::on_graph_info_button_clicked()
{
    netAnalysis = getNetworkAnalysis();

    string mostActive =netAnalysis->calculateMostActive();
    string mostInfluncer = netAnalysis->calculateMostInfluencer();

    string info = "Most Active user: "+mostActive +"\nMost Influncer user: "+mostInfluncer;
    open_result_window(info);
}


void MainWindow::on_mutual_friends_button_clicked()
{

    netAnalysis = getNetworkAnalysis();
    string friend1 = ui->user1_text_edit->toPlainText().toStdString();
    string friend2 = ui->user2_text_edit->toPlainText().toStdString();

    vector<string> mutualFriends =netAnalysis->get_mutual_friends(friend1,friend2);
    string info="";
    for(int i=0;i<mutualFriends.size();i++){
        info=info + '-' + mutualFriends[i];
        info+='\n';
    }
    open_result_window(info);
}


void MainWindow::on_suggest_followers_button_clicked()
{
    netAnalysis = getNetworkAnalysis();
    vector<string> suggested =netAnalysis->suggest_new_followers(ui->suggest_text_edit->toPlainText().toStdString());
    string info="";
    for(int i=0;i<suggested.size();i++){
        info=info + '-' + suggested[i];
        info+='\n';
    }
    open_result_window(info);
}





void MainWindow::on_format_button_clicked()
{
    currentData=parser.xml_format();
    open_result_window(currentData);
}

