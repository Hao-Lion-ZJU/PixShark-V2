# PixShark V2.0 开发固件
___
## 1.前言
**什么是PixShark？**</br>
PixShark是专门研发给工业级水下机器人的一款开源的软硬件框架，用于水下机器人的实时控制，希望能填补专用于水下机器人的开源平台缺少的空白。</br>
**为什么要做PixShark？**</br>
水下机器人领域比较小众，开源的资料又少。由于和无人机飞控的操纵需要极为相似，所以不少水下机器人采用了飞控的解决方案。例如Bluerov作为成熟的产品，结合其开源的优势，经历了多年的技术迭代，在市场上受到极大欢迎。</br>
Bulerov的框架为Pixhawk（ardusub）—— Raspberry Pi 3B（不能升级）——QGroundControl。</br>`这些代码大多为了飞控而设置，复杂且臃肿，里面有许许多多水下机器人用不到的东西！`
传统PixHawk采用飞控的MAVLINK与Raspberry Pi通信，MAVROS作为ROS信息与MAVLINK之间的桥梁，这样做使得整个项目将变得更加冗余。同时，外接传感器需要额外的开发板，也意味着额外的水密舱，而且MAVLINK与ROS间协议有时MAVROS也无法协调等问题。</br>
水下电子舱内寸土寸金，我们希望有没有一种硬件小巧灵活，可以被很好的嵌入到Raspberry Pi中去，有没有一种嵌入式软件能够天然支持ROS框架，使开发者简单易用，不必忍受ardusub那复杂而又臃肿的代码，使得非嵌入式工程师也能快速掌握。我们希望更多的时间被应用于应用层代码编写，而不是枯燥乏味的硬件调试。</br>现在，它来了！

**PixShark有什么特点**
- 小巧方便，可以像Raspberry Pi HAT那样直接插入到树莓派上面作为一个模块单独使用。甚至你可以将PixShark单独放在水下舱内，通过载波、光纤等方式与岸基进行通信。
- 麻雀虽小，五脏俱全，主控芯片采用STM32H743VGT6，480M高速主频，在55cm*49cm的空间上，集成了网口、USB、5路串口（含232、485）、IIC、CAN、SPI、PWM等外设，基于CubeMX图形化界面配置外设，并且都以类linux的文件操作方式封装，非嵌入式工程师也能较快掌握。
- 采用c++11开发单片机，面向对象语言使代码可读性更强，同时又不损失性能。
- 引入ROS2框架。ROS2相比ROS1有着天然的在多机通信上的优势，实时性更强，而且更够在嵌入式等资源受限的环境下部署。为此我们查找了大量资料把micros部署在PixShark上面。同时提供串口、USB和网口用于物理上连接。
## 2.配置环境
本项目采用cmake + make + arm-none-eabi-gcc 交叉编译工具链开发，下载程序到单片机使用openocd
`请事先下载好对应环境`</br>
**Linux环境安装**</br>
~~sudo apt-get install arm-none-eabi-gcc~~</br>
~~sudo apt-get install openocd~~

`apt下载的openocd可能版本会比较旧，无法下载H7系列，建议进入openocd官网下载最新版本源码编译`</br>

接着安装stlink驱动:
```bash
#安装依赖库
sudo apt-get install git make cmake libusb-1.0-0-dev
sudo apt-get install gcc build-essential
#下载编译
git clone https://github.com/stlink-org/stlink
cd stlink
cmake
make
#添加环境
cd bin
sudo cp st-* /usr/local/bin
cd ../lib
sudo cp *.so* /lib32
sudo cp stlink/config/udev/rules.d/49-stlinkv* /etc/udev/rules.d/
```

输入st-info --probe查看时候识别到stlink



**Win环境安装**</br>
交叉编译器：进入ARM官网下载[下载链接](https://developer.arm.com/downloads/-/gnu-rm)</br>
openocd：[下载链接](https://github.com/xpack-dev-tools/openocd-xpack/releases/)</br>
整个windows环境下工具链开发可以参考文章：[参考文章](https://zhuanlan.zhihu.com/p/576972892)</br>

win的同学自行安装stlink驱动

`项目使用make，所以需要安装mingw，无需安装Ninja作为构建工具`

## 3.食用
_win环境下需要安装Git_
```bash
git clone git@github.com:Hao-Lion-ZJU/PixShark-V2.git
mkdir build -p && cd build
#windows环境下可能需要指定构建工具，否则win下cmake会自动帮你选择nmake
#然而这不是我们期望的，所以需要 -G "Unix Makefiles"指定，Linux环境下不需要
cmake -G "Unix Makefiles" ..
#根据你CPU的最大核心数决定
make -j8
#连接仿真器下载,项目使用STLINK，如果更换，请修改openocd.cfg中的配置
openocd -f ./openocd.cfg -c download
```
## 4.简介
### 设备 PixShark系列开发板
|硬件|型号|参数|
|---|---|---|
|主控芯片|STM32H743VGT6|480MHZ,1MB Flash,1MB RAM|
### 软件环境

 - Toolchain/IDE : cmake + make + arm-none-eabi-gcc / VSCode
 - STM32CubeMx:6.8.0
 - package version: STM32Cube FW_H7 V1.11.0
 - FreeRTOS version: 10.3.1
 - LWIP version: 2.1.2
 - CMSIS-RTOS version: 2.00
 - ROS2-humble
### 编程规范
- APP层和设备驱动代码使用C++11进行重构，引入很多高级语言特性，同时底层部分用C混编，不影响代码性能
- 对硬件依赖完全解耦了，可以方便以后移植到其他平台的MCU，去除了冗余代码代码也结构化逻辑更加清晰
- 变量和函数命名方式遵循 Unix/Linux 风格
- 不需要精确计时的任务，采用自行实现的软件定时器实现，定时精度受任务调度影响

## 5.整体框架
### 文件树  
```
PixShark/
├── components
│   ├──algorithm （存放常用数学算法与DSP库文件）
│   ├── controller（存放控制器实现）
│   └── devices（存放水下机器人上设备的驱动文件）
│   ├── hardware（STM32外设基于HAL库的c++封装）
│   ├── support（存放一些数据结构和校验算法）
│   ├── common.cpp/hpp（引入RTOS后的通用头文件，重载了operate new/delete，使用FreeRTOS内存管理接口）
├── Core
    ├── Inc		（CUBEMX生成外设头文件）
    ├── Src		（CUBEMX生成外设源文件）
    └── Startup	(启动文件)
├── doc	(详细说明文件和记录)
├── Drivers	(CUBEMX生成HAL库驱动)
├── Drivers	(CUBEMX生成HAL库驱动)
├── LWIP	(CUBEMX生成LWIP用户接口)
├── micro_ros	(micro_ros的头文件与静态库(M7内核))
├── Middlewares（CUBEMX生成LWIP、FREERTOS等三方库）
├── Robot
│   ├── (others).cpp/h（各个机器人任务的处理函数源文件）
├── USB_DEVICE	(CUBEMX生成USB用户接口)
├── UserAPP	    (用户二次开发水下机器人接口)
├── openocd.cfg	(openocd配置文件，指定仿真器类型，端口等等)
├── pixshark.ioc（CUBEMX工程）
├── STM32H743VGTX_FLASH.ld（链接脚本）
└── STM32H743x.svd（CPU对应的外设地址映射表，供DEBUG查看寄存器状态时使用）
#其余文件与项目无关

```
