#include <string>
#include <cstring>
#include <algorithm>
#include "mainwindow.h"
#include <iostream>
#include "ui_mainwindow.h"
#include <X11/Xlib.h>
#include <curl/curl.h>
#include "boost/regex.hpp"
#include <regex>
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}
std::pair<int,int> Resolution(){
    Display * dis = XOpenDisplay(NULL);
    Screen * scr = DefaultScreenOfDisplay(dis);
    std::pair<int,int> pair (scr->width,scr->height);
    return pair;
}



class HTMLParse{
    std::string HTML;
public:
    HTMLParse(std::string html){
        HTML = html;
    }
    std::string parseHTML(){
        boost::regex regex("<tr><td><\/td><\/tr>.*<tr><td.* style.* left;.*>(.*)<\/td><\/tr><\/table>");
        boost::smatch match;
        std::string Res;
        if(boost::regex_search(HTML,match,regex)){
            Res = match[0];
            }
       size_t pos = Res.find('.');
       return Res.substr(0,pos);

    }
    std::string getImage(){

        boost::regex regex("^<\/tr><tr><td.*>(<a.*><img.*\s*src=.*\/yugioh\/.*\s*alt=.*\s*class=.*><\/a>)");
        boost::smatch match;
        std::string img;
        if(boost::regex_search(HTML,match,regex)){
            img = match[0];
        }

        else{
            std::cout << "failed";
        }

        size_t pos1 = img.find("src=\"");

        size_t pos2 = img.substr(pos1,img.length()).find(" ");
        img = img.substr(pos1,pos2).substr(5,img.substr(pos1,pos2).length());
        return img.substr(0,img.size()-1);
}

};





MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    std::pair<int,int> res = Resolution();
    search = new QLineEdit(this);
    search->setGeometry(QRect(res.first*.22,50,150,25));
    button = new QPushButton("Search",this);
    button->setGeometry(QRect(res.first*.3,50,75,25));
    Description = new QLabel("",this);
    Description->setGeometry(QRect(res.first/2.7,res.second/6,1000,600));
    getData = new QNetworkAccessManager(this);
    //image = new QImage(res.first/10,res.second/2,QImage::Format_RGB32);
    connect(button,SIGNAL (clicked()),this,SLOT (card()));
    ShowImg = new QPixmap(500,500);
    ShowImg->loadFromData(image,"PNG");
    Pixmap = new QLabel("",this);
    Pixmap->setGeometry(QRect(500,500,500,500));
    Pixmap->setPixmap(*ShowImg);
    setFixedSize(res.first,res.second);

}

MainWindow::~MainWindow()
{
    delete ui;
}
void ParseString(std::string &cardName){
    for(unsigned int i = 0; i < cardName.length(); i++){
        if(cardName[i] == ' '){
            cardName[i] = '_';
        }


    }
}

std::string getHTML(std::string cardName){
    CURLcode data;
    std::string Response = "";
    CURL* curl = curl_easy_init();
    curl_global_init(CURL_GLOBAL_DEFAULT);
    std::string url =  "http://yugioh.wikia.com/wiki/" + cardName;
    if(curl){
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &Response);

    data = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    }
    return Response;
    }




void MainWindow::card(){
    std::string cardName =      search->text().toStdString();
    ParseString(cardName);
    std::string HTML = getHTML(cardName);
    HTMLParse Parser(HTML);
    std::string desc = Parser.parseHTML();
    std::string img = Parser.getImage();
    img = img.substr(0,img.find(".png"));

    std::cout << img.c_str();
    connect(getData, SIGNAL (finished(QNetworkReply * )),this,SLOT (ImgBytes(QNetworkReply *)));
    QUrl url = QUrl(img.c_str());
    QNetworkRequest request(url);
    getData->get(request);
    Description->setText(desc.c_str());
    std::cout << image.size();

}
void MainWindow::ImgData(QNetworkReply * reply){
image = reply->readAll();
std::cout << reply;
}
