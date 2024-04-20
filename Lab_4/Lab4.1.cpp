// Lab4.1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <time.h>
#include <vector>
#include <string.h>
#include <stdlib.h>

using namespace std;

//Инициализация функций с задачами
void task1();
void task2();
void task3();
void task4();
void task5();

//Инициализация вспомогательных функций
typedef unsigned int bitword;
//Инициализирует массив битов длины num, устанавливая все его биты в ноль
void bitsetZero(bitword* arr, int num);
//Возвращает значение idx-ого бита (0 или 1)
int bitsetGet(const bitword* arr, int idx);
//Устанавливает значение idx-ого бита в newval (которое равно 0 или 1)
void bitsetSet(bitword* arr, int idx, int newval);
//Возвращает 1, если среди битов с номерами k для left <= k < right есть единичный, и 0 иначе
int bitsetAny(const bitword* arr, int left, int right);
//Устанавливает значение idx-ого бита c конца в newval (которое равно 0 или 1) в целом числе
int IntbitsetSet(vector<int> arr, int idx, int newval);

bitword* Arr = (bitword*)calloc(1, sizeof(bitword));

int main()
{
    //Подключаем русский язык
    setlocale(LC_ALL, "Rus");
    //Задача №1
   //task1();
   //Задача №2
   //task2();
   //Задача №3
   //task3();
   //Задача №4
    //task4();
    //Задача №5
    task5();
}

void task1()
{
    //Изначальное число, которое мы переведем в 2 систему счисления для подсчета количества единиц, идущх подряд
    int N,
        //Максимальное количество единиц, идущих подряд
        Max = 1,
        //Число единиц, на данный момент идущих подряд
        Counter = 1;
    scanf_s("%i", &N);
    //Результат перевода изначального числа в двоичную систему
    char* Res = (char*)calloc(100, sizeof(char));
    //Если не получилось выделить память, то завершаем работу программы
    if (!Res)
    {
        printf("Error there is no memory");
        return;
    }
    //Переводим изначальное число в двоичную систему
    Res = _itoa(N, Res, 2);
    //Считаем максимальное количество единиц, идущих подряд
    for (int i = 1; i < strlen(Res); i++)
    {
        if (Res[i] == '1')
        {
            Counter += 1;
            if (Counter > Max)
            {
                Max = Counter;
            }
        }
        else
        {
            if (Counter > Max)
            {
                Max = Counter;
            }
            Counter = 0;
        }
    }
    //Выводим результат
    printf("%i", Max);
    //Очищаем выделенную память
    free(Res);
}

void task2()
{
    //Изначальное число
    int N,
        //Число, которое будет выведено во 2 строке
        SecStr = 0;
    scanf_s("%i", &N);
    //Побитовый вывод числа
    for (int i = 0; i < 32; i++)
    {
        printf("%i", (N >> 31 - i) & 1);
    }
    printf("\n");
    //Побитово инвертируем изначальное число
    for (int i = 0; i < 32; i++)
    {
        SecStr |= abs(N % 2) << 31 - i;
        N >>= 1;
    }
    //Выводим побитово инвертированное изначальное число в качестве десятичного числа
    printf("%i", SecStr);
    printf("\n");
    //Побитовый вывод инвертированного числа
    for (int i = 0; i < 32; i++)
    {
        printf("%i", (SecStr >> 31 - i) & 1);
    }

}

void task3()
{
    //Число запросов
    int N;
    scanf_s("%i", &N);
    for (int i = 0; i < N; i++)
    {
        //Число, в котором мы ищем 2 в максимальной степени k, как один из множителей 
        int X,
            //Максимальная сепень 2
            k = 0;
        scanf_s("%i", &X);
        bool Flag = false;
        while (!Flag)
        {
            if (X % 2 == 0)
            {
                k += 1;
                X /= 2;
            }
            else
            {
                Flag = true;
            }

        }
        printf("%.lf\n", pow(2, k));
    }
}

void task4()
{
    //Число запросов
    int N;
    int BitValue;
    scanf_s("%i", &N);
    //Если не смогли выделить память, то завершаем работу програмы
    if (!Arr)
    {
        printf("Error there is no memory");
        return;
    }
    //Запрашиваем операции заданное ранее количество раз
    for (int i = 0; i < N; i++)
    {
        //Вид операции
        int t;
        scanf_s("%i", &t);
        switch (t)
        {
            //Инициализация массива
        case 0:
            //Размер массива (в битах)
            int ArrSize;
            scanf_s("%i", &ArrSize);
            //Инициализируем массив
            bitsetZero(Arr, ArrSize);
            break;
            //Вывод значения определенного бита
        case 1:
            //Индекс бита, значение которого нужно вывести
            int Index;
            scanf_s("%i", &Index);
            //Значения бита под номером Index
            BitValue = bitsetGet(Arr, Index);
            printf("%i\n", BitValue);
            break;
            //Замена значения бита
        case 2:
            //Индекс бита, значение которого нужно поменять
            int ElIndex, NewVal;
            scanf_s("%i%i", &ElIndex, &NewVal);
            //Меняем значение определенного бита
            bitsetSet(Arr, ElIndex, NewVal);
            break;
            //Вывод информации о том, есть ли единичный бит в заданном дипазоне
        case 3:
            //Левая граница диапазона
            int LeftBoard,
                //Правая граница диапазона
                RightBoard;
            scanf_s("%i%i", &LeftBoard, &RightBoard);
            //Смотрим есть ли единичный бит в заданном дипазоне
            int IsUnit = bitsetAny(Arr, LeftBoard, RightBoard);
            //Если есть
            if (IsUnit == 1)
            {
                printf("some\n");
            }
            //Если нет
            else
            {
                printf("none\n");
            }
            break;

        }
    }
}

