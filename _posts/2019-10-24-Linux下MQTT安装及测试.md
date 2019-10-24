---
layout:     post
title:      Linux下MQTT安装及测试
subtitle:   MQTT
date:       2019-10-24
author:     bbkgl
header-img: img/post-bg-0008.jpg
catalog: true
tags:
    - Linux
---

>雨打梨花深闭门
>
>忘了青春
>
>误了青春

物联网老师上课的时候突然让用MQTT写一个通信程序，实现命令控制，他说的是客户端输入`ls`，那边就得返回目录信息，不是很懂，查了一大堆也不会，今天有点时间把第一步走了。

## MQTT程序安装

> 千里之行，始于足下

这东西安装也是费了大劲，百度一查全是介绍协议的，CSDN博客上也是互相抄的飞起，没一个是真正能用的，要么抄别人没抄完，要么抄的就是错的。

![](https://ae01.alicdn.com/kf/Hb22b3b5446434c7b912b28f2dc44d887r.jpg)

理一下我们的需求：使用MQTT通信，实现部分远程控制命令，基于C/C++编程语言实现。

然后再看看MQTT到底是个什么？

简单来说就是个消息代理，双方制定同一个订阅ID，假设是“2333”，那么发布端负责使用“2333”发布消息，订阅端则使用“2333”接收消息。

所以我们需要安装两个东西：

- MQTT代理服务器
- MQTT的C/C++接口库

接下来的安装步骤均基于Ubuntu 16.04的环境下进行。

#### mosquitto安装

我又要吐槽了，人家官网都说了，Ubuntu可以apt安装，我就不明白为什么网上一搜全是源码安装的，国内这群人无脑抄真是难搞。。。[mosquitto官网下载](https://mosquitto.org/download/)

![img](https://ae01.alicdn.com/kf/He6bb63a2cfe34e698e34c62878e2cfc2Q.jpg)

直接执行命令：

```she
sudo apt install mosquitto
```

会自动安装对应的依赖库的，简单吧！！！

