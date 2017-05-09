#pragma once

#include <cstdint>
#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <cstddef>
#include <cstdint>

class HuffTree;


class TreeNode {
	friend HuffTree;
private:
	uint64_t frequency_;
	int id_;
	TreeNode* left_;
	TreeNode* right_;
	std::vector<bool> code_;
public:
	TreeNode(TreeNode* left, TreeNode* right, int id);
	TreeNode(uint64_t frequency, char character);
	uint64_t frequency() const;
	int id() const;
	void calculate_codes();
	bool operator==(const TreeNode& other) const;
	std::string codeForDebug() const;
};


class HuffTree {
private:
	std::vector<TreeNode> tree_;
	std::size_t leaf_num_;
public:
	HuffTree(const std::unordered_map<char, uint64_t>& char_frequency);
	std::unordered_map<char, std::vector<bool> > chars_to_code() const;
	std::unordered_map<std::vector<bool>, char> codes_to_char() const;
	const TreeNode& root() const; //for tests
};
