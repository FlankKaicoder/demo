#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPushButton"
#include "iconhelper.h"
#include <QTimer>
#include <QFile>
#include "qcustomplot.h"
#include <QRandomGenerator>
#include <QRegularExpression>

#define iconSize    50
#define iconWidth   100
#define iconHeight  70
#define navBtnWidth 45
#define navIcoWidth 18

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);//初始化QLineEdit指针
    system_init();//系统初始化
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::extractValues(const QString &data)
{
    QRegularExpression regex(
            R"(dc\d+\.(u\d)=([0-9.]+)v|dc\d+\.(i\d)=([0-9.]+)a|dc+(\d+\.temp)=([0-9.]+)degC)"
        );

        QRegularExpressionMatchIterator i = regex.globalMatch(data);
        while (i.hasNext()) {
            QRegularExpressionMatch match = i.next();
            if (match.hasMatch()) {
                QString key = match.captured(1);
                if (key.isEmpty()) key = match.captured(3);
                if (key.isEmpty()) key = match.captured(5);

                QString value = match.captured(2);
                if (value.isEmpty()) value = match.captured(4);
                if (value.isEmpty()) value = match.captured(6);
                qDebug() << key << "=" << value;
                displayData(key,value);
            }
        }
}

void MainWindow::displayData(QString key, QString value)
{
    float floatValue = value.toFloat();
    float intValueV,intValueA,intValueT;
    intValueV = ui->lineedit_V_value->text().toFloat();
    intValueA = ui->lineedit_A_value->text().toFloat();
    intValueT = ui->lineedit_temp_value->text().toFloat();
    if(key=="u0"){
        ui->lcdNumber_v->display(floatValue);
        if(floatValue>intValueV){
            setLED(ui->led1_v1, 1, 14);
        }else {
            setLED(ui->led1_v1, 2, 14);
        }
    }else if(key=="u1"){
        ui->lcdNumber_v_2->display(floatValue);
        if(floatValue>intValueV){
            setLED(ui->led1_v2, 1, 14);
        }else {
            setLED(ui->led1_v2, 2, 14);
        }
    }else if(key=="u2"){
        ui->lcdNumber_v_3->display(floatValue);
        if(floatValue>intValueV){
            setLED(ui->led1_v3, 1, 14);
        }else {
            setLED(ui->led1_v3, 2, 14);
        }
    }else if(key=="u3"){
        ui->lcdNumber_v_4->display(floatValue);
        if(floatValue>intValueV){
            setLED(ui->led1_v4, 1, 14);
        }else {
            setLED(ui->led1_v4, 2, 14);
        }
    }else if(key=="i0"){
        ui->lcdNumber_a->display(floatValue);
        if(floatValue>intValueA){
            setLED(ui->led1_a1, 1, 14);
        }else {
            setLED(ui->led1_a1, 2, 14);
        }
    }else if(key=="i1"){
        ui->lcdNumber_a_2->display(floatValue);
        if(floatValue>intValueA){
            setLED(ui->led1_a2, 1, 14);
        }else {
            setLED(ui->led1_a2, 2, 14);
        }
    }else if(key=="i2"){
        ui->lcdNumber_a_3->display(floatValue);
        if(floatValue>intValueA){
            setLED(ui->led1_a3, 1, 14);
        }else {
            setLED(ui->led1_a3, 2, 14);
        }
    }else if(key=="i3"){
        ui->lcdNumber_a_4->display(floatValue);
        if(floatValue>intValueA){
            setLED(ui->led1_a4, 1, 14);
        }else {
            setLED(ui->led1_a4, 2, 14);
        }
    }else if(key=="1.temp"){
        ui->lcdNumber_t_1->display(floatValue);
        if(floatValue>intValueT){
            setLED(ui->led1_t1, 1, 14);
        }else {
            setLED(ui->led1_t1, 2, 14);
        }
    }else if(key=="2.temp"){
        ui->lcdNumber_t_2->display(floatValue);
        if(floatValue>intValueT){
            setLED(ui->led1_t2, 1, 14);
        }else {
            setLED(ui->led1_t2, 2, 14);
        }
    }else if(key=="3.temp"){
        ui->lcdNumber_t_3->display(floatValue);
        if(floatValue>intValueT){
            setLED(ui->led1_t3, 1, 14);
        }else {
            setLED(ui->led1_t3, 2, 14);
        }
    }else if(key=="4.temp"){
        ui->lcdNumber_t_4->display(floatValue);
        if(floatValue>intValueT){
            setLED(ui->led1_t4, 1, 14);
        }else {
            setLED(ui->led1_t4, 2, 14);
        }
    }else if(key=="5.temp"){
        ui->lcdNumber_t_5->display(floatValue);
        if(floatValue>intValueT){
            setLED(ui->led1_t5, 1, 14);
        }else {
            setLED(ui->led1_t5, 2, 14);
        }
    }else if(key=="6.temp"){
        ui->lcdNumber_t_6->display(floatValue);
        if(floatValue>intValueT){
            setLED(ui->led1_t6, 1, 14);
        }else {
            setLED(ui->led1_t6, 2, 14);
        }
    }else if(key=="7.temp"){
        ui->lcdNumber_t_7->display(floatValue);
        if(floatValue>intValueT){
            setLED(ui->led1_t7, 1, 14);
        }else {
            setLED(ui->led1_t7, 2, 14);
        }
    }else if(key=="8.temp"){
        ui->lcdNumber_t_8->display(floatValue);
        if(floatValue>intValueT){
            setLED(ui->led1_t8, 1, 14);
        }else {
            setLED(ui->led1_t8, 2, 14);
        }
    }
}

