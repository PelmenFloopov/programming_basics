// Lab_6.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <ctime>
#include <string>
using namespace std;

//Объявляем функции с задачами
void task1();
void task2();
void task3();
void task4();

//Объявляем вспомогательные функции функции

//Здесь a — имя массива целых чисел, l и r — индексы элементов, соответсвующие левой и правой границам поиска, x — значение искомого элемента.
int binsearch(int a[], int l, int r, int x);

int main()
{
	setlocale(LC_ALL, "Rus");
	//Задача №1
	//task1();
	//Задача №2
	//task2();
	//Задача №3
	//task3();
	//Задача №4
	task4();
}

void task1()
{
	//Количество чисел в массиве
	int N,
	//Число, которое нужно найти
		X,
	//Номер числа в массиве
		Num = -1;
	cin >> N >> X;
	//Создаем и инициализируем массив 
	vector<int> Arr(N, 10000001);
	//Считываем числа в массив
	for (int i = 0; i < N; i++)
	{
		cin >> Arr[i];
	}
	//Начальная граница поиска
	int Begin = 0,
	//Конечная граница поиска
		End = N - 1;
	//Пока не получим номер числа или максиально близкого к нему числу, сдвигаем границы поиска
	while (Begin != End)
	{
		//Сдвиг до середины границ поиска
		int Shift = (End - Begin) / 2;
		//Если средний элемент больше или равен числу, то ставим середину текущих границ в качестве конца (отсекаем все элементы справа)
		if (Arr[Begin + Shift] >= X)
		{
			End = Begin + Shift;
		}
		//Если средний элемент меньше числа, то сдвигаем начало границ на 1 правее середины (отсекаем все элементы слева)
		else
		{
			Begin = Begin + Shift + 1;
		}
	}
	//Если число под найденным номером это то число, которое мы искали, то запоминаем его номер
	if (Arr[Begin] == X)
	{
		Num = Begin;
	}
	//Выводим номер числа в массиве (-1 если его нет в данном массиве)
	cout << Num;
}

void task2()
{
	//Количество чисел в массиве
	int N,
		//Число, к которому нужно найти самое близкое
		X;
	cin >> N >> X;
	//Создаем и инициализируем массив 
	vector<float> Arr(N, 10000001.0);
	//Считываем числа в массив
	for (int i = 0; i < N; i++)
	{
		cin >> Arr[i];
	}
	//Начальная граница поиска
	int Begin = 0,
		//Конечная граница поиска
		End = N - 1;
	//Пока не получим номер числа или максиально близкого к нему числу, сдвигаем границы поиска
	while (Begin != End)
	{
		//Сдвиг до середины границ поиска
		int Shift = (End - Begin) / 2;
		//Если модуль разности числа в середине и нужного нам числа меньше модуля разности соседнего числа справа и нужного нам числа, то ставим середину текущих границ в качестве конца
		//(отсекаем все элементы справа)
		if (abs(Arr[Begin + Shift] - X) < abs(Arr[Begin + Shift + 1] - X))
		{
			End = Begin + Shift;
		}
		//Иначе отсекаем все элементы слева середины, включая элемент посередине
		else
		{
			Begin = Begin + Shift + 1;
		}
	}
	//Выводим номер элемента, максимально близкого к нужному нам числу
	cout << Begin;
}

