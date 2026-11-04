# QCefBrowser

基于 CEF 和 Qt Widgets 封装的 Windows 浏览器示例，提供网页浏览、Qt 与 JavaScript 消息交互，以及多媒体、动画和离屏渲染相关探索代码。

原项目使用 VS2017 + Qt 5.12.11 开发，当前工程工具集为 VS2022 / v143，目标平台为 x86。

## 功能与示例

- 网页加载、前进、后退、刷新和缩放。
- 本地 HTML 页面加载。
- Qt 与 JavaScript 双向消息交互。
- 通过文件选择器加载 WebP、GIF 文件。
- 独立离屏测试窗口，支持基础鼠标、滚轮和键盘交互。

音视频格式支持取决于 CEF 的编译选项及页面资源，相关编译和集成资料见文末。

## 界面预览

![浏览器演示](GIF/1.gif)

## 开发环境

| 依赖 | 当前工程配置 |
| --- | --- |
| 操作系统 | Windows |
| Visual Studio | VS2022，安装“使用 C++ 的桌面开发”组件 |
| MSVC 工具集 | v143 |
| Qt | Qt 5.12.11，MSVC2017 32 位版本 |
| Qt 安装名称 | Qt5.12.11_msvc2017_32 |
| Qt 模块 | Core、Gui、Widgets；Debug 配置额外包含 WinExtras |
| Qt 构建集成 | Qt VS Tools 及其 Qt/MSBuild 构建规则 |
| Windows SDK | Debug：10.0，使用已安装的可用版本；Release：10.0.17763.0 |
| CEF 头文件版本 | 3.3239.1723.g071d1c1 |
| Chromium 版本 | 63.0.3239.132 |
| 目标平台 | 解决方案 x86，对应项目 Win32 |

Qt、CEF 开发库及运行库需与程序保持相同架构和版本。Qt 的 MSVC2017 安装包名称与项目当前使用的 v143 工具集分别属于 Qt 安装配置和项目编译配置。

## 项目结构

| 路径 | 说明 |
| --- | --- |
| [QCefBrowser.sln](QCefBrowser.sln) | 解决方案入口 |
| [QCefBrowser/](QCefBrowser/) | C++ 源码、Qt 界面和资源 |
| [QCefBrowser/include/](QCefBrowser/include/) | CEF 头文件 |
| [QCefBrowser/lib/](QCefBrowser/lib/) | CEF 导入库和 wrapper 静态库 |
| [Debug/](Debug/) | Debug 程序输出及随附 CEF 运行资源 |
| [Release/](Release/) | Release 程序输出及随附 CEF 运行资源 |

## 构建步骤

1. 安装 VS2022、v143 工具集、所需 Windows SDK，以及 Qt 5.12.11 的 MSVC2017 32 位版本。
2. 安装 Qt VS Tools，在 Qt Versions 中注册 Qt，名称设为 `Qt5.12.11_msvc2017_32`，路径填写实际安装位置。该名称需与项目的 `QtInstall` 一致。
3. 确认 Qt/MSBuild 能够找到 `qt.props` 和 `qt.targets`。
4. 打开 [QCefBrowser.sln](QCefBrowser.sln)，选择 `Debug / x86` 或 `Release / x86`。CEF 依赖路径使用 `$(SolutionDir)`，建议从解决方案构建。
5. 确认头文件和库目录完整。Debug 链接 `libcef.lib`、`libcef_dll_wrapperd.lib`；Release 链接 `libcef.lib`、`libcef_dll_wrapper.lib`。
6. 生成解决方案，按照下文准备运行依赖后启动程序。

Release 配置固定使用 Windows SDK `10.0.17763.0`，需要安装该版本，或在项目属性中调整为本机已安装的 SDK。

## 运行与部署

仓库根目录的 Debug、Release 同时存放程序输出和 CEF 运行资源。部署时保留对应配置下的完整资源组合，包括：

- `libcef.dll`、`chrome_elf.dll`。
- `libEGL.dll`、`libGLESv2.dll`、随附的 D3DCompiler DLL 和 `swiftshader` 目录。
- `icudtl.dat`、各个 pak 文件、`locales` 目录及快照 bin 文件。
- `test.html`、`test2.html` 等本地测试页面。
- 生成的 `QCefBrowser.exe`，以及匹配的 Qt 和 VC 运行库。

程序启动时从 EXE 所在目录加载 `test.html`。CEF 子进程复用同一个 `QCefBrowser.exe`，部署时需要保留该程序。

Qt 运行库及 `platforms/qwindows.dll` 可使用对应 32 位 Qt 的部署工具准备。进入 EXE 所在目录，在该 Qt 的命令行环境中执行：

```bat
windeployqt QCefBrowser.exe
```

`windeployqt` 用于部署 Qt 依赖，CEF 文件及本地页面仍需按上述结构保留。更换 CEF 版本时，同步匹配头文件、导入库、wrapper 库及运行资源。

## 使用说明与示例状态

- 网页浏览：输入地址后加载，使用前进、后退、刷新和缩放按钮操作。
- JS 交互：使用随附本地页面，在界面输入消息并发送到页面，页面消息会显示在 Qt 界面中。
- 图片加载：通过 WebP/GIF 文件选择入口打开本地文件。
- 测试web：打开原生 `QCefBrowser` 测试窗口，沿用原有测试页面入口。
- 离屏测试：在主界面地址栏输入 URL 后点击“osr”，每次打开一个独立离屏窗口；地址为空时加载程序目录的 `test.html`。窗口支持拖动改变大小，也可同时打开多个。
- 页面交互：支持点击、双击、滚轮、焦点切换及基础键盘输入，按 F5 刷新。当前离屏窗口使用 CEF 软件帧缓冲交给 Qt 绘制。
- 动画与 SVGA：准备对应网页及脚本资源后，可通过地址栏在测试窗口中加载。
- 当前范围：页面下拉弹层的离屏绘制、中文输入法组合输入及候选框、高 DPI 全面适配尚未实现。

## Git 提交说明

[.gitignore](.gitignore) 覆盖 VS 缓存、本机项目设置、项目内编译中间目录、浏览器 GPU 缓存、日志及指定的程序和调试产物。

根目录 Debug、Release 内的 CEF DLL、pak、locales、快照文件和测试页面属于运行依赖，需要保留；CEF 头文件及静态库也需要保留。因此忽略规则按具体路径区分生成文件和依赖资源。

已被 Git 跟踪的缓存或生成文件不会因新增忽略规则自动取消跟踪，需要另行处理其跟踪状态。

## 学习资料

- [CEF 开发学习总结](https://blog.csdn.net/qq_36651243/article/details/115350668)
- [自编译支持视频播放的 CEF 3.3239：步骤及编译错误处理](https://blog.csdn.net/qq_36651243/article/details/115482577)
- [CEF 源码下载及集成多媒体功能](https://blog.csdn.net/qq_36651243/article/details/115670877)
- [CEF 源码下载错误处理](https://blog.csdn.net/qq_36651243/article/details/116157824)
- [CEF 官方项目](https://bitbucket.org/chromiumembedded/cef)
- [CEF 官方构建 Wiki](https://bitbucket.org/chromiumembedded/cef/wiki/MasterBuildQuickStart)
- [CEF 官方论坛](http://www.magpcss.org/ceforum)
- [CEF Automated Builds](https://cef-builds.spotifycdn.com/index.html)
- [CefSharp 参考项目](https://github.com/cefsharp/CefSharp)
- [cefutil 开发参考](https://github.com/fanfeilong/cefutil)
- [QCefView 文档（独立参考项目）](https://cefview.github.io/QCefView/)