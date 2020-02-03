#include "stdafx.h"
#include "element.h"
#include "iostream"
#include "fstream"
#include "convert_utf_cp1251.h"

//Конструкторы

Element::Element() {//конструктор для редактора (запись элементов в файл типа json)
	int ans = 0;
	int vector_degree = 0;
	//std::string vector_comments_utf;//перевод строки в формат utf_8
	std::cout << "Введите название элемента (символ из таблицы Менделеева, например, Ag (серебро) или F (фтор)).\n";
	std::cin >> name;
Try_again:
	std::cout << "Количество атомов в молекуле (введите 1 или 2)\n";
	std::cin >> ans;
	if (ans == 1) {
		amounts_atoms = monoatomic;
	}
	else if (ans == 2) {
		amounts_atoms = diatomic;
	}
	else {
		std::cout << "Неправильное введенное число атомов, попробуйте снова.\n";
		goto Try_again;
	}
	std::cout << "Введите количество степеней окисления\n";
	std::cin >> ans;
	std::cout << "Введите степень окисления и замечание к ней\n";
	for (int i = 0; i < ans; i++) {
		std::cout << "Степень окисления:\n";
		std::cin >> vector_degree;
		oxidation_degree.push_back(vector_degree);
		std::cout << "Замечание\n";
		char vector_comments[100];//массив для замечание
		std::cin >> vector_comments;
		std::string vector_comments_utf = cp1251_to_utf8(vector_comments);//преобразование в формат utf_8для сохранения в файле типа json
		comments.push_back(vector_comments_utf);
	}
}

Element::Element(std::string n)//конструктор для чтения из файла типа json
{
	read_json(n);
}

//Методы

bool Element::is_empty() {
	if (name != "/0") return 1;
	else return 0;
}

void Element::show_oxidation_degree() {//вывод степеней окисления
	int size = oxidation_degree.size();
	for (int i = 0; i < size; i++) {
		std :: cout << oxidation_degree[i] << "  ";
	}
	std::cout << "\n";
}

int Element::size_oxidation_degree() {//количество степеней окисления
	return (oxidation_degree.size());
}

bool Element::check_oxidation_degree(int user_oxidation_degree) {
	int size = oxidation_degree.size();
	bool answer = 0;
	for (int i = 0; i < size; i++) {
		if (oxidation_degree[i] == user_oxidation_degree) {
			answer = 1;
			break;
		}
	}
	return answer;
}

int Element::get_oxidation_degree() {
	return oxidation_degree[0];
}

void Element::formula_oxide(int oxi_degree) {//формирование формулы оксида в зависимости от выбранно степени окисления
	if (oxi_degree < 1 || oxi_degree > 8)
	{
	std::cout << "Введена неправильная валентность элемента.\n";
	oxi_degree = 0;
	oxygen_atom = 0;
	element_atom = 0;
	}
	else
		{
		if (oxi_degree == 2)//если валетность элемента равна валентности кислорода
			{
			oxygen_atom = 1;
			element_atom = 1;
			}
		else if (oxi_degree == 1)//если валетность элемента равна 1
			{
			oxygen_atom = 1;
			element_atom = 2;
			}
		if (oxi_degree > 2 && oxi_degree < 9)//если валентность элемента больше 2
			{
			if (oxi_degree % 2)//если валентность элемента нечетная
				{
				oxygen_atom = oxi_degree;
				element_atom = 2;
				}
			else//если валетность элемента четная
				{
				oxygen_atom = oxi_degree / 2;
				element_atom = 1;
				}
			}
		}
	}

void Element::show_oxide()
{
	if (element_atom !=1 && oxygen_atom != 1)
	{
		std::cout << name << element_atom << "O" << oxygen_atom << std::endl;
	}
	else if (element_atom == 1 && oxygen_atom != 1)
	{
		std::cout << name << "O" << oxygen_atom << std::endl;
	}
	else if (element_atom != 1 && oxygen_atom == 1)
	{
		std::cout << name << element_atom << "O" << std::endl;
	}
	else
	{
		std::cout << name << "O" << std::endl;
		//начнем с уравнивания количества атомов кислорода, затем уравнивается количество атомов элемента
	}
}

