// convert_utf_cp1251.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "convert_utf_cp1251.h"
#include <Windows.h>

//перевод строки из cp1251 в utf_8
string cp1251_to_utf8(const char *str) {
	string res;
	int result_u, result_c;
	result_u = MultiByteToWideChar(1251, 0, str, -1, 0, 0);
	if (!result_u) { return 0; }
	wchar_t *ures = new wchar_t[result_u];
	if (!MultiByteToWideChar(1251, 0, str, -1, ures, result_u)) {
		delete[] ures;
		return 0;
	}
	result_c = WideCharToMultiByte(65001, 0, ures, -1, 0, 0, 0, 0);
	if (!result_c) {
		delete[] ures;
		return 0;
	}
	char *cres = new char[result_c];
	if (!WideCharToMultiByte(65001, 0, ures, -1, cres, result_c, 0, 0)) {
		delete[] cres;
		return 0;
	}
	delete[] ures;
	res.append(cres);
	delete[] cres;
	return res;
}
//обратное преобразование строки
string utf8_to_cp1251(const char *str) {
	string res;
	int result_u, result_c;
	result_u = MultiByteToWideChar(65001, 0, str, -1, 0, 0);
	if (!result_u) { return 0; }
	wchar_t *ures = new wchar_t[result_u];
	if (!MultiByteToWideChar(65001, 0, str, -1, ures, result_u)) {
		delete[] ures;
		return 0;
	}
	result_c = WideCharToMultiByte(1251, 0, ures, -1, 0, 0, 0, 0);
	if (!result_c) {
		delete[] ures;
		return 0;
	}
	char *cres = new char[result_c];
	if (!WideCharToMultiByte(1251, 0, ures, -1, cres, result_c, 0, 0)) {
		delete[] cres;
		return 0;
	}
	delete[] ures;
	res.append(cres);
	delete[] cres;
	return res;
}
