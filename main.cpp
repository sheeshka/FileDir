#include <iostream>
#include <windows.h>
#include <string>
#include <io.h>
#include <fcntl.h>
#include <Shlwapi.h>
#include <fstream>
using namespace std;

void display_folder(int lvl, wstring a, ofstream& outFile)
{
	int text = 0;
	int background = 14;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
	int i = 0;
	wstring space = L"    ";
	wstring pred = L"";
	while (i < lvl)
	{
		pred = pred + space;
		i++;
	}
	a = pred + a;
	wcout << a << L" Уровень" << lvl << L"\n";
	wstring ws = a;
	string s(ws.begin(), ws.end());
	outFile << s << " Уровень " << lvl << endl;
}

void display_file(int lvl, wstring a, ofstream& outFile)
{
	int text = 11;
	int background = 13;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
	int i = 0;
	wstring space = L"    ";
	wstring pred = L"";
	while (i < lvl)
	{
		pred = pred + space;
		i++;
	}
	a = pred + a;
	wcout << a << L"\n";
	wstring ws = a;
	string s(ws.begin(), ws.end());
	outFile << s << endl;
}


void prohod(wstring adress2, int& lvl, ofstream& outFile)
{
	lvl++;
	//wcout << L"\nНовый уровень: " << lvl;
	WIN32_FIND_DATA fd;							// переменая для атрибутов 
	HANDLE hFind;								// переменая для next
	wchar_t text[MAX_PATH];
	wchar_t buffer[MAX_PATH];					// Переменная которая хранит путь к вызываемой программе
	GetCurrentDirectory(MAX_PATH, buffer);		// возвращает путь к программе
	int i = 0;
	while (adress2[i] != '\0')
	{
		text[i] = adress2[i];
		text[i + 1] = '\\';
		text[i + 2] = '*';
		text[i + 3] = '.';
		text[i + 4] = '*';
		text[i + 5] = '\0';
		i++;
	}

	hFind = FindFirstFile(text, &fd);			// Ищем первый файл = .
												//wcout << fd.cFileName << endl;
	if (hFind == INVALID_HANDLE_VALUE)		// если ошибка
	{
		wcout << L"Ошибка, какталог не найден!" << endl;
		outFile << "Ошибка, какталог не найден!" << endl;
	}
	else
	{
		FindNextFile(hFind, &fd);					// Ищем второй файл = ..
		int j = 1;
		while (j != 0)
		{
			i = FindNextFile(hFind, &fd);			// для отслеживания нуля
			if (i == 0)
			{
				break;
			}
			if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)   // Если папка
			{
				wstring a = fd.cFileName;
				//wcout << fd.cFileName;
				display_folder(lvl, a, outFile);
				int re = 1;
				i;
				wstring ba;
				ba = adress2;
				adress2 = adress2 + L"\\" + fd.cFileName;
				prohod(adress2, lvl, outFile);
				adress2 = ba;
				lvl--;
			}
			else if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))  // Если файл
			{
				wstring a = fd.cFileName;
				display_file(lvl, a, outFile);
				//wcout << a << endl;
				wstring ws = a;
				string s(ws.begin(), ws.end());
				//outFile << s << endl;
			}

		}
	}
	//FindClose(hFind);							// Закрываем поиск

}


int main()
{
	setlocale(LC_ALL, "Russian");				// коректное отображение на русском
	_setmode(_fileno(stdout), _O_U8TEXT);
	ofstream outFile;								// для записи
	outFile.open("prob2.txt");						// открываем файл txt (или создаём) для записи
													/* Предпрограмма */
	int selection = 2;									// Переменная хранит значение с клавиатуры
	wcout << L"1 - ввод адресса с клавиатуры \nне 1(к примеру 2) - адресс папки программы \nВведите ваш выбор:" << endl;
	wcin >> selection;
	wchar_t adress[MAX_PATH];
	int size;
	if (selection == 1)
	{
		wcin >> adress;
		wcout << L"Начальный каталог: ";
		wcout << adress << endl;
		int i = 0;
		while (adress[i] != 0)
		{
			adress[i];
			i++;
			if (adress[i] == '\0')
			{
				break;
			}
		}
		//wcout << adress << endl;
	}
	else
	{
		wchar_t buffer[MAX_PATH];					// Переменная которая хранит путь к вызываемой программе
		GetCurrentDirectory(MAX_PATH, buffer);		// возвращает путь к программе
		wcout << L"Начальный каталог: ";
		outFile << "Начальный каталог: " << endl;					// Записываем строку в файл
		int i = 0;
		while (buffer[i] != '\0')
		{
			adress[i] = buffer[i];
			//adress[i + 1] = '\\';
			//adress[i + 2] = '*';
			//adress[i + 3] = '.';
			//adress[i + 4] = '*';
			adress[i + 1] = '\0';
			i++;
		}
		wcout << adress << endl;
		wstring ws = adress;
		string s(ws.begin(), ws.end());
		outFile << s << endl;
	}
	/* Предпрограмма */
	/* глобальные переменные */
	int lvl = 0;
	adress;
	wstring adress2 = adress;
	/* глобальные переменные */
	/* Вызов функции*/
	prohod(adress2, lvl, outFile);
	/* Вызов функции*/
	int text = 15;
	int background = 0;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
	wcout << L"               Конец!=)               \n";
	system("pause");
	return 0;
	outFile.close();
}