void Element::chemical_reaction(int oxi_degree)
{
	formula_oxide(oxi_degree);//формируем формулу оксида с выбранной степенью окисления вещества
	int k_el = 0;//коэффициент перед элементом, левая сторона уравнения
	int k_o = 0;//коэффициент перед кислородом, левая сторона уравнения
	int k_ox = 0;//коэффициент перед оксидом, правая сторона уравнения
	if (amounts_atoms == 1) {//для одноатомного элемента 
		if (oxygen_atom > 2)//если количество атомов кислорода больше 2
		{
			if (oxygen_atom % 2)// и нечетное число
			{
				k_o = oxygen_atom;
				k_ox = 2;
				k_el = element_atom * k_ox;
			}
			else//и четное число
			{
				k_o = oxygen_atom / 2;
				k_el = element_atom;
				k_ox = 1;
			}
		}
		else if (oxygen_atom == 2)
		{
			k_o = 1;
			k_ox = 1;
			k_el = 1;
		}
		else if (oxygen_atom == 1)
		{
			k_o = 1;
			k_ox = 2;
			k_el = 2;
		}
		//вывод химической реакции с коэффициентами
		int n = 0, m = 0;
		int k[] = { k_el, k_o, k_ox };//массив коэффициентов
		std::string Str[] = { name + "+", "O2 = " };//массив выражений
		for (int i = 1; i <= 5; i++)
		{
			if ((i % 2 != 0) && (k[n] != 1))
			{
				std::cout << k[n];
				n++;
			}
			else if (i % 2 != 0) {
				n++;
			}
			else if ((i % 2 == 0))
			{
				std::cout << Str[m];
				m++;
			}
		}
		show_oxide();
	}
	else {//для двухатомного элемента
		if (oxygen_atom == element_atom) {
			k_el = 1;
			k_o = 1;
			k_ox = 2;
		}
		else if (element_atom == 2 && oxygen_atom == 1) {
			k_el = 2;
			k_o = 1;
			k_ox = 2;
		}
		else if (element_atom == 1 && element_atom < oxygen_atom) {
			k_el = 1;
			k_o = oxygen_atom;
			k_ox = 2;
		}
		else if (element_atom == 2 && oxygen_atom > 2) {
			k_el = 2;
			k_o = oxygen_atom;
			k_ox = 2;
		}
		//вывод химической реакции с коэффициентами
		int n = 0, m = 0;
		int k[] = { k_el, k_o, k_ox };//массив коэффициентов
		std::string Str[] = { name + "2" + "+", "O2 = " };//массив выражений
		for (int i = 1; i <= 5; i++)
		{
			if ((i % 2 != 0) && (k[n] != 1))
			{
				std::cout << k[n];
			}
			else if (i % 2 != 0) {
				n++;
			}
			else if ((i % 2 == 0))
			{
				std::cout << Str[m];
				m++;
			}
		}
		show_oxide();
	}
	
}

nlohmann::json Element::to_json()//для записи данных об элементе в файл типа json
{
	nlohmann::json j;//объект для записи в файл json
	j["name"] = name;
	j["amounts_atoms"] = amounts_atoms;
	j["oxidation_degree"] = oxidation_degree;
	j["comments"] = comments;
	return j;
}

void Element::read_json(std::string str) {
	std::fstream file;
	file.open("elements.json");
	nlohmann::json j;
	string str_utf;
	const char* str_u;
	nlohmann::json j_array = nlohmann::json ::array();
	file >> j_array;
	nlohmann::json::iterator it = j_array.begin();
	for (it; it != j_array.end(); it++) {
		j = *it;
		if (j["name"] == str) {
			break;
		}
	}
	if (it != j_array.end()) {
		name = j["name"].get<std::string>();
		amounts_atoms = j["amounts_atoms"];
		int size_degree = j["oxidation_degree"].size();
		for (int i = 0; i < size_degree; i++) {
			oxidation_degree.push_back(j["oxidation_degree"][i]);
			str_utf = j["comments"][i].get<std::string>();//временная строка для хранение строки в формате utf_8
			str_u = str_utf.c_str();
			comments.push_back(utf8_to_cp1251(str_u));//преобразование в формат cp1251
		}
		
	}
	
	file.close();
}