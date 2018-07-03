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
#include <QKeyEvent>
#include <QStyle>
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
    void keyPressEvent(QKeyEvent *enter);

signals:

private slots:

    void card();
    void ImgData(QNetworkReply * reply);
};

#endif // MAINWINDOW_H
