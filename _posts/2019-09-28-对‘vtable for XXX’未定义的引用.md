---
layout:     post
title:      对‘vtable for ×××’未定义的引用
subtitle:   undefined reference to `vtable for
date:       2019-09-28
author:     bbkgl
header-img: img/post-bg-keybord.jpg
catalog: true
tags:
    - C++
---

> 我与春风皆过客
>
> 你携秋水揽星河
>

这个问题真的是，搞了我好久了，搜了好多，看了好多文章，最后还是自己的问题。。。

代码大概是这样的：

```cpp
class Socket {
public:
    Socket(std::string addr, int port, std::string out_path);
    virtual ~Socket();
    virtual int sendl(std::string content);
    virtual int recvl();
    
    
// 属性
protected:
	...
};

class NORSocket : public Socket {
public:
    NORSocket(std::string addr, int port, std::string out_path = "2333.html");
    ~NORSocket();

    virtual int sendl(std::string content);
    virtual int recvl();

private:

};
```

按照大部分博客说的，一般是以下的原因：

- 存在虚函数没有被实现
- 父类的虚函数没有被实现
- QT中的某些设置。。。

我没有用到QT。

这里我已经实现了所有的虚函数了，甚至最后都不继承了。。。还是报错！！！

其实从报错信息`vtable for NORSocket`来看就是虚函数的问题。。。

但是在我某次，在析构函数后头加了个`{}`以后，就不报错了！！！

也就是：

```cpp
class NORSocket : public Socket {
public:
    NORSocket(std::string addr, int port, std::string out_path = "2333.html");
    ~NORSocket() {};

    virtual int sendl(std::string content);
    virtual int recvl();

private:

};
```

也就是我声明了析构函数，但是没有实现析构函数。。。

总结一下出现对**‘vtable for ×××’未定义的引用**这个错误的原因：

- 存在虚函数没有被实现
- 父类的虚函数没有被实现
- QT中的某些设置。。。
- **析构函数声明了没有实现**

