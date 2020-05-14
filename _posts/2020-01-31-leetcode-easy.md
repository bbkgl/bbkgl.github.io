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

## [437. Path Sum III](https://leetcode-cn.com/problems/path-sum-iii/)

这也不算是easy题了，感觉还是比较绕的，但树的算法题总是离不开dfs，我一直觉得树的题就是套娃题。

如果换个题目，可能就比较容易想到了：找到**从给定的根节点root**开始，连续结点和等于sum的路径的总数。。。那估计大家都是5分钟完事。。。

其实这个题不就是相当于将**从给定的根节点root开始**这个条件，换成了**从任意结点结点开始**吗？那直接外面再套个dfs，前中后序遍历都欧科的。

这样想的话还是蛮简单的，可是如果像我一样，总想往O(N)解，那题目就难了。

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int pathSum(TreeNode* root, int sum) {
        if (root == nullptr) return 0;
        return dfs(root, sum) + pathSum(root->left, sum) + pathSum(root->right, sum);
        
    }

    int dfs(TreeNode *root, int sum) {
        if (root == nullptr) return 0;
        sum -= root->val;
        if (sum == 0)
            return 1 + dfs(root->left, sum) + dfs(root->right, sum);
        else 
            return dfs(root->left, sum) + dfs(root->right, sum);
    }
};
```

## [155. Min Stack](https://leetcode-cn.com/problems/min-stack/)

简单：

```cpp
class MinStack {
private:
    std::stack<int> sk_;
    std::stack<int> minsk_;

public:
    /** initialize your data structure here. */
    MinStack() {
        
    }
    
    void push(int x) {
        sk_.push(x);
        if (minsk_.empty() || minsk_.top() >= x)
            minsk_.push(x);
    }
    
    void pop() {
        if (!minsk_.empty() && minsk_.top() == sk_.top())
            minsk_.pop();
        sk_.pop();
    }
    
    int top() {
        return sk_.top();
    }
    
    int getMin() {
        return minsk_.top();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
```

## [101. Symmetric Tree](https://leetcode-cn.com/problems/symmetric-tree/)

简单的递归，算是经典题了。。。

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
    bool isSame(TreeNode *left, TreeNode *right) {
        if (!left && !right)
            return true;
        else if (left && right && left->val == right->val)
            return isSame(left->left, right->right) && isSame(left->right, right->left);
        else return false;
    }
public:
    bool isSymmetric(TreeNode* root) {
        if (root)
            return isSame(root->left, root->right);
        else return true;
    }
};
```

## [104. Maximum Depth of Binary Tree](https://leetcode-cn.com/problems/maximum-depth-of-binary-tree/)

简单。。。

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (root == nullptr)
            return 0;
        else {
            return 1 + max(maxDepth(root->left), maxDepth(root->right));
        }
    }
};
```

## [121. Best Time to Buy and Sell Stock](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock/)

简单dp，dp[i]表示到i位置的最小值，但实际上dp不用数组，临时数就可以了。

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        size_t len = prices.size();
        if (len <= 0) return 0;
        int ans = 0;
        int dp = prices[0];
        for (size_t i = 1; i < len; i++) {
            if (prices[i] < dp) 
                dp = prices[i];
            else {
                ans = max(ans, prices[i] - dp);
            }
        }
        return ans;
    }
};
```

## [124. Binary Tree Maximum Path Sum](https://leetcode-cn.com/problems/binary-tree-maximum-path-sum/)

这道题其实是我面试Momenta（第一家实习公司）的一面的手撕算法题。重点在于以下两点：

- 后序遍历的时候，返回值应该是以根结点作为路径起（终）点的最大路径和
- 计算最终结果的时候，应该加上左右子树的和，注意处理负数

把上面两点想清楚就不是很难了。

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
private:
    int dfs(TreeNode* root, int &ans) {
        if (root == nullptr) return 0;
        int left = dfs(root->left, ans);
        int right = dfs(root->right, ans);
        int returnv = max(left, 0) + max(right, 0) + root->val;
        ans = max(returnv, ans);
        return max(0, max(left, right)) + root->val;
    }

