// Lab_1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <time.h>
#include <string.h>
using namespace std;

//Инициализация функций с задачами
void task1();
void task2();
void task4();
//Инициализация вспомогательных функций
bool IsNumPrime(int Num);

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
   task4();

}

void task1()
{
    int N;
    printf("Введите  целое число от 2 до 10000\n");
    scanf_s("%i", &N);
    bool Border = true;
    if ((N < 2) || (N > 10000))
    {
        Border = false;
        while (!Border)
        {
            printf("Ошибка. Введено неправильное число. Введите число заново\n");
            scanf_s("%i", &N);
            if ((N >= 2) && (N <= 10000))
            {
                Border = true;
            }
        }
    }
    if (N!=2)
    {
        bool Flag = false;
        for (int i = 2; i < N; i++)
        {
            if (N % i == 0)
            {
                Flag = true;
                printf("NO");
                break;
            }
           
        }
        if (!Flag)
        {
            printf("YES");
        }
       
    }
    else
    {
        printf("YES");
    }
}

void task2()
{
    //Число, до которого нам нужно найти все простые числа
    int N;
    printf("Введите  целое число от 2 до 1.000.000\n");
    scanf_s("%i", &N);
    //Массив чисел от 2 до N
    int* Arr = (int*)calloc(N-1, sizeof(int));
    //Если ошибка, то выходим из программы
    if (!Arr)
    {
        printf("Error there is no memory");
        return;
    }
    //Заполняем массив
    for (int i = 0; i < N-1; i++)
    {
        Arr[i] = i + 2;
    }
    //Прохпдим по числам от 2 до N
    for (int i = 0; i < N - 1; i++)
    {
        //Если число непроверенное, то убираем числа, кратные простым множителям
        if (Arr[i] != 0)
        {
            //Убираем числа, кратные простым множителям, начиная с 2
            for (int j = i + Arr[i]; j < N - 1; j += Arr[i])
            {
                Arr[j] = 0;
            }
        }
    }
    //Выводим простые числа на экран
    for (int i = 0; i < N - 1; i++)
    {
        if (Arr[i]>0)
        {
            printf("%i ", Arr[i]);
        }
        
    }
    //Освобождаем выделенную память
    free(Arr);

}

void task4()
{
    int N, Q, x;
    printf("Введите диапазон, в котором нужно найти простые числа (от 10 до 20.000.000) и количество запросов в файле (от 1 до 100.000)\n");
    scanf_s("%d %d", &N, &Q);
    for (int i = 0; i < Q; i++)
    {
        printf("Введите число от 0 до %d не включая\n", N);
        scanf_s("%d", &x);
        bool Border = true;
        if ((x < 0) || (x >= N))
        {
            Border = false;
            while (!Border)
            {
                printf("Ошибка. Введено неправильное число. Введите число заново\n");
                scanf_s("%d", &x);
                if ((x >= 0) && (x < N))
                {
                    Border = true;
                }
            }
        }
        if (IsNumPrime(x))
        {
            printf("%d prime\n", x);
        }
        else
        {
            printf("%d not\n", x);
        }
    }

}


bool IsNumPrime(int Num)
{
    bool Flag = true;
    if ((Num<2) &&(Num>=0))
    {
        Flag = false;
    }
    else
    {
        for (int i = 2; i < Num; i++)
        {
            if (Num % i == 0)
            {
                Flag = false;
                break;
            }
        }
    }
    return (Flag);
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
