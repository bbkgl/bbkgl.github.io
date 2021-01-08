---
layout:     post
typora-root-url: ..
title:      apt install 出现 Encountered a section with no Package header
subtitle:   section with no Package
date:       2019-10-24
author:     bbkgl
header-img: img/post-bg-0007.jpg
catalog: true
tags:
    - Linux
---
> 流水下滩非有意
>
> 白云出岫本无心

安装uuid的时候报错了，其实很多次安装的时候都报过这种错：

```
sudo apt install libuuid-devel
```

然后就出现：

```
正在读取软件包列表... 有错误！
E: Encountered a section with no Package: header
E: Problem with MergeList /var/lib/apt/lists/ppa.launchpad.net_noobslab_macbuntu_ubuntu_dists_xenial_main_binary-amd64_Packages
```

解决办法，依次执行：

```
sudo rm /var/lib/apt/lists/* -vf
sudo apt-get update
```

然后想安装什么就安装什么了！
