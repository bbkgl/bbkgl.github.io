---
layout:     post
typora-root-url: ..
title:      ptrace等调试方法的权限问题
subtitle:   ptrace以及gdb等调试工具的权限问题
date:       2020-06-09
author:     bbkgl
header-img: img/post-bg-0009.jpg
catalog: true
tags:
    - leetcode
    - 单调栈
---

>宁可枝头抱香死
>
>何曾吹落北风中

问题的表现通常是开发人员在使用gdb或者ptrace系统调用的时候，对应的`errno == 1`：

```cpp
ptrace: Operation not permitted.
```

这个问题在CLion的[帮助文档](https://www.jetbrains.com/help/clion/attaching-to-local-process.html?_ga=2.145183860.1534397970.1591426065-2040722644.1571297157)里有说明，为了避免ptrace失败，可以sudo执行进程，或者是执行如下命令：

```
echo 0 | sudo tee /proc/sys/kernel/yama/ptrace_scope
```

为了能够持久生效，建议修改配置，打开`/etc/sysctl.d/10-ptrace.conf`，然后把`kernel.yama.ptrace_scope`的值改成0。 保存后再执行：

```
echo 0 | sudo tee /proc/sys/kernel/yama/ptrace_scope
```


