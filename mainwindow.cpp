#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QScreen>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTime>

#ifdef Q_OS_WIN
#include "windows.h"
#pragma comment(lib, "user32.lib")
#endif

#ifdef Q_OS_LINUX
#include <X11/Xlib.h>
#endif

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));

    m_nExecutionType = 0;
    m_nScreen_width = 0;
    m_nScreen_height = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_start_clicked()
{
    m_timer->start(ui->spinBox_timer->value());
}

void MainWindow::update()
{
    QString strOprType = "";

    switch (m_nExecutionType) {
    case 0:
    {
        QScreen* screen = QGuiApplication::primaryScreen();
        QRect mm = screen->availableGeometry();
        m_nScreen_width = mm.width();
        m_nScreen_height = mm.height();
        strOprType = "Qt API";
        break;
    }
    case 1:
    {
#ifdef Q_OS_WIN
        m_nScreen_width = GetSystemMetrics(SM_CXSCREEN);
        m_nScreen_height = GetSystemMetrics(SM_CYSCREEN);
        strOprType = "Windows API";
#endif
        break;
    }
    case 2:
    {
#ifdef Q_OS_LINUX
        Display *display = XOpenDisplay(NULL);
        int screen_num = DefaultScreen(display);
        m_nScreen_width = XDisplayWidth(display,screen_num);
        m_nScreen_height = XDisplayHeight(display,screen_num);
        strOprType = "Linux API";
#endif
        break;
    }
    default:
        break;
    }

    QString str = QString("[%1]-> Width: %2, Height: %3  Operation:%4")
            .arg(getSystemTime())
            .arg(m_nScreen_width)
            .arg(m_nScreen_height)
            .arg(strOprType);


    ui->textEdit->append(str);
}

void MainWindow::on_pushButton_clear_clicked()
{
    ui->textEdit->clear();
}

void MainWindow::on_pushButton_stop_clicked()
{
    m_timer->stop();
}

void MainWindow::on_pushButton_Qt_clicked()
{
    m_nExecutionType = 0;
}

void MainWindow::on_pushButton_Win_clicked()
{
    m_nExecutionType = 1;
}

void MainWindow::on_pushButton_Linux_clicked()
{
    m_nExecutionType = 2;
}

void MainWindow::on_pushButton_save_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save Data"), "",
                                                    tr("Data Files (*.txt)"));
    if (filePath.isNull())
        return;

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        QMessageBox::information(this, QString("Hint"),
                                 QString(""));
        return;
    }
    QString data = ui->textEdit->toPlainText();
    file.write(data.toLatin1());
}

QString MainWindow::getSystemTime()
{
    QTime *time = new QTime();
    QString strTime;
    strTime = time->currentTime().toString("HH:mm:ss.zzz");
    return strTime;
}

void MainWindow::on_spinBox_timer_valueChanged(int arg)
{
    if(m_timer->isActive())
        m_timer->start(arg);
}
