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

## [128. Longest Consecutive Sequence](https://leetcode-cn.com/problems/longest-consecutive-sequence/)

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

## [239. Sliding Window Maximum](https://leetcode-cn.com/problems/sliding-window-maximum/)

滑动窗口，用双端单调队列，其实一开始我就想到了单调栈，但是单调栈只能一端进出，同时具有单调递增/减和两端进出的数据结构就是双端单调队列了。。。

问题就是如何维护这么个队列：

- 队列的长度小于等于K
- 队列的左（front）端元素不能落后于滑动窗口的左端
- 队列内所有元素保持递减，即最大值永远在左端

明确问题后，对队列的处理如下：

- 队列保存元素的索引，而不是元素值
- 按照当前i的大小，队列左侧元素需要进行pop
- 每次添加新元素，将队列中小于新元素的值pop

简单！

```cpp
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> dq;
        vector<int> ans;
        for (int i = 0; i < nums.size(); i++) {
            if (!dq.empty() && dq.front() + k <= i) dq.pop_front();
            while (!dq.empty() && nums[dq.back()] <= nums[i]) dq.pop_back();
            dq.push_back(i);
            if (i >= k - 1) ans.push_back(nums[dq.front()]);
        }
        return ans;
    }
};
```

