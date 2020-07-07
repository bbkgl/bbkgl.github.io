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

## [283. Move Zeroes](https://leetcode-cn.com/problems/move-zeroes/)

简单题，硬是绕了一下。。。

```CPP
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int cnt = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (cnt != 0) {
                nums[i - cnt] = nums[i];
                if (nums[i] == 0) cnt++;
                nums[i] = 0;
                continue;
            }
            if (nums[i] == 0) cnt++;
            if (cnt + i >= nums.size()) nums[i] = 0;
        }
    }
};
```

## [617. Merge Two Binary Trees](https://leetcode-cn.com/problems/merge-two-binary-trees/)

简单。

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
    TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
        if (t1 && t2) {
            t1->val += t2->val;
            t1->left = mergeTrees(t1->left, t2->left);
            t1->right = mergeTrees(t1->right, t2->right);
        } else if (!t1 && !t2) 
            return nullptr;
        else {
            if (t1) {
                t1->left = mergeTrees(t1->left, nullptr);
                t1->right = mergeTrees(t1->right, nullptr);
            }
            else {
                t2->left = mergeTrees(t2->left, nullptr);
                t2->right = mergeTrees(t2->right, nullptr);
                t1 = t2;
            }
        }
        return t1;
    }
};
```

## [581. Shortest Unsorted Continuous Subarray](https://leetcode-cn.com/problems/shortest-unsorted-continuous-subarray/)

感觉并不是那么easy。。。

核心点：

- 序列的组成可以看作：`[有序1，无序，有序2]`
- 整个序列符合：`有序1 < 无序 < 有序2`
- 从左到右，找到第一个小于左边最大值的数
- 从右到左，扎到第一个小于右边最小值的数

主要根据后面两点写代码。。。

```cpp
class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        int len = nums.size();
        int leftmax = INT_MIN, left = -1;
        int right = -1, rightmin = INT_MAX;
        for (int i = 0; i < len; i++) {
            leftmax = max(nums[i], leftmax);
            rightmin = min(nums[len - i - 1], rightmin);
            if (nums[i] < leftmax) left = i;
            if (nums[len-i-1] > rightmin) right = len - i - 1;
        }
        if (left > right)
            return left - right + 1;
        return 0;
    }
};
```

## [543. Diameter of Binary Tree](https://leetcode-cn.com/problems/diameter-of-binary-tree/)

这是我第一份实习Momenta的一面的手撕算法题。。。

很简单，dfs后序返回每个结点到叶子结点的最长路径，然后树的直径就是：

```cpp
ans = max(ans, left + right + 1);
```

代码也是相当简短：

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
    int dfs(TreeNode *root, int &ans) {
        if (root == nullptr)
            return 0;
        int left = dfs(root->left, ans);
        int right = dfs(root->right, ans);
        ans = max(left + right, ans);
        return max(left, right) + 1;
    }

public:
    int diameterOfBinaryTree(TreeNode* root) {
        int ans = 0;
        dfs(root, ans);
        return ans;
    }
};
```

## [538. Convert BST to Greater Tree](https://leetcode-cn.com/problems/convert-bst-to-greater-tree/)

就是dfs：

- 每层递归的返回值是右子树返回值+左子树返回值+当前结点的和
- 每层结点的新值是右子树返回值+presum
- 递归左子树传入的presum为右子树返回值+presum+左子树返回值
- 递归右子树传入的presum为presum

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
    int dfs(TreeNode *root, int preSum = 0) {
        if (root == nullptr)
            return 0;
        int right = dfs(root->right, preSum);
        root->val += right;
        int ret = root->val;
        root->val += preSum;
        int left = dfs(root->left, root->val);
        return ret + left;
    }
