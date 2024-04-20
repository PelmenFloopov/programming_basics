// Lab_5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include<stdio.h>
#include <vector>
#include <ctime>
using namespace std;

//Объявляем функции с задачами
void task1();
void task2();
void task3();
void task4();
//Объявляем вспомогательные функции функции

//Делает таблицу инверсий b для перестановки a длины n
void permut_to_invtab(int a[], int b[], int n);
//Восстанавливает перестановку a по таблице инверсий b размером n. Функция возвращает 1, если восстановление прошло корректно, иначе она возвращает 0
int invtab_to_permut(int b[], int a[], int n);
//Получает следующую перестановку для данной нам перестановки a длины n
void next_permut(int a[], int n);
//
vector<char> NextStrPermut(vector<char> Str, int n);

int main()
{
	setlocale(LC_ALL, "Rus");
	//Задача №1
	//task1();
	//Задача №2
	//task2();
	//Задача №3
	task3();
	//Задача №4
	//task4();
}

void task1()
{
	//Количество чисел в перестановке
	int N;
	cin >> N;
	//Изначальная перестановка
	int Arr[1000];
	//Получившаяся таблица инверсий
	int Result[1000];
	//Считываем перестановку
	for (int i = 0; i < N; i++)
	{
		cin >> Arr[i];
	}
	//Составляем таблицу инверсий
	permut_to_invtab(Arr, Result, N);
	//Выводим таблицу инверсий на экран
	for (int i = 0; i < N; i++)
	{
		cout << Result[i] << ' ';
	}
}

void task2()
{
	//Количество чисел в перестановке
	int N;
	cin >> N;
	//Изначальная таблица инверсий 
	int Arr[1000];
	//Получившаяся перестановка
	int Result[1000];
	//Считываем таблицe инверсий
	for (int i = 0; i < N; i++)
	{
		cin >> Arr[i];
	}
	//Проверяем, коректно ли составлена таблиа инерсий и еслм да, то делаем для нее перестановку
	int Correct = invtab_to_permut(Arr, Result, N);
	//Если составленна коректно, то выводим перестановку на экран
	if (Correct == 1)
	{
		for (int i = 0; i < N; i++)
		{
			cout << Result[i] << ' ';

		}
	}
	//Если некоректно, то выводим сообщение NO 
	else
	{
		cout << "NO";
	}


}

void task3()
{
	//Количество элементов в перестановке
	int N;
	cin >> N;
	//Изначальная перестановка
	int Arr[1000];
	for (int i = 0; i < N; i++)
	{
		cin >> Arr[i];
	}
	//Вычисляем следующую перестановку для изначальной
	next_permut(Arr, N);
	//Выводим перестановку на экран
	for (int i = 0; i < N; i++)
	{
		cout << Arr[i] << ' ';
	}

}

void task4()
{
	int N;
	cin >> N;
	vector<char> Str(N);
	for (int i = 0; i < N; i++)
	{
		cin >> Str[i];
	}
	Str = NextStrPermut(Str, N);
	for (int i = 0; i < N; i++)
	{
		cout << Str[i] << ' ';
	}
}

void permut_to_invtab(int a[], int b[], int n)
{
	//Перебираем числа, которые нужно найти
	for (int i = 1; i <= n; i++)
	{
		//Ищем число
		for (int j = 0; j < n; j++)
		{
			//Если нашли
			if (a[j] == i)
			{
				//Если число стоит не в начале
				if (j != 0)
				{
					//Количество чисел больших найденного
					int Amm = 0;
					//Ищем чисела большие найденного и считаем их
					for (int k = j - 1; k >= 0; k--)
					{
						if (a[k] > a[j])
						{
							Amm += 1;
						}

					}
					//Записываем количество чисел больших найденного в таблицу инверсий
					b[i - 1] = Amm;
				}
				//Если число стоит в начале, то перед ним не может быть никаких чисел, поэтому записываем 0 
				else
				{
					b[i - 1] = 0;
				}
				
			}
		}
	}
}

