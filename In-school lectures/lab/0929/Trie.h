#include <iostream>
#include <string>
#include <vector>

// 字典树节点结构体
struct TrieNode {
    char val;
    bool isend;
    std::vector<TrieNode *> child;
    int prefix_count;

    // 默认构造函数
    TrieNode();

    // 带字符参数的构造函数
    TrieNode(char v);
    
    // 析构函数，负责输出信息
    ~TrieNode();

    char getVal(){
        return val;
    }

    bool getIsEnd(){
        return isend;
    }
};

// 字典树类
class Trie {
private:
    TrieNode *root;
    // 辅助函数，用于在析构函数中递归释放所有节点内存
    void destroy(TrieNode* node);
    void addNode(TrieNode* currentRoot, TrieNode* node);

public:
    // 构造函数
    Trie();

    // 析构函数
    ~Trie();
    
    // 向字典中插入一个单词
    void Insert(std::string st);

    // 查询某个单词是否存在于字典中
    bool Lookup(std::string st);

    // 查询某个字符串作为前缀的单词数量
    int Prefix(std::string st);
};