void MainWindow::displayWave()
{
    double value;
    int index = ui->comboBox->currentIndex();
    switch (index) {
    case 1:
        value = ui->lcdNumber_t_1->value();
        wavedata = QString::number(value);
        break;
    case 2:
        value = ui->lcdNumber_t_2->value();
        wavedata = QString::number(value);
        break;
    case 3:
        value = ui->lcdNumber_t_3->value();
        wavedata = QString::number(value);
        break;
    case 4:
        value = ui->lcdNumber_t_4->value();
        wavedata = QString::number(value);
        break;
    case 5:
        value = ui->lcdNumber_t_5->value();
        wavedata = QString::number(value);
        break;
    case 6:
        value = ui->lcdNumber_t_6->value();
        wavedata = QString::number(value);
        break;
    case 7:
        value = ui->lcdNumber_t_7->value();
        wavedata = QString::number(value);
        break;
    case 8:
        value = ui->lcdNumber_t_8->value();
        wavedata = QString::number(value);
        break;
    default:
        wavedata = "";
        break;
    }
}


void MainWindow::system_init()//界面初始化（导航栏、波形表）
{
    global_port = new QSerialPort(this);
    //n,8,1
    global_port->setParity(QSerialPort::NoParity);
    global_port->setDataBits(QSerialPort::Data8);
    global_port->setStopBits(QSerialPort::OneStop);



    ui->labTitle->setText("电源老化监控上位机");
    this->setWindowTitle(ui->labTitle->text());
    this->setProperty("canMove", true);
    this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
    ui->widgetTop->setProperty("flag", "nav");
    ui->widgetTop->setFixedHeight(40);

    IconHelper::Instance()->setIcon(ui->btnReturn, 0xf147, navIcoWidth);
    IconHelper::Instance()->setIcon(ui->btnClose, 0xf057, navIcoWidth);//在ttf文件中选择合适的Iconfont

    QStringList qss;
    //全局无焦点虚边框,全局文字颜色,全局字号
    qss.append(QString("*{outline:0px;color:#130c0e;}"));
    //主窗体背景
    //qss.append(QString("QWidget#centralWidget{border-image:url(%1);}").arg(":/images/main.jpg"));
    //标题字体大小
    qss.append(QString("QLabel#labTitle{font:%1px;}").arg(navIcoWidth));
    //顶部导航
    qss.append(QString("QWidget[flag=\"nav\"]{background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,"
                       "stop:0 %1,stop:1 %2);}").arg("#fab27b").arg("#65c294"));
    qss.append(QString("QWidget[flag=\"nav\"] QAbstractButton{background:none;border:none;"
                       "min-width:%1px;max-width:%1px;}").arg(navBtnWidth));
    this->setStyleSheet(qss.join(""));

    if(!global_port->isOpen())
        setLED(ui->led1, 1, 14);//设置LED1为红色

    ui->lineedit_V_value->setText("10");
    ui->lineedit_A_value->setText("10");
    ui->lineedit_temp_value->setText("100");

    ui->auto_time_wave->setText("100");//设定默认波形刷新周期为200ms
    ui->button_wave_stop->setEnabled(false);
    startAuto = false;
    isOk = false;
    time_up_date();
    tableInit();
    TimerUpDate = new QTimer(this);
    connect(TimerUpDate, &QTimer::timeout, this, [=](){time_up_date();});
    TimerUpDate -> start(1000);//每隔一秒更新一次当前时间
    connect(global_port, SIGNAL(readyRead()), this, SLOT(receive_data()));    
    connect(ui->checkBox_X,&QCheckBox::stateChanged,this,&MainWindow::checkbox_change);
    connect(ui->checkBox_Y,&QCheckBox::stateChanged,this,&MainWindow::checkbox_change);
    connect(ui->checkBox_XY,&QCheckBox::stateChanged,this,&MainWindow::checkbox_change);
}

