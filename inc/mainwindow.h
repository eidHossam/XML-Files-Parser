#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_decompress_button_clicked();

    void on_fix_data_button_clicked();

    void on_locate_button_clicked();

    void on_json_button_clicked();

    void on_compress_button_clicked();

    void on_show_errors_button_clicked();

private:
    Ui::MainWindow *ui;

    QPushButton *button_2;
};

#endif // MAINWINDOW_H
