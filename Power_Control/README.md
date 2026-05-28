# Power_Control 项目说明

`Power_Control` 是 Qt 5 C++ 桌面应用的主体工程目录。工程文件为 `login1.pro`，应用目标名为 `ClassRoom`。

## 功能概览

- `login.*`：登录界面、SQLite 用户表初始化、语言切换入口和系统托盘初始化。
- `mainwindow.*`：串口检测与通信、设备数据解析、阈值判断、LCD 显示、表格记录和波形绘制。
- `register.*`：注册对话框，负责采集用户名、密码和邮箱。
- `passwdedit.*`：修改当前用户密码。
- `systemtrayicon.*`：系统托盘菜单、显示/隐藏窗口、退出程序和语言切换。
- `qcustomplot.*`：第三方绘图库，用于实时曲线显示。

## 构建命令

推荐从仓库根目录使用 CMake：

```powershell
cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_PREFIX_PATH=D:/QT/5.14.2/mingw73_64
cmake --build build
```

也可以在本目录使用原 qmake 工程：

```powershell
qmake login1.pro
mingw32-make
```

如需重新生成翻译文件：

```powershell
lrelease login1.pro
```

## 资源与数据

- 图片、图标、样式和字体位于 `images/`。
- 资源清单包括 `myqrc.qrc`、`qss.qrc` 和 `lang.qrc`。
- 翻译源文件为 `cn.ts`、`en.ts`，编译产物为 `cn.qm`、`en.qm`。
- `database.db` 和 `logdata/` 属于运行期数据，提交前应确认是否确实需要更新。

## 维护注意事项

界面变更优先修改 `.ui` 文件，不要手工编辑生成的 `ui_*.h`。构建产物、对象文件和 Qt Creator 的 `*.pro.user` 文件通常不应作为后续功能变更的一部分提交。
