---
layout:     post
title:      Linux下MQTT安装及测试
subtitle:   MQTT
date:       2019-10-25
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

- MQTT代理服务器（mosquitto）
- MQTT的C/C++接口库（paho.mqtt.c）

接下来的安装步骤均基于Ubuntu 16.04的环境下进行。

#### mosquitto安装

我又要吐槽了，人家官网都说了，Ubuntu可以apt安装，我就不明白为什么网上一搜全是源码安装的，无脑抄真是难搞。。。[mosquitto官网下载](https://mosquitto.org/download/)

![img](https://ae01.alicdn.com/kf/He6bb63a2cfe34e698e34c62878e2cfc2Q.jpg)

直接执行命令：

```she
sudo apt install mosquitto   # 安装MQTT服务器

sudo apt install mosquitto-clients # 安装MQTT客户端
```

会自动安装对应的依赖库的，简单吧！！！

可以用一个小例子检测下是否安装成功：

依次开三个终端执行以下命令：

终端1，作为代理服务器：

```shell
mosquitto -p 1883   # mosquitto默认时候用1883端口

# 以下这个命令可以检测mosquito是否运行
sudo service mosquitto status 
```

终端2，作为订阅端：

```cpp
mosquitto_sub -t mqtt
```

终端3:，作为发布端：

```shell
mosquitto_pub -h localhost -t mqtt -m "23333"
```

然后，就能在终端2收到消息了：

![](https://ae01.alicdn.com/kf/H87930d5abfc146c0b2497def0a4a1b81N.jpg)

#### paho.mqtt.c安装

这个得从github上下载源码安装，其实安装教程在[README](<https://github.com/eclipse/paho.mqtt.c/blob/master/README.md>)中已经写了，基本执行以下命令就行了：

安装依赖：

```shell
sudo apt-get install build-essential gcc make cmake cmake-gui cmake-curses-gui

# 如果提示openssl错误，再装以下openssl
sudo apt-get install libssl-dev
```

安装paho.mqtt.c：

```shell
# clone
git clone git@github.com:eclipse/paho.mqtt.c.git   # ssh
git clone https://github.com/eclipse/paho.mqtt.c.git # https
# run
cd paho.mqtt.c
make
sudo make install
```

然后就安装好了，需要注意的是，头文件默认在`/usr/local/include`下，动态/静态库默认在`/usr/local/lib`下，也就是说你如果要用到这个库的话，得想好怎么去引用，可以使用cmake或者你再移动到`/usr/include`和`/usr/lib`下，当然只是完成作业的话还有一种非常简单粗暴的方法，就是把文件拷贝到当前目录下哈哈哈。

## C/C++中使用MQTT

很简单，调接口就行了。

举个小例子。

发布端 publish.cpp：

```cpp
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "MQTTClient.h"

int main(int argc, char **argv) {
    char *address = "tcp://localhost:1883";
    char *client_id = "publish_client";
    char *topic = "mqtt_examples";
    char buf[1024];
    const int time_out = 10000;
    int rv;
    int QOS = 1;
    MQTTClient client;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    MQTTClient_message publish_msg = MQTTClient_message_initializer;
    MQTTClient_deliveryToken token;

    conn_opts.keepAliveInterval = 60;
    conn_opts.cleansession = 1;

    MQTTClient_create(&client, address, client_id, MQTTCLIENT_PERSISTENCE_NONE,
                      nullptr);
    if ((rv = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS) {
        printf("MQTTClient_connect failure:%s\n", strerror(errno));
        return 0;
    }
    publish_msg.qos = QOS;
    publish_msg.retained = 0;
    while (1) {
        printf("enter the message you want to send\n");
        fgets(buf, sizeof(buf), stdin);
        publish_msg.payload = (void *)buf;
        publish_msg.payloadlen = strlen(buf);
        MQTTClient_publishMessage(client, topic, &publish_msg, &token);
        printf(
            "waiting for %d seconds for publication of %s on topic %s for "
            "client with CLIENTID :%s\n",
            time_out / 1000, buf, topic, client_id);
        rv = MQTTClient_waitForCompletion(client, token, time_out);
        printf("Message with delivery token %d delivered\n", rv);
        printf("%s\n", buf);  //用于测试
        sleep(3);
    }
}
```

订阅端 client.cpp：

```cpp
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "MQTTClient.h"

int main() {
    char *address = "tcp://localhost:1883";
    char *client_id = "client_sub";
    char *payload = "mqtt_examples";
    int rv, i;
    char *ptr = nullptr;
    char *topic = nullptr;
    int topic_len;
    MQTTClient client;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    MQTTClient_deliveryToken token;
    MQTTClient_message *receive_msg = nullptr;
    conn_opts.keepAliveInterval = 60;
    conn_opts.cleansession = 1;

    if ((rv = MQTTClient_create(&client, address, client_id,
                                MQTTCLIENT_PERSISTENCE_NONE, nullptr)) < 0) {
        printf("MQTTClient_create failure:%s\n", strerror(errno));
        return 0;
    }
    printf("MQTTClient_create successfully\n");
    if ((rv = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS) {
        printf("MQTTClient_connect failure:%s\n", strerror(errno));
        return 0;
    }
    printf("MQTTClient_connect successfuly\n");
    MQTTClient_subscribe(client, payload, 1);
    /* if((rv=MQTTClient_receive(client,&topic,&topic_len,&receive_msg,5000))!=MQTTCLIENT_SUCCESS)
    {
        printf("MQTTClient_receive failure:%s\n",strerror(errno));
        return 0;
    }
    printf("MQTTClient_receive successfully\n");*/
    // receive 函数放在外面传递信息不会改变
    while (1) {
        if ((rv = MQTTClient_receive(client, &topic, &topic_len, &receive_msg,
                                     100000)) !=
            MQTTCLIENT_SUCCESS)  //最后一个参数是超时时间,单位是毫秒
        {
            printf("MQTTClient_receive failure:%s\n", strerror(errno));
            break;
        }
        printf("MQTTClient_receive successfully\n");
        ptr = (char *)receive_msg->payload;
        printf("Topic:%s\nTopic_len:%d\nmsg:", topic, topic_len);
        for (i = 0; i < receive_msg->payloadlen; i++) {
            putchar(*ptr++);
        }
        printf("\nmsg_len:%d\nmsg_id:%d\n", receive_msg->payloadlen,
               receive_msg->msgid);
        sleep(3);
    }
    printf("end\n");
    MQTTClient_disconnect(client, 10000);
    MQTTClient_destroy(&client);
    return 0;
}
```

分别编译两个源文件，需要链接上paho.mqtt.c的动态库，可以使用cmake，可以参考我的：

```cmake
cmake_minimum_required(VERSION 3.9)

add_definitions(-std=c++11)
add_definitions(-g)

include_directories(/usr/local/include)
add_executable(publish src/publish.cpp) 
# 为了方便，我把动态库直接放到CMakeLists.txt目录下的lib下面了
target_link_libraries(publish ${CMAKE_CURRENT_SOURCE_DIR}/lib/libpaho-mqtt3c.so)
```

得到可执行文件 publish和client.。

然后在三个不同的终端依次执行：

```shell
mosquitto -p 1883
./client.
./publish
```

在publish下输入23333：

![](https://ae01.alicdn.com/kf/Hf963ff09e5b24832b67e993ce9969dfcZ.jpg)

在client的终端下就能收到如下消息：

![](https://ae01.alicdn.com/kf/H43e60e5068314075bcc92640fd742086J.jpg)

验证成功！