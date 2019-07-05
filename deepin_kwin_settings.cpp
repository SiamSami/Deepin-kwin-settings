#include "deepin_kwin_settings.h"
#include "ui_deepin_kwin_settings.h"
#include <iostream>
#include <fstream>
#include <QListWidgetItem>
#include <QMessageBox>
using namespace std;
QListWidgetItem* checkbox[5];
string home = getenv("HOME");
bool plugins = false;
bool effectcover = false;

deepin_kwin_settings::deepin_kwin_settings(QWidget *parent) :
    DMainWindow(parent),
    ui(new Ui::deepin_kwin_settings)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->gridLayoutWidget);
    checkbox[0] = new QListWidgetItem("Wobbly windows", ui->listWidget);
    checkbox[0]->setCheckState(Qt::Unchecked);
    checkbox[1] = new QListWidgetItem("Blur", ui->listWidget);
    checkbox[1]->setCheckState(Qt::Unchecked);
    checkbox[2] = new QListWidgetItem("Dim screen for Administrator mode", ui->listWidget);
    checkbox[2]->setCheckState(Qt::Unchecked);
    checkbox[3] = new QListWidgetItem("Cover switch", ui->listWidget);
    checkbox[3]->setCheckState(Qt::Unchecked);
    ifstream file(home+"/.config/kwinrc");
    //QString str;
    std::string temp;
    while (getline(file, temp)) {
        if(temp=="[Plugins]"){
            plugins= true;
        }
        if(temp == "[Effect-CoverSwitch]"){
            effectcover = true;
        }
        if(temp=="wobblywindowsEnabled=true"){
            checkbox[0]->setFlags(checkbox[0]->flags() | Qt::ItemIsUserCheckable);
            checkbox[0]->setCheckState(Qt::Checked);
        }
        if(temp=="blurEnabled=true"){
            checkbox[1]->setFlags(checkbox[1]->flags() | Qt::ItemIsUserCheckable);
            checkbox[1]->setCheckState(Qt::Checked);
        }
        if(temp=="kwin4_effect_dimscreenEnabled=true"){
            checkbox[2]->setFlags(checkbox[2]->flags() | Qt::ItemIsUserCheckable);
            checkbox[2]->setCheckState(Qt::Checked);
        }
        if(temp == "coverswitchEnabled=true"){
            checkbox[3]->setFlags(checkbox[3]->flags() | Qt::ItemIsUserCheckable);
            checkbox[3]->setCheckState(Qt::Checked);
        }
    }
    file.close();
}

deepin_kwin_settings::~deepin_kwin_settings()
{
    delete ui;
}

void deepin_kwin_settings::on_pushButton_clicked()
{
    ifstream file(home+"/.config/kwinrc");
    QString backup;
    string temp;
    while (getline(file, temp)) {
        backup.append(QString(temp.c_str())+"\n");
    }
    if(plugins){
        if(checkbox[0]->checkState()){
            backup.replace("wobblywindowsEnabled=false", "wobblywindowsEnabled=true");
        }else {
        backup.replace("wobblywindowsEnabled=true", "wobblywindowsEnabled=false");
        }
        if(checkbox[1]->checkState()){
            backup.replace("blurEnabled=false", "blurEnabled=true");
        }else {
            backup.replace("blurEnabled=true", "blurEnabled=false");
        }
        if(checkbox[2]->checkState()){
            backup.replace("kwin4_effect_dimscreenEnabled=false", "kwin4_effect_dimscreenEnabled=true");
        }else {
            backup.replace("kwin4_effect_dimscreenEnabled=true", "kwin4_effect_dimscreenEnabled=false");
        }
        if(checkbox[3]->checkState()){
            backup.replace("coverswitchEnabled=false","coverswitchEnabled=true");
        }else {
            backup.replace("coverswitchEnabled=true", "coverswitchEnabled=false");
}
    }else {
        if(!effectcover){
            backup.append("[Effect-CoverSwitch]\nReflection=true\nTabBox=true\nTabBoxAlternative=true\n");
        }
        backup.append("[Plugins]\n");
        if(checkbox[0]->checkState()){
            backup.append("wobblywindowsEnabled=true");
        }else {
            backup.append("wobblywindowsEnabled=false");
        }
        if(checkbox[1]->checkState()){
            backup.append("blurEnabled=true");
        }else {
            backup.append("blurEnabled=false");
        }
        if(checkbox[2]->checkState()){
            backup.append("kwin4_effect_dimscreenEnabled=true");
        }else {
            backup.append("kwin4_effect_dimscreenEnabled=false");
        }
        if(checkbox[3]->checkState()){
            backup.append("coverswitchEnabled=true");
        }else {
            backup.append("coverswitchEnabled=false");
}
    }
    file.close();
    ofstream write(home+"/.config/kwinrc");
    write << backup.toStdString() << endl;
    write.close();
    system("kwin_x11 --replace&");
    QMessageBox success;
    success.setWindowTitle("Message");
    success.setText("Done!");
    success.setStandardButtons(QMessageBox::Ok);
    success.exec();
}
