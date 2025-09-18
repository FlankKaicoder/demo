#include "login.h"
#include "ui_login.h"
#include "exam.h"
#include "mainwindow.h"
#include "passwdedit.h"
#include "register.h"
#include "systemtrayicon.h"
#include <QMessageBox>
#include <QUrl>
#include <QDesktopServices>
#include <QDir>
#include <QDebug>
#include <QMenu>

float opacity1 = 0.0, opacity2 = 1.0;//打开和关闭窗口透明度设置的变量

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    init();
    //信号与槽的绑定
    connect(this,SIGNAL(close()),this,SLOT(close()));

}

Login::~Login()
{
    delete ui;
}

void Login::init()   //登陆界面初始化
{
    setWindowTitle(tr("登录"));//设置窗口标题

//    ui->btn_edit_pwd->setStyleSheet("background-color:transparent;");
//    ui->btn_regist->setStyleSheet("background-color:transparent;");
//    ui->btn_login->setStyleSheet("background-color:transparent;");

    m_Drag = false;//鼠标拖动

    timer1 = new QTimer;//创建一个定时器类的对象
    timer1->start(7.5);   //设置5微妙启动窗口时间
    timer2 = new QTimer;//创建一个定时器类的对象
    connect(timer1, SIGNAL(timeout()), this, SLOT(slot_timer1()));//timer1启动，时间溢出后运行slot_timer1()函数
    connect(timer2, SIGNAL(timeout()), this, SLOT(slot_timer2()));//timer2启动，时间溢出后运行slot_timer2()函数

    configWindow();//UI界面设置  去边框，最小化，最大化button
    init_sql();//初始化界面密码，帐号的初值

    //init记住密码
    ui->checkBox_rPasswd->setChecked(true);//默认记住密码复选框勾选
    ui->lineEdit_passwd->setEchoMode(QLineEdit::Password);//设置lineEdit_passwd显示模式为密码模式
    /*setEchoMode()函数一共定义了四种显示模式:
        1.QLineEdit::Normal	按照输入的内容正常显示
        2.QLineEdit::NoEcho	不显示任何内容，可以通过my_lineedit->text()得到QLineEdit内容
        3.QLineEdit::Password	密码模式，即输入的字符会转换为特殊字符
        4.QLineEdit::PasswordEchoOnEdit	显示字符时转换为特殊字符，编辑时正常显示字符
    */
}

void Login::get_user_info()//获取当前用户账号密码
{
    user_info_stu.userName.clear();
    user_info_stu.userName = ui->cBox_account->currentText();//文本框中内容赋给结构体中的成员
    user_info_stu.passwd.clear();
    user_info_stu.passwd = ui->lineEdit_passwd->text();
}

void Login::configWindow()//设置窗口和任务栏托盘
{
    // 填充背景图片
     QPalette palette;

     palette.setBrush(/*QPalette::Background*/this->backgroundRole(),
                        QBrush(QPixmap(":/images/background.png")));
     this->setPalette(palette);

    //去掉窗口边框
    setWindowFlags(Qt::FramelessWindowHint);

    //程序init时,设置top ,user img
    set_top_img();//ture设置图片显示为随机显示,false则默认显示1false, 1
    set_user_img(false, 1);//ture设置user图片为随机显示，false则默认显示1

    //设置UI的按钮button
    set_button();

    //设置任务栏系统托盘 start
    QStringList strList;         //QStringList类提供了一个字符串列表
    strList << "Rose" << "Login";//strList : ["Rose","Login"]   login 为设置trayico的显示提示
    QIcon icon(":/images/ico/user1.png");//QIcon类代表图标
    SystemTrayIcon *trayIcon = new SystemTrayIcon(strList, icon, this);
    //托盘程序
    connect(trayIcon, SIGNAL(signal_lang_refresh()), this, SLOT(refresh()));//关联语言设置函数,刷新界面
    //设置任务栏系统托盘 end
    //trayIcon -> show();
}

