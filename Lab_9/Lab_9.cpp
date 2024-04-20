// Lab_9.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>
using namespace std;

void task1();
void task2();
void task3();
void task4();
void task5();
void task6();
void task7();
void task8();

//Объявляем вспомогательные функции
//Проводит сорировку слиянием двух ранее отсортированных массивов a и b размерами ak и bk соответственно
int* merge(int* a, int ak, int* b, int bk);
//
int partition(int* Arr, int startNum, int endNum, int pivot);

int main()
{
	setlocale(LC_ALL, "Rus");
	//task1();
	//task2();
	//task3();
	//task4();
	//task5();
	//task6();
	//task7();
	unsigned char a;
	a = (unsigned char)1023;
	cout << (int)a;
	//task8();
}

void task1()
{
	//Входящий файловый поток
	ifstream Fin("input.txt", ios::in);
	//Если не удалось открыть файл, то выдаем ошибку и завершаем работу программы
	if (!Fin)
	{
		cout << "Ошибка!!!\n";
		return;
	}
	string TextInStr;
	//Массив символов в строке 
	string letInStr;
	//Массив количеств символов в строке
	vector<int> lettersAmm;
	while (Fin)
	{
		//Считываем строки из входного файла
		getline(Fin, TextInStr);
		//Идем по символам в строке
		for (unsigned i = 0; i < TextInStr.size(); i++)
		{
			if (unsigned char(TextInStr[i]) > 12)
			{
				//ПоказываетЮ встречали ли мы данный символ раньше
				bool Flag = false;
				//Сравниваем данный символ с теми, что мы встречали раньше 
				for (unsigned j = 0; j < letInStr.size(); j++)
				{
					//Если встречали, то увеличиваем количество этих сиволов на 1 и выходим из цикла
					if (TextInStr[i] == letInStr[j])
					{
						Flag = true;
						lettersAmm[j] += 1;
						break;
					}
				}
				//Если не встречали, то добавляем символ в массив символов и новое количество (сначала 1, так как мы в первый раз встретили символд) в массив количеств
				if (!Flag)
				{
					letInStr.push_back(TextInStr[i]);
					lettersAmm.push_back(1);
				}
			}
		}
	}
	Fin.close();
	//Пока есть символы для сравнения
	while (lettersAmm.size() > 1)
	{
		//Номер символа с минимальным кодом
		int MinNum = 0;
		//Ищем номер символа с минимальным кодом
		for (unsigned j = 1; j < lettersAmm.size(); j++)
		{
			
			if (static_cast<unsigned int>(static_cast<unsigned char>(letInStr[MinNum])) > static_cast<unsigned int>(static_cast<unsigned char>(letInStr[j])))
			{
				MinNum = j;
			}
		
		}
		//Выводм код символа, сам символ и его количество
		cout << static_cast<unsigned int>(static_cast<unsigned char>(letInStr[MinNum])) << ' ' << ':' << ' ' << letInStr[MinNum] << ' ' << '-' << ' ' << lettersAmm[MinNum] << '\n';
		//Итератор для символа с минимальным кодом
		vector<int>::iterator Itr = lettersAmm.begin();
		//Ставим итератор на символ с минимальным кодом и меняем его с последним элементом в обоих массивах
		advance(Itr, MinNum);
		swap(*Itr, *(lettersAmm.end() - 1));
		string::iterator Itr_2 = letInStr.begin();
		advance(Itr_2, MinNum);
		swap(*Itr_2, *(letInStr.end() - 1));
		//Удаляем символ с наименьшим кодом м его количество, так как мы их уже вывели
		lettersAmm.pop_back();
		letInStr.pop_back();
	}
	//Выводим оставшийся символ на экран
	cout << static_cast<unsigned int>(static_cast<unsigned char>(letInStr[0])) << ' ' << ':' << ' ' << letInStr[0] << ' ' << '-' << ' ' << lettersAmm[0] << '\n';
}

