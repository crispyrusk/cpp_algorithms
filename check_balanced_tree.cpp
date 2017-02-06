///
/// CTCI 4.1 - check if a binary tree is balanced - the height of the left and right subtrees must be within a difference of one
///

#include <iostream>
#include <memory>
#include <vector>
#include <queue>
#include <cassert>

using namespace std;


class BinaryTreeNode
{
public:
    BinaryTreeNode(const int key) : key_(key)
    {
    }

    shared_ptr<BinaryTreeNode> leftChild;
    shared_ptr<BinaryTreeNode> rightChild;

    const int getKey() { return key_; }
private:
    const int key_;

};

struct TreeHeight
{
    TreeHeight(const int heightArg, const bool childrenBalancedArg) : height(heightArg), childrenBalanced(childrenBalancedArg)
    {
    }

    int height = -1;
    bool childrenBalanced = 0;
};


class BinaryTree
{
public:
    BinaryTree(const vector<int>& levelOrderSequence)
    {
        if (levelOrderSequence.empty()) { return; }
        assert(root_ == nullptr);
        std::queue< shared_ptr<BinaryTreeNode> > nodeQueue;
        std::queue<int> depthQueue;
        root_ = shared_ptr<BinaryTreeNode>(new BinaryTreeNode(levelOrderSequence[0]));
        nodeQueue.push(root_);
        std::size_t sequenceIndex = 1;
        while (!nodeQueue.empty())
        {
            if (sequenceIndex == levelOrderSequence.size()) { return; }
            auto node = nodeQueue.front();
            nodeQueue.pop();
            const int leftKey = levelOrderSequence[sequenceIndex++];
            node->leftChild = shared_ptr<BinaryTreeNode>(new BinaryTreeNode(leftKey));
            nodeQueue.push(node->leftChild);
            if (sequenceIndex == levelOrderSequence.size()) { return; }
            const int rightKey = levelOrderSequence[sequenceIndex++];
            node->rightChild = shared_ptr<BinaryTreeNode>(new BinaryTreeNode(rightKey));
            nodeQueue.push(node->rightChild);
        }
    }

    /// level order printing
    void print()
    {
        if (root_ == nullptr) { return; }
        std::queue< shared_ptr<BinaryTreeNode> > nodeQueue;
        std::queue<int> depthQueue;
        nodeQueue.push(root_);
        depthQueue.push(0);
        int currentDepth = 0;
        while (!nodeQueue.empty())
        {
            assert(nodeQueue.size() == depthQueue.size());
            auto node = nodeQueue.front();
            auto nodeDepth = depthQueue.front();
            nodeQueue.pop();
            depthQueue.pop();
            auto leftChild = node->leftChild;
            auto rightChild = node->rightChild;
            if (leftChild)
            {
                nodeQueue.push(leftChild);
                depthQueue.push(nodeDepth + 1);
            }
            if (rightChild)
            {
                nodeQueue.push(rightChild);
                depthQueue.push(nodeDepth + 1);
            }
            if (nodeDepth > currentDepth)
            {
                assert(nodeDepth = currentDepth + 1);
                std::cout << "\n";
                currentDepth = nodeDepth;
            }
            std::cout << node->getKey() << " ";
        }
        std::cout << "\n";
    }

    TreeHeight getTreeHeightDiff(const shared_ptr<BinaryTreeNode>& root)
    {
        if (root == nullptr)
        {
            return TreeHeight(0, true);
        }

        auto leftTreeHeight = TreeHeight(0, true);
        auto rightTreeHeight = TreeHeight(0, true);
        if (root->leftChild) 
        {
            leftTreeHeight = getTreeHeightDiff(root->leftChild);
        }

        if (root->rightChild)
        {
            rightTreeHeight = getTreeHeightDiff(root->rightChild);
        }

        auto rtrn = TreeHeight(0, true);
        rtrn.height = std::max(leftTreeHeight.height, rightTreeHeight.height) + 1;
        if (!leftTreeHeight.childrenBalanced || !rightTreeHeight.childrenBalanced) {
            rtrn.childrenBalanced = false;
        }
        if (std::abs(leftTreeHeight.height - rightTreeHeight.height) > 1) {
            rtrn.childrenBalanced = false;
        }
        return rtrn;
    }

    bool checkBalanced()
    {
        if (root_ == nullptr) { return true; }
        return (getTreeHeightDiff(root_).childrenBalanced);
    }


private:
    shared_ptr<BinaryTreeNode> root_ = nullptr;
};


void testFn1()
{
    std::cout << "Test Fn 1" << std::endl;
    std::vector<int> levelOrderSequence = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    auto bt = BinaryTree(levelOrderSequence);
    bt.print();
    std::cout << "Balanced: " << bt.checkBalanced() << std::endl;
}

int main(int argc, char** argv)
{
    testFn1();
    return 0;
}