void Login::init_sql()//数据库初始化
{
    db = QSqlDatabase::addDatabase("QSQLITE"); // 使用 QSQLITE 数据库
    db.setDatabaseName("database.db"); // 设置数据库名称
    qDebug() << "2.数据库初始化开始!";
    if (!db.open()) {
        qDebug() << "数据库初始化打开失败!";
    } else {
        QSqlQuery q;
        QString sql_create_table = "CREATE TABLE IF NOT EXISTS userInfo (name VARCHAR PRIMARY KEY, passwd VARCHAR, email VARCHAR)";
        if (!q.exec(sql_create_table)) {
            qDebug() << "创建 userInfo 表失败!";
        } else {
            qDebug() << "2.userInfo的表创建完成!";
            if (q.exec("insert into userInfo (name, passwd, email) values ('admin', 'admin', 'ding3380@163.com')")) {
                qDebug() << "插入数据失败!";
            } else {
                if (!q.exec("select * from userInfo")) {
                    qDebug() << "查询数据失败!";
                } else {
                    while (q.next()) {
                        QString userName = q.value(0).toString();
                        ui->cBox_account->addItem(userName);
                        QString passwd = q.value(1).toString();
                        userPasswd.append(passwd);
                    }
                    ui->cBox_account->setCurrentIndex(1);
                    ui->lineEdit_passwd->setText(userPasswd.at(1));
                }
            }
        }
        db.close();
    }

}

void Login::set_top_img()//顶部图像设置bool isSandom, int index_img
{

    QString top_img_path=":/images/top_img1.png";
    QImage top_img;
    top_img.load(top_img_path);
    QPixmap top_pic=QPixmap::fromImage(top_img.scaled(ui->label_top_img->width(),
                                                      ui->label_top_img->height()));
                                        ui->label_top_img->setPixmap(top_pic);
    qDebug() << "3.set_top_img()//顶部图像设置!";
}

void Login::set_button()//设置、最小化、关闭按钮设置
{
    //构建最小化、关闭按钮,设置按钮，键盘ico
    minBtn = new QToolButton(this);
    closeBbtn = new QToolButton(this);
    setBtn = new QToolButton(this);
    keyBtn = new QToolButton(this);

    //获取界面的宽度
    int width = this->width();
    //设置最小化、关闭按钮在界面的位置
    minBtn->setGeometry(width-52.5,5,20,20);
    closeBbtn->setGeometry(width-25,5,20,20);
    setBtn->setGeometry(width-80,5,20,20);
    //设置键盘ico坐标
    int x = ui->lineEdit_passwd->x();
    int y = ui->lineEdit_passwd->y();
    int widthkey = ui->lineEdit_passwd->width();
    keyBtn->setGeometry(x+widthkey-20, y+3, 20, 20);

    //设置鼠标移至按钮上的提示信息
    minBtn->setToolTip(tr("最小化"));
    closeBbtn->setToolTip(tr("关闭"));
    setBtn->setToolTip(tr("设置"));
    keyBtn->setToolTip(tr("虚拟键盘"));

    //设置最小化、关闭按钮的样式图标
    minBtn->setIcon(QIcon(":/images/ico/mini.png"));
    minBtn->setStyleSheet("background-color:transparent;");//设置透明背景
    closeBbtn->setIcon(QIcon(":/images/ico/close.png"));
    closeBbtn->setStyleSheet("background-color:transparent;");//设置透明背景
    setBtn->setIcon(QIcon(":/images/ico/setting.png"));
    setBtn->setStyleSheet("background-color:transparent;");//设置透明背景
    keyBtn->setIcon(QIcon(":/images/keyBoard.png"));
    keyBtn->setStyleSheet("background-color:transparent;");//设置透明背景

    //关联最小化、关闭按钮的槽函数,键盘exe
    connect(minBtn, SIGNAL(clicked()), this, SLOT(slot_minWindow()));
    connect(closeBbtn, SIGNAL(clicked()), this, SLOT(slot_closeWindow()));
    connect(keyBtn, SIGNAL(clicked()), this, SLOT(slot_getKeyBoard()));
    connect(setBtn, SIGNAL(clicked()), this, SLOT(slot_setLanguage()));
    create_menuLanguage();      //创建语言菜单
}

void Login::set_user_img(bool isSandom, int index_img)//用户头像设置
{
    //40,182 85 85
    int set_index_img = 1;
    if(isSandom == true)//随机显示userimg
    {

        QTime time_sand;
        time_sand= QTime::currentTime();//获取当前时间
        qsrand(time_sand.msec()+time_sand.second()*1000);
        set_index_img = qrand()%5 + 1 ;//在1-5中选出随机数

    }
    if(isSandom == false) //不随机显示，按index_img显示图片s
    {
        set_index_img = index_img;
    }

    QString user_img_path=":/images/ico/user1.png";
    QImage user_img;
    user_img_path = ":/images/ico/user" + QString::number(set_index_img, 10)  + ".png";
    user_img.load(user_img_path);
    QPixmap img_pic=QPixmap::fromImage(user_img.scaled(ui->label_user_img->width(),
                                                       ui->label_user_img->height()));
                                       ui->label_user_img->setPixmap(img_pic);
}

