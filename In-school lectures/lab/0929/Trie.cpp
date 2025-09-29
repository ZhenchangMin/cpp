#include "Trie.h"
#include <algorithm>
#include <iostream>

// TrieNode 默认构造函数的实现
TrieNode::TrieNode() : val('\0'), isend(false), prefix_count(0)
{
  child.clear();
}

// TrieNode 带字符参数的构造函数的实现
TrieNode::TrieNode(char v) : val(v), isend(false), prefix_count(0) {}

// TrieNode 析构函数的实现
// 负责输出信息，但不负责删除子节点，子节点的内存释放由Trie类的析构函数负责
TrieNode::~TrieNode() { std::cout << "~TrieNode!" << std::endl; }

// Trie 类构造函数的实现
Trie::Trie()
{
  root = new TrieNode(); // 创建根节点
}

// Trie 类析构函数的实现
// 负责释放所有动态内存
Trie::~Trie()
{
  destroy(root);
  root = nullptr;
}

// 辅助函数，用于递归释放所有节点
void Trie::destroy(TrieNode *node)
{
  // TODO: 实现递归释放所有子节点内存的逻辑
  // 提示：这是一个递归函数，注意基本情况（base case）
  if (node == nullptr)
    return;
  for (TrieNode *childNode : node->child)
  {
    destroy(childNode);
  }
  delete node;
}

void Trie::addNode(TrieNode *currentRoot, TrieNode *node)
{
  currentRoot->child.push_back(node);
}

// 插入一个单词
void Trie::Insert(std::string st)
{
  if (st.length() == 0){
    root->isend = true;
    return;
  }
  TrieNode *node = root;
  for (int i = 0; i < st.length(); i++)
  {
    bool found = false;
    for (TrieNode *childNode : node->child)
    {
      if (childNode->getVal() == st[i])
      {
        node = childNode; 
        found = true;
        break;
      }
    }
    if (!found)
    {
      TrieNode *newNode = new TrieNode(st[i]);
      addNode(node, newNode);
      node = newNode; 
    }
    node->prefix_count++;
    if (i == st.length() - 1)
    {
      node->isend = true;
    }
  }
}

// 查询一个单词是否存在
bool Trie::Lookup(std::string st)
{
  TrieNode *node = root;
  for (int i = 0; i < st.length(); i++)
  {
    bool found = false;
    for (TrieNode *childNode : node->child)
    {
      if (childNode->getVal() == st[i])
      {
        node = childNode;
        found = true;
        break;
      }
    }
    if (!found)
      return false;
  }
  return node->isend;
}

// 查询前缀的单词数量，空串是任何字符串的前缀
int Trie::Prefix(std::string st)
{
  if (st.empty())
  {
    int total = 0;
    for (TrieNode *childNode : root->child)
    {
      total += childNode->prefix_count;
    }
    if (root->isend)
      total++;
    return total;
  }
  TrieNode *node = root;
  for (int i = 0; i < st.length(); i++)
  {
    bool found = false;
    for (TrieNode *childNode : node->child)
    {
      if (childNode->getVal() == st[i])
      {
        node = childNode; 
        found = true;
        break;
      }
    }
    if (!found)
    {
      return 0;
    }
  }
  return node->prefix_count;
}
