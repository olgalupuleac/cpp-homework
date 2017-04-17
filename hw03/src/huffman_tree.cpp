#include <iostream>
#include <assert.h>
#include <utility>
#include <fstream>
#include "huffman_tree.h"


using std::size_t;
using std::pair;
using std::unordered_map;
using std::priority_queue;
using std::ifstream;
using std::ofstream;
using std::vector;
using std::string;

struct ComparTreeNode {
    bool operator()(TreeNode* lhs, TreeNode* rhs) {
        return (lhs->frequency() > rhs->frequency() || (
            lhs->frequency() == rhs->frequency(
            ) && lhs->character() > rhs->character()));
    }
};

TreeNode::TreeNode() : left_(NULL), right_(NULL), code_("") {}
TreeNode::TreeNode(std::size_t frequency,
    TreeNode* left, TreeNode* right, int character) :frequency_(
    frequency), character_(character), left_(left), right_(right), code_("") {
}
TreeNode::TreeNode(std::size_t frequency, char character) :frequency_(
    frequency), character_(character), left_(NULL), right_(NULL), code_("") {}

std::size_t TreeNode::frequency() const {
    return frequency_;
}

int TreeNode::character() const {
    return character_;
}

string TreeNode::code() const {
    return code_;
}



HuffTree::HuffTree(
    const unordered_map<char, size_t>& char_frequency):leaf_num_(
        char_frequency.size())
{
    assert(char_frequency.size() < 257);
    tree_.reserve(2 * char_frequency.size() - 1);
    for (pair<char, size_t> used_char : char_frequency) {
        tree_.push_back(TreeNode(used_char.second, used_char.first));
        assert(!tree_.back().left_ && !tree_.back().right_);
        eprintf("adding in tree freq %d and char %c\n", (int)used_char.second, used_char.first);
    }
    priority_queue<TreeNode*, vector<TreeNode*>, ComparTreeNode> sorted_nodes;
    for (size_t i = 0; i < leaf_num(); i++) {
        sorted_nodes.push(&tree_[i]);
    }
    int char_id = 300; //differs new nodes in CompareTreeNode for correct decoding
    while (sorted_nodes.size()) {
        TreeNode* first = sorted_nodes.top();
        eprintf("freq %d and char %c\n", (int)first->frequency_, first->character_);
        sorted_nodes.pop();
        if (sorted_nodes.empty()) break;
        TreeNode* second = sorted_nodes.top();
        eprintf("freq %d and char %c\n", (int)second->frequency_, second->character_);
        sorted_nodes.pop();
        TreeNode node(first->frequency() + second->frequency(), 
            first, second, char_id++);
        tree_.push_back(node);
        eprintf("pushing new node\n");
        eprintf("its code %s\n", node.code_.c_str());
        sorted_nodes.push(&tree_.back());
    }
}

void HuffTree::get_code(TreeNode* node) {
    if (!node->left_) return;
    eprintf("%c\n", node->left_->character_);
    node->left_->code_ = node->code_ + '0';
    node->right_->code_ = node->code_ + '1';
    get_code(node->left_);
    get_code(node->right_);
}

void HuffTree::calculate_codes() {
    eprintf("start coding\n");
    get_code(&tree_.back());
}

std::size_t HuffTree::leaf_num() const {
    return leaf_num_;
}

TreeNode* HuffTree::root() {
    return &tree_.back();
}

std::pair<char, std::size_t> HuffTree::get(std::size_t i) const {
    return std::make_pair(tree_[i].character(), tree_[i].frequency());
}

void code(HuffTree& tree, unordered_map<char, string>& codes) {
    for (size_t i = 0; i < tree.leaf_num(); i++) {
        eprintf("%c %s\n", tree.tree_[i].character(), tree.tree_[i].code().c_str());
        codes[tree.tree_[i].character()] = tree.tree_[i].code();
    }
    eprintf("all codes\n");
}

void decode(HuffTree& tree, unordered_map<string, char>& keys) {
    eprintf("leaf number %d\n", (int)tree.leaf_num());
    for (size_t i = 0; i < tree.leaf_num(); i++) {
        eprintf("%c %s\n", tree.tree_[i].character(), tree.tree_[i].code().c_str());
        keys[tree.tree_[i].code()] = tree.tree_[i].character();
    }
        
}