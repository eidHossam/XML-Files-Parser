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

    void checkFile();
    void on_decompress_button_clicked();
    void on_fix_data_button_clicked();
    void on_locate_button_clicked();
    void on_json_button_clicked();
    void on_compress_button_clicked();
    void on_show_errors_button_clicked();
    void on_locate_address_button_clicked();
    void on_see_file_data_button_clicked();
    void on_save_current_button_clicked();
    void on_edit_data_button_clicked();
    void updateData(const QString &text);
    void initButtons();
    void on_undo_button_clicked();
    void on_redo_button_clicked();
    void on_save_minified_button_clicked();
    void on_search_word_button_clicked();
    void open_result_window(std::string info);



    void on_graph_info_button_clicked();

    void on_mutual_friends_button_clicked();

    void on_suggest_followers_button_clicked();


    void on_format_button_clicked();

private:
    Ui::MainWindow *ui;
    QPushButton *button_2;
};

#endif // MAINWINDOW_H
