# 仓库贡献指南

## 项目结构与模块划分

本仓库是 Qt 5 C++ 桌面应用，主体代码位于 `Power_Control/`。入口文件是 `Power_Control/main.cpp`，Qt 工程文件是 `Power_Control/login1.pro`，生成目标为 `ClassRoom`。登录、注册和密码修改分别由 `login.*`、`register.*`、`passwdedit.*` 负责；串口通信、数据显示、阈值提示、表格日志和波形绘制集中在 `mainwindow.*`；系统托盘逻辑在 `systemtrayicon.*`。界面文件为 `*.ui`，资源清单位于 `myqrc.qrc`、`qss.qrc`、`lang.qrc`，图片和样式资源位于 `Power_Control/images/`。

## 构建、测试与开发命令

优先使用 CMake 构建：

```powershell
cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_PREFIX_PATH=D:/QT/5.14.2/mingw73_64
cmake --build build
```

原 qmake 工程仍保留，可在 `Power_Control/` 目录执行：

- `qmake login1.pro`：根据 Qt 工程文件重新生成 Makefile。
- `mingw32-make`：使用 Qt MinGW 工具链构建程序。
- `lrelease login1.pro`：根据 `cn.ts`、`en.ts` 生成 `*.qm` 翻译文件。

日常开发建议使用 Qt Creator 打开仓库根目录的 `CMakeLists.txt`，并选择 Qt 5.x MinGW 套件。

## 编码风格与命名约定

保持现有 Qt/C++ 风格：类声明放在 `.h`，实现放在 `.cpp`，界面文件按窗口或对话框命名，例如 `login.ui`、`register.ui`。缩进使用四个空格。新增 QObject 派生类时保持信号、槽函数和 UI 初始化逻辑集中清晰。不要手工修改 `ui_*.h`、`moc_*.cpp`、`qrc_*.cpp` 等生成文件，应修改对应的 `.ui`、`.h`、`.cpp`、`.qrc` 或 `.ts` 源文件。

## 测试要求

当前仓库没有自动化测试。提交前至少完成一次本地构建，并手动验证受影响流程：登录、注册、修改密码、串口检测与打开关闭、数据显示、阈值状态灯、波形绘制、日志保存和语言切换。如后续补充测试，建议使用 Qt Test，并将测试代码放入 `Power_Control/tests/`，命名示例为 `test_login.cpp`。

## 提交与合并请求规范

现有提交历史较少，后续提交请使用清晰的祈使句摘要，例如 `修复登录校验`、`更新串口数据显示逻辑`。合并请求应说明变更目的、影响范围、构建环境、手动验证结果；涉及界面变化时附截图；涉及数据库、资源、翻译或日志文件时单独说明。

## 配置与安全注意事项

`database.db`、`logdata/` 和 `mylog.txt` 属于运行期数据，提交前确认是否确实需要更新。Qt Creator 的 `*.pro.user`、对象文件、生成的 `release/` 内容通常不应随功能改动提交。处理用户信息和默认账号时，避免在新代码中加入真实密码或个人邮箱。

## tips
每次对话都以kk你好开头，然后进行对话。
