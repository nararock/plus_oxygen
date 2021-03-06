// plus_oxygen.cpp : Defines the entry point for the console application.
//editor is the magic word

#include "stdafx.h"
#include "element.h"
#include "iostream"
#include "fstream"

using namespace std;

int main()
{
	system("chcp 1251 > text");
	setlocale(LC_ALL, "Russian");
	string name_element;
	while (true) {
		cout << "Введите название элемента (символ из таблицы Менделеева, например, Ag (серебро) или F (фтор)).\n";
  		cin >> name_element;
		cin.ignore(100, '\n');
		if (name_element == "editor") {
			break;
		}
		Element My_element(name_element);
		int check_ans = 0;
		bool check_object = My_element.is_empty();
		if (check_object == 0) {
			cout << "Данного элемента нет в базе данных.\n"
				<< "Выберите дальнейшее действие (1 или 2):"
				<< "\t1. Введете новый элемент\n"
				<< "\t2. Завершить работу\n";
		}
		if (check_ans == 1) {
			continue;
		}
		else if(check_ans == 2) { break; }
		int size_degree = My_element.size_oxidation_degree();//количество степеней окисления
		if (size_degree > 1) {
			while (true) {
				cout << "Степени окисления элемента " << name_element << " :" << endl;
				My_element.show_oxidation_degree();
				cout << "Введите степень окисления, с которой будет протекать химическая реакция\n";
				int user_degree = 0;
				cin >> user_degree;
				bool check = My_element.check_oxidation_degree(user_degree);
				if (!check) {
					cout << "Вы ввели неправильную степень окисления, попробуйте снова!\n";
					continue;
				}
				My_element.chemical_reaction(user_degree);//выводим уравнение химической реакции
				cout << "Хотите вывести уравнение химической реакции с другой степенью окисления (да или нет)?\n";
				string answer;
				cin >> answer;
				if (answer != "да") {
					break;
				}
			}
		}
		else {
			int temp_degree = My_element.get_oxidation_degree();
			My_element.chemical_reaction(temp_degree);//выводим уравнение химической реакции
		}
		
		cout << "Ваши дальнейшие действия (введите номер ответа): \n"
			<< "\t 1. Химическая реакция с новым элементом\n"
			<< "\t 2. Закончить работу и выйти\n";
		int answer = 0;
		cin >> answer;
		if (answer == 2) {
			break;
		}	
	}
	if (name_element == "editor") {//режим записи элементов в файл 
		nlohmann::json j_array = nlohmann::json::array();//массив для записи элементов в файл
		fstream file;
		file.open("elements.json");
		file >> j_array;
		int count = j_array.size();//счетчик элементов для массива
		while (true) {
			int answer;
			Element element_editor;
			nlohmann::json j = element_editor.to_json();
			j_array[count] = j;
			count++;
			cout << "Что дальше (выбрать номер действия):\n"
				<< "\t1. Записать еще элемент в файл\n"
				<< "\t2. Завершить работу\n";
			cin.ignore(100, '\n');
			cin >> answer;
			if (answer == 2) {
				break;
			}
		}
		file.seekg(0);
		file << j_array;
		cout << "Файл записан\n";
		file.close();
	}
	return 0; 
}

