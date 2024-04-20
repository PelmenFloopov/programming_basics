// Lab_7.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;



//Инициализируем функции с задачами
void task1();
void task2();
void task3();


//Инициализируем вспомогательные функции
//Сортировка вставками
void ins_sort(int a[], int n);
//Сортировка выбором
void select_sort(int a[], int n);
//Сортиовка шейкером
void shake_sort(int a[], int n);

int main()
{
	setlocale(LC_ALL, "Rus");
	//Задача №1
	//task1();
	//Задача №2
	//task2();
	//Задача №3
	task3();

}

void task1()
{
	int N, Arr[1000000];
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> Arr[i];
	}
	ins_sort(Arr, N);
	for (int i = 0; i < N; i++)
	{
		cout << Arr[i] << ' ';
	}
}

void task2()
{
	int N, Arr[1000000];
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> Arr[i];
	}
	select_sort(Arr, N);
	for (int i = 0; i < N; i++)
	{
		cout << Arr[i] << ' ';
	}

}

void task3()
{
	int N;
	cin >> N;
	int* Arr = new int[N];
	for (int i = 0; i < N; i++)
	{
		cin >> Arr[i];
	}
	shake_sort(Arr, N);
	for (int i = 0; i < N; i++)
	{
		cout << Arr[i] << ' ';
	}
}

void ins_sort(int a[], int n)
{
	for (int i = 1; i < n; i++)
	{
		for (int j = i; j >= 0; j--)
		{
			if (a[i] < a[j])
			{
				while ((a[i] < a[j]) && (j > 0))
				{
					j--;
				}
				if (a[j] < a[i])
				{
					j++;
				}
				int temp = a[i];
				for (int k = i; k > j; k--)
				{
					a[k] = a[k - 1];
				}
				a[j] = temp;
				break;
			}
		}
	}
}

void select_sort(int a[], int n)
{
	int startpos = 0;
	while (startpos < n - 1)
	{
		int Min = a[startpos], MinNum = startpos;
		for (int i = startpos + 1; i < n; i++)
		{
			if (a[i] < Min)
			{
				Min = a[i];
				MinNum = i;
			}
		}
		int temp = a[startpos];
		a[startpos] = Min;
		a[MinNum] = temp;
		startpos += 1;
	}
}

void shake_sort(int a[], int n)
{
	int startnum = 0, endnum = n - 1;
	bool IsSorted = false;
	while (!IsSorted)
	{
		for (int i = endnum; i > startnum; i--)
		{
			if (a[i] < a[i - 1])
			{
				int temp = a[i];
				a[i] = a[i - 1];
				a[i - 1] = temp;
			}
		}
		IsSorted = true;
		for (int i = 0; i < n - 1; i++)
		{
			if (a[i] > a[i + 1])
			{
				IsSorted = false;
			}
		}
		startnum += 1;
		for (int i = startnum; i < endnum; i++)
		{
			if (a[i] > a[i + 1])
			{
				int temp = a[i + 1];
				a[i + 1] = a[i];
				a[i] = temp;
			}
		}
		IsSorted = true;
		for (int i = 0; i < n - 1; i++)
		{
			if (a[i] > a[i + 1])
			{
				IsSorted = false;
			}
		}
		endnum -= 1;
	}
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
