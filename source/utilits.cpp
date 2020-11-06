#include "../include/utilits.h"
#include <iostream>

/*Tabela gerada durante a aplicação do CYK*/
std::string showTable(std::vector<std::vector<std::string>>& table) {
	std::string ret("");
	for (int i = 0; i < (signed)table.size(); i++) {
		for (int j = 0; j < signed(table[i].size()); j++)
		{
			ret.append(table[i][j]).append("\t");
		}
		ret.append("\n");
	}
	return ret;
}

Grammar loadFile()
{
	std::ifstream reader("grammar.txt");
	Grammar grammar;
	if (reader.is_open()) {
		std::string line;
		std::vector<std::string> strings;
		std::set<char> variablesSet;
		std::set<char> terminalsSet;
		std::string startSymbol;
		int count = 0;
		while (std::getline(reader, line)) {
			strings = split(line.c_str(), ' ');
			if (count == 0) {
				startSymbol = strings[0];
				count++;
			}
			variablesSet.insert(strings[0][0]);
			for (int i = 1; i < signed(strings.size()); i++) {
				if (strings[i] != "|" && strings[i] != "=>") {
					grammar.addProduction(strings[0], strings[i].c_str());
					if (islower(strings[i][0])) {
						terminalsSet.insert(strings[i][0]);
					}
				}
			}
		}
		std::vector<char> variables(variablesSet.begin(), variablesSet.end());
		std::vector<char> terminals(terminalsSet.begin(), terminalsSet.end());
		grammar.setTerminals(terminals);
		grammar.setVariables(variables);
		grammar.setStartSymbol(startSymbol);
		reader.close();
	}
	return grammar;
}