void task3()
{
	//Изначальная строка
	string T
	//Подстрока, которую нужно найти в строке
		, P;
	cin >> T >> P;
	//Размер изначальной строки
	int N = T.size(),
	//Размер подстроки
		M = P.size();
	//Таблица сдвигов
	vector <int> ShiftTable;
	//Таблица букв, которым соотвествует определенный сдвиг 
	vector<char> LettersInSubstr;
	//Сдвиг для предпоследней буквы в подстроке, если она состоит больше,чем из 1 буквы
	if (M != 1)
	{
		ShiftTable.push_back(1);
		LettersInSubstr.push_back(P[M - 2]);
	}
	//Сдвиг для первой буквы в подстроке, если она состоит из 1 буквы
	else
	{
		ShiftTable.push_back(M);
		LettersInSubstr.push_back(P[0]);
	}
	
	//Добавляем значения в таблицу сдвигов и букв, соотвествующим этим сдвигам
	for (int i = M - 3; i >= 0; i--)
	{
		//Показывает, есть ли повтор конкретной буквы в подстроке
		bool IsRepeat = false;
		//Смотрим, есть ли повтор данной буквы
		for (int j = i + 1; j < M - 1; j++)
		{
			if (P[i] == P[j])
			{
				IsRepeat = true;
				break;
			}
		}
		//Если повтров данной буквы мы еще не видели, то присваеваем для нее расстояние до последнего элемента в подстроке
		if (!IsRepeat)
		{
			ShiftTable.push_back(M - 1 - i);
			LettersInSubstr.push_back(P[i]);
			bool IsAll = true;
			for (int j = i - 1; j >= 0; j--)
			{
				bool Flag = false;
				for (int k = 0; k < LettersInSubstr.size(); k++)
				{
					if (LettersInSubstr[k] == P[j])
					{
						Flag = true;
						break;
					}
				}
				if (!Flag)
				{
					IsAll = false;
					break;
				}
			}
			if (IsAll)
			{
				break;
			}
		}
	}
	bool IsRepeat = false;
	for (int i = 0; i < LettersInSubstr.size(); i++)
	{
		//Если повтров данной буквы мы еще не видели и это последняя буква, то присваеваем для нее делаем сдвижку на всю длину подстроки
		if (LettersInSubstr[i] == P[M - 1])
		{
			IsRepeat = true;
			break;
		}
	}
	if (!IsRepeat)
	{
		ShiftTable.push_back(M);
		LettersInSubstr.push_back(P[M - 1]);
	}
	//Сдвижка для букв, которых нет в подстроке
	ShiftTable.push_back(M);
	//Номера элементов вхождений подстроки в строку
	vector<int> Entries;
	//Количетсво вхождений подтроки в строку
	int EntriesAmm = 0;
	//Перебираем подстроки по алгоритму Бойра-Мура-Хорспула
	for (int i = M - 1; i < N;)
	{
		//Подстрока, с которой мы сравниваеосновную подстроку, которую нужно найти
		string temp;
		for (int j = i - (M - 1); j <= i; j++)
		{
			temp += T[j];
		}
		//Если подстроки совпали, то увеличиваем количество вхождений в строке и сдвигаемся по строке 
		if (P == temp)
		{
			Entries.push_back(i - (M - 1));
			EntriesAmm += 1;
			i += ShiftTable[ShiftTable.size() - 2];
		}
		//Если не совпали, то сдвигаемся соответсвенно таблице сдвигов
		else
		{
			bool IsLetterInSubstr = false;
			for (int j = 0; j < LettersInSubstr.size(); j++)
			{
				if (T[i] == LettersInSubstr[j])
				{
					IsLetterInSubstr = true;
					i += ShiftTable[j];
					break;
				}
			}
			if (IsLetterInSubstr == false)
			{
				i += ShiftTable[ShiftTable.size() - 1];
			}
		}
	}
	//Выводим количество вхождений на экран
	cout << EntriesAmm << '\n';
	//Если количество вхождений не равно 0, то выводим места вхождений
	if (EntriesAmm != 0)
	{
		for (int i = 0; i < Entries.size(); i++)
		{
			cout << Entries[i] << '\n';
		}
	}
}

void task4()
{
	//Количество чисел в массиве
	int N, Arr[100001];
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> Arr[i];
	}
	int Q;
	cin >> Q;
	int Now = 0, Previous = 0, X;
	for (int i = 0; i < Q; i++)
	{
		if (i == 0)
		{
			cin >> X;
			Previous = binsearch(Arr, 0, N, X);
			cout << Previous << '\n';
		}
		else
		{
			cin >> X;
			Now = Previous + X;
			Previous = binsearch(Arr, 0, N, Now);
			cout << Previous << '\n';
		}

	}
}

int binsearch(int a[], int l, int r, int x)
{
	int Num = -1;
	//Начальная граница поиска
	int Begin = 0,
		//Конечная граница поиска
		End = r - 1;
	//Пока не получим номер числа или максиально близкого к нему числу, сдвигаем границы поиска
	while (Begin != End)
	{
		//Сдвиг до середины границ поиска
		int Shift = (End - Begin) / 2;
		//Если средний элемент больше или равен числу, то ставим середину текущих границ в качестве конца (отсекаем все элементы справа)
		if (a[Begin + Shift] > x)
		{
			End = Begin + Shift;
		}
		//
		else if ((a[Begin + Shift] == a[Begin + Shift + 1]) == x)
		{
			Num = Begin + Shift + 1;
			return(Num);
		}
		else if ((a[Begin + Shift] == a[Begin + Shift - 1]) == x)
		{
			Num = Begin + Shift;
			return(Num);
		}
		else if ((a[Begin + Shift] == x) && !((a[Begin + Shift] == a[Begin + Shift + 1]) == x) && !((a[Begin + Shift] == a[Begin + Shift - 1]) == x))
		{
			End = Begin + Shift;
		}

		//Если средний элемент меньше числа, то сдвигаем начало границ на 1 правее середины (отсекаем все элементы слева)
		else if (a[Begin + Shift] < x)
		{
			Begin = Begin + Shift + 1;
		}
	}
	//Если число под найденным номером это то число, которое мы искали, то запоминаем его номер
	if (a[Begin] == x)
	{
		Num = Begin;
	}
	//Выводим номер числа в массиве (-1 если его нет в данном массиве)
	return(Num);
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