void Login::create_menuLanguage()//菜单栏-设置
{
    //语言
    act_chinese = new QAction(tr("简体中文"), this);//创建一个新的对象
    act_english = new QAction(tr("English"), this);
    menu1 = new QMenu;
    menu1->addAction(act_chinese);//将语言添加
    menu1->addAction(act_english);
}

/****************实现无边窗且可以移动窗体**************************/
void Login::mousePressEvent(QMouseEvent *e)//鼠标点击事件
{
    if (e->button() == Qt::LeftButton) {       //如果左键按下
        m_Drag = true;
        m_point = e->globalPos() - this->pos();//globalPos()函数返回的是相对屏幕的位置坐标；而pos()则是返回鼠标在当前控件（即捕获该鼠标事件的控件）中的位置
        e->accept(); //e->accept()指它将事件拦截，父控件将无法收到已经被accept过的事件；e->ignore()使得事件能够继续流向父控件
    }
}
void Login::mouseMoveEvent(QMouseEvent *e)//鼠标移动事件
{
    if (m_Drag & (e->buttons() & Qt::LeftButton)) {
        move(e->globalPos() - m_point);//
        e->accept();
    }
}
void Login::mouseReleaseEvent()//鼠标释放事件
{
    m_Drag = false;
}
/**************************************************************/

void Login::on_btn_login_clicked()//登录按钮设置
{
    if(ui->cBox_account->currentText().isEmpty() ||
            ui->lineEdit_passwd->text().isEmpty()){
        QMessageBox::warning(this,tr("警告"),tr("请输入用户名和密码！"));
    }     //弹出信息提示窗
    else
    {
        int is_use_exist_flag = 0;         //判断用户是否存在
        int is_use_nampwd_check_flag = 0;  //判断用户名和密码是否匹配
        get_user_info();

        if(!db.open())
        {
            qDebug() << "用户数据库打开失败!";
        }
        else
        {
            QSqlQuery query;
            query.exec("select * from userInfo");
            while (query.next())
            {
                QString userName = query.value(0).toString();
                QString passwd = query.value(1).toString();

                if(userName == user_info_stu.userName){
                    is_use_exist_flag = true;              //用户存在
                    if(passwd == user_info_stu.passwd){
                        is_use_nampwd_check_flag = true;          //用户名和密码匹配
                       // Exam *e = new Exam;
                        //e->show();
                        MainWindow *e = new MainWindow;  //转到新窗口MainWindow
                        e->show();
                        emit close();//关闭当前窗口
                    }
                }
            }

            if(is_use_exist_flag == false)
            {
                QMessageBox::information(this,tr("提示"),tr("用户不存在！"));
            }
            else
            {
                if(is_use_nampwd_check_flag == false)
                {
                    QMessageBox::warning(this,tr("警告"),tr("用户密码错误！"));
                }
            }
        }

        db.close();
    }
}

void Login::on_btn_regist_clicked()//注册按钮设置
{
    Register r;
    r.setParent(this);      //设置父对象register
   //transmitdb(database);
    r.exec();    //注册页面r，仅仅获取信息.

//    get_user_info();
    if(user_info_stu.userName.isEmpty() || user_info_stu.passwd.isEmpty()){
        QMessageBox::information(this,tr("提示"),tr("请输入用户名和密码！"));
    }
    else
    {
        bool exitFlag = false;       //判断用户是否存在
        if(!db.open())
        {
            qDebug() << "注册用户数据库打开失败!";
        }
        else
        {
            QSqlQuery query;
            query.exec("select * from userInfo");
            while (query.next())
            {
                QString userName = query.value(0).toString();
                QString passwd = query.value(1).toString();
                if(userName == user_info_stu.userName){
                    exitFlag = true;              //用户存在
                }
            }
            if(exitFlag == false){
                query.exec(QString("insert into userInfo values ('%1','%2','%3')")
                           .arg(user_info_stu.userName).arg(user_info_stu.passwd)
                           .arg(user_info_stu.email));

                ui->cBox_account->addItem(user_info_stu.userName);
                userPasswd.append(user_info_stu.passwd);
                QMessageBox::information(this,tr("提示"),tr("注册成功！"));

                query.exec("select * from userInfo");
                while (query.next())
                {
                    QString userName = query.value(0).toString();
                    QString passwd = query.value(1).toString();
                }
            }else{
                QMessageBox::warning(this,tr("警告"),tr("用户已存在！"));
            }
        }
        db.close();
    }
}