void task5()
{
    //Количество чиел в строке
    int N,
    //Количество операций над числами
        M,
    //Номер бита, который мы изменяем
        BitNum,
    //Значение бита, которое мы ставим в нужный бит
        NewBitVal;
    cin >> N >> M;
    //Массив чисел
    vector <int> Arr(N);
    //Заполняем массив
    for (int i = 0; i < N; i++)
    {
        cin >> Arr[i];
    }
    //Выполняем замену битов
    for (int i = 0; i < M; i++)
    {
        cin >> NewBitVal >> BitNum;
        Arr[BitNum/32] = IntbitsetSet(Arr, BitNum, NewBitVal);
    }
    
    for (int i = 0; i < N; i++)
    {
        cout << Arr[i] << ' ';
    }
}

void bitsetZero(bitword* arr, int num)
{
    int NewSize = round((float)num / 32);
    if (NewSize < 1)
    {
        NewSize = 1;
    }
    if (NewSize*32 < num)
    {
        //Перевыделяем память под новый массив нового размера
        arr = (bitword*)realloc(arr, (NewSize +1 ) * sizeof(bitword));
        
    }
    else
    {
        //Перевыделяем память под новый массив нового размера
        arr = (bitword*)realloc(arr, NewSize * sizeof(bitword));
    }
    
    //Если не смогли выделить память, то завершаем работу програмы
    if (!arr)
    {
        printf("Error there is no memory");
        return;
    }
    for (int i = 0; i < NewSize; i++)
    {
        arr[i] = 0;
    }
}

int bitsetGet(const bitword* arr, int idx)
{
    //Номер элемента массива
    int Number = idx / 32;
    //Индекс бита внутри элемента
    int IdxInNum = idx % 32;
    //Возвращаем значение бита
    return((arr[Number] >> IdxInNum) & 1);
}

void bitsetSet(bitword* arr, int idx, int newval)
{
    //Номер элемента массива
    int Number = idx / 32;
    //Индекс бита внутри элемента
    int IdxInNum = idx % 32;
    //Если меняем бит на 1
    if (newval == 1)
    {
        arr[Number] |= (int)pow(2, IdxInNum);
    }
    //Если меняем бит на 0
    else
    {
        //Число с зануленным битом
        int Diff = 0;
        for (int i = 0; i < 32; i++)
        {
            //Все биты кроме зануляемого оставляем без изменений
            if (i != IdxInNum)
            {
                if (((arr[Number] >> i) & 1) == 1)
                {
                    Diff += (int)pow(2, i);
                }
            }

        }
        arr[Number] = Diff;
    }
}

int bitsetAny(const bitword* arr, int left, int right)
{
    //Показывает есть ли 1 в данном бите
    bool Flag = false;
    for (int i = left; i < right; i++)
    {
        //
        if ((i % 32 == 0) && (i + 32 <= right))
        {
            if (arr[i/32] > 0)
            {
                Flag = true;
                return 1;
            }
            else
            {
                i += 31;
            }
        }
        else
        {
            unsigned x = (unsigned)pow(2, i % 32);
            unsigned y = (arr[i / 32] & x);
            if (y == x)
            {
                Flag = true;
                return 1;
            }
        }
        
    }
    if(!Flag)
    {
        return 0;
    }
}

int IntbitsetSet(vector<int> arr , int idx, int newval)
{
    //Номер элемента массива
    int Number = idx / 32;
    //Индекс бита внутри элемента
    int IdxInNum = 31 - (idx % 32);
    //Если меняем бит на 1
    if (newval == 1)
    {
        arr[Number] |= (int)pow(2, IdxInNum);
    }
    //Если меняем бит на 0
    else
    {
        //Число с зануленным битом
        int Diff = 0;
        for (int i = 0; i < 32; i++)
        {
            //Все биты кроме зануляемого оставляем без изменений
            if (i != IdxInNum)
            {
                if (((arr[Number] >> i) & 1) == 1)
                {
                    Diff += (int)pow(2, i);
                }
            }

        }
        arr[Number] = Diff;
    }
    return(arr[Number]);
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
