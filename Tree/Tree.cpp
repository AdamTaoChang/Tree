// Tree.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

/**
 * Definition for a binary tree node.
 */

#include <vector>
#include <iostream>
#include <queue>


struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

class Solution {
public:
    static TreeNode* buildTree(std::vector<int>& preorder, std::vector<int>& inorder) 
    {
        const int nTreeLen = inorder.size();
        if (nTreeLen == 0) return nullptr;
        
        int* pArrInorder = new int[nTreeLen];
        int* pArrPreorder = new int[nTreeLen];
        std::copy(inorder.begin(), inorder.end(), pArrInorder);
        std::copy(preorder.begin(), preorder.end(), pArrPreorder);
        return DFS(pArrInorder, pArrPreorder, 0, nTreeLen - 1, 0, nTreeLen - 1);
    }
    static TreeNode* DFS(int inorder[], int preorder[],
        int head1, int tail1, int head2, int tail2)
    {
        std::cout << head1 << "," << tail1 << "," << head2 << "," << tail2 << std::endl;
        //什么时候结束？
        //没有左子树或者右子树的时候。
        if (head2 > tail2)
        {
            return nullptr;
        }
        int nRootVal = preorder[head2];
        TreeNode* pRoot = new TreeNode(nRootVal);
        //找到中序中根节点的位置
        int nMidIndex = 0;
        while (inorder[head1 + nMidIndex] != nRootVal)
        {
            nMidIndex++;
        }
        //nMidIndex 这里找到其实也是左子树的元素个数、长度。
        //这里需不需要判断nMidIndex找不到的情况？
        //如果找不到那说明这二个序列是构不成树的。
        pRoot->left = DFS(inorder, preorder,
            head1, head1 + nMidIndex,
            head2 + 1, head2 + nMidIndex);
        pRoot->right = DFS(inorder, preorder,
            head1 + nMidIndex + 1, tail1,
            head2 + nMidIndex + 1, tail2);
        return pRoot;
    }
    
    static void levelOrder(Node* pRoot) 
    {
        if (pRoot == NULL)
        {
            return;
        }
        std::queue<Node*> queueSameLevel;
        queueSameLevel.push(pRoot);
        while (!queueSameLevel.empty())
        {
            int nQueueSize = queueSameLevel.size();
            Node* pPreNode = nullptr;
            for (int index = 0; index < nQueueSize; ++index)
            {
                Node* front = queueSameLevel.front();
                queueSameLevel.pop();
                if (pPreNode != nullptr)
                {
                    pPreNode->next = front;
                }
                //然后再让当前节点成为前一个节点
                pPreNode = front;
                //是不是我在访问的时候队列为空其实就是没有兄弟右侧节点。
                //但是如果有怎么处理呢？？？
                if (front->left != nullptr)
                {
                    queueSameLevel.push(front->left);
                }

                if (front->right != nullptr)
                {
                    queueSameLevel.push(front->right);
                }
            }

        }
    }

    static Node* MakeTree()
    {
        //[1,2,3,4,5,6,7]
        Node* pRoot = new Node(1);
        pRoot->left = new Node(2);
        pRoot->right = new Node(3);
        Node * pNodeTemp = pRoot->left;
        pNodeTemp->left = new Node(4);
        pNodeTemp->right = new Node(5);

        pNodeTemp = pRoot->right;
        pNodeTemp->left = new Node(6);
        pNodeTemp->right = new Node(7);
        return pRoot;

    }

    static TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) 
    {
        if (root == nullptr || root == p || root == q)
            return root;
        TreeNode* pLeftLowestCommonAncestor =
            lowestCommonAncestor(root->left, p, q);
        TreeNode* pRightLowestCommonAncestor =
            lowestCommonAncestor(root->right, p, q);


        //如果left为空，说明这两个节点在cur结点的右子树上，
        //我们只需要返回右子树查找的结果即可
        if (pLeftLowestCommonAncestor == nullptr)
            return pRightLowestCommonAncestor;
        //同上
        if (pRightLowestCommonAncestor == nullptr)
            return pLeftLowestCommonAncestor;
        //如果left和right都不为空，
        //说明这两个节点一个在cur的左子树上一个在cur的右子树上，
        //我们只需要返回cur结点即可。
        return root;




    }


    /////////////////////////////////////
    static TreeNode * MakeSerializeTree()
    {
        //[1, 2, 3, null, null, 4, 5]
        TreeNode* pRoot = new TreeNode(1);
        pRoot->left = new TreeNode(2);
        pRoot->right = new TreeNode(3);
        TreeNode* pNodeTemp = pRoot->left;
        pNodeTemp->left = nullptr;
        pNodeTemp->right = nullptr;

        pNodeTemp = pRoot->right;
        pNodeTemp->left = new TreeNode(4);
        pNodeTemp->right = new TreeNode(5);
        return pRoot;
    }

    //得出结论，序列化不适合按照BFS来遍历
    //层级优先遍历不好处理没有节点的情况。

    // Encodes a tree to a single string.
    static std::string serialize(TreeNode* pRoot)
    {
        if (pRoot == NULL)
        {
            return "";
        }
        std::string strRes;
        TreeNode* pNullNode = new TreeNode(0);
        std::queue<TreeNode*> queueSameLevel;
        queueSameLevel.push(pRoot);
        while (!queueSameLevel.empty())
        {
            int nQueueSize = queueSameLevel.size();
            //TreeNode* pPreNode = nullptr;
            for (int index = 0; index < nQueueSize; ++index)
            {
                TreeNode* front = queueSameLevel.front();
                queueSameLevel.pop();

                if (front->val == 0)
                {
                    strRes.append("null,");
                    continue;
                }

                char arrBuffer[10] = {0};
                _itoa_s(front->val, arrBuffer, 10, 10);
                std::string strTemp(arrBuffer);
                strRes.append(strTemp);
                strRes.append(",");
                if (front->left != nullptr)
                {
                    queueSameLevel.push(front->left);
                }
                else
                {
                    queueSameLevel.push(pNullNode);
                }

                if (front->right != nullptr)
                {
                    queueSameLevel.push(front->right);
                }
                else
                {
                    queueSameLevel.push(pNullNode);
                }
                
            }

        }
        strRes.erase(strRes.end() - 1);
        return strRes;
    }
};

int main()
{
    
    
    std::vector<int> preorder;
    //[3, 9, 20, 15, 7]
    //[9, 3, 15, 20, 7]
    preorder.push_back(3);
    preorder.push_back(9);
    preorder.push_back(20);
    preorder.push_back(15);
    preorder.push_back(7);
    std::vector<int> inorder;
    inorder.push_back(9);
    inorder.push_back(3);
    inorder.push_back(15);
    inorder.push_back(20);
    inorder.push_back(7);
    TreeNode* pTreeNode = Solution::buildTree(preorder, inorder);


    std::queue<int> afafa;
    //afafa.

    Node* pRoot = Solution::MakeTree();
    Solution::levelOrder(pRoot);

    TreeNode * pTreeRoot = Solution::MakeSerializeTree();
    if (pTreeRoot)
    {
        std::string strData = Solution::serialize(pTreeRoot);
    }
    int a = 0;
    scanf_s("%d", &a);
    return 0;
}
// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
