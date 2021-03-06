#include <string>
#include <cstring>
#include <algorithm>
#include "mainwindow.h"
#include <iostream>
#include "ui_mainwindow.h"
#include <X11/Xlib.h>
#include <curl/curl.h>
#include <QDebug>
#include "boost/regex.hpp"
std::string img;
std::string Res;
std::string parse;
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
        bool parseHTML(){
        boost::regex regex("<tr><td><\/td><\/tr>.*<tr><td.* style.* left;.*>(.*)<\/td>");
        boost::smatch match;
        if(boost::regex_search(HTML,match,regex)){
            Res = match[0];
            }
        else{
            return false;
        }
       size_t pos = Res.find(".<");
       Res = Res.substr(0,pos);


       for(int i = 0; i < Res.length(); i++){
           if(Res[i] == '<'){

           Res.erase(i, Res.substr(i,Res.length()).find('>')+1);

               }

       }

       Res = Res.substr(87,Res.length());

       return true;
    }

   bool getImage(){

        boost::regex regex("^<\/tr><tr><td.*>(<a.*><img.*\s*src=.*\/yugioh\/.*\s*alt=.*\s*class=.*>)");
        boost::smatch match;

        if(boost::regex_search(HTML,match,regex)){
            img = match[0];
        }

        else{
      return false;
        }

        size_t pos1 = img.find("src=\"");

        size_t pos2 = img.substr(pos1,img.length()).find(" ");

        img = img.substr(pos1,pos2);
        img =  img.substr(5,img.length()-6);

        return true;
   }

};




std::pair<int,int> res = Resolution();

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ShowImg = new QPixmap(500,500);
    ui->setupUi(this);

    search = new QLineEdit(this);
    search->setGeometry(QRect(609,10,121,30));
    search->setStyleSheet("QLineEdit {background-color:#196D8D;color: #59B6DA;border:2px;border-color: #0A3E53;border-radius: 5px; }");
    button = new QPushButton("Search",this);
    button->setGeometry(QRect(740,10,90,30));
    button->setStyleSheet("QPushButton { background-color:#196D8D;color: #59B6DA;border:2px;border-color: #0A3E53;border-radius: 5px;}");
    getData = new QNetworkAccessManager(this);
    connect(button,SIGNAL (clicked()),this,SLOT (card()));

    connect(getData, SIGNAL (finished(QNetworkReply * )),this,SLOT (ImgData(QNetworkReply *)));
    ShowImg = new QPixmap(500,500);
    Pixmap = new QLabel("",this);
    Pixmap->setGeometry(QRect(res.first/25,res.second/17,500,500));
    Description = new QLabel("",this);
    Description->setGeometry(QRect(res.first/5,res.second/12,1000,600));
    setFixedSize(res.first/2,res.second/2);




}

MainWindow::~MainWindow()
{
    delete ui;
}
void ParseString(std::string &cardName){

    for(unsigned int i = 0; i < cardName.length(); i++){
        if(cardName[i] == ' '){
            cardName[i] = '_';
            cardName[i+1] = toupper(cardName[i+1]);
            i++;
        }
        else{
            cardName[i] = tolower(cardName[i]);
        }



}
cardName[0] = toupper(cardName[0]);
std::cout << cardName;

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
    std::string k;

    if(Parser.parseHTML()){
        for(size_t br = Res.find(':'); br != std::string::npos; br = Res.find(':',br) ){
            Res.replace(br,1,"<br>");
        }
         for(size_t i = Res.find(','); i != std::string::npos; i = Res.find(',',i) ){
            Res.replace(i,1,"<br>");
        }
        //QFont font("Wingdings",12); l m a o
        Description->setStyleSheet("color: #0b3b89");
        Description->setFont(font);
        Description->setText(Res.c_str());
        std::cout << Description->fontInfo().family().toStdString();
        std::cout << search->fontInfo().family().toStdString();
        Parser.getImage();
        QUrl url = QUrl(img.c_str());

        QNetworkRequest request(url);
        getData->get(request);
        connect(getData, SIGNAL (finished(QNetworkReply * )),this,SLOT (ImgData(QNetworkReply *)));
    }


    else{
        Description->setText("Sorry Card not found");
        Pixmap->clear();

    }




}
void MainWindow::keyPressEvent(QKeyEvent *enter){
    if((enter->key() == Qt::Key_Enter || enter->key() == Qt::Key_Return) && search->text().toStdString().size() > 1){
       card();
    }
}
void MainWindow::ImgData(QNetworkReply * reply){
image = reply->readAll();
if(ShowImg->loadFromData(image,"PNG") || ShowImg->loadFromData(image,"JPG"))
{
    Pixmap->setPixmap(*ShowImg);

}


}
