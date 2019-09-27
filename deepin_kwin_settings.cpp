#include "deepin_kwin_settings.h"
#include "ui_deepin_kwin_settings.h"
#include <iostream>
#include <fstream>
#include <QListWidgetItem>
#include <QMessageBox>
using namespace std;
QListWidgetItem* checkbox[10];
string home = getenv("HOME");
bool plugins = false;
bool effectcover = false;
bool tabBox = false;
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
    checkbox[4] = new QListWidgetItem("Sliding popup animation", ui->listWidget);
    checkbox[4]->setCheckState(Qt::Unchecked);
    checkbox[5] = new QListWidgetItem("Show Desktop while switching through programs", ui->listWidget);
    checkbox[5]->setCheckState(Qt::Unchecked);
    checkbox[6] = new QListWidgetItem("Translucency", ui->listWidget);
    checkbox[6]->setCheckState(Qt::Unchecked);
    checkbox[7] = new QListWidgetItem("Sheet: Make dialogues smoothly fly in and out", ui->listWidget);
    checkbox[7]->setCheckState(Qt::Unchecked);
    checkbox[8] = new QListWidgetItem("Glide windows as they appear or disappear", ui->listWidget);
    checkbox[8]->setCheckState(Qt::Unchecked);
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
        if(temp == "[TabBox]"){
            tabBox = true;
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
        if(temp == "slidingpopupsEnabled[$d]"){
            checkbox[4]->setFlags(checkbox[5]->flags() | Qt::ItemIsUserCheckable);
            checkbox[4]->setCheckState(Qt::Checked);
        }
        if(temp == "ShowDesktopMode=1"){
            checkbox[5]->setFlags(checkbox[6]->flags() | Qt::ItemIsUserCheckable);
            checkbox[5]->setCheckState(Qt::Checked);
        }
        if(temp == "kwin4_effect_translucencyEnabled[$d]"){
            checkbox[6]->setCheckState(Qt::Checked);
        }
        if(temp == "sheetEnabled=true"){
            checkbox[7]->setCheckState(Qt::Checked);
        }
        if(temp == "glideEnabled=true"){
            checkbox[8]->setCheckState(Qt::Checked);
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
        if(checkbox[6]->checkState()){
            backup.replace("kwin4_effect_translucencyEnabled=false", "kwin4_effect_translucencyEnabled[$d]");
        }else {
            backup.replace("kwin4_effect_translucencyEnabled[$d]", "kwin4_effect_translucencyEnabled=false");
        }
        if(checkbox[4]->checkState()){
            backup.replace("slidingpopupsEnabled=false", "slidingpopupsEnabled[$d]");
        }else{
            backup.replace("slidingpopupsEnabled[$d]", "slidingpopupsEnabled=false");
        }
        if(checkbox[7]->checkState()){
            backup.replace("sheetEnabled=false", "sheetEnabled=true");
        }else{
            backup.replace("sheetEnabled=true", "sheetEnabled=false");
        }
        if(checkbox[8]->checkState()){
            backup.replace("glideEnabled=false", "glideEnabled=true");
        }else{
            backup.replace("glideEnabled=true","glideEnabled=false");
        }

    }else {
        if(!effectcover){
            backup.append("[Effect-CoverSwitch]\nReflection=true\nTabBox=true\nTabBoxAlternative=true\n");
        }
        backup.append("[Plugins]\n");
        if(checkbox[0]->checkState()){
            backup.append("wobblywindowsEnabled=true\n");
        }else {
            backup.append("wobblywindowsEnabled=false\n");
        }
        if(checkbox[1]->checkState()){
            backup.append("blurEnabled=true\n");
        }else {
            backup.append("blurEnabled=false\n");
        }
        if(checkbox[2]->checkState()){
            backup.append("kwin4_effect_dimscreenEnabled=true\n");
        }else {
            backup.append("kwin4_effect_dimscreenEnabled=false\n");
        }
        if(checkbox[3]->checkState()){
            backup.append("coverswitchEnabled=true\n");
        }else {
            backup.append("coverswitchEnabled=false\n");
        }
        if(checkbox[4]->checkState()){
            backup.append("slidingpopupsEnabled[$d]\n");
        }else{
            backup.append("slidingpopupsEnabled=false\n");
        }
        if(checkbox[6]->checkState()){
            backup.append("kwin4_effect_translucencyEnabled[$d]");
        }else {
            backup.append("kwin4_effect_translucencyEnabled=false");
        }
        if(checkbox[7]->checkState()){
            backup.append("sheetEnabled=true");
        }else{
            backup.append("sheetEnabled=false");
        }
        if(checkbox[8]->checkState()){
            backup.append("glideEnabled=true");
        }else{
            backup.append("glideEnabled=false");
        }
    }
    if(tabBox){
        if(checkbox[5]->checkState()){
            backup.replace("ShowDesktopMode=0","ShowDesktopMode=1");
        }else {
            backup.replace("ShowDesktopMode=1","ShowDesktopMode=0");
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
