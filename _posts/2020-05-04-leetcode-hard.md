---
layout:     post
title:      leetcode的hard题解法
subtitle:   你快乐吗
date:       2020-05-04
author:     bbkgl
header-img: img/post-bg-0003.jpg
catalog: true
tags:
    - leetcode
---



好像还有其他的解法，我这里觉得还是并查集合适。。。

比较麻烦的就是并查集这个数组如何表示。

这里我用next数组表示，其中next[i]：

- next[i]如果小于零，则-next[i]表示这个集合里的个数
- next[i]如果大于等于零，则next[i]表示下一个结点的下标

然后就按照正常并查集的操作就行了。。。

当然题目其实还有一个地方，就是要去下重。。不然不好建这个并查集。。。

代码如下：

```cpp
class Solution {
private:
    int findx(vector<int> &next, int x) {
        if (next[x] < 0)
            return x;
        else return (next[x] = findx(next, next[x]));
    }

    void unionx(vector<int> &next, int a, int b) {
        int fa = findx(next, a);
        int fb = findx(next, b);
        if (fa < fb) {
            next[fa] += next[fb];
            next[fb] = fa;
        }
        else {
            next[fb] += next[fa];
            if (fa != fb) next[fa] = fb;
        }
    }

public:
    int longestConsecutive(vector<int>& nums) {
        size_t len = nums.size();
        vector<int> next(len, -1);
        unordered_map<int, int> hash;
        unordered_map<int, bool> exist;
        for (int i = 0; i < len; i++) {
            if (!hash.count(nums[i]))
                hash[nums[i]] = i;
        }
        for (int i = 0; i < len; i++) {
            int it = nums[i];
            if (exist[it])
                continue;
            else exist[it] = true;
            int right = it + 1;
            if (hash.count(right)) {
                unionx(next, i , hash[right]);
            }
        }
        int ans = 0;
        for (int i = 0; i < len; i++) {
            if (next[i] < 0)
                ans = max(ans, -next[i]);
        }
        return ans;
    }
};
```

