#pragma once
#include <string>
#include <vector>
#include "json.hpp"
#include <vector>

enum atoms{ monoatomic = 1, diatomic = 2};//��� �������� ����������� ��� �����������
class Element
{
private:
	std::string name;//�������� ��������
	atoms amounts_atoms;//���������� ������
	std::vector <int> oxidation_degree;//������� ��������� �������� ��� ���������� ��������: Element + O2
	std::vector <std::string> comments;//
	int oxygen_atom;//���������� ������ ��������� � ������� ������ � ���������
	int element_atom;//���������� ������ �������� � ������� ������
public:
	Element();
	Element(std::string n);
	bool is_empty();//��������� ��������� �� ���� �������
	void show_oxide();//������� ������� ������ ��������
	void chemical_reaction(int oxi_degree); //������� ���������� ������� ������� + �������� � �������������� ��������������
	nlohmann::json to_json();//������� ����� ������ � ������ json
	void read_json(std :: string str);//������ ������ � ��� ���� json
	void formula_oxide(int oxi_degree);//������� ������ � ����������� �� ������� ��������� (oxi_degree)
	void show_oxidation_degree();//����� �������� ���������
	int size_oxidation_degree();//������ �������
	bool check_oxidation_degree(int user_oxidation_degree);//�������� ��������� ������� ���������
	int get_oxidation_degree();//�������� ������� ��������� , ���� ������ ������� �� ��������� ����� 1
};
