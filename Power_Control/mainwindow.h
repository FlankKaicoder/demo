#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QtSerialPort/QtSerialPort>
#include <QSerialPortInfo>
#include <QString>
#include <QCharRef>
#include <QChar>
#include <QLineEdit>
#include <QLabel>
#include <qcustomplot.h>

//#include <QObject>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //正则表达式处理数据
    void extractValues(const QString &data);
    //将处理好的数据显示到对应控件
    void displayData(QString key,QString value);
    //选择波形显示数据
    void displayWave();
    //判断是否超过阈值
    //void jugement();
    //三通道波形显示
    void qcustomplot();

    void customsplot_init(QString array1);

    void checkbox_change();

    void tableInit();

    void insert_table(QString date, QString data);

    void insert_log(QString log);
    QString LogData;
    QString readData ;//串口接收数据
    QString wavedata ;//波形绘制数据
    QByteArray input_data;
    QTimer *TimerSend_text;
    QTimer *_pTimerUpdate;
    float y_high=100,y_low=0;
    double savedata1;     //数据1
    double savedata2;    //数据2
    double savedata3;    //数据3
    int x=0,y=0,z=0;
    int time;     //数据刷新周期ms
    bool isOk ;
    bool startAuto;


private slots:

    void receive_data();//连接槽函数的程序一定要放在slots里

    void on_but_close_clicked();//关闭端口

    void on_but_Open_clicked();//打开端口

    void on_btn_JianCeChuanKou_clicked();//检测系统内串口信息

    void on_btnReturn_clicked();

    void on_btnClose_clicked();

    void setLED(QLabel* label, int color, int size);

    void on_button_cleardata_clicked();

    void on_button_savedata_clicked();

    void on_button_wave_start_clicked();

    void on_button_wave_stop_clicked();

    void on_button_savedata_2_clicked();

    void on_button_cleardata_2_clicked();

    void on_pushButton_temp_clicked();

    void on_pushButton_V_clicked();

    void on_pushButton_A_clicked();

    void on_comboBox_currentIndexChanged();

private:
    Ui::MainWindow *ui;

    void system_init();//系统初始化函数

    QTimer *TimerUpDate;
    void time_up_date();
    QSerialPort *global_port;//端口函数

    void String2Hex(QString str, QByteArray &senddata);
    char ConvertHexChar(char ch);
};

#endif // MAINWINDOW_H
