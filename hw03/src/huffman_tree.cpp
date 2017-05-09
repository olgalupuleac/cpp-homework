#include <iostream>
#include <assert.h>
#include <utility>
#include <fstream>
#include "huffman_tree.h"
#include "debug.h"


using std::pair;
using std::unordered_map;
using std::priority_queue;
using std::istream;
using std::ostream;
using std::vector;
using std::string;

struct TreeNodeComparator {
	bool operator()(TreeNode* lhs, TreeNode* rhs) {
		if (lhs->frequency() != rhs->frequency())
			return  lhs->frequency() > rhs->frequency();
		return lhs->id() > rhs->id();
	}
};


TreeNode::TreeNode(TreeNode* left,
	TreeNode* right, int id) :frequency_(
		left->frequency_ + right->frequency_), id_(id), left_(left), right_(right) {
}
TreeNode::TreeNode(uint64_t frequency, char character) : frequency_(
	frequency), id_(character), left_(NULL), right_(NULL) {}

uint64_t TreeNode::frequency() const {
	return frequency_;
}

int TreeNode::id() const {
	return id_;
}


void TreeNode::calculate_codes() {
	if (!left_)
		return;
	left_->code_ = code_;
	right_->code_ = code_;
	left_->code_.push_back(0);
	right_->code_.push_back(1);
	left_->calculate_codes();
	right_->calculate_codes();
}

bool TreeNode::operator==(const TreeNode& other) const {
	if (!left_)
		return !other.left_ && other.id_ == id_ && other.frequency_ == frequency_;
	if (!other.left_) 
		return false;
	return other.id_ == id_ && other.frequency_ == frequency_ && 
		*left_ == *other.left_ && *right_ == *other.right_;
}

string TreeNode::codeForDebug() const {
	string code;
	for (bool c : code_)
		code += std::to_string(c);
	return code;
}


HuffTree::HuffTree(
	const unordered_map<char, uint64_t>& char_frequency) :leaf_num_(
		char_frequency.size())
{
	assert(char_frequency.size() < 257);
	tree_.reserve(2 * char_frequency.size());
	for (pair<char, uint64_t> used_char : char_frequency) {
		tree_.push_back(TreeNode(used_char.second, used_char.first));
		assert(!tree_.back().left_ && !tree_.back().right_);
		eprintf("adding in tree freq %d and char %c\n", (int)used_char.second, used_char.first);
	}
	priority_queue<TreeNode*, vector<TreeNode*>, TreeNodeComparator> sorted_nodes;
	for (std::size_t i = 0; i < leaf_num_; i++) {
		sorted_nodes.push(&tree_[i]);
	}
	int char_id = 1000; //differs new nodes in TreeNodeComparator for correct decoding
	while (sorted_nodes.size()) {
		TreeNode* first = sorted_nodes.top();
		sorted_nodes.pop();
		if (sorted_nodes.empty()) 
			break;
		TreeNode* second = sorted_nodes.top();
		sorted_nodes.pop();
		tree_.push_back(TreeNode(first, second, char_id++));
		eprintf("pushing new node\n");
		sorted_nodes.push(&tree_.back());
	}
	if(tree_.size())
		tree_.back().calculate_codes();
}


unordered_map<char, vector<bool>> HuffTree::chars_to_code() const {
	unordered_map<char, vector<bool> > codes;
	for (std::size_t i = 0; i < leaf_num_; i++) {
		codes[tree_[i].id()] = tree_[i].code_;
	}
	eprintf("all codes\n");
	return codes;
}

unordered_map<vector<bool>, char> HuffTree::codes_to_char() const {
	unordered_map<vector<bool>, char> keys;
	eprintf("leaf number %d\n", (int)leaf_num_);
	for (std::size_t i = 0; i < leaf_num_; i++) {
		keys[tree_[i].code_] = tree_[i].id();
		eprintf("c %c code %s\n", tree_[i].id(), tree_[i].codeForDebug().c_str());
	}
	return keys;
}

const TreeNode& HuffTree::root() const {
	return tree_.back();
}
