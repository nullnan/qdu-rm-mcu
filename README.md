# 青岛大学 RoboMaster 嵌入式 代码开源

***Developing***

***开发测试中***

[Gitee](https://gitee.com/qdu-rm-2022/qdu-rm-mcu)
[Github](https://github.com/Jiu-xiao/qdu-rm-mcu.git)

## 软件功能介绍

本开源软件为青岛大学未来战队机器人的嵌入式控制代码。参考了官方开源和其他战队代码，结合对其他嵌入式项目的理解（如PX4），从零编写而成。

主要特色：

- BSP兼容层使用纯C实现，上层代码使用C++，稳定实时，开发方便
- 一个项目适配不同型号的机器人型号，现已支持步兵/英雄/哨兵/平衡
- 利用Cmake & GCC实现跨平台开发
- 多开发板支持
- 兵种配置文件及图形化配置
- 操作手自定义UI
- 命令行界面（CLI）
- USB上位机控制
- VSCode一键编译调试

## 图片展示

利用命令行可以辅助调试程序、校准开发板、初始化机器人、读取不同参数配置。

| ![客户端UI](./doc/image/调试界面.png?raw=true "VSCode调试界面") |
| :-------------------------------------------------------------: |
|                        *VSCode调试界面*                         |

| ![命令行界面（CLI）](./doc/image/命令行界面.png?raw=true "命令行界面（CLI）") |
| :---------------------------------------------------------------------------: |
|                              *命令行界面（CLI）*                              |

| ![客户端UI](./doc/image/客户端UI.png?raw=true "客户端UI") |
| :-------------------------------------------------------: |
|                        *客户端UI*                         |

## 推荐开发配置

### 系统

- Windows Subsystem for Linux (WSL) 2 Ubuntu [安装说明](https://docs.microsoft.com/zh-cn/windows/wsl/install-win10)

- Ubuntu native [详细信息](https://ubuntu.com)

### 配置环境

- [Visual Studio Code](https://code.visualstudio.com/)
  - 安装必备插件`C/C++` `CMake`
- 安装构建工具`sudo apt install cmake gcc-arm-none-eabi ninja-build python3-tk`

### 获取源代码

1. 克隆本库 `git clone --recursive https://gitee.com/qsheeeeen/qdu-rm-mcu.git`

或者

1. `git clone https://gitee.com/qsheeeeen/qdu-rm-mcu.git`
1. `git submodule init && git submodule update`

### 配置工程

- `./project.py config`
![配置界面](./doc/image/配置工具.png?raw=true "配置界面")

### 编译固件

- 命令行操作
  1. `cmake -DCMAKE_TOOLCHAIN_FILE:STRING=toolchain/toolchain.cmake -H. -B./build -G Ninja`
  1. `cd build && ninja`

- VS Code 操作
![命令行界面（CLI）](./doc/image/VSCode编译固件.png?raw=true "命令行界面（CLI）")
  1. 选择构建类型
  1. 编译

### 使用预先设置好的配置文件编译

![编译目标](./doc/image/编译目标.png?raw=true "编译目标")

1. 查看可编译目标
`./project.py list`

2. 选择目标进行编译
例如：`./project.py build rm-c infantry`编译C板步兵代码，或者使用`./project.py build all all`编译所有开发板的所有兵种代码。

### 调试 & 烧写

#### Ozone

- Ubuntu native
  1. 安装Jlink驱动
  1. 安装Ozone Linux版
  1. 正常调试

- Windows WSL with WSLg
  1. Windows Host中安装Jlink驱动
  1. WSL中安装Ozone Linux版
  1. WSL中使用Ozone调试，通过网络连接Jlink

- Windows WSL without WSLg
  1. Windows Host中安装Jlink驱动和Ozone
  1. Windows Host中使用Ozone调试，通过USB连接Jlink，在ozone project中修改路径

#### OpenOCD

TODO

## 文件目录结构&文件用途说明

| 文件夹    | 来源   | 内容                                |
| --------- | ------ | ----------------------------------- |
| build     | CMake  | 构建产物                            |
| config    | 用户   | 配置文件                            |
| doc       | 开发者 | 文档                                |
| hw        | 开发者 | 板级支持包                          |
| src       | 开发者 | 源代码                              |
| lib       | 开发者 | 第三方仓库                          |
| toolchain | 开发者 | 编译工具链相关文件                  |
| utils     | 开发者 | 使用到的工具，如CubeMonitor, Matlab |

| src       | 内容                                                   |
| --------- | ------------------------------------------------------ |
| component | 包含各种组件，自成一体，相互依赖，但不依赖于其他文件夹 |
| device    | 独立于开发板的设备，依赖于bsp                          |
| system    | 系统兼容层                                             |
| module    | 对机器人各模块的抽象，各模块一起组成机器人             |
| robot     | 机器人的配置文件与初始化                               |

## 系统介绍

| ![硬件系统框图（全官方设备）](./doc/image/步兵嵌入式硬件框图.png?raw=true "硬件系统框图（全官方设备）") |
| :-----------------------------------------------------------------------------------------------------: |
|                                      *硬件系统框图（全官方设备）*                                       |

| ![嵌入式程序数据流向图](./doc/image/嵌入式程序数据流向图.png?raw=true "嵌入式程序数据流向图") |
| :-------------------------------------------------------------------------------------------: |
|                                    *嵌入式程序数据流向图*                                     |

| ![嵌入式程序层次图](./doc/image/嵌入式程序层次图.png?raw=true "嵌入式程序层次图") |
| :-------------------------------------------------------------------------------: |
|                                *嵌入式程序层次图*                                 |

## 原理介绍

### 云台控制原理

| ![云台控制原理（与PX类似）](./doc/image/云台控制原理.png?raw=true "嵌入式程序层次图") |
| :-----------------------------------------------------------------------------------: |
|                              *云台控制原理（与PX类似）*                               |

### 其他参考文献新

- 云台控制参考[PX4 Controller Diagrams](https://dev.px4.io/master/en/flight_stack/controller_diagrams.html)

- 底盘Mixer和CAN的Control Group参考[PX4 Mixing and Actuators](https://dev.px4.io/master/en/concept/mixing.html)

- PID请参考[pid.c](src/component/comp_pid.c)

### TODO

- [x] 利用好CCM RAM[参考文档](https://www.st.com/resource/en/application_note/an4296-use-stm32f4stm32g4-ccm-sram-with-iar-embedded-workbench-keil-mdkarm-stmicroelectronics-stm32cubeide-and-other-gnubased-toolchains-stmicroelectronics.pdf)
- [x] 使用[TinyUSB](https://github.com/hathach/tinyusb)
- [ ] 使用MPU保护内存地址空间，防止错误访存出现。例如NULL指针读写。
- [ ] 实现固件运行在开发板，机器人运行在Gazebo的Hardware in the Loop(HITL)仿真
