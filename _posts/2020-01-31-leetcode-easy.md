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

