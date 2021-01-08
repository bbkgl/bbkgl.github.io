---
layout:     post
typora-root-url: ..
title:      C++使用ssl发送https请求
subtitle:   使用ssl访问
date:       2019-09-28
author:     bbkgl
header-img: img/post-bg-universe.jpg
catalog: true
tags:
    - http
---

> 渐行渐远渐无书
> 
> 水阔鱼沉何处问
> 

最近用C++写爬虫，发现很不对劲。。。因为大部分网站都换成了https，每次获得的响应都是302。。

提示重定向到他们的https站点上去，这太伤人心了，搞了半天，居然访问不了。

![H592b1e643bbd4bcbae9a25c06715e063t](/cloud_img/H592b1e643bbd4bcbae9a25c06715e063t.jpg)

当然不能这么放弃了，于是各种搜，终于明白了，https请求如何发出去和收到响应。

总的来说，需要经过以下步骤：

1. 初始化OpenSSL
2. 创建CTX上下文环境
3. 建立TCP连接
4. 创建SSL套接字，将SSL与TCP SOCKET 连接
5. 建立SSL连接
6. 然后就是通信，blablabla..
7. 最后依次关闭连接和回收资源
   1. 关闭SSL套接字
   2. 释放SSL套接字
   3. 释放SSL会话环境
   4. 关闭TCP连接
8. 退出程序（多余的2333）

当然代码如下（在linux环境下，且安装了openssl和libssl）：

```cpp
#include <arpa/inet.h>
#include <netdb.h>
#include <openssl/err.h>
#include <openssl/ssl.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main() {
    int client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    //添加SSL的加密/HASH算法
    SSLeay_add_ssl_algorithms();
    //客户端，服务端选择SSLv23_server_method()
    const SSL_METHOD *meth = SSLv23_client_method();
    //建立新的SSL上下文
    SSL_CTX *ctx = SSL_CTX_new(meth);
    if (ctx == nullptr) {
        cout << "SSL_CTX_new error !";
        return -1;
    }

    if (client < 0) {
        cout << "socket error !";
        return -1;
    }

    string host = "www.baidu.com";
    unsigned short port = 443;
    hostent *ip = gethostbyname(host.c_str());

    sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    sin.sin_addr = *(in_addr *)ip->h_addr_list[0];

    if (connect(client, (sockaddr *)&sin, sizeof(sin)) < 0) {
        cout << "connect error 1";
        return -1;
    }

    //建立SSL
    int ret;
    SSL *ssl = SSL_new(ctx);
    if (ssl == nullptr) {
        cout << "SSL NEW error";
        return -1;
    }
    //将SSL与TCP SOCKET 连接
    SSL_set_fd(ssl, client);
    // SSL连接
    ret = SSL_connect(ssl);
    if (ret == -1) {
        cout << "SSL ACCEPT error ";
        return -1;
    }

    stringstream stream;
    stream << "GET https://" << host << " HTTP/1.0\r\n";
    stream << "Accept: */*\r\n";
    // stream << "Accept-Encoding: gzip, deflate,
    // br\r\n";//不要编码，否则还得多一个解码的步骤
    stream << "Accept-Language: zh-Hans-CN, zh-Hans; q=0.8, en-US; q=0.5, en; "
              "q=0.3\r\n";
    stream << "Connection: Keep-Alive\r\n";
    stream << "Host: " << host << "\r\n";
    stream << "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) "
              "AppleWebKit/537.36 (KHTML, like Gecko) Chrome/64.0.3282.140 "
              "Safari/537.36 Edge/17.17134\r\n";
    stream << "\r\n";

    string s = stream.str();
    const char *sendData = s.c_str();
    ret = SSL_write(ssl, sendData, strlen(sendData));
    if (ret == -1) {
        cout << "SSL write error !";
        return -1;
    }
    char *rec = new char[1024 * 1024];
    int start = 0;
    while ((ret = SSL_read(ssl, rec + start, 1024)) > 0) {
        start += ret;
    }
    rec[start] = 0;
    cout << rec;

    //关闭SSL套接字
    SSL_shutdown(ssl);
    //释放SSL套接字
    SSL_free(ssl);
    //释放SSL会话环境
    SSL_CTX_free(ctx);

    close(client);
}
```


