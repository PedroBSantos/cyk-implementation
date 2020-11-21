#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <map>
#include <vector>
#include <string>
#include <ostream>

class Grammar
{
private:
	//Representa os não-terminals da gramática
	std::vector<char> variables;
	//Representa o alfabeto da gramática
	std::vector<char> terminals;
	//mapeia um terminal ou não terminal para um conjunto de produções que geram esse terminal ou não terminal
	std::multimap<std::string, char> productions;
	//Mapeia um não terminal para as suas produções
	std::multimap<std::string, std::string> invProductions;
	//Símbolo inicial da gramática
	std::string startSymbol;
public:
	Grammar();
	Grammar(std::vector<char> variables, std::vector<char> terminals, std::string startSymbol);
	Grammar(const Grammar& grammar);
	~Grammar() = default;
	std::vector<char>& getVariables();
	std::vector<char>& getTerminals();
	void setVariables(std::vector<char> variables);
	void setTerminals(std::vector<char> terminals);
	std::string getStartSymbol();
	void setStartSymbol(std::string startSymbol);
	std::multimap<std::string, char>& getProductions();
	std::multimap<std::string, std::string>& getInvProductions();
	void addProduction(std::string head, const char* body);
	friend std::ostream& operator<<(std::ostream& ostream, const Grammar& grammar);
};

#endif
