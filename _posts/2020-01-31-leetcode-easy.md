---
layout:     post
title:      leetcode easy 题集合
subtitle:   你快乐吗
date:       2020-01-31
author:     bbkgl
header-img: img/post-bg-0011.jpg
catalog: true
tags:
    - leetcode
---

## [20. Valid Parentheses](https://leetcode-cn.com/problems/valid-parentheses/)

这个题就是直接用栈，然后配对就好了，判断是否能配对，asii码相差小于等于2的就是配对符号。

```cpp
class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        for (const char &it : s) {
            if (it == ')' || it == ']' || it == '}') {
                if (!st.empty() && abs(it - st.top()) <= 2) {
                    st.pop();
                    continue;
                }
                else
                    return false;
            }
            st.push(it);
        }
        return st.empty();
    }
};
```

## [21. Merge Two Sorted Lists](https://leetcode-cn.com/problems/merge-two-sorted-lists/)

链表合并，也是简单的经典题，没什么好说的哈哈哈！！！

技巧：弄个前置结点。

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        using ln = ListNode;
        ln *dummy = new ListNode(0);
        ln *p = dummy;
        while (l1 && l2) {
            if (l1->val < l2->val) {
                p->next = l1;
                l1 = l1->next;
            } else {
                p->next = l2;
                l2 = l2->next;
            }
            p = p->next;
        }
        if (l1) p->next = l1;
        else if (l2) p->next = l2;
        else p->next = nullptr;
        return dummy->next;
    }
};
```

## [53. Maximum Subarray](https://leetcode-cn.com/problems/maximum-subarray/)

这道题其实不是easy题，估计是面试的时候被考烂了，所以当成easy题了。。。

两种解法，动态规划，需要数组额外空间以及在线更新不需要额外O(N)的空间。

都贴下代码，都很好理解，第二种不理解的可以看[连续子数组的最大和](<https://bbkgl.github.io/2019/09/26/%E8%BF%9E%E7%BB%AD%E5%AD%90%E6%95%B0%E7%BB%84%E7%9A%84%E6%9C%80%E5%A4%A7%E5%92%8C/>)。

### 动态规划

相当简单，递推公式，`dp[i] = max(dp[i-1] + nums[i], nums[i])`。

```cpp
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int m = nums.size();
        int *dp = new int[m];
        int ans = dp[0] = nums[0];
        for (int i = 1; i < m; i++) {
            dp[i] = max(dp[i-1] + nums[i], nums[i]);
            ans = max(ans, dp[i]);
        }
        delete[] dp;
        return ans;
    }
};
```

### 在线更新

可以看[连续子数组的最大和](<https://bbkgl.github.io/2019/09/26/%E8%BF%9E%E7%BB%AD%E5%AD%90%E6%95%B0%E7%BB%84%E7%9A%84%E6%9C%80%E5%A4%A7%E5%92%8C/>)，不再赘述。

```cpp
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int ans = INT_MIN;
        int tempsum = 0;
        for (const int &it : nums) {
            if (tempsum <= 0)
                tempsum = it;
            else
                tempsum += it;
            ans = max(tempsum, ans);
        }
        return ans;
    }
};
```



## [70. Climbing Stairs](https://leetcode-cn.com/problems/climbing-stairs/)

这也是考烂的题呀，动态规划无脑。。

```cpp
class Solution {
public:
    int climbStairs(int n) {
        vector<int> dp(n + 1, 0);
        dp[0] = 1;
        dp[1] = 1;
        for (int i = 2; i <= n; i++) 
            dp[i] += (dp[i-1] + dp[i-2]);
        return dp[n];
    }
};
```

