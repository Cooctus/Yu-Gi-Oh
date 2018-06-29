#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTextBlock>
#include <QLabel>
#include <QLineEdit>
#include "QtNetwork/QNetworkAccessManager"
#include <QtNetwork>
#include <QUrl>
#include <QPixmap>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

     MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:

    Ui::MainWindow *ui;
    QPushButton * button;
    QLabel * Description;
    QLabel * Pixmap;
    QLineEdit  * search;
    QNetworkAccessManager * getData;
    QByteArray image;
    QPixmap * ShowImg;
signals:

public slots:

    void card();
    void ImgData(QNetworkReply * reply);
};

#endif // MAINWINDOW_H