int invtab_to_permut(int b[], int a[], int n)
{
	//Если таблица составлена некорректно, возвращаем 0
	if (b[n - 1] > 0)
	{
		return 0;
	}
	//Если таблица составленна корректно
	else
	{
		//Заполняем нужное количество чисел 0-ми
		for (int i = 0; i < n; i++)
		{
			a[i] = 0;
		}
		//Перебираем числа из таблицы инверсий
		for (int i = 0; i < n; i++)
		{
			//Количество нулей перед числом
			int Count = 0;
			for (int j = 0; j < n; j++)
			{
				//Если число нулей перед числом совпадает с числом из табицы инверсий и элемент в перестановке не занят, то соотвествующее число ставим на это место
				if ((b[i] == Count) && (a[j] == 0))
				{
					a[j] = i + 1;
					break;
				}
				//Иначе если элемент в перестановке равен 0, то увеличиваем количество нулей перед нужным числом
				else
				{
					if (a[j] == 0)
					{
						Count += 1;
					}
				}
			}
		}
		return 1;
	}
}

void next_permut(int a[], int n)
{
	//Номер первого элемента, меньшего элемента справа от него
	int MismatchNum = 0;
	//Номер минимального элемента большего MismatchNum
	int MinMoreNum = 0;
	//Ищем номер первого элемента, меньшего элемента справа от него
	for (int i = n - 1; i > 0; i--)
	{
		if (a[i - 1] < a[i])
		{
			//Если нашли, записываем его
			MismatchNum = i - 1;
			//Инициализируем MinMoreNum
			MinMoreNum = MismatchNum + 1;
			//Ищем MinMoreNum
			for (int j = MismatchNum + 1; j < n; j++)
			{
				if ((a[j] > a[i - 1]) && (a[j] < a[MinMoreNum]))
				{
					MinMoreNum = j;
				}
			}
			break;
		}
	}
	//Меняем местами MismatchNum и MinMoreNum
	int Temp = a[MismatchNum];
	a[MismatchNum] = a[MinMoreNum];
	a[MinMoreNum] = Temp;
	//Конечный номер дмапозона в котором мы ищем минимальный и максимальный элементы
	int EndNum = n - 1;
	//Сортируем все числа после MismatchNum по возрастанию
	for (int i = MismatchNum + 1; i < n; i++)
	{
		//Номер максимального элемента
		int MaxNum = i;
		//Номер минимального элемента
		int MinNum = i;
		//Ищем номера максимального и минимального элементов
		for (int j = i; j <= EndNum; j++)
		{
			if (a[j] > a[MaxNum])
			{
				MaxNum = j;
			}
			if (a[j] < a[MinNum])
			{
				MinNum = i;
			}
		}
		//Ставим максимальный элемент на последнее место 
		Temp = a[EndNum];
		a[EndNum] = a[MaxNum];
		a[MaxNum] = Temp;
		//Ставим минимальный элемент на 
		Temp = a[i];
		a[i] = a[MinNum];
		a[MinNum] = Temp;
		EndNum -= 1;
		bool IsSorted = true;
		for (int j = MismatchNum + 1; j < n - 1; j++)
		{
			if (a[j] > a[j + 1]) 
			{
				IsSorted = false;
				break;
			}
		}
		if (IsSorted)
		{
			break;
		}

	}
}

vector<char> NextStrPermut(vector<char> Str, int n)
{
	int MismatchNum = 0;
	int MinMoreNum = 0;
	for (int i = n - 1; i > 0; i--)
	{
		if (Str[i - 1] < Str[i])
		{
			MismatchNum = i - 1;
			MinMoreNum = MismatchNum + 1;
			for (int j = MismatchNum + 1; j < n; j++)
			{
				if ((Str[j] > Str[i - 1]) && (Str[j] < Str[MinMoreNum]))
				{
					MinMoreNum = j;
				}
			}
			break;
		}
	}
	char Temp = Str[MismatchNum];
	Str[MismatchNum] = Str[MinMoreNum];
	Str[MinMoreNum] = Temp;

	int EndNum = n - 1;
	for (int i = MismatchNum + 1; i < n; i++)
	{

		int MaxNum = i;

		int MinNum = i;
		for (int j = i; j <= EndNum; j++)
		{
			if (Str[j] > Str[MaxNum])
			{
				MaxNum = j;
			}
			if (Str[j] < Str[MinNum])
			{
				MinNum = i;
			}
		}
		Temp = Str[EndNum];
		Str[EndNum] = Str[MaxNum];
		Str[MaxNum] = Temp;
		Temp = Str[i];
		Str[i] = Str[MinNum];
		Str[MinNum] = Temp;
		EndNum -= 1;
		bool IsSorted = true;
		for (int j = MismatchNum + 1; j < n - 1; j++)
		{
			if (Str[j] > Str[j + 1])
			{
				IsSorted = false;
				break;
			}
		}
		if (IsSorted)
		{
			break;
		}

	}

	return(Str);
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
