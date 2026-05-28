# 电源监控 Qt 桌面程序

本仓库是一个基于 Qt 5 的 C++ 桌面应用，项目主体位于 `Power_Control/`。程序从登录窗口启动，登录后进入主界面，用于串口数据读取、数据显示、阈值状态提示、波形绘制、日志记录和基础用户管理。

## 主要功能

- 登录、注册和修改密码，用户数据存储在 SQLite 数据库 `database.db`。
- 通过 `QSerialPort` 检测、打开和关闭串口，接收设备上报数据。
- 解析电压、电流和温度数据，并在 LCD 控件、状态灯和表格中展示。
- 使用 `qcustomplot` 绘制选定通道的实时波形。
- 支持系统托盘、窗口最小化、语言切换和 Qt 资源文件加载。

## 项目结构

```text
Power_Control/
  login1.pro          Qt 工程文件
  main.cpp            程序入口
  login.*             登录窗口和用户数据库初始化
  mainwindow.*        串口、数据显示、波形和日志主界面
  register.*          注册对话框
  passwdedit.*        修改密码对话框
  systemtrayicon.*    系统托盘菜单
  images/             图标、背景、样式和字体资源
  *.ui                Qt Designer 界面文件
  *.qrc               Qt 资源清单
  cn.ts / en.ts       翻译源文件
```

## 环境要求

- Qt 5.x，原说明中使用过 Qt 5.7。
- Windows 下建议使用 Qt Creator 和 MinGW 工具链。
- 工程依赖 Qt 模块：`core`、`gui`、`widgets`、`sql`、`serialport`、`printsupport`。

## 构建与运行

推荐使用 CMake 构建。仓库根目录和 `Power_Control/` 都已经提供 `CMakeLists.txt`，可直接用 Qt Creator 打开仓库根目录，选择 Qt 5 MinGW Kit 后配置并构建。

命令行方式示例：

```powershell
cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_PREFIX_PATH=D:/QT/5.14.2/mingw73_64
cmake --build build
```

如果继续使用原 qmake 工程，也可以在 `Power_Control/` 目录执行：

```powershell
qmake login1.pro
mingw32-make
```

生成的可执行文件目标名为 `ClassRoom`。qmake 文件 `Power_Control/login1.pro` 暂时保留，方便迁移期间回退。

更新翻译文件时执行：

```powershell
lrelease login1.pro
```

## 开发说明

不要直接修改 `ui_*.h`、`moc_*.cpp`、`qrc_*.cpp` 等生成文件。界面改动应编辑对应的 `.ui` 文件，资源改动应同步更新 `.qrc` 文件。当前仓库没有自动化测试，修改后至少需要完成一次本地构建，并手动验证登录、串口连接、数据显示、波形绘制和语言切换流程。
