#ifndef CYK_H
#define CYK_H

#include "grammar.h"
#include <algorithm>
#include <string>

class CYK
{
private:
	std::vector<std::vector<std::string>> table;
	void startTable(int wordLength);
public:
	CYK() = default;
	CYK(const CYK& cyk);
	~CYK() = default;
	std::string algorithm(Grammar& grammar, std::string word);
	const std::vector<std::vector<std::string>>& getTable() const;
};

#endif
