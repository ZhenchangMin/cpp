#include "Trie.h"
#include <algorithm>
#include <iostream>

// TrieNode 默认构造函数的实现
TrieNode::TrieNode() : val('\0'), isend(false), prefix_count(0) {
  val = '\0';
  isend = false;
  prefix_count = 0;
  child.clear();
}

// TrieNode 带字符参数的构造函数的实现
TrieNode::TrieNode(char v) : val(v), isend(false), prefix_count(0) {
  val = v;
  isend = false;
  prefix_count = 0;
}

// TrieNode 析构函数的实现
// 负责输出信息，但不负责删除子节点，子节点的内存释放由Trie类的析构函数负责
TrieNode::~TrieNode() { std::cout << "~TrieNode!" << std::endl; }

// Trie 类构造函数的实现
Trie::Trie() {
  root = new TrieNode(); // 创建根节点
  root->child.clear();
}

// Trie 类析构函数的实现
// 负责释放所有动态内存
Trie::~Trie() {
  destroy(root);
  for (TrieNode *node : nodes) {
    delete node;
  }
  delete root;
}

// 辅助函数，用于递归释放所有节点
void Trie::destroy(TrieNode *node) {
  // TODO: 实现递归释放所有子节点内存的逻辑
  // 提示：这是一个递归函数，注意基本情况（base case）
  if (node->child.empty()) {
    node->~TrieNode();
  } else {
    for (TrieNode *nod : node->child) {
      destroy(nod);
    }
    node->~TrieNode();
  }
}

void Trie::addNode(TrieNode *currentRoot, TrieNode *node) {
  nodes.push_back(node);
  currentRoot->child.push_back(node);
}

// 插入一个单词
void Trie::Insert(std::string st) {
  // TODO: 实现向字典树中插入单词的逻辑
  // 提示：从根节点开始遍历字符串，如果节点不存在则创建新节点
  TrieNode *node = root;
  bool found = false;
  for (int i = 0; i < st.length(); i++) {
    found = false;
    if (node->child.empty()) {
      TrieNode *newNode = new TrieNode(st[i]);
      addNode(node, newNode);
      if (i == st.length() - 1) {
        newNode->isend = true;
      }
      node = newNode;
      continue;
    } else {
      for (TrieNode *nod : node->child) {
        if (nod->getVal() == st[i]) {
          node = nod;
          found = true;
          if (i == st.length() - 1) {
            nod->isend = true;
          }
          break;
        }
      }
      if (!found) {
        TrieNode *newNode = new TrieNode(st[i]);
        addNode(node, newNode);
        if (i == st.length() - 1) {
          newNode->isend = true;
        }
      }
    }
  }
}
// 查询一个单词是否存在
bool Trie::Lookup(std::string st) {
  // TODO: 实现查询某个单词是否存在的逻辑
  // 提示：遍历字符串路径，如果路径中断或最后一个节点的isend为false，则返回false
  TrieNode *node = root;
  bool found = false;
  for (int i = 0; i < st.length(); i++) {
    for (TrieNode *nod : node->child) {
      if (nod->isend == false && i == st.length() - 1)
        return false;
      if (nod->getVal() == st[i]) {
        node = nod;
        found = true;
        break;
      }
    }
    if (!found)
      return false;
  }
  return true;
}

// 查询前缀的单词数量
int Trie::Prefix(std::string st) {
  // TODO: 实现查询前缀的单词数量的逻辑
  // 提示：找到前缀对应的最后一个节点，然后返回其prefix_count
  int count = 0;
  TrieNode *node = root;
  for (int i = 0; i < st.length(); i++) {
    for (TrieNode *nod : node->child) {
    }
  }

  return count;
}

int main() {
  Trie *trie = new Trie;
  trie->Insert("ab");
  if (trie->Lookup("ac")) {
    std::cout << "Yes\n";
  } else
    std::cout << "No\n";
  delete trie;
  return 0;
}