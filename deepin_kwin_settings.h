#ifndef DEEPIN_KWIN_SETTINGS_H
#define DEEPIN_KWIN_SETTINGS_H

#include <QMainWindow>

namespace Ui {
class deepin_kwin_settings;
}

class deepin_kwin_settings : public QMainWindow
{
    Q_OBJECT

public:
    explicit deepin_kwin_settings(QWidget *parent = nullptr);
    ~deepin_kwin_settings();

private slots:
    void on_pushButton_clicked();

private:
    Ui::deepin_kwin_settings *ui;
};

#endif // DEEPIN_KWIN_SETTINGS_H