public:
    int maxPathSum(TreeNode* root) {
        int ans = INT32_MIN;
        dfs(root, ans);
        return ans;
    }
};
```

## [141. Linked List Cycle](https://leetcode-cn.com/problems/linked-list-cycle/)

快慢指针！

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
    bool hasCycle(ListNode *head) {
        if (!head) return false;
        ListNode *dummy = new ListNode(0);
        dummy->next = head;
        ListNode *slow = dummy, *fast = head->next;
        while (fast != nullptr && fast != slow) {
            slow = slow->next;
            fast = fast->next;
            if (fast)
                fast = fast->next;
            else return false;
        }
        return fast != nullptr;
    }
};
```

## [160. Intersection of Two Linked Lists](https://leetcode-cn.com/problems/intersection-of-two-linked-lists/)

经典题！！！计算差值然后前后指针。

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
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode *pa = headA, *pb = headB;
        int stepa = 0, stepb = 0;
        while (pa || pb) {
            if (pa) { pa = pa->next; stepa++; }
            if (pb) { pb = pb->next; stepb++; }
        }
        pa = headA; pb = headB;
        if (stepa > stepb) swap(pa, pb);
        for (int i = 0; i < abs(stepb - stepa); i++) pb = pb->next;
        while (pa && pb) {
            if (pa == pb)
                return pa;
            pa = pa->next;
            pb = pb->next;
        }
        return nullptr;
    }
};
```

## [169. Majority Element](https://leetcode-cn.com/problems/majority-element/)

经典题，经典 ==“你没做过，就做不出来！”

理论：超过半数，1对1消耗，剩下的必然是超过半数的。。。

```cpp
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int cnt = 0, ans = INT_MIN;
        for (const int &it : nums) {
            if (cnt == 0) {
                cnt = 1;
                ans = it;
            }
            else if (ans == it) cnt++;
            else cnt--;
        }
        return ans;
    }
};
```

## [198. House Robber](https://leetcode-cn.com/problems/house-robber/)

简单题，`dp[i] = max(dp[i-2], dp[i-3]) + nums[i];`

```cpp
class Solution {
public:
    int rob(vector<int>& nums) {
        size_t len = nums.size();
        int ans = 0;
        int *dp = new int[len];
        for (int i = 0; i < len; i++) {
            if (i < 2) {
                dp[i] = nums[i];
            } 
            else if (i < 3)  {
                dp[i] = nums[i] + dp[0];
            } else {
                dp[i] = max(dp[i-2], dp[i-3]) + nums[i];
            }
            ans = max(dp[i], ans);
        }
        delete[] dp;
        return ans;
    }
};
```

## [206. Reverse Linked List](https://leetcode-cn.com/problems/reverse-linked-list/)

简单题，头插法。。。

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
    ListNode* reverseList(ListNode* head) {
        if (!head) return nullptr;
        ListNode *now = head->next;
        head->next = nullptr;
        ListNode *pre = head;
        while (now) {
            ListNode *next = now->next;
            now->next = pre;
            pre = now;
            now = next;
        }
        return pre;
    }
};
```

## [226. Invert Binary Tree](https://leetcode-cn.com/problems/invert-binary-tree/)

五行代码的简单题。。。

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (!root) return nullptr;
        TreeNode *right = invertTree(root->right);
        root->right = invertTree(root->left);
        root->left = right;
        return root;
    }
};
```

## [234. Palindrome Linked List](https://leetcode-cn.com/problems/palindrome-linked-list/)

三步：

1. 统计长度
2. 翻转后一半
3. 比较前一半和后一半是否相等

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
private:
    ListNode *reverse_list(ListNode *head) {
        if (!head) return nullptr;
        ListNode *pre = head;
        ListNode *now = head->next;
        head->next = nullptr;
        while (now) {
            ListNode *next = now->next;
            now->next = pre;
            pre = now;
            now = next;
        }
        return pre;
    }

    inline ListNode *indexof(ListNode *root, int index) {
        while (index--) root = root->next;
        return root;
    }

    bool is_same(ListNode *a, ListNode *b) {
        while (a && b) {
            if (a->val != b->val) return false;
            a = a->next;
            b = b->next;
        } 
        return true;
    }

public:
    bool isPalindrome(ListNode* head) {
        int len = 0;
        ListNode *p = head;
        while(p) { p = p->next; len++; }
        if (len <= 1) return true;
        int cnt = 1;
        if (len % 2 == 0) p = indexof(head, len / 2 - 1);
        else p = indexof(head, len / 2);
        return is_same(head, reverse_list(p->next));
    }
};
```

