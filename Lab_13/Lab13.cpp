#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>

using namespace std;

//Просеиваем кучу
void func(int a[], int l, int r)

{

	int le = (2 * l) + 1; //Левый потомок

	int ri = le + 1; //Правый потомок

	int in = l; //Индекс элемента, с которым мы меняем местами родителя

	if (le < r && a[in] < a[le])

	{

		in = le;

	}

	if (ri < r && a[in] < a[ri])

	{

		in = ri;

	}

	if (in != l)

	{

		swap(a[l], a[in]);//обменивает значения двух переменных, которые содержат одинаковые типы данных.

		func(a, in, r);

	}

}

void heap_sort(int* a, int N)//сортировка кучи

{

	for (int i = (N / 2) - 1; i >= 0; i--)

	{

		func(a, i, N);

	}

	for (int i = N - 1; i >= 1; i--)

	{

		swap(a[0], a[i]);

		func(a, 0, i);

	}

}

int main()

{

	int N;//количество чисел в массиве

	FILE* input, * output;
	//ifstream fin("input.bin", ios::binary | ios::in);

	input = fopen("input.bin", "rb");//откртыие потока входа
	//fin >> N;
	fread(&N, sizeof(int), 1, input);//fread: возвращает количество прочитанных элементов.

	int* a = new int[N];//массив

	for (int i = 0; i < N; i++)

	{
		//fin >> a[i];
		fread(&a[i], sizeof(int), 1, input);//fread: возвращает количество прочитанных элементов.

	}
	//fin.close();
	//fclose(input);//закрытие потока

	heap_sort(a, N);

	output = fopen("output.bin", "wb");//открытие потока выхода
	//ofstream fout("output.bin", ios::binary | ios::out);

	for (int i = 0; i < N; i++)

	{
		//fout << a[i];
		fwrite(&a[i], sizeof(int), 1, output);//выводим содержимое массива а после

	}
	//fout.close();
	fclose(output);//закрытие потока

	delete[] a;//освобождаем память	

}
//#include <iostream>
//#include <fstream>
//#include <vector>
//using namespace std;
//
//void sift_down(vector<int>& heap, int root, int end);
//void heapSort(vector<int>& heap);
//
//void func(int a[], int l, int r)
//
//{
//
//    int le = (2 * l) + 1;
//
//    int ri = le + 1;
//
//    int in = l;
//
//    if (le < r && a[in] < a[le])
//
//    {
//
//        in = le;
//
//    }
//
//    if (ri < r && a[in] < a[ri])
//
//    {
//
//        in = ri;
//
//    }
//
//    if (in != l)
//
//    {
//
//        swap(a[l], a[in]);//обменивает значения двух переменных, которые содержат одинаковые типы данных.
//
//        func(a, in, r);
//
//    }
//
//}
//
//void heap_sort(int* a, int N)//сортировка кучи
//
//{
//
//    for (int i = (N / 2) - 1; i >= 0; i--)
//
//    {
//
//        func(a, i, N);
//
//    }
//
//    for (int i = N - 1; i >= 1; i--)
//
//    {
//
//        swap(a[0], a[i]);
//
//        func(a, 0, i);
//
//    }
//
//}
//
////
//void task1();
//
////Требуется отсортировать массив 𝐴 по неубыванию, используя алгоритм сортировки кучей
//void task2();
//
////
//void task3();
//
//
//
//
//int main()
//{
//    //task1();
//    task2();
//    //task3();
//}
//
//
//void task2()
//{
//    ifstream fin("input.bin", ios::binary); //Открываем чтение из файла
//    int n; //Размерность массива 
//    fin >> n;
//    int* arr= new int [n]; //Массив чисел
//    //arr.reserve(0);
//    //Считываем числа из файла
//    for (int i = 0; i < n; i++)
//    {        
//        fin >> arr[i];
//    }
//    fin.close(); //Закрываем чтение из файла
//    heap_sort(arr, n);
//    //Записываем отсортированный массив в выходной файл
//    ofstream fout("output.bin", ios::out); //Открываем запись в файл
//    for (int i = 0; i < n; i++)
//    {
//        fout << arr[i];
//    }
//    fout.close(); //Закрываем запись в файл
//}
//
//
//
//
//// Просеивание элемента вниз по куче
//void sift_down(vector<int>& heap, int root, int end)
//{
//    int child = root * 2 + 1; // Левый потомок
//    while (child <= end) {
//        // Если правый потомок больше, чем левый, используем правый потомок
//        if (child + 1 <= end && heap[child] < heap[child + 1]) {
//            child++;
//        }
//        // Если больший потомок больше, чем корень, то меняем местами
//        if (heap[root] < heap[child]) {
//            swap(heap[root], heap[child]);
//            root = child;
//            child = root * 2 + 1;
//        }
//        else {
//            return;
//        }
//    }
//}
//
//// Сортировка кучей
//void heapSort(vector<int>& heap)
//{
//    int end = heap.size() - 1;
//    // Строим кучу
//    for (int i = end / 2; i >= 0; i--) {
//        sift_down(heap, i, end);
//    }
//    // Последовательно извлекаем максимум из кучи и помещаем его в конец
//    while (end > 0) {
//        swap(heap[0], heap[end]);
//        end--;
//        sift_down(heap, 0, end);
//    }
//}