void MainWindow::qcustomplot()
{
    ui->widget_qcus->addGraph();
    ui->widget_qcus->graph(0)->setPen(QPen(Qt::red,2));
    ui->widget_qcus->graph(0)->setAntialiasedFill(false);

    //坐标轴1设置
    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%m:%s");             //时间格式：  秒
    ui->widget_qcus->xAxis->setTicker(timeTicker);       // 横坐标显示时间
    ui->widget_qcus->axisRect()->setupFullAxesBox();     //坐标为矩
    // x轴设置

    ui->widget_qcus->xAxis->setLabel("时间(s)");         // 设置横轴标签
    ui->widget_qcus->yAxis->setLabel("温度(℃)");
    ui->widget_qcus->yAxis->setRange(0,100);
    ui->widget_qcus->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);    //允许可缩放，移动
    QList < QCPAxis *>  xis;
    xis.append(ui->widget_qcus->xAxis);
    ui->widget_qcus->axisRect()->setRangeZoomAxes(xis);

    // 轴随动
    connect(ui->widget_qcus->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->widget_qcus->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->widget_qcus->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->widget_qcus->yAxis2, SLOT(setRange(QCPRange)));
    // 实时更新槽函数
    _pTimerUpdate = new QTimer(this);
    connect(_pTimerUpdate, &QTimer::timeout, this, [=](){
        displayWave();
        customsplot_init(wavedata);//添加判断语句，确定显示波形
    });
}

void MainWindow::customsplot_init(QString array1)//波形显示
{
    savedata1 = array1.toDouble();
    static QTime time(QTime::currentTime());        //获取当前时间
    double mytime = time.elapsed()/1000.0;
    static double lastPointKey = 0;

    if (mytime-lastPointKey > 0.002) //大于2ms添加一个数据
    {
        ui->widget_qcus->graph(0)->addData(mytime, savedata1);      //加到右侧数据中
    }
    ui->widget_qcus->xAxis->setRange(mytime, 10, Qt::AlignRight);        //设置x轴范围
    ui->widget_qcus->replot();       //画图
    insert_table(ui->current_day->text(),array1);
    QList < QCPAxis *>  axis_x,axis_y,axis_xy;// 缩放轴
    axis_x.append(ui->widget_qcus->xAxis);
    axis_y.append(ui->widget_qcus->yAxis);
    axis_xy.append(ui->widget_qcus->xAxis);
    axis_xy.append(ui->widget_qcus->yAxis);
    if(ui->checkBox_X->checkState())
    {
        ui->widget_qcus->axisRect()->setRangeZoomAxes(axis_x);
    }
    if(ui->checkBox_Y->checkState())
    {
        ui->widget_qcus->axisRect()->setRangeZoomAxes(axis_y);
    }
    if(ui->checkBox_XY->checkState())
    {
        ui->widget_qcus->axisRect()->setRangeZoomAxes(axis_xy);
    }
}

