import os

fdir = "_posts/"

file_names = os.listdir(fdir)

temp = '''---
layout:     post
title:      {}
subtitle:   leetcode，C++
date:       2019-09-26
author:     bbkgl
header-img: img/post-bg-map.jpg
catalog: true
tags:
    - leetcode
---

'''

for name in file_names:
    if "2019" in name:
        continue
    file = "./" + fdir + name
    text = None
    with open(file, 'r') as f:        
        text = f.read()
    text = temp.format(name[11:-3]) + text
    with open(file, 'w') as f:
        f.write(text)

print(os.listdir(fdir))

