#pragma once
#include <string>
#include <vector>
#include "json.hpp"
#include <vector>

enum atoms{ monoatomic = 1, diatomic = 2};//тип молекулы одноатомная или двухатомная
class Element
{
private:
	std::string name;//название элемента
	atoms amounts_atoms;//количество атомов
	std::vector <int> oxidation_degree;//степень окисления элемента при химических реакциях: Element + O2
	std::vector <std::string> comments;//
	int oxygen_atom;//количество атомов кислорода в формуле оксида с элементом
	int element_atom;//количество атомов элемента в формуле оксида
public:
	Element();
	Element(std::string n);
	bool is_empty();//проверяет заполнены ли поля объекта
	void show_oxide();//выводит формулу оксида элемента
	void chemical_reaction(int oxi_degree); //выводит химическую реакцию элемент + кислород с расставленными коэффициентами
	nlohmann::json to_json();//перевод полей класса в объект json
	void read_json(std :: string str);//чтение данных в фал типа json
	void formula_oxide(int oxi_degree);//формула оксида в зависимости от степени окисления (oxi_degree)
	void show_oxidation_degree();//вывод степеней оксиления
	int size_oxidation_degree();//размер вектора
	bool check_oxidation_degree(int user_oxidation_degree);//проверка введенной степени окисления
	int get_oxidation_degree();//получить степень оксиления , если размер вектора со степенями равен 1
};