void MainWindow::checkbox_change()// 缩放轴
{
    QList < QCPAxis *>  axis_x,axis_y,axis_xy;
    axis_x.append(ui->widget_qcus->xAxis);
    axis_y.append(ui->widget_qcus->yAxis);
    axis_xy.append(ui->widget_qcus->xAxis);
    axis_xy.append(ui->widget_qcus->yAxis);
    if(ui->checkBox_X->checkState())
    {
       ui->widget_qcus->axisRect()->setRangeZoomAxes(axis_x);
    }
    if(ui->checkBox_Y->checkState())
    {
       ui->widget_qcus->axisRect()->setRangeZoomAxes(axis_y);
    }
    if(ui->checkBox_XY->checkState())
    {
       ui->widget_qcus->axisRect()->setRangeZoomAxes(axis_xy);
    }

}

void MainWindow::tableInit()//表格初始化
{
    // 单选框
    QButtonGroup* pButtonGroup = new QButtonGroup(this);
    pButtonGroup->addButton(ui->checkBox_X,1);
    pButtonGroup->addButton(ui->checkBox_Y,2);
    pButtonGroup->addButton(ui->checkBox_XY,3);

    // 表格初始化
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setAlternatingRowColors(true);     //设置隔行变颜色
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);       //选中整行
    //设置表头
    QStringList header;
    header<<tr("时间")<<tr("温度");
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->setColumnWidth(0,115);
    ui->tableWidget->setColumnWidth(0,115);
}

void MainWindow::receive_data()//接收数据
{
    readData=global_port->readAll();
    extractValues(readData);
    if(startAuto){
        //ui->lineedit_A->setText(wavedata1);
    }
}

void MainWindow::time_up_date()//获取当前时间
{
    QDateTime time = QDateTime::currentDateTime();
    QString str= time.toString("yyyy-MM-dd");//"yyyy-MM-dd hh:mm:ss dddd"
    QString str1 = time.toString("hh:mm:ss");
    QString tm = time.toString("yyyy-MM-dd hh:mm:ss");//"yyyy-MM-dd hh:mm:ss dddd"
    ui->current_day->setText(tm);
}

void MainWindow::String2Hex(QString str, QByteArray &senddata)//将QString类型字符串转化为QByteArray十六进制数组类型
{
    int hexdata,lowhexdata;
    int hexdatalen = 0;
    int len = str.length();
    senddata.resize(len/2);
    char lstr,hstr;
    for(int x=0; x<len; )
    {
        //char lstr,
        //hstr=str[x].toAscii();//qt4

        hstr=str[x].toLatin1();//qt5
        if(hstr == ' ')
        {
            x++;
            continue;
        }
        x++;
        if(x >= len)
            break;
        lstr = str[x].toLatin1();//qt5
        hexdata = ConvertHexChar(hstr);
        lowhexdata = ConvertHexChar(lstr);
        if((hexdata == 16) || (lowhexdata == 16))
            break;
        else
            hexdata = hexdata*16+lowhexdata;
        x++;
        senddata[hexdatalen] = (char)hexdata;
        hexdatalen++;
    }
    senddata.resize(hexdatalen);
}

char MainWindow::ConvertHexChar(char ch)//进制转换
{
    if((ch >= '0') && (ch <= '9'))
        return ch-0x30;
    else if((ch >= 'A') && (ch <= 'F'))
        return ch-'A'+10;
    else if((ch >= 'a') && (ch <= 'f'))
        return ch-'a'+10;
    else return (-1);
}

void MainWindow::on_btn_JianCeChuanKou_clicked()//检测串口
{
    QString log = "检测串口";
    insert_log(log);
    ui->com_Port_no->clear();//清空当前列表
    qDebug() << "清空当前列表成功！";//检索端口
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        ui->com_Port_no->addItem(info.portName());
    }
}

