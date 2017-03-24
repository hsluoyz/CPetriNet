# CPetriNet

[![Release](https://img.shields.io/github/release/hsluoyz/cpetrinet.svg)](https://github.com/hsluoyz/cpetrinet/releases)
![License](https://img.shields.io/github/license/hsluoyz/cpetrinet.svg)
![Downloads](https://img.shields.io/github/downloads/hsluoyz/cpetrinet/latest/total.svg)
![TotalDownloads](https://img.shields.io/github/downloads/hsluoyz/cpetrinet/total.svg)

CPetriNet is PetriNet simulator written in C/C++ on Windows. It simulates the processing of [CPN Tools](http://cpntools.org/). CPN Tools is a very useful but GUI tool. So we can't do large-scale experiments because it doesn't provide an API. CPetriNet doesn't rely on but simulates all elements about CPN Tools.

# Build

Build ``CPNetTest.dsw`` with **Visual Studio 6.0**. Welcome PR to migrate it to a modern Visual Studio version.

# Releases

https://github.com/hsluoyz/CPetriNet/releases

# An example

```C++
CCPNet *cpnet = new CCPNet(); \\ 表示一个colored petri网
cpnet->addPlace("P1", "int", CValue("int", 1, "int", 10)); \\ 添加名为P1的处所, 第二个参数为Place Type，第三个参数是初值。
cpnet->addPlace("P2", "int");
cpnet->addPlace("P3", "int");

cpnet->addTransition("T1_2"); \\ 添加名为T1_2的变迁
cpnet->transitionAddFromPlaceAndValue("T1_2", "P1", CValue("int", 1, "int", 10)); \\ 添加由P1连接到T1_2的弧，第三个参数是弧的expr
cpnet->transitionAddToPlaceAndValue("T1_2", "P2", CValue("int", 1, "int", 10));

cpnet->addTransition("T2_3");
cpnet->transitionAddFromPlaceAndValue("T2_3", "P2", CValue("int", 1, "int", 10));
cpnet->transitionAddToPlaceAndValue("T2_3", "P3", CValue("int", 1, "int", 10));

cpnet->initAllTransitions(); \\ 创建工作完毕后，初始化所有的变迁，做一次就行了
cpnet->fireToEnd(); \\ 触发变迁，直到终止，如果图本身停不了的话，程序也就停不了了

cout << cpnet->places2String(); \\ 在控制台显示所有处所中的token情况
```

# In Chinese

相信CPN Tools大家都用过，此API就是CPN Tools在C++上的实现，可以代码级别地进行声明和设置mark，可以单步执行，执行到终点。我没有设置固定的输出格式。但是信息都在类里封装好了，想读取也非常容易。

这个API的特点是：

1. 没有界面，全部用代码实现输入输出，可以做出规模很大的实验或工程应用。
2. 保持与CPN Tools的一致性，目前CPN Tools可以说是做着色Petri网设计与仿真的最佳工具了，会用CPN Tools的童鞋相信可以很快上手，可以大大节约学习成本。
3. 用C++实现，在VC6上开发与测试通过，相信在VS7，8，9，10上也可以顺利运行。比Java出身的CPN Tools速度不知快了多少倍。
4. 开源，方便大家增加一些其它功能，如n步执行，分析功能等等。

目前的一些不足：

1. 虽然目前并没有GUI编辑显示的功能，但是有对于处所已经写好了toString函数，相信调试不会太难。
2. 错误处理做的很简单，有些地方如colorset甚至没有类型检查，也是考虑到效率的问题。

大家最好确保声明和mark写对，如果控制台显示xxx Error.或者直接崩了的话，应该就是有的输入没写对的原因。API写的很仓促，如果大家发现是API本身的bug，请及时反馈给我。

源代码直接提供了我开发时用的VC6的工程，除了CPNetTest.cpp是测试文件，其它都是源代码，熟悉VC的相信一看就知道。测试文件里写了5个例子，通过不同的函数来切换。其中4个比较大的例子是直接照着CPN Tools里的模型写的，.cpn模型我就不传了，如果有需要再告诉我把。
