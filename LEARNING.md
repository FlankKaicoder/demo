# 项目学习路线

本文面向想系统学习本仓库的同学。目标不是只看懂界面，而是能说清楚程序启动流程、Qt 模块关系、串口数据链路、数据库逻辑、绘图逻辑，并能做出可验证的小改造。

## 1. 先建立整体认识

本项目是一个 Qt 5 C++ 桌面上位机程序，主体目录是 `Power_Control/`。程序从登录窗口启动，登录成功后进入“电源老化监控上位机”主界面。主界面负责串口连接、数据接收、数据解析、电压/电流/温度显示、阈值状态灯、波形绘制、表格记录和日志保存。

核心流程如下：

```text
main.cpp
  -> QApplication 初始化
  -> AppInit::Instance()->start()
  -> 显示 Login
  -> Login::init()
  -> Login::init_sql()
  -> Login::on_btn_login_clicked()
  -> 创建 MainWindow
  -> MainWindow::system_init()
  -> QSerialPort::readyRead()
  -> MainWindow::receive_data()
  -> extractValues()
  -> displayData()
  -> qcustomplot()/customsplot_init()
```

学习时先围绕这条主线读代码，不要一开始陷入所有 UI 控件细节。

## 2. 准备环境并运行项目

建议使用 Windows + Qt Creator + Qt 5.x MinGW 套件。原工程使用的是 qmake 工程，工程文件为：

```text
Power_Control/login1.pro
```

命令行构建方式：

```powershell
cd Power_Control
qmake login1.pro
mingw32-make
```

也可以直接用 Qt Creator 打开 `login1.pro`，选择 Qt 5 套件后构建运行。运行后先验证三个入口：登录、注册、修改密码。默认数据库文件是 `database.db`，用户表名是 `userInfo`。

## 3. 第一阶段：读懂 Qt 工程结构

先读 `login1.pro`，确认项目依赖和编译范围：

- `QT += sql`：SQLite 用户数据库。
- `QT += widgets`：桌面控件界面。
- `QT += serialport`：串口通信。
- `QT += printsupport`：打印支持。
- `SOURCES`、`HEADERS`、`FORMS`、`RESOURCES`：分别对应源码、头文件、UI 文件和资源文件。

重点理解 Qt 项目中的几类文件：

- `.cpp/.h`：真正的业务代码。
- `.ui`：Qt Designer 生成的界面结构。
- `.qrc`：图片、图标、翻译等资源清单。
- `ui_*.h`、`moc_*.cpp`、`qrc_*.cpp`：构建生成文件，不要手工修改。

学习动作：打开 `login.ui` 和 `mainwindow.ui`，对照 `login.cpp`、`mainwindow.cpp` 中的 `ui->控件名`，理解代码如何操作界面控件。

## 4. 第二阶段：读懂登录和用户管理

重点文件：

```text
Power_Control/main.cpp
Power_Control/login.h
Power_Control/login.cpp
Power_Control/register.cpp
Power_Control/passwdedit.cpp
```

阅读顺序：

1. `main.cpp`：理解 `QApplication`、窗口图标、初始化类和 `Login w; w.show();`。
2. `Login::init()`：理解登录窗口初始化、定时器、窗口配置和数据库初始化。
3. `Login::init_sql()`：理解 `QSqlDatabase::addDatabase("QSQLITE")`、`database.db`、`userInfo` 表。
4. `Login::on_btn_login_clicked()`：理解登录校验、数据库查询、成功后创建 `MainWindow`。
5. `Login::on_btn_regist_clicked()`：理解注册对话框如何把用户名、密码、邮箱回传给登录窗口。
6. `passwdEdit::on_btn_ok_clicked()`：理解修改密码如何执行 `update userInfo`。

需要重点思考的问题：

- 当前密码是明文存储，真实项目中应改成哈希存储。
- SQL 语句通过字符串拼接生成，存在 SQL 注入风险，后续应改成 `prepare()` + `bindValue()`。
- `init_sql()` 中默认插入 `admin/admin` 的逻辑和日志提示需要复查。
- `ui->cBox_account->setCurrentIndex(1)` 在用户数量不足时可能越界。

练习任务：

- 把默认账号初始化逻辑改成“先查询是否存在 admin，再决定是否插入”。
- 把注册和修改密码 SQL 改成参数绑定。
- 给登录失败增加更明确的日志输出。

## 5. 第三阶段：读懂主窗口和串口链路

重点文件：

```text
Power_Control/mainwindow.h
Power_Control/mainwindow.cpp
Power_Control/mainwindow.ui
```

先看 `MainWindow::system_init()`。这里完成主界面初始化：

- 创建 `QSerialPort`。
- 设置串口参数：无校验、8 位数据位、1 位停止位。
- 设置标题栏、无边框窗口、样式表。
- 初始化阈值：电压、电流、温度。
- 初始化波形刷新周期。
- 初始化表格和波形控件。
- 连接 `readyRead()` 到 `receive_data()`。

串口数据流如下：

```text
on_btn_JianCeChuanKou_clicked()
  -> 枚举 QSerialPortInfo::availablePorts()

on_but_Open_clicked()
  -> setPortName()
  -> setBaudRate()
  -> open(QIODevice::ReadWrite)

readyRead()
  -> receive_data()
  -> readAll()
  -> extractValues()
  -> displayData()
```

