#include "stdafx.h"
#include "element.h"
#include "iostream"
#include "fstream"
#include "convert_utf_cp1251.h"

//������������

Element::Element() {//����������� ��� ��������� (������ ��������� � ���� ���� json)
	int ans = 0;
	int vector_degree = 0;
	//std::string vector_comments_utf;//������� ������ � ������ utf_8
	std::cout << "������� �������� �������� (������ �� ������� ����������, ��������, Ag (�������) ��� F (����)).\n";
	std::cin >> name;
Try_again:
	std::cout << "���������� ������ � �������� (������� 1 ��� 2)\n";
	std::cin >> ans;
	if (ans == 1) {
		amounts_atoms = monoatomic;
	}
	else if (ans == 2) {
		amounts_atoms = diatomic;
	}
	else {
		std::cout << "������������ ��������� ����� ������, ���������� �����.\n";
		goto Try_again;
	}
	std::cout << "������� ���������� �������� ���������\n";
	std::cin >> ans;
	std::cout << "������� ������� ��������� � ��������� � ���\n";
	for (int i = 0; i < ans; i++) {
		std::cout << "������� ���������:\n";
		std::cin >> vector_degree;
		oxidation_degree.push_back(vector_degree);
		std::cout << "���������\n";
		char vector_comments[100];//������ ��� ���������
		std::cin >> vector_comments;
		std::string vector_comments_utf = cp1251_to_utf8(vector_comments);//�������������� � ������ utf_8��� ���������� � ����� ���� json
		comments.push_back(vector_comments_utf);
	}
}

Element::Element(std::string n)//����������� ��� ������ �� ����� ���� json
{
	read_json(n);
}

//������

bool Element::is_empty() {
	if (name != "/0") return 1;
	else return 0;
}

void Element::show_oxidation_degree() {//����� �������� ���������
	int size = oxidation_degree.size();
	for (int i = 0; i < size; i++) {
		std :: cout << oxidation_degree[i] << "  ";
	}
	std::cout << "\n";
}

int Element::size_oxidation_degree() {//���������� �������� ���������
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

void Element::formula_oxide(int oxi_degree) {//������������ ������� ������ � ����������� �� �������� ������� ���������
	if (oxi_degree < 1 || oxi_degree > 8)
	{
	std::cout << "������� ������������ ����������� ��������.\n";
	oxi_degree = 0;
	oxygen_atom = 0;
	element_atom = 0;
	}
	else
		{
		if (oxi_degree == 2)//���� ���������� �������� ����� ����������� ���������
			{
			oxygen_atom = 1;
			element_atom = 1;
			}
		else if (oxi_degree == 1)//���� ���������� �������� ����� 1
			{
			oxygen_atom = 1;
			element_atom = 2;
			}
		if (oxi_degree > 2 && oxi_degree < 9)//���� ����������� �������� ������ 2
			{
			if (oxi_degree % 2)//���� ����������� �������� ��������
				{
				oxygen_atom = oxi_degree;
				element_atom = 2;
				}
			else//���� ���������� �������� ������
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
		//������ � ����������� ���������� ������ ���������, ����� ������������ ���������� ������ ��������
	}
}

void Element::chemical_reaction(int oxi_degree)
{
	formula_oxide(oxi_degree);//��������� ������� ������ � ��������� �������� ��������� ��������
	int k_el = 0;//����������� ����� ���������, ����� ������� ���������
	int k_o = 0;//����������� ����� ����������, ����� ������� ���������
	int k_ox = 0;//����������� ����� �������, ������ ������� ���������
	if (amounts_atoms == 1) {//��� ������������ �������� 
		if (oxygen_atom > 2)//���� ���������� ������ ��������� ������ 2
		{
			if (oxygen_atom % 2)// � �������� �����
			{
				k_o = oxygen_atom;
				k_ox = 2;
				k_el = element_atom * k_ox;
			}
			else//� ������ �����
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
		//����� ���������� ������� � ��������������
		int n = 0, m = 0;
		int k[] = { k_el, k_o, k_ox };//������ �������������
		std::string Str[] = { name + "+", "O2 = " };//������ ���������
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
	else {//��� ������������ ��������
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
		//����� ���������� ������� � ��������������
		int n = 0, m = 0;
		int k[] = { k_el, k_o, k_ox };//������ �������������
		std::string Str[] = { name + "2" + "+", "O2 = " };//������ ���������
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

nlohmann::json Element::to_json()//��� ������ ������ �� �������� � ���� ���� json
{
	nlohmann::json j;//������ ��� ������ � ���� json
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
			str_utf = j["comments"][i].get<std::string>();//��������� ������ ��� �������� ������ � ������� utf_8
			str_u = str_utf.c_str();
			comments.push_back(utf8_to_cp1251(str_u));//�������������� � ������ cp1251
		}
		
	}
	
	file.close();
}