public:
    TreeNode* convertBST(TreeNode* root) {
        dfs(root);
        return root;
    }
};
```

## [461. Hamming Distance](https://leetcode-cn.com/problems/hamming-distance/)

异或以后，找出二进制中1的个数。。。

```cpp
class Solution {
public:
    int hammingDistance(int x, int y) {
        int d = x ^ y;
        int cnt = 0;
        for (int i = 0; i <= 31; i++) {
            if (d & (1 << i))
                cnt++;
        }
        return cnt;
    }
};
```

## [448. Find All Numbers Disappeared in an Array](https://leetcode-cn.com/problems/find-all-numbers-disappeared-in-an-array/)

一个数组的每个元素除了能存储本身值的信息外，还能通过某种手段存储额外的信息，常见的：

- 一半空间存值，一半空间存储额外信息
- 正整数数组，正数表示正常信息，负数表示额外信息

本题中就是利用对应下标位置`index`的负数元素表示这个`index + 1`这个元素出现过。。。后面直接数正数就好了。。。需要注意的就是计算`index`应该用`index = abs(nums[i] - 1)`。

```cpp
class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        int len = nums.size();
        for (int i = 0; i < len; i++) {
            int index = abs(nums[i]) - 1;
            if (nums[index] > 0)
                nums[index] *= -1;
        }
        vector<int> ans;
        for (int i = 0; i < len; i++) {
            if (nums[i] < 0) {
                nums[i] *= -1;
            } else
                ans.push_back(i + 1);
        }
        return ans;
    }
};
```

## [125. Valid Palindrome](https://leetcode-cn.com/problems/valid-palindrome/)

很简单。。。

```cpp
class Solution {
private:
    bool dfs(const char *left, const char *right) {
        while (!isalnum(*left) && left < right) left++;
        while (!isalnum(*right) && left < right) right--;
        if (left >= right)
            return true;
        if (*left == *right || (abs(*right - *left) == 32 && isalpha(*right) && isalpha(*left)))
            return dfs(left + 1, right - 1);
        else return false;
    }
public:
    bool isPalindrome(string s) {
        return dfs(s.data(), s.data() + s.length() - 1);
    }
};
```

## [67. Add Binary](https://leetcode-cn.com/problems/add-binary/)

这个也太简单了。。。

```cpp
class Solution {
private:
    inline string strip0(string &&s) {
        const char *p = s.data();
        while (*p && *p == '0') p++;
        string temp = *p ? string(p) : string();
        reverse(temp.begin(), temp.end());
        return temp;
    }
public:
    string addBinary(string a, string b) {
        a = strip0(std::move(a));
        b = strip0(std::move(b));
        string ans;
        if (a.length() < b.length())
            swap(a, b);
        int8_t plus = 0;
        for (int i = 0; i < a.length(); i++) {
            if (i < b.length()) {
                int8_t c = (a[i] + b[i] - '0' - '0' + plus);
                if (c > 1)
                    plus = 1;
                else
                    plus = 0;
                c = c % static_cast<int8_t>(2);
                ans.push_back(c + '0');
                continue;
            }
            int8_t c = (a[i] - '0' + plus);
            if (c > 1)
                plus = 1;
            else plus = 0;
            c = c % static_cast<int8_t>(2);
            ans.push_back(c + '0');
        }
        if (plus) ans.push_back('1');
        reverse(ans.begin(), ans.end());
        if (ans.empty()) ans.push_back('0');
        return ans;
    }
};
```



## [面试题 02.01. Remove Duplicate Node LCCI](https://leetcode-cn.com/problems/remove-duplicate-node-lcci/)

很懵逼，leetcode中下面代码如果没有加14行那句`memset`直接会报错。。。按理来说无论如何也不会报错呀，new出来的bool数组应该默认赋值`false`。。。。

```
Line 18: Char 17: runtime error: load of value 190, which is not a valid value for type 'bool' (solution.cpp)
```

按照字面意思理解是随机赋值为190，而不是`true/false`。。。这样想的话`bool`在编译器中的设计是一个字节，确实可能被赋值为190，而`bool`运算符重载的时候可能只认`0/1`，其他值确实可能直接抛错。

按理来说`new`运算符会直接调用默认构造函数，那样应该被赋值为0，也就是`false`。

经过测试，基础类型不会默认赋值，是随机值，如果在`new`后加上`()`，就会默认赋值为`false`了。

```cpp
bool *hash = new bool[20001]();
```

题目还是相当简单的。。。

```cpp
/*
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* removeDuplicateNodes(ListNode* head) {
        if (!head) return head;
        bool *hash = new bool[20001];
        memset(hash, 0x0, 20001 * sizeof(bool));
        ListNode *dummy = new ListNode(-1);
        dummy->next = head;
        ListNode *pre = dummy, *curr = head;
        while (curr) {
            if (hash[curr->val]) {
                pre->next = curr->next;
                curr = pre->next;
            } else {
                hash[curr->val] = true;
                pre = curr;
                curr = curr->next;
            }
        }
        delete[] hash;
        return dummy->next;
    }
};
```

## [572. Subtree of Another Tree](https://leetcode-cn.com/problems/subtree-of-another-tree/)

简单粗暴：dfs遍历`s`的每个结点，然后如果当前结点结点和`t`的根结点相等，则以当前结点为根结点的子树与`t`是相等。`s`中有一个结点满足，则返回`true`。

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
private:
    bool is_same(TreeNode *a, TreeNode *b) {
        if (!a && !b) return true;
        if (!a && b) return false;
        if (1 && !b) return false;
        if (a->val != b->val) return false;
        else return is_same(a->left, b->left) && is_same(a->right, b->right);
    }
public:
    bool isSubtree(TreeNode* s, TreeNode* t) {
        if (s == nullptr || t == nullptr) return false;
        if (s->val == t->val) {
            if (is_same(s, t)) return true;
            return isSubtree(s->left, t) || isSubtree(s->right, t);
        }
        return isSubtree(s->left, t) || isSubtree(s->right, t);
    }
};
```

## [680. 验证回文字符串 Ⅱ](https://leetcode-cn.com/problems/valid-palindrome-ii/)

不是很难，正确删除某个字符的方法是双指针，然后跳过该字符进行比对。

```cpp
class Solution {
private:
    bool dfs(const char *left, const char *right, bool can_del) {
        if (left >= right) return true;
        if (*left == *right) 
            return dfs(left + 1, right - 1, can_del);
        if (!can_del) return false;
        return dfs(left + 1, right, false) || dfs(left, right - 1, false);
    }
public:
    bool validPalindrome(string s) {
        return dfs(s.c_str(), s.c_str() + s.length() - 1, true);
    }
};
```

## [7. Reverse Integer](https://leetcode-cn.com/problems/reverse-integer/)

简单，处理边界。

```cpp
class Solution {
public:
    int reverse(int x) {
        queue<uint8_t> q;
        int high = 2147483647, low = -2147483648;
        int sign = (x >= 0 ? 1 : -1);
        while (x) {
            q.push(abs(x % 10));
            x /= 10;
        }
        while (!q.empty() && q.front() == 0) q.pop();
        long ans = 0;
        while (!q.empty()) {
            ans *= 10;
            ans += q.front();
            q.pop();
        }
        if (sign > 0 && ans > high || sign < 0 && -ans < low) return 0;
        return ((int) ans) * sign;
    }
};
```

## [剑指 Offer 09. 用两个栈实现队列](https://leetcode-cn.com/problems/yong-liang-ge-zhan-shi-xian-dui-lie-lcof/)

一进一出。。。

```cpp
class CQueue {
private:
    stack<int> stack_in_;
    stack<int> stack_out_;
public:
    CQueue() {

    }

    void appendTail(int value) {
        stack_in_.push(value);
    }

    int deleteHead() {
        if (stack_out_.empty()) {
            while (!stack_in_.empty()) {
                stack_out_.push(stack_in_.top());
                stack_in_.pop();
            }
        }
        int pop_v = stack_out_.empty() ? -1 : stack_out_.top();
        if (!stack_out_.empty()) stack_out_.pop();
        return pop_v;
    }
};

```

## [202. Happy Number](https://leetcode-cn.com/problems/happy-number/)

只有一个无限循环：` 4 → 16 → 37 → 58 → 89 → 145 → 42 → 20 → 4`。

```cpp
class Solution {
public:
    bool isHappy(int n) {
        while (true) {
            int temp = 0;
            while (n) {
                temp += pow(n % 10, 2);
                n /= 10;
            }
            n = temp;
            if (temp == 1) return true;
            else if (temp == 4) return false;
        }
    }
};
```

## [112. Path Sum](https://leetcode-cn.com/problems/path-sum/)

直接递归。

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
    bool hasPathSum(TreeNode* root, int sum) {
        if (!root) return false;
        sum -= root->val;
        if (!root->left && !root->right && sum == 0) return true;
        if (!root->left && !root->right && sum != 0) return false;
        return (hasPathSum(root->left, sum) || hasPathSum(root->right, sum));
    }
};
```

