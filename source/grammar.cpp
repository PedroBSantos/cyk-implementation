#include "../include/grammar.h"

Grammar::Grammar() {}

Grammar::Grammar(std::vector<char> variables, std::vector<char> terminals, std::string startSymbol) :
	variables(variables), terminals(terminals), startSymbol(startSymbol) {}

Grammar::Grammar(const Grammar& grammar) :
	variables(grammar.variables), terminals(grammar.terminals), productions(grammar.productions),
	startSymbol(grammar.startSymbol), invProductions(grammar.invProductions) {}

std::vector<char>& Grammar::getVariables()
{
	return this->variables;
}

std::vector<char>& Grammar::getTerminals()
{
	return this->terminals;
}

void Grammar::setVariables(std::vector<char> variables)
{
	this->variables = variables;
}

void Grammar::setTerminals(std::vector<char> terminals)
{
	this->terminals = terminals;
}

std::string Grammar::getStartSymbol()
{
	return this->startSymbol;
}

void Grammar::setStartSymbol(std::string startSymbol)
{
	this->startSymbol = startSymbol;
}

std::multimap<std::string, char>& Grammar::getProductions()
{
	return this->productions;
}

std::multimap<std::string, std::string>& Grammar::getInvProductions()
{
	return this->invProductions;
}

void Grammar::addProduction(std::string head, const char* body)
{
	this->productions.insert(std::make_pair(body, head[0]));
	this->invProductions.insert(std::make_pair(head, body));
}


std::ostream& operator<<(std::ostream& ostream, const Grammar& grammar)
{
	ostream << "Gramática: " << "\n";
	for (auto iterador1 = grammar.invProductions.begin(); iterador1 != grammar.invProductions.end(); iterador1++) {
		ostream << iterador1->first << " => " << iterador1->second << "\n";
	}
	return ostream;
}
