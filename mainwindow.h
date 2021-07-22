#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGlobal>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void update();
    void on_pushButton_start_clicked();
    void on_pushButton_stop_clicked();
    void on_pushButton_Qt_clicked();
    void on_pushButton_Win_clicked();
    void on_pushButton_Linux_clicked();
    void on_pushButton_save_clicked();
    void on_pushButton_clear_clicked();
    QString getSystemTime();

    void on_spinBox_timer_valueChanged(int arg);



private:
    Ui::MainWindow *ui;
    QTimer* m_timer;
    int m_nExecutionType;
    int m_nScreen_width;
    int m_nScreen_height;
};

#endif // MAINWINDOW_H
