#ifndef MAINWIDGET_H
#define MAINWIDGET_H
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListWidget>
#include <QTableWidget>
#include <QGroupBox>
#include <QPushButton>
#include <QLineEdit>
#include <QFile>
#include <QDataStream>
#include <QLabel>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QDataStream>
#include <QFileInfo>
#include <iostream>
using namespace std;
//自定义窗口
class MainWidget : public QWidget{
    Q_OBJECT
public:
    //构建主窗口界面
    MainWidget();

public slots:
    //点击碰撞按钮后，开始碰撞
    void collision();

private:
    //创建主窗口信息面板
    QGroupBox * catchFile();
    QGroupBox * showResult();
    void readFile();
    void createfile();

private:

    //获取目标文件
    QFile *file;
    //提交目标文件路径
    QPushButton * SubmitBtn;
    QPushButton * ExitBtn;

    //显示MD5值的文本
    QLabel * lab;


};




#endif // MAINWIDGET_H
