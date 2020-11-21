#include <iostream>
#include "../include/grammar.h"
#include "../include/cyk.h"
#include "../include/utilits.h"

/*
	A entrada deve ser uma gramática na forma normal de Chomsky
	Padrão para escrita no arquivo (gramatica.txt):
	Variavel(espaço)=>(espaço)VariavelVariavel(espaço)|(espaço)VariavelVariavel(espaço)|(espaço)VariavelVariavel
	Variavel(espaço)=>(espaço)terminal
*/
int main() {
	CYK cyk;
	Grammar grammar = loadFile();
	std::cout << "Palavra que será verificada: ";
	std::string word;
	std::getline(std::cin, word);
	std::cout << "\n" << grammar << std::endl;
	std::cout << "Resultado da aplicação do CYK na gramática e a palavra: " << cyk.algorithm(grammar, word) << std::endl;
	auto table = cyk.getTable();
	std::cout << "\n" << showTable(table);
	system("pause");
	return 0;
}
/*
	0^n1^n (01, 0011, 000111, ...)
	S => XB | AB
	X => AS
	A => 1
	B => 0

	0^n10^n (010, 00100, 0001000, ...)
	S => CB
	A => 1 | CB
	B => 0
	C => BA

	número de a's igual ao número de b's (aabb, baab, ababab, ...)
	S => CS | EB | DS | FA | FE | EF | AB | BA
	A => a
	B => b
	C => AB
	D => BA
	E => AS
	F => BS

	Palavras do tipo AcB, onde |A| é par e >= 2 e |B| é impar e >= 1
	S => JB
	A => GD | HD
	D => GC | a | HC | b
	C => GD | HD
	B => GE | a | HE | b
	E => GF | HF
	F => GE | a | HE | b
	G => a
	H => b
	I => c
	J => AI
*/