void task2()
{
	//Входящий файловый поток
	ifstream Fin("input.txt", ios::in);
	//Если не удалось открыть файл, то выдаем ошибку и завершаем работу программы
	if (!Fin)
	{
		cout << "Ошибка!!!\n";
		return;
	}
	string Str;
	//Массив с массивом длинн слов и массивом их колличеств
	vector<vector<int>> Arrs(2);
	while (Fin)
	{
		getline(Fin, Str);
		int wordSize = 0;
		for (int i = 0; i <= Str.size(); i++)
		{
			if ((Str[i] != ' ') && (Str[i] != '\n') && (Str[i] != '\0') && (Str[i] != '\t'))
			{
				wordSize += 1;
			}
			else
			{
				if (wordSize != 0)
				{
					bool Flag = false;
					for (int j = 0; j < Arrs[0].size(); j++)
					{
						if (wordSize == Arrs[0][j])
						{
							Flag = true;
							Arrs[1][j] += 1;
							wordSize = 0;
							break;
						}
					}
					if (!Flag)
					{
						Arrs[0].push_back(wordSize);
						Arrs[1].push_back(1);
						wordSize = 0;
					}
				}
			}

		}
	}
	Fin.close();
	while (Arrs[0].size() > 1)
	{
		int MinNum = 0;
		for (int i = 0; i < Arrs[0].size(); i++)
		{
			if (Arrs[0][MinNum] > Arrs[0][i])
			{
				MinNum = i;
			}
		}
		cout << Arrs[0][MinNum] << ' ' << '-' << ' ' << Arrs[1][MinNum] << '\n';
		vector<int>::iterator Itr = Arrs[0].begin();
		advance(Itr, MinNum);
		swap(*Itr, *(Arrs[0].end() - 1));
		vector<int>::iterator Itr_2 = Arrs[1].begin();
		advance(Itr_2, MinNum);
		swap(*Itr_2, *(Arrs[1].end() - 1));
		Arrs[0].pop_back();
		Arrs[1].pop_back();
	}
	cout << Arrs[0][0] << ' ' << '-' << ' ' << Arrs[1][0] << '\n';
}

void task3()
{
	//Входящий файловый поток
	ifstream Fin("input.txt", ios::in);
	//Если не удалось открыть файл, то выдаем ошибку и завершаем работу программы
	if (!Fin)
	{
		cout << "Ошибка!!!\n";
		return;
	}
	int StrAmm = 0;
	string Str;
	while (getline(Fin, Str))
	{
		StrAmm += 1;
	}
	cout << StrAmm;
}

void task4()
{
	//Входящий файловый поток
	ifstream Fin("input.txt", ios::in);
	//Если не удалось открыть файл, то выдаем ошибку и завершаем работу программы
	if (!Fin)
	{
		cout << "Ошибка!!!\n";
		return;
	}
	string TextInStr;
	//Массив символов в строке 
	string letInStr;
	//Массив количеств символов в строке
	vector<int> lettersAmm;
	//Пока есть символы для сравнения
	while (Fin)
	{
		//Считываем строки из входного файла
		getline(Fin, TextInStr);
		//Идем по символам в строке
		for (unsigned i = 0; i < TextInStr.size(); i++)
		{
			if (unsigned char(TextInStr[i]) > 12)
			{
				//ПоказываетЮ встречали ли мы данный символ раньше
				bool Flag = false;
				//Сравниваем данный символ с теми, что мы встречали раньше 
				for (unsigned j = 0; j < letInStr.size(); j++)
				{
					//Если встречали, то увеличиваем количество этих сиволов на 1 и выходим из цикла
					if (TextInStr[i] == letInStr[j])
					{
						Flag = true;
						lettersAmm[j] += 1;
						break;
					}
				}
				//Если не встречали, то добавляем символ в массив символов и новое количество (сначала 1, так как мы в первый раз встретили символд) в массив количеств
				if (!Flag)
				{
					letInStr.push_back(TextInStr[i]);
					lettersAmm.push_back(1);
				}
			}
		}
	}
	while (lettersAmm.size() > 1)
	{
		//Номер символа с минимальным кодом
		int MinNum = 0;
		//Ищем номер символа с минимальным кодом
		for (unsigned j = 1; j < lettersAmm.size(); j++)
		{

			if (letInStr[MinNum] > letInStr[j])
			{
				MinNum = j;
			}

		}
		//Выводм код символа, сам символ и его количество
		cout << letInStr[MinNum] << ' ';
		for (int i = 0; i < lettersAmm[MinNum]; i++)
		{
			cout << '#';
		}
		cout << '\n';
		//Итератор для символа с минимальным кодом
		vector<int>::iterator Itr = lettersAmm.begin();
		//Ставим итератор на символ с минимальным кодом и меняем его с последним элементом в обоих массивах
		advance(Itr, MinNum);
		swap(*Itr, *(lettersAmm.end() - 1));
		string::iterator Itr_2 = letInStr.begin();
		advance(Itr_2, MinNum);
		swap(*Itr_2, *(letInStr.end() - 1));
		//Удаляем символ с наименьшим кодом м его количество, так как мы их уже вывели
		lettersAmm.pop_back();
		letInStr.pop_back();
	}
	//Выводим оставшийся символ на экран
	cout << letInStr[0] << ' ';
	for (int i = 0; i < lettersAmm[0]; i++)
	{
		cout << '#';
	}
	cout << '\n';
}

void task5()
{
	//Открываем бинарный файл на чтение
	ifstream fin("input.bin", ios::binary|ios::in);
	if (!fin)
	{
		cout << "Ошибка!!!\n";
		return;
	}
	//Открываем бинарный файл на запись
	ofstream fout("output.bin", ios::binary | ios::out);
	if (!fout)
	{
		cout << "Ошибка!!!\n";
		return;
	}
	int A, B;
	//Считываем число размером 4 байта из файла
	fin.read((char*)&A, sizeof(A));
	fin.read((char*)&B, sizeof(B));
	if (A==B)
	{
		fout.write((char*)&A, sizeof(A));
	}
	else
	{
		double Temp = double(A / 2.0) + double(B / 2.0);
		int halfSum = floor(Temp);
		fout.write((char*)&halfSum, sizeof(halfSum));
	}
	fin.close();
	fout.close();
}

void task6()
{
	//Открываем бинарный файл на чтение
	ifstream fin("input.bin", ios::binary | ios::in);
	//Если не получилось, то выводим ошибку и заканчиваем работу программы
	if (!fin)
	{
		cout << "Ошибка!!!\n";
		return;
	}
	//Открываем бинарный файл на запись
	ofstream fout("output.bin", ios::binary | ios::out);
	//Если не получилось, то выводим ошибку и заканчиваем работу программы
	if (!fout)
	{
		cout << "Ошибка!!!\n";
		return;
	}
	//Количество чисел в бинарном файле
	int N
	//Сумма всех чисел в бинарном файле
		, Sum = 0;
	//Считываем количество чисел в бинарном файле
	fin.read((char*)&N, sizeof(N));
	//Массив чисел в файле
	int* Arr;
	//Если биты в числе читаются нормально
	if (*((int16_t*)&N))
	{
		//Создаем массив нужной размерности
		Arr = new int[N];
		//Если не получилось, то выводим ошибку и заканчиваем работу программы
		if (!Arr)
		{
			cout << "Ошибка!!!\n";
			return;
		}
		//Считываем числа из файла в массив
		for (int i = 0; i < N; i++)
		{
			fin.read((char*)&Arr[i], sizeof(Arr[i]));
		}
		//Закрываем входной поток как только считали все числа
		fin.close();
		//Суммируем все числа в файле
		for (int i = 0; i < N; i++)
		{
			Sum += Arr[i];
		}
	}
	//Если биты в числе читаются задом наперед
	else
	{
		//Для того чтобы менять местами байты в числе
		char* tmp = (char*)&N;
		//Меняем байты в числе
		for (int i = 0; i < sizeof(N) / 2; i++)
		{
			swap(tmp[i], tmp[3 - i]);
		}
		//Создаем массив нужной размерности
		Arr = new int[N];
		//Если не получилось, то выводим ошибку и заканчиваем работу программы
		if (!Arr)
		{
			cout << "Ошибка!!!\n";
			return;
		}
		//Считываем числа из файла в массив
		for (int i = 0; i < N; i++)
		{
			fin.read((char*)&Arr[i], sizeof(Arr[i]));
			//Меняем байты в числах массива
			tmp = (char*)&Arr[i];
			for (int j = 0; j < sizeof(Arr[i]) / 2; j++)
			{
				swap(tmp[j], tmp[3 - j]);
			}
		}
		//Закрываем входной поток
		fin.close();
		//Суммируем все числа в файле
		for (int i = 0; i < N; i++)
		{
			Sum += Arr[i];
		}
		tmp = (char*)&Sum;
		for (int i = 0; i < sizeof(Sum) / 2; i++)
		{
			swap(tmp[i], tmp[3 - i]);
		}
	}
	//Записываем сумму чисел в файл, открытый для записи
	fout.write((char*)&Sum, sizeof(Sum));
	//Освобождаем память, выделенную под массив
	delete[] Arr;
	//Закрываем файл, открытый для записи
	fout.close();
}

void task7()
{
	//Открываем бинарный файл на чтение
	ifstream fin("input.bin", ios::binary | ios::in);
	//Если не получилось, то выводим ошибку и заканчиваем работу программы
	if (!fin)
	{
		cout << "Ошибка!!!\n";
		return;
	}
	//Открываем бинарный файл на запись
	ofstream fout("output.bin", ios::binary | ios::out);
	//Если не получилось, то выводим ошибку и заканчиваем работу программы
	if (!fout)
	{
		cout << "Ошибка!!!\n";
		return;
	}
	//Количество чисел в массиве А
	int N
	//Количество чисел в массиве В
		, M;
	fin.read((char*)&N, sizeof(N));
	//Если байты в числах читаются задом наперед
	if (!(*((int16_t*)&N)))
	{
		//Для того, чтобы менять биты местами
		char* tmp = (char*)&N;
		//Меняем байты местами
		for (int i = 0; i < sizeof(N)/2; i++)
		{
			swap(tmp[i], tmp[3 - i]);
		}
		fin.read((char*)&M, sizeof(M));
		tmp = (char*)&M;
		//Меняем байты местами
		for (int i = 0; i < sizeof(M)/2; i++)
		{
			swap(tmp[i], tmp[3 - i]);
		}
		//Первый массив чисел
		int* A = new int[N];
		//Если не получилось, то выводим ошибку и заканчиваем работу программы
		if (!A)
		{
			cout << "Ошибка!!!\n";
			return;
		}
		//Второй массив чисел
		int* B = new int[M];
		//Если не получилось, то выводим ошибку и заканчиваем работу программы
		if (!B)
		{
			cout << "Ошибка!!!\n";
			return;
		}
		//Считывем числа из файла в массив А и меняем байты местами
		for (int i = 0; i < N; i++)
		{
			fin.read((char*)&A[i], sizeof(A[i]));
			tmp = (char*)&A[i];
			for (int j = 0; j < 2; j++)
			{
				swap(tmp[j], tmp[3 - j]);
			}
		}
		//Считывем числа из файла в массив В и меняем байты местами
		for (int i = 0; i < M; i++)
		{
			fin.read((char*)&B[i], sizeof(B[i]));
			tmp = (char*)&B[i];
			for (int j = 0; j < 2; j++)
			{
				swap(tmp[j], tmp[3 - j]);
			}
		}
		//Закрываем входной поток как только считали все числа
		fin.close();
		//Результат слияния массивов А и В
		int* mergedArr = merge(A, N, B, M);
		//Освобождаем выделенную на массивы А и В память
		delete[]A;
		delete[]B;
		//Записываем получившийся массив в файл, открытый на запись
		for (int i = 0; i < N + M; i++)
		{
			fout.write((char*)&mergedArr[i], sizeof(mergedArr[i]));
		}
		//Закрываем выходной поток как только записали все числа
		fout.close();
		//Освобождаем выделенную память
		delete[]mergedArr;
	}
	//Если байты в числах читаются нормально
	else
	{
		fin.read((char*)&M, sizeof(M));
		//Первый массив чисел
		int* A = new int[N];
		//Если не получилось, то выводим ошибку и заканчиваем работу программы
		if (!A)
		{
			cout << "Ошибка!!!\n";
			return;
		}
		//Второй массив чисел
		int* B = new int[M];
		//Если не получилось, то выводим ошибку и заканчиваем работу программы
		if (!B)
		{
			cout << "Ошибка!!!\n";
			return;
		}
		//Считываем числа в массив А
		for (int i = 0; i < N; i++)
		{
			fin.read((char*)&A[i], sizeof(A[i]));
		}
		//Считываем числа в массив В
		for (int i = 0; i < M; i++)
		{
			fin.read((char*)&B[i], sizeof(B[i]));
		}
		//Закрываем входной поток как только считали все числа
		fin.close();
		//Результат слияния массивов А и В
		int* mergedArr = merge(A, N, B, M);
		//Освобождаем выделенную на массивы А и В память
		delete[]A;
		delete[]B;
		//Записываем получившийся массив в файл, открытый на запись
		for (int i = 0; i < N + M; i++)
		{
			fout.write((char*)&mergedArr[i], sizeof(mergedArr[i]));
		}
		//Закрываем выходной поток как только записали все числа
		fout.close();
		//Освобождаем выделенную память
		delete[]mergedArr;
	}
}

void task8()
{
	//Открываем бинарный файл на чтение
	ifstream fin("input.bin", ios::binary | ios::in);
	//Если не получилось, то выводим ошибку и заканчиваем работу программы
	if (!fin)
	{
		cout << "Ошибка!!!\n";
		return;
	}
	//Открываем бинарный файл на запись
	ofstream fout("output.bin", ios::binary | ios::out);
	//Если не получилось, то выводим ошибку и заканчиваем работу программы
	if (!fout)
	{
		cout << "Ошибка!!!\n";
		return;
	}
	int* Arr = NULL;
	//Количество чисел в массиве с числами из входного файла
	int N,
	//Опорный элемент при разделении массива
		pivot;
	//
	fin.read((char*)&N, sizeof(N));
	Arr = new int[N];
	//Если не получилось, то выводим ошибку и заканчиваем работу программы
	if (!Arr)
	{
		cout << "Ошибка!!!\n";
		return;
	}
	fin.read((char*)&pivot, sizeof(pivot));
	for (int i = 0; i < N; i++)
	{
		fin.read((char*)&Arr[i], sizeof(Arr[i]));
	}
	fin.close();
	int amm = partition(Arr, 0, N - 1, pivot);
	int sameLeft = 0, sameRight = 0;
	for (int i = 0; i < amm; i++)
	{
		if (Arr[i] == pivot)
		{
			sameLeft += 1;
		}
	}
	for (int i = amm; i < N; i++)
	{
		if (Arr[i] == pivot)
		{
			sameRight += 1;
		}
	}
	fout.write((char*)&amm, sizeof(amm));
	for (int i = 0; i < N; i++)
	{
		fout.write((char*)&Arr[i], sizeof(Arr[i]));
	}
	delete[]Arr;
	fout.close();
}

int* merge(int* a, int ak, int* b, int bk)
{
	int* res = new int[ak + bk];
	if (!res)
	{
		cout << "Ошибка!!!\n";
		return(NULL);
	}
	int i = 0, j = 0, t = 0;
	bool End = false;
	while (!End)
	{
		if (t > (ak + bk) - 1)
		{
			End = true;
		}
		else
		{
			if (i > ak - 1)
			{
				for (int x = j; x < bk; x++)
				{
					res[t] = b[x];
					t += 1;
				}
			}
			else if (j > bk - 1)
			{
				for (int x = i; x < ak; x++)
				{
					res[t] = a[x];
					t += 1;
				}
			}
			else
			{
				if (a[i] >= b[j])
				{
					res[t] = b[j];
					j += 1;
					t += 1;
				}
				else
				{
					res[t] = a[i];
					i += 1;
					t += 1;
				}
			}
		}
	}
	return (res);
}

int partition(int* Arr, int startNum, int endNum, int pivot)
{
	//Номер элемента слева от опорного элемента
	int l = startNum,
		//Номер элемента справа от опорного эемента
		r = endNum;
	while (l < r)
	{
		//Пока элементы слева меньше, чем опорный игнорируем их
		while (Arr[l] < pivot)
		{
			l += 1;
		}
		//Пока элементы справа больше, чем опорный игнорируем их
		while (Arr[r] > pivot)
		{
			r -= 1;
		}
		//Если номера корректные, то меняем несовпавшие элементы
		if (l < r)
		{
			swap(Arr[l], Arr[r]);
			l += 1;
			r -= 1;
		}
	}
	int leftPartAmm = r + 1;
	return(leftPartAmm);
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
