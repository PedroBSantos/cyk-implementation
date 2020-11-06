#include "../include/cyk.h"

CYK::CYK(const CYK& cyk) : table(cyk.table) {}

const std::vector<std::vector<std::string>>& CYK::getTable() const
{
	return this->table;
}

/*
	Responsável por gerar uma tabela de dimensão n X n, onde n é o tamanho da palavra.
	No fim da aplicação do algoritmo, o triângulo superior da matriz estará preenchido.
*/
void CYK::startTable(int wordLength)
{
	for (int i = 0; i < wordLength; i++) {
		this->table.push_back(std::vector<std::string>(wordLength));
	}
}

std::string CYK::algorithm(Grammar& grammar, std::string word)
{
	if (word.empty()) {
		return "A palavra n�o � gerada pela gram�tica.";
	}
	int wordLength = signed(word.size());
	int count = 0;
	this->startTable(wordLength);
	//Realizando o primeiro passo do algoritmo (Encontrar as produções que geram cada símbolo da palavra)
	//Na diagonal principal da matriz, cada posição [i][j] da matriz irá conter os não-terminais que geram o símbolo que está sendo analisado na iteração i.
	//A diagonal principal representa os nós folha da arvore de derivação da palavra.
	for (int i = 0; i < wordLength; i++) {
		char aux1[2];
		aux1[1] = '\0';
		aux1[0] = word[i];
		const char* aux2 = &aux1[0];
		//Obtendo todas as produções para o símbolo atual(Produções do tipo A -> a)
		auto productions = grammar.getProductions().equal_range(aux2);
		std::string aux3 = "";
		//Percorrendo as produções para o símbolo atual
		for (auto iterador3 = productions.first; iterador3 != productions.second; iterador3++) {
			aux1[0] = iterador3->second;
			aux1[1] = '\0';
			aux2 = &aux1[0];
			//aux3 = aux2;
			if (aux3.empty()) {
				aux3.append(aux2);
			}
			else {
				aux3.append(", ").append(aux2);
			}
		}
		//Adicionando o não-terminal que gera o símbolo atual(palavra[i])
		this->table[count][count] = aux3;
		count++;
	}
	//Obtendo as regras de produção da gramática
	auto productions = grammar.getInvProductions();
	int j = 0;
	//A cada iteração l, verifica se é possível gerar l símbolos da palavra através das regras da gramática.
	//Com l = 2, verifica se � poss�vel gerar 2 s�mbolos da palavra atrav�s das regras da gram�tica. Por exemplo, abaab. Verifica se � poss�vel gerar "ab", depois "ba", por fim "ab"
	//Com l = 3, verifica se � poss�vel gerar 3 s�mbolos da palavra atrav�s das regras da gram�tica. Por exemplo, abaab. Verifica se � poss�vel gerar "aba", depois "baa", depois "aab"
	//Com l = 4, at� l = tamanho da palavra.
	//No final, com l = tamanho da palavra, verifica se � poss�vel gerar os n s�mbolos da palavra atrav�s do s�mbolo inicial da gram�tica. Por exemplo, abaab, Com o resultado obtido nas itera��es anteriores,
	//conseguimos verificar se � poss�vel gerar a palavra inteira pois, o algoritmo gera uma esp�cie de arvore de deriva��o. Cada itera��o l utiliza de resultados gerados em itera��es 
	//anteriores para conseguir os resultados da itera��o atual.
	for (int l = 2; l < wordLength + 1; l++) {
		//Faz o que foi escrito nas linhas 63, 64, 65, 66. Obter substrings da palavra para verificar se � poss�vel gera-las. In�cio da substring.
		for (int i = 0; i < wordLength - l + 1; i++) {
			j = i + l - 1;
			//Faz o que foi escrito nas linhas 63, 64, 65, 66. Obter substrings da palavra para verificar se � poss�vel gera-las. Fim da substring. Come�a em palavra[i] e termina em palavra[k].
			for (int k = i; k < j; k++) {
				//Obtendo um n� da arvore que foi gerado em itera��es anteriores
				std::string& aux1 = this->table[i][k];
				//Obtendo um n� da arvore que foi gerado em itera��es anteriores
				std::string& aux3 = this->table[k + 1][j];
				//N� da arvore que ser� gerado na itera��o atual
				std::string& aux5 = this->table[i][j];
				//Procurando por produ��es do tipo A -> BC
				//Verificando se existe alguma produ��o na gram�tica do tipo P -> this->tabela[i][k]this->tabela[k + 1][j]
				//Se existir, a cabe�a dessa produ��o(P) � adicionada em this->tabela[i][j]
				//A compara��o se da entre 2 vari�veis (aux1 e aux3), pois juntas representam regras do tipo A => BC, onde B � aux1 e C � aux3. aux5 representa a cabe�a da produ��o A => BC.
				for (auto iterador = productions.begin(); iterador != productions.end(); iterador++) {
					if (std::find(aux1.begin(), aux1.end(), iterador->second[0]) != aux1.end() &&
						std::find(aux3.begin(), aux3.end(), iterador->second[1]) != aux3.end()) {
						if (aux5 != "") {
							if (std::find(aux5.begin(), aux5.end(), iterador->first[0]) == aux5.end()) {
								aux5.append(", ").append(iterador->first);
							}
						}
						else {
							aux5.append(iterador->first);
						}
					}
				}
			}
		}
	}
	std::string aux = this->table[0][wordLength - 1];
	auto iterador = std::find(aux.begin(), aux.end(), grammar.getStartSymbol()[0]);
	//A palavra � reconhecida se o s�mbolo inicial da gram�tica estiver na posi��o [0][tamanho_palavra - 1] da tabela
	return iterador != aux.end() ? "A palavra � gerada pela gram�tica." : "A palavra n�o � gerada pela gram�tica.";
}