`extractValues()` 使用 `QRegularExpression` 解析类似下面的数据：

```text
dc1.u0=12.3v
dc1.i0=1.2a
dc1.temp=35.6degC
```

然后把 `u0/u1/u2/u3`、`i0/i1/i2/i3` 和 `1.temp` 等键值分发给 `displayData()`，更新 LCD 数码显示和状态灯。

需要重点思考的问题：

- `readAll()` 不保证一次读到完整帧，真实串口协议通常需要缓存区和帧边界。
- 正则解析适合文本协议，但要明确输入格式、单位和异常数据处理。
- UI 更新必须在主线程进行，耗时解析或保存文件不应阻塞界面。

练习任务：

- 写一个 `parseSerialFrame(QString)` 小函数，只负责解析数据并返回结构化结果。
- 增加一组固定输入样例，手动验证解析结果。
- 给串口接收增加缓冲区，按换行符或结束符拆帧。

## 6. 第四阶段：读懂波形、表格和日志

波形相关函数：

```text
MainWindow::qcustomplot()
MainWindow::displayWave()
MainWindow::customsplot_init()
MainWindow::checkbox_change()
```

核心逻辑是：

1. `qcustomplot()` 添加曲线、设置坐标轴、设置时间轴和缩放交互。
2. `_pTimerUpdate` 定时触发。
3. `displayWave()` 根据下拉框选择当前要显示的温度通道。
4. `customsplot_init()` 把数据追加到曲线，并保持最近 10 秒范围。
5. 同时调用 `insert_table()` 把数据加入表格。

日志相关函数：

```text
insert_log()
on_button_savedata_clicked()
on_button_savedata_2_clicked()
```

需要重点思考的问题：

- 表格持续插入行会无限增长，长时间运行会影响内存和 UI 性能。
- 日志拼接和显示逻辑可以拆成“内存日志模型”和“界面展示”两部分。
- 文件保存路径拼接要注意目录分隔符，建议使用 `QDir` 或 `QFileInfo`。

练习任务：

- 给波形表格增加最大行数，例如只保留最近 1000 条。
- 把日志保存路径改成 `QDir(filename).filePath(...)`。
- 给波形刷新周期输入增加合法性校验。

## 7. 第五阶段：系统托盘、资源和国际化

重点文件：

```text
Power_Control/systemtrayicon.cpp
Power_Control/myqrc.qrc
Power_Control/qss.qrc
Power_Control/lang.qrc
Power_Control/cn.ts
Power_Control/en.ts
```

学习点：

- `QSystemTrayIcon` 如何创建托盘图标和右键菜单。
- `QAction`、`QMenu`、`QActionGroup` 如何组织菜单行为。
- `QTranslator` 如何加载 `cn.qm`、`en.qm`。
- `:/images/...` 这种路径来自 Qt 资源系统，不是普通文件系统路径。

练习任务：

- 增加一个托盘菜单项“显示主窗口”或“清空日志”。
- 修改一处界面文本，使用 `tr()` 包裹，然后更新 `.ts/.qm`。
- 找一张图标加入 `images/`，更新 `.qrc` 并在界面中使用。

## 8. 推荐学习节奏

### 第 1 周：能跑、能看懂主线

- 成功构建并运行项目。
- 画出启动流程图。
- 读完 `main.cpp`、`login.cpp`、`mainwindow.cpp` 的主流程。
- 在 Qt Creator 中熟悉信号槽跳转和 UI 控件定位。

### 第 2 周：能改登录和数据库

- 修复默认账号初始化逻辑。
- 将注册、登录、修改密码 SQL 改为参数绑定。
- 梳理 `userInfo` 表字段和数据库生命周期。

### 第 3 周：能改串口数据链路

- 设计一个明确的串口文本协议。
- 增加接收缓冲区和拆帧逻辑。
- 把数据解析从 UI 更新中拆出来。

### 第 4 周：能改绘图、日志和稳定性

- 限制表格最大行数。
- 优化日志保存。
- 给阈值输入、刷新周期、串口打开失败增加错误处理。

### 第 5 周以后：做工程化升级

- 用 Qt Test 给解析函数写单元测试。
- 把耗时任务移动到工作线程。
- 改造为 CMake 工程。
- 增加 Socket 通信版本，为 RK3588 Client/Server 项目做衔接。

## 9. 学习时要形成的能力

学完这个项目后，你应该能回答：

- Qt 程序的事件循环从哪里开始？
- 信号和槽如何把按钮、定时器、串口事件连接起来？
- `.ui` 文件和 `ui->控件名` 是什么关系？
- Qt 资源系统为什么能用 `:/images/...` 路径？
- SQLite 在这个项目里如何初始化、查询、插入和更新？
- 串口 `readyRead()` 为什么不等于“收到完整一包数据”？
- 实时绘图为什么需要控制刷新频率和数据量？
- 哪些逻辑应该留在 UI 线程，哪些应该放到工作线程？

如果这些问题能讲清楚，并且能完成几个小改造，这个项目就不只是“看过”，而是可以放进你的 Qt/C++ 项目能力体系中。