void Login::on_btn_edit_pwd_clicked()//修改密码函数
{
    if(ui->cBox_account->currentText().isEmpty() ||
            ui->lineEdit_passwd->text().isEmpty()){
        QMessageBox::information(this,tr("提示"),tr("请输入用户名和密码！"));
    }
    else
    {
        bool is_use_exist_flag = false;       //判断用户是否存在
        bool is_use_nampwd_check_flag = false;//判断用户名和密码是否匹配
        get_user_info();                      //获取当前用户账号密码

        if(!db.open())
        {
            qDebug() << "用户数据库打开失败!";
        }
        else
        {
            QSqlQuery query;//创建数据库表
            query.exec("select * from userInfo");//查询信息，查询完毕它的内部指针会指向返回结果前面的位置。“*”号表明查询表中记录的所有属性。
            if (query.exec())                                   //这条语句执行完后，我们便获得了相应的执行结果，因为获得的结果可能不止一条记录，所以我们称之为结果集。
            {
                while (query.next())
                {
                    QString userName = query.value(0).toString();  //value(0)指创建的数据库中的name,见114行
                    QString passwd = query.value(1).toString();    //value(1)指创建的数据库中的passwd,见114行

                    if(userName == user_info_stu.userName)     //数据库中的用户名userName与当前输入的结构体中的userName对比
                    {
                        is_use_exist_flag = true;              //用户存在
                        if(passwd == user_info_stu.passwd)     //数据库中的密码passwd与当前输入的结构体中的passwd对比
                        {
                            is_use_nampwd_check_flag = true;   //用户名和密码匹配
                            passwdEdit passwd;                 //修改密码，暂不理解
                            passwd.setLogin(this);
                            //this->hide();
                            passwd.exec();
                        }
                    }
                }
            }
            if(is_use_exist_flag == false)
            {
                QMessageBox::information(this,tr("提示"),tr("用户不存在！"));
            }
            else
            {
                if(is_use_nampwd_check_flag == 0){
                    QMessageBox::warning(this,tr("警告"),tr("用户密码错误！"));
                }
            }
        }
        db.close();
    }
}

void Login::slot_minWindow()//最小化函数
{
    this->showMinimized();
}

void Login::slot_closeWindow()//关闭窗口函数
{
    timer2->start(5);  //开始定时器，并设定定时周期,每隔5毫秒就会重启定时器
}

void Login::slot_getKeyBoard()//调用屏幕键盘
{
    QString curPath = QApplication::applicationDirPath();
    curPath.append("/osk.exe");
    QDesktopServices::openUrl(QUrl(curPath, QUrl::TolerantMode));
}

void Login::slot_setLanguage()//设置语言
{
    menu1->exec(QCursor::pos());//菜单在当前鼠标处显示
}

void Login::slot_actGrp(QAction *act)//设置登陆状态.
{
    if (act == act0) {

    } else if (act == act1) {

    } else if (act == act2) {

    } else if (act == act3) {

    }
}

/****************设置打开和关闭窗口时的渐变透明度**************************/
void Login::slot_timer1()//设置打开窗口透明度
{
    if (opacity1 >= 1.0) {
        timer1->stop();
    }else{
        opacity1 += 0.01;
    }
    setWindowOpacity(opacity1);   //打开时opacity1从0.0(完全透明的)到1.0(完全不透明)
}
void Login::slot_timer2()//设置关闭窗口透明度
{
    if (opacity2 <= 0.0) {
        timer2->stop();
        this->close();
    }else{
        opacity2 -= 0.01;
    }
    setWindowOpacity(opacity2);
}
/********************************************************************/

void Login::on_cBox_account_activated(int index)//切换账户时显示新的账户及密码
{
    ui->lineEdit_passwd->setText(userPasswd.at(index));
}

void Login::refresh()//刷新login页面当前的字符串。其它页面无需刷新，因为打开时候，会自动刷新相关字符串。而主窗口不会。
{
    ui->btn_login->setText(tr("登录"));
    ui->btn_edit_pwd->setText(tr("找回密码"));
    ui->btn_regist->setText(tr("注册用户"));
    //ui->checkBox_autoLogin->setText(tr("自动登录"));
    ui->label->setText(tr("记住密码"));
    ui->label_2->setText(tr("自动登录"));

}

