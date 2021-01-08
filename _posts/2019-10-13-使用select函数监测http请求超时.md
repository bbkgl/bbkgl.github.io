---
layout:     post
typora-root-url: ..
title:      使用select函数监测http请求超时
subtitle:   socket超时
date:       2019-10-13
author:     bbkgl
header-img: img/post-bg-2356.jpg
catalog: true
tags:
    - http
---

> 人生如逆旅
>
> 我亦是行人

最近研究怎么实现HTTP请求超时检测并踢掉请求的功能。

一开始想到用linux的信号机制，可是用了感觉问题挺多的，好多时候不生效，要么就是不能一个进程里重复用。

然后就在博客上找，基本都是说select的，索性我就两个都用了，DNS请求用信号，TCP连接和HTTP请求用seletct。

一般我们用select都是在用到多路复用的情况下，也就是委托系统内核帮我们先检测一下这一堆IO中是否有事件，而不是程序员开发个轮询非阻塞的东西去试探，当然select也需要开发程序去轮询，但起码知道一定有事件了。

这次实现检测HTTP请求响应也是同理，当select提醒了再去读不就行了吗，既可以设置超时而且还不用设置成非阻塞，实在简单方便呀。

利用自己开发的一些HTTP请求库实现了一个简单的例子：

### DNS请求超时

DNS请求超时控制：

```cpp
std::string get_host(std::string name) {
    struct hostent *addr = nullptr;
    std::string host;
    tmp = "Connect the DNS server time out, please check your url and network!(%d)";
    signal(SIGALRM, alarmhandle);
    alarm(5);
    addr = gethostbyname(name.c_str());
    alarm(0);
    sigrelse(SIGALRM);
    // 如果是网络问题，这里会返回空指针
    if (!addr) {
        std::cerr << "Can't connect the DNS, please check your url and network!" << std::endl;
        bbkgl::error_num = DNSERROR;
    }
    else
        host = std::string(inet_ntoa(*(struct in_addr *)addr->h_addr_list[0]));
    return host;
}
```

样例程序：

```cpp
#include <map>
#include <cstdio>
#include "crequests.h"

int main() {
    std::map<std::string, std::string> headers;
    headers["Connection"] = "keep-alive";
    std::string url = "https://www.233333333333.com";
    headers.insert(std::make_pair("User-Agent", "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/77.0.3865.90 Safari/537.36"));
    // 设置超时时间为3s
    auto r = crequests::get(url, headers, 3);
    printf("%d\n", r.status_code_);
    printf("%s\n", r.get_body().c_str());
    return 0;
}
```

输出：

```http
Connect the DNS server time out, please check your url and network!(14)
Can't connect the DNS, please check your url and network!
-1
ERROR
```

利用信号实现，没什么好说的。

### TCP连接超时

connect函数超时控制：

```cpp
Socket::Socket(std::string addr, int port, int timeout, bool ishead) :
    debug_txt_("debug.txt"),
    port_(port),
    ishead_(ishead) {

    // 设置超时时间，单位是秒
    time_out_.tv_sec = timeout;
    time_out_.tv_usec = 0;
    FD_ZERO(&rfds_);
    FD_SET(fd_, &rfds_);
    FD_ZERO(&wfds_);
    FD_SET(fd_, &wfds_);

    // TCP连接和超时控制
    // 先设置成非阻塞
    bbkgl::set_nonblock(fd_);
    int flag = ::connect(fd_, (struct sockaddr*)&serv_addr_, sizeof(serv_addr_));
    if (flag == 0) {
        // 连接成功需要设置回阻塞，不然后面会出问题
        std::cout << "TCPConnect success!" << std::endl; 
        bbkgl::set_block(fd_);
    }
    else {
        if (errno != EINPROGRESS) {
            std::cerr << "TCPConnect failed!(" << flag << ")" << std::endl;
            bbkgl::error_num = TCPERROR;
        }
        else {
            int res = select(fd_ + 1, nullptr, &wfds_, nullptr, &time_out_);
            if (res < 0) {
                std::cerr << "TCPConnect failed!(" << flag << ")" << std::endl;
                bbkgl::error_num = TCPERROR;
            } else if (res == 0) {
                std::cerr << "TCPConnect timeout!" << std::endl;
                bbkgl::error_num = TIMEOUTERROR;
            } else {
                std::cout << "TCPConnect success!" << std::endl; 
                bbkgl::set_block(fd_);          
            }
        }
    }
}

```

样例程序：

```cpp
#include <map>
#include <cstdio>
#include "crequests.h"

int main() {
    std::map<std::string, std::string> headers;
    headers["Connection"] = "keep-alive";
    std::string url = "https://www.badu.com";
    headers.insert(std::make_pair("User-Agent", "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/77.0.3865.90 Safari/537.36"));
    // 设置超时时间为10s
    auto r = crequests::get(url, headers, 3);
    printf("%d\n", r.status_code_);
    printf("%s\n", r.get_body().c_str());
    return 0;
}
```

输出：

```http
TCPConnect timeout!
-1
ERROR
```

也就是利用“连接成功是一个可写事件”的性质，让select去监测。

注意connect前将socket设置成非阻塞，连接后设置成阻塞。

### 阻塞IO读取缓冲区超时

recv/read函数超时控制：

```cpp
int SSLSocket::read_buff(char *buff, const int read_len) {
    int flag = select(fd_ + 1, &rfds_, nullptr, nullptr, &time_out_);
    ssize_t tlen = -1;
    if (flag && FD_ISSET(fd_, &rfds_))
        tlen = ::SSL_read(ssl_, buff, read_len);
    return tlen;
}
```

样例程序：

```cpp
#include <map>
#include <cstdio>
#include "crequests.h"

int main() {
    std::map<std::string, std::string> headers;
    headers["Connection"] = "keep-alive";
    std::string url = "https://www.baidu.com";
    headers.insert(std::make_pair("User-Agent", "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/77.0.3865.90 Safari/537.36"));
    // 设置超时时间为10s
    auto r = crequests::get(url, headers, 3);
    printf("%d\n", r.status_code_);
    printf("%s\n", r.get_body().c_str());
    return 0;
}
```

输出：

```http
TCPConnect success!
SSLConnect success!
Can't recv message from server, please check your url and network!
-1
ERROR
```

也就是利用“收到消息是一个可读事件”的性质，让select去监测。

也就是每次用select检测了再去读，超时时间自定义。

### 总结

- 利用“连接成功是一个可写事件”的性质，让select去监测，实现TCP三次握手连接的超时控制
- 利用“收到消息是一个可读事件”的性质，让select去监测，实现阻塞IO接收响应的超时控制
- 利用信号机制实现DNS请求超时控制

详细代码和策略可以参考我写的HTTP/HTTPS请求库[crequest](https://github.com/bbkgl/crequests)。


