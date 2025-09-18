#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMouseEvent>  //鼠标事件头文件
#include <QTimer>
#include <QToolButton>
#include <QMenu>
#include <QAction>
#include <QActionGroup>  //以上为添加用到的头文件

struct UserInfoStu{   //用户信息结构体
    QString userName;
    QString passwd;
    QString email;
};

namespace Ui {
class Login;
}

class Login : public QWidget     //类Login是基类QWidget的派生类
{
    Q_OBJECT   //这个宏的作用是启动Qt元对象系统的一些特性，如支持信号和槽，必须放置到类定义的私有区
    
public:        //类定义的共有区，在这个区内声明的槽意味着任何对象都可将信号与之相连接。
    explicit Login(QWidget *parent = 0);
    ~Login();//构造函数，parent指定Login的父窗口部件，parent=0表示窗口部件为一个窗口，否则为parent的子窗口部件

    void init();   //初始化函数
    void get_user_info();//获取用户信息
    void configWindow();//设置窗口
    void init_sql();//初始化数据库
    void set_top_img();//设置图片显示方式函数bool isSandom, int index_img
    void set_button();//设置UI上的按钮
    void set_user_img(bool isSandom, int index_img);//设置UI上用户头像
    void create_menuLanguage();         //设置语言菜单
    void setStyle(const QString &style);//设置style

protected:  //类定义的保护区，在这个区内声明的槽意味着只有当前类及其子类可以将信号与之相连接。

    void mousePressEvent(QMouseEvent *e);//鼠标点击事件
    void mouseMoveEvent(QMouseEvent *e);//鼠标移动事件
    void mouseReleaseEvent();//鼠标释放事件
    //定义这三个函数是为了实现无边框，且可以移动窗体
signals:
    void close();//关闭窗口
    
private slots://类定义的私有区，在这个区内声明的槽意味着只有类自己可以将信号与之相连接。

    void on_btn_login_clicked();    //点击登录按钮
    void on_btn_regist_clicked();   //点击登录按钮
    void slot_minWindow();          //最小化窗口
    void slot_closeWindow();        //关闭窗口
    void slot_getKeyBoard();        //调用屏幕键盘
    void slot_setLanguage();        //设置语言
    void slot_actGrp(QAction* act); //在线状态设置
    void slot_timer1();             //打开程序时从透明逐渐到不透明
    void slot_timer2();             //关闭程序时从不透明逐渐到透明
    void on_cBox_account_activated(int index);//切换账户时显示新的账户及密码
    void on_btn_edit_pwd_clicked(); //修改密码程序
    void refresh();//刷新login界面字符串

private:
    Ui::Login *ui;

    bool m_Drag;  //鼠标拖动
    QPoint m_point; //鼠标指针
    QTimer *timer1, *timer2;
    QStringList userPasswd;         //用户密码

    QToolButton *minBtn;
    QToolButton *closeBbtn;
    QToolButton *setBtn;
    QToolButton *keyBtn;
    QToolButton *status_tBtn;       //在线状态

    QMenu *menu1;                   //语言菜单//QMenu类包含便利功能，用于创建适合用作菜单项的动作。
    QAction *act_chinese;           //QAction类提供了一个抽象的用户界面操作，可以将其插入到小部件中。
    QAction *act_english;

    QMenu *menu2;                   //在线状态
    QAction *act0;                  //在线
    QAction *act1;                  //隐身
    QAction *act2;                  //离线
    QAction *act3;                  //忙碌
    QActionGroup *actGrp;

public:
    UserInfoStu user_info_stu;
    QSqlDatabase db;
};

#endif // LOGIN_H
