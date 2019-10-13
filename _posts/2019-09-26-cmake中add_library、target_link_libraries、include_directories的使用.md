---
layout:     post
title:      cmake中add_library、target_link_libraries、include_directories的使用
subtitle:   add_library、target_link_libraries、include_directories
date:       2019-09-26
author:     bbkgl
header-img: img/post-bg-debug.png
catalog: true
tags:
    - cmake
---

**这里没有细说每个函数的功能，因为这个百度都有的，我只说在我这里起到的作用。当然其实理解了这个项目的cmake，其他的也问题不大，大部分情况下的都是类似的。**

## 栗子

其实这个东西最好就是举个例子了，首先可以看到整个项目的层级如下图，我们只需要一个CMakeLists.txt就好了。

![1569489173968](https://wx3.sinaimg.cn/large/006moDdjly1g7d3z47ta9j306c05bt8p.jpg)

然后看下cmake怎么写：

```cmake
project(fist-week)
cmake_minimum_required(VERSION 3.9)
set(CMAKE_CXX_STANDARD 11)

# 加入所有头文件
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
# 添加所有源文件
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRCLIST)
# 将源文件打包成动态库
add_library(libcircle SHARED ${SRCLIST})

add_executable(main sample/main.cpp)

# 将动态库链接到目标
target_link_libraries(main libcircle)
```

根据上述注释和目录层级，我们就能知道add_library、target_link_libraries、include_directories分别的作用。

## 说明

### include_directories

`include_directories`其实就是指定头文件目录，我们可以指定某个目录，表示所有的头文件都在下面。

### add_library

就像注释中说的那样，`add_library`就是将指定的一些源文件打包成动态库和静态库，第一个参数就是生成库的名字，第二个参数是生成库的类型，后面的参数就都是源文件了，可以是之前定义的列表，也可以用`1.cpp 2.cpp 3.cpp`去指定。

### target_link_libraries

`target_link_libraries`就是将之前打包的库，链接到生成的目标上，不然会出现光声明，没定义的错误，注意也可以直接指定库名，如`target_link_libraries(main XXX.so)`或`target_link_libraries(main XXX.a)`。