void MainWindow::on_but_close_clicked()//关闭串口
{
    QString log = "关闭串口";
    insert_log(log);
    global_port->close();
    setLED(ui->led1, 1, 14);//设置LED1为红色
    isOk = false;
}

void MainWindow::on_but_Open_clicked()//打开串口
{
    QString log = "打开串口";
    insert_log(log);
    global_port->setPortName(ui->com_Port_no->currentText());//设置端口号
    qDebug()<<"当前端口号为："<<ui->com_Port_no->currentText();
    global_port->setBaudRate(ui->com_bot->currentText().toInt());//设置波特率
    qDebug()<<"当前波特率为："<<ui->com_bot->currentText().toInt();
    global_port->open(QIODevice::ReadWrite);//读写模式打开串口
    if(global_port->isOpen()){
        setLED(ui->led1, 2, 14);//设置LED1为绿色
        isOk = true;
    }
}

void MainWindow::on_btnReturn_clicked()//窗口最小化
{
    this->setWindowState(Qt::WindowMinimized);
}

void MainWindow::on_btnClose_clicked()//关闭窗口
{
    global_port->close();
    exit(0);
}

void MainWindow::setLED(QLabel* label, int color, int size)//指示灯控件
{
    // 该函数将label控件变成一个圆形指示灯，需要指定颜色color以及直径size
    // color 0:grey 1:red 2:green 3:yellow
    // size  单位是像素
    // 将label中的文字清空
    label->setText("");
    // 先设置矩形大小
    // 如果ui界面设置的label大小比最小宽度和高度小，矩形将被设置为最小宽度和最小高度；
    // 如果ui界面设置的label大小比最小宽度和高度大，矩形将被设置为最大宽度和最大高度；
    QString min_width = QString("min-width: %1px;").arg(size);              // 最小宽度：size
    QString min_height = QString("min-height: %1px;").arg(size);            // 最小高度：size
    QString max_width = QString("max-width: %1px;").arg(size);              // 最小宽度：size
    QString max_height = QString("max-height: %1px;").arg(size);            // 最小高度：size
    // 再设置边界形状及边框
    QString border_radius = QString("border-radius: %1px;").arg(size/2);    // 边框是圆角，半径为size/2
    QString border = QString("border:1px solid black;");                    // 边框为1px黑色
    // 最后设置背景颜色
    QString background = "background-color:";
    switch (color) {
    case 0:
        background += "rgb(190,190,190)";        // 灰色
        break;
    case 1:
        background += "rgb(255,0,0)";        // 红色
        break;
    case 2:
        background += "rgb(0,255,0)";// 绿色
        break;
    case 3:
        background += "rgb(255,255,0)";// 黄色
        break;
    default:
        break;
    }
    const QString SheetStyle = min_width + min_height + max_width + max_height + border_radius + border + background;
    label->setStyleSheet(SheetStyle);
}

void MainWindow::insert_table(QString date, QString data)// 插入数据至波形表1
{
    update();
    int row_count = ui->tableWidget->rowCount();   //获取总行数
    ui->tableWidget->insertRow(row_count);         //插入行
    QTableWidgetItem *item0 = new QTableWidgetItem();
    QTableWidgetItem *item1 = new QTableWidgetItem();
    item0->setText(date);
    item1->setText(data);
    ui->tableWidget->setItem(row_count,0,item0);
    ui->tableWidget->setItem(row_count,1,item1);
    ui->tableWidget->scrollToBottom();
}

