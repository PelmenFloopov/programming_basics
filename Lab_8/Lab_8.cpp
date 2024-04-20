// Lab_8.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
using namespace std;

//Инициализируем функции с задачами
void task1();
void task2();
void task3();

//Инициализируем вспомогательные функции
//Сортировка Шелла. Сортирует массив arr размером n
vector<int> ShellSort(vector<int> arr, int n);
//Сортировка вставками. Сортирует элементы массив arr размером n с шагом step
vector<int> ins_sort(vector<int>arr, int n, int step);
//Пирамидальная сортировка. Сортирует массив arr размером n
vector<int> heapSort(vector<int>arr, int n);
//Упорядочивает элементы "дерева" в "кучу" начиная с корневого элемента root
vector<int> heapSift(vector<int>arr, int n, int root);
//Быстрая сортировка. Сортирует элементы массив arr размером n с шагом step методом Хоара
void Quicksort(int Arr[], int startNum, int endNum);



int main()
{
    //task1();
    //task2();
    task3();
}


void task1()
{
	//Размер массива
    int N;
    cin >> N;
	//Массив чисел
    vector<int> Arr(N);
	//Считываем числа
	for (int i = 0; i < N; i++)
	{
		cin >> Arr[i];
	}
	int step = N; // Шаг поисков и вставки

	int i, j;

	do {

		// Вычисляем новый шаг

		step = step / 3 + 1;

		// Производим сортировку простыми вставками с заданным шагом

		for (i = step; i < N; i++) {

			int c = Arr[i];

			for (j = i - step; j >= 0 && Arr[j] > c; j -= step) {

				Arr[j + step] = Arr[j];

			}

			Arr[j + step] = c;

		}

	} while (step != 1);
	////Сортируем массив
	//Arr = ShellSort(Arr, N);
	////Выводим массив на экран
	for (int i = 0; i < N; i++)
	{
		cout << Arr[i] << ' ';
	}
}

void task2()
{
	//Размер массива
	int N;
	cin >> N;
	//Массив чисел
	vector<int> Arr(N);
	//Считываем числа
	for (int i = 0; i < N; i++)
	{
		cin >> Arr[i];
	}
	//Сортируем массив
	Arr = heapSort(Arr, N);
	//Выводим массив на экран
	for (int i = 0; i < N; i++)
	{
		cout << Arr[i] << ' ';
	}
}

void task3()
{
	//Размер массива
	int N;
	cin >> N;
	int* Arr = new int[N];
	//Считываем числа
	for (int i = 0; i < N; i++)
	{
		cin >> Arr[i];
	}
	//Сортируем массив
	Quicksort(Arr, 0, N - 1);
	//Выводим массив на экран
	for (int i = 0; i < N; i++)
	{
		cout << Arr[i] << ' ';
	}
	//Очищаем выделенную память
	delete [] Arr;
}

vector<int> ShellSort(vector<int> arr, int n)
{
	//Массив шагов
    vector<int> stepsArr;
	//Последний шаг всегда = 1
	stepsArr.push_back(1);
	//Номер шага
	int StepNum = 1;
	//Показывает, достаточно ли шагов мы посчитали
	bool Flag = false;
	while (!Flag)
	{
		//Если число четное
		if (StepNum % 2 == 0)
		{
			//Если шаг не превышает треть массива
			if ((9 * pow(2, StepNum) - 9 * pow(2, StepNum / 2) + 1) < n / 3)
			{
				stepsArr.push_back(9 * pow(2, StepNum) - 9 * pow(2, StepNum / 2) + 1);
				StepNum += 1;
			}
			//Если шаг превышает треть массива
			else
			{
				Flag = true;
			}
		}
		//Если число нечетное
		else 
		{
			//Если шаг не превышает треть массива
			if ((8 * pow(2, StepNum) - 6 * pow(2, (StepNum + 1) / 2) + 1) < n / 3)
			{
				stepsArr.push_back(8 * pow(2, StepNum) - 6 * pow(2, (StepNum + 1) / 2) + 1);
				StepNum += 1;
			}
			//Если шаг превышает треть массива
			else
			{
				Flag = true;
			}
		}
		
	}
	//Сротируем массив вставками с шагами, посчитанными ранее
	for (int i = stepsArr.size() - 1; i >= 0; i--)
	{
		arr = ins_sort(arr, n, stepsArr[i]);
	}
	return(arr);
}

vector<int> ins_sort(vector<int>arr, int n, int step)
{
	for (int i = 0; i < step; i++)
	{
		for (int j = step + i; j < n; j += step)
		{
			int MinNum = j - step;
			while ((arr[MinNum] > arr[j]) && (MinNum - step >= 0))
			{
				MinNum -= step;
			}
			if (arr[MinNum] < arr[j])
			{
				MinNum += step;
			}
			if (MinNum < j)
			{
				int temp = arr[MinNum];
				arr[MinNum] = arr[j];
				arr[j] = temp;
			}
			/*for (int k = j - step; k >= 0; k -= step)
			{
				if (arr[k] > arr[MinNum])
				{
					int temp = arr[k];
					arr[k] = arr[MinNum];
					arr[MinNum] = temp;
					MinNum = k;
				}
			}*/
		}
	}
	return(arr);
}

vector<int> heapSift(vector<int>arr, int n, int root)
{
	int largest = root;
	// Инициализируем наибольший элемент как корень
	//Левый дочерный элемент = 2*root + 1
	int left = 2 * root + 1; 
	//Правый дочерный элемент = 2*root + 1
	int right = 2 * root + 2; 
	// Если левый дочерний элемент больше корня
	if (left < n && arr[left] > arr[largest])
	{
		largest = left;
	}
	// Если правый дочерний элемент больше, чем самый большой элемент на данный момент
	if (right < n && arr[right] > arr[largest])
	{
		largest = right;
	}
	// Если самый большой элемент не корень
	if (largest != root)
	{
		swap(arr[root], arr[largest]);
		// Рекурсивно преобразуем в двоичную кучу затронутое поддерево
		arr = heapSift(arr, n, largest);
	}
	return(arr);
}

vector<int> heapSort(vector<int>arr, int n)
{
	// Построение кучи (перегруппируем массив)
	for (int i = n / 2 - 1; i >= 0; i--)
	{
		arr = heapSift(arr, n, i);
	}
	// Один за другим извлекаем элементы из кучи
	for (int i = n - 1; i >= 0; i--)
	{
		// Перемещаем текущий корень в конец
		swap(arr[0], arr[i]);

		// вызываем процедуру heapify на уменьшенной куче
		arr = heapSift(arr, i, 0);
	}
	return (arr);
}



void Quicksort(int Arr[], int startNum, int endNum)
{
	//Номер элемента слева от опорного элемента
	int l = startNum,
	//Номер элемента справа от опорного эемента
		r = endNum;
	//Опорный элемент (в нашем случае средний)
	int supEl = Arr[(l + r) / 2];
	while (l < r)
	{
		//Пока элементы слева меньше, чем опорный игнорируем их
		while (Arr[l] < supEl)
		{
			l += 1;
		}
		//Пока элементы справа больше, чем опорный игнорируем их
		while (Arr[r] > supEl)
		{
			r -= 1;
		}
		//Если номера корректные, то меняем несовпавшие элементы
		if (l <= r) 
		{
			swap(Arr[l], Arr[r]);
			l += 1;
			r -= 1;
		}
	} 
	//Если есть что сортировать, то вызывам функцию еще раз рекурсивно
	if (startNum < r)
	{
		Quicksort(Arr, startNum , r);
	}
	if (l < endNum)
	{
		Quicksort(Arr, l, endNum);
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
