#include "mainwidget.h"
#include "fastcoll.h"
#include<QDebug>


MainWidget::MainWidget(){
    setWindowTitle("Fastcoll@RareKiwi");
    this->resize(1200,500);
    QHBoxLayout *HBoxLayout=new QHBoxLayout(this);
    QGroupBox *Left_Table_Box=showResult();
    QGroupBox *Right_Table_Box=catchFile();

    HBoxLayout->addWidget(Left_Table_Box,4);
    HBoxLayout->addWidget(Right_Table_Box,2);
}


void MainWidget::collision(){
    readFile();
    createfile();
    QMessageBox::information(this,"Fastcoll","Done!!!");
}

void MainWidget::readFile(){
    QString f=QFileDialog::getOpenFileName(this,QString("选择文件"),QString("/"),QString("All Files(*.*)"));
    file=new QFile;
    file->setFileName(f);
    createfile();

}

//生成碰撞文件
void MainWidget::createfile(){


    // 定义随机种子
    seed32_1 = uint32(time(NULL));
    seed32_2 = 0x12345678;
    uint32 block[16];  //存储文件内容
    uint32 IV[4] = { MD5IV[0], MD5IV[1], MD5IV[2], MD5IV[3] };

    //获取目标文件地址
    string prefixfn=QFileInfo(*file).absoluteFilePath().toStdString();
    //获取生成文件地址
    string outfn1=QFileInfo(*file).path().toStdString()+"/"+"result_01_"+QFileInfo(*file).fileName().toStdString();
    string outfn2=QFileInfo(*file).path().toStdString()+"/"+"result_02_"+QFileInfo(*file).fileName().toStdString();
    //生成写入文件流
    ofstream ofs1(outfn1.c_str(), ios::binary);
    ofstream ofs2(outfn2.c_str(), ios::binary);
    // 指定输出路径
    //以二进制形式读取文件内容获取文件信息并生成输出文件名


    //读入文件

    ifstream ifs(prefixfn.c_str(), ios::binary);

    unsigned len = load_block(ifs, block);  //获取文件内容长度
    if (len)
    {
        save_block(ofs1, block);
        save_block(ofs2, block);
        md5_compress(IV, block);
    }

//处理初始值
                    unsigned oldwidth = cout.width(2);
                    char oldfill = cout.fill('0');

                    for (unsigned i = 0; i < 4; ++i)
                    {
                        for (unsigned b = 0; b < 4; ++b)
                        {
                            cout.width(2);
                            cout.fill('0');
                            cout << ((IV[i]>>(b*8))&0xFF);
                        }
                    }
                    cout.width(oldwidth);
                    cout.fill(oldfill);
                    cout << dec << endl;


    //碰撞

                uint32 msg1block0[16];
                uint32 msg1block1[16];
                uint32 msg2block0[16];
                uint32 msg2block1[16];
                find_collision(IV, msg1block0, msg1block1, msg2block0, msg2block1);

                save_block(ofs1, msg1block0);
                save_block(ofs1, msg1block1);
                save_block(ofs2, msg2block0);
                save_block(ofs2, msg2block1);


}

//构建功能面板

QGroupBox * MainWidget::catchFile(){
    QGroupBox * box = new QGroupBox("功能面板");
    QVBoxLayout * VBoxLayout = new QVBoxLayout;

    QGridLayout * Buts = new QGridLayout;
    SubmitBtn=new QPushButton("碰撞");
    ExitBtn=new QPushButton("退出");

    Buts->addWidget(SubmitBtn,0,0);
    Buts->addWidget(ExitBtn,1,0);
    VBoxLayout->addLayout(Buts,4);

    box->setLayout(VBoxLayout);
    //点击碰撞按钮,开始碰撞
    connect(SubmitBtn,&QPushButton::clicked,this,&MainWidget::collision);
    //点击退出按钮，关闭主窗口
    connect(ExitBtn,&QPushButton::clicked,this,&MainWidget::close);
    return box;

}



//构建结果显示面板
QGroupBox * MainWidget::showResult(){
    QGroupBox * box=new QGroupBox("碰撞结果");

    lab=new QLabel("点击碰撞传入目标文件");
    //设置文本框内容居中显示
    lab->setAlignment(Qt::AlignCenter);
    //设置文本框的坐标和尺寸
    lab->setGeometry(100,100,400,400);
    lab->show();
    QHBoxLayout * AutoHBoxLayout=new QHBoxLayout;
    AutoHBoxLayout->addWidget(lab);
    box->setLayout(AutoHBoxLayout);

    return box;
}