void MainWindow::on_button_savedata_clicked()//保存波形表1数据
{
    QString log = "保存波形表数据";
    insert_log(log);
    QString filename = QFileDialog::getExistingDirectory(this,tr("file dialog"),"./logdata");
   //文件名  E:/QT/login-master/login-master/
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString date = time.toString("MM-dd-hh-mm"); //设置显示格式
    filename +="save"+ date+".txt";
    //文件对象
    QFile file(filename);
    //只写方式打开
    if(!file.open(QFile::WriteOnly | QFile::Text))      //只写方式
    {
        QMessageBox::warning(this,tr("double file edit"),tr("no write ").arg(filename).arg(file.errorString()));
        return ;
    }
    //文件流对象
    QTextStream out(&file);
    //遍历数据
    int romcount = ui->tableWidget->rowCount();     //获取总行数
    for(int x = 0; x < romcount; x++)
    {
        QString rowstring;
        for(int j = 0; j < 2; j++)
        {
            rowstring += ui->tableWidget->item(x,j)->text();
            rowstring += "  ";
        }
        rowstring += "\n";
        out << rowstring;
    }

    file.close();
}

void MainWindow::on_button_cleardata_clicked()//清空波形表1数据
{
    QString log = "清空波形表数据";
    insert_log(log);
    while(ui->tableWidget->rowCount())
    {
        ui->tableWidget->removeRow(0);
    }
}

void MainWindow::on_button_wave_start_clicked()//开始绘制波形
{
    if(isOk)
    {
        QString log = "开始获取数据";
        insert_log(log);
        startAuto = true;

        time = ui->auto_time_wave->text().toInt();

        qcustomplot();
        qDebug()<<"已执行qcus";
        _pTimerUpdate ->start(time);
        //_pTimertest->start(100);//测试随机数
        ui->button_wave_stop->setEnabled(true);
        ui->button_wave_start->setEnabled(false);
    }
    else
    {
        QMessageBox::warning(this,"警告","串口未连接！");
    }
}

void MainWindow::on_button_wave_stop_clicked()//停止绘制波形
{
    QString log = "停止获取数据";
    insert_log(log);
    startAuto = false;
    //_pTimertest->stop();//测试随机数
    _pTimerUpdate ->stop();
    ui->button_wave_stop->setEnabled(false);
    ui->button_wave_start->setEnabled(true);
}

void MainWindow::insert_log(QString log)//插入操作日志
{
    LogData = ui->textEdit_log->toPlainText();
    QString current_time = ui->current_day->text();
    LogData+=current_time;
    ui->textEdit_log->setText("时间："+LogData+"\n");
    LogData+=log;
    ui->textEdit_log->setText(LogData+"\n");
    ui->textEdit_log->moveCursor(QTextCursor::End);
}

void MainWindow::on_button_savedata_2_clicked()
{
    QString log = "保存操作日志";
    insert_log(log);

    QString filename = QFileDialog::getExistingDirectory(this,tr("file dialog"),"./logdata");
   //文件名  E:/QT/login-master/login-master/
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString date = time.toString("MM-dd-hh-mm"); //设置显示格式
    filename += date+".txt";
    //文件对象
    QFile file(filename);
    //只写方式打开
    if(!file.open(QFile::WriteOnly | QFile::Text))      //只写方式
    {
        QMessageBox::warning(this,tr("double file edit"),tr("no write ").arg(filename).arg(file.errorString()));
        return ;
    }
    //文件流对象
    QTextStream out(&file);
    qDebug()<<LogData;
    out << LogData;
    file.close();
}


void MainWindow::on_button_cleardata_2_clicked()
{
    ui->textEdit_log->clear();
}


void MainWindow::on_pushButton_temp_clicked()
{
    QString value = ui->lineedit_temp_value->text();
    QString log = "设置温度阈值为:"+value+"℃";
    insert_log(log);
}


void MainWindow::on_pushButton_V_clicked()
{
    QString value = ui->lineedit_V_value->text();
    QString log = "设置电压阈值为:"+value+"V";
    insert_log(log);
}


void MainWindow::on_pushButton_A_clicked()
{
    QString value = ui->lineedit_A_value->text();
    QString log = "设置电流阈值为:"+value+"A";
    insert_log(log);
}


void MainWindow::on_comboBox_currentIndexChanged()
{
    QString value = ui->comboBox->currentText();
    QString log = "选择绘制"+value+"的数据";
    insert_log(log);
}

