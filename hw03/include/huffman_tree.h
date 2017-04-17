#pragma once


#include <cstdio>

#ifdef DEBUG
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define eprintf(...)
#endif


#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <cstddef>
#include <cstdint>

class HuffTree;
void code(HuffTree& tree, std::unordered_map<char, std::string>& codes);
void decode(HuffTree& tree, std::unordered_map<std::string, char>& keys);

class TreeNode {
    friend HuffTree;
private:
    std::size_t frequency_;
    int character_;
    TreeNode* left_;
    TreeNode* right_;
    std::string code_;
public:
    TreeNode();
    TreeNode(std::size_t frequency, TreeNode* left, TreeNode* right, int character);
    TreeNode(std::size_t frequency, char character);
    std::size_t frequency() const;
    int character() const;
    std::string code() const;
};


class HuffTree {
    friend void code(HuffTree& tree, std::unordered_map<char, std::string>& codes);
    friend void decode(HuffTree& tree, std::unordered_map<std::string, char>& keys);
private:
    std::vector<TreeNode> tree_;
    //HuffTree(const HuffTree& other){}
    //HuffTree& operator=(const HuffTree other){}
    std::size_t leaf_num_;
    void get_code(TreeNode* node);
public:
    HuffTree(){}
    HuffTree(const std::unordered_map<char, std::size_t>& char_frequency);
    void calculate_codes();
    std::size_t leaf_num() const;
    std::pair<char, std::size_t> get(std::size_t i) const;
    TreeNode* root();
};
