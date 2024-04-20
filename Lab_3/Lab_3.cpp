// Lab_3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//


#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

//Инициализация функций с задачами
void task1();
void task2();
void task3();
void task4();
void task5();
void task6();
//Инициализация вспомогательных функций


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
    //task5();
    //Задача №6
    task6();
}

void task1()
{
    //Десятичное число, которое нам нужно перевести в систему счисления с основанием b
    int N,
    //Основание системы счисления, в которую нужно перевести десятичное число N
        b;
    scanf_s("%i", &b);
    scanf_s("%i", &N);
    //Количество разрядов в числе
    int DigitAmm = 1;
    //Временная переменная, которая поможет посчитать количество разрядов
    int Temp = N;
    //Считаем количество разрядов
    while (Temp >= b)
    {
        DigitAmm += 1;
        Temp = Temp / b;
    }
    //Число, которое получится при переводе
    char* Result = (char*)calloc(DigitAmm, sizeof(char));
    //Если не получилось выделить память, то завершаем работу программы
    if (!Result)
    {
        printf("Error there is no memory");
        return;
    }
    //Переводим число в систему счисления с основанием b
    Result = _itoa(N, Result, b);
    //Выводим число на экран
    for (int i = 0; i < strlen(Result); i++)
    {
        printf("%c", Result[i]);
    }
    //Освобождаем выделенную память
    free(Result);
}

void task2()
{
    //Основание системы счисления, из которой нужно перевести число 
    int b;
    scanf_s("%i", &b);
    //Изначальное число
    char OrigNum[101];
    scanf("%s", OrigNum);
    //Множитель, на который мы умножаем при переводе
    int Multiplier = 1;
    //Результат перевода в дксятичную систему счисления
    int Result = 0;
    for (int i = strlen(OrigNum) - 1; i >= 0; i--)
    {
        switch (OrigNum[i])
        {
        //Если прибавляем к результату число от 0 до 9
        default:
            Result += (OrigNum[i] - '0') * Multiplier;
            Multiplier *= b;
            break;
        //Если прибавляем к результату 10
        case 'a':
            Result += 10 * Multiplier;
            Multiplier *= b;
            break;
        //Если прибавляем к результату 11
        case 'b':
            Result += 11 * Multiplier;
            Multiplier *= b;
            break;
        //Если прибавляем к результату 12
        case 'c':
            Result += 12 * Multiplier;
            Multiplier *= b;
            break;
        //Если прибавляем к результату 13
        case 'd':
            Result += 13 * Multiplier;
            Multiplier *= b;
            break;
        //Если прибавляем к результату 14
        case 'e':
            Result += 14 * Multiplier;
            Multiplier *= b;
            break;
        //Если прибавляем к результату 15
        case 'f':
            Result += 15 * Multiplier;
            Multiplier *= b;
            break;
        }
    }
    //Выводим результат
    printf("%i", Result);
}

void task3()
{
    //Десятичное число больше 0, но меньше 1, которое нам нужно перевести в систему счисления с основанием b
    double N;
    //Основание системы счисления, в которую нужно перевести десятичное число N
    int   b
    //Количество знаков после запятой
        , k;
    scanf_s("%i%i", &b, &k);
    scanf_s("%lf", &N);
    //Рзультат перевода
    char* Result = (char*)calloc(k + 3, sizeof(char));
    if (!Result)
    {
        printf("Error there is no memory");
        return;
    }

    //Поскольку число меньше 1, то сразу показываем это
    Result[0] = '0';
    Result[1] = '.';
    //Переводим с точностью, ввденной выше
    for (int i = 0; i < k; i++)
    {
        //Умножаем изначальное число на основание системы счисления
        N *= b;
        //Округленный результат умножения
        int Temp = (int)N;
        //Если округление произошло в большую сторону
        if (Temp > N)
        {
            //Получаем целую часть путем отнимания от умноженного числа дробой части
            int IntPart = N - (N - (Temp - 1));
            //Оставляем от числа только дробную часть
            N -= Temp - 1;
            switch (IntPart)
            {
            //Если приписываем число от 0 до 9
            default:
                Result[i + 2] = IntPart + '0';
                break;
            //Если прибавляем к результату 10
            case 10:
                Result[i + 2] = 'a';
                break;
            //Если прибавляем к результату 11
            case 11:
                Result[i + 2] = 'b';
                break;
            //Если прибавляем к результату 12
            case 12:
                Result[i + 2] = 'c';
                break;
            //Если прибавляем к результату 13
            case 13:
                Result[i + 2] = 'd';
                break;
            //Если прибавляем к результату 14
            case 14:
                Result[i + 2] = 'e';
                break;
            //Если прибавляем к результату 15
            case 15:
                Result[i + 2] = 'f';
                break;
            }
            //Если мы перевели число полносью, то чтобы не писать уточняющие нули, прерываем цикл 
            if (N == 0)
            {
                break;
            }
        }
        //Если округление произошло в меньшую сторону
        else
        {
            //Получаем целую часть путем отнимания от умноженного числа дробой части
            int IntPart = N - (N - Temp);
            //Оставляем от числа только дробную часть
            N -= Temp;
            switch (IntPart)
            {
                //Если приписываем число от 0 до 9
            default:
                Result[i + 2] = IntPart + '0';
                break;
                //Если прибавляем к результату 10
            case 10:
                Result[i + 2] = 'a';
                break;
                //Если прибавляем к результату 11
            case 11:
                Result[i + 2] = 'b';
                break;
                //Если прибавляем к результату 12
            case 12:
                Result[i + 2] = 'c';
                break;
                //Если прибавляем к результату 13
            case 13:
                Result[i + 2] = 'd';
                break;
                //Если прибавляем к результату 14
            case 14:
                Result[i + 2] = 'e';
                break;
                //Если прибавляем к результату 15
            case 15:
                Result[i + 2] = 'f';
                break;
            }
            //Если мы перевели число полносью, то чтобы не писать уточняющие нули, прерываем цикл 
            if (N == 0)
            {
                break;
            }
        }   
    }
    for (int i = 0; i < strlen(Result); i++)
    {
        printf("%c", Result[i]);
    }
    free(Result);
}

void task4()
{
    //Результат перевода
    double Result = 0;
    //Основание системы счисления, из которой нужно перевести число 
    int b;
    //Степень множителя, на который мы умножаем при переводе
    //Изначальное число
    char OrigNum[54];
    scanf_s("%i", &b);
    scanf("%s", OrigNum);
    //Знаминатель множителя, используемого для перевода дроной части
    double DenomOfMultiplier = b;
    //Множитель, используемый для перевода дроной части
    double Multiplier = 1/DenomOfMultiplier;
    //Переводим изначальное число в десятичную систему счисления
    for (int i = 2; i < strlen(OrigNum); i++)
    {
        switch (OrigNum[i])
        {
            //Если переводим число от 0 до 9
        default:
            Result += (OrigNum[i] - '0') * Multiplier;
            break;
            //Если прибавляем к результату 10
        case 'a':
            Result += 10 * Multiplier;
            break;
            //Если прибавляем к результату 11
        case 'b':
            Result += 11 * Multiplier;
            break;
            //Если прибавляем к результату 12
        case 'c':
            Result += 12 * Multiplier;
            break;
            //Если прибавляем к результату 13
        case 'd':
            Result += 13 * Multiplier;
            break;
            //Если прибавляем к результату 14
        case 'e':
            Result += 14 * Multiplier;
            break;
            //Если прибавляем к результату 15
        case 'f':
            Result += 15 * Multiplier;
            break;
        }
        DenomOfMultiplier *= b;
        Multiplier = 1 / DenomOfMultiplier;
    }
    printf("%.5lf", Result);
}

void task5()
{
    //Основание системы счисления изначального числа, которое нужно будет перевести
    int p,
    //Основание системы счисления, в которую нам нужно будет перевести изначальное число
        q;
    //Изначальное число
    char N[51];
    scanf("%i %i %s", &p, &q, N);
    //Результат перевода в десятичную систему счисления
    int DecResult = 0,
    //Множитель, на который мы умножаем при переводе
        Multiplier = 1;
    //Переводим в десятичную систему счисления
    for (int i = strlen(N) - 1; i >= 0; i--)
    {
        //Если цифра от 1 до 9
        if (((int)N[i] >= 48) && ((int)N[i] <= 57))
        {
            DecResult += ((int)N[i] - 48) * Multiplier;
            Multiplier *= p;
        }
        //Если больше
        else
        {
            DecResult += ((int)N[i] - 87) * Multiplier;
            Multiplier *= p;
        }
    }
    //Результат перевода в систему счисления с основанием q
    char* FinalResult = (char*)calloc(51, sizeof(char));
    //Если не получилось выделить память, то завершаем работу программы
    if (!FinalResult)
    {
        printf("Error there is no memory");
        return;
    }
    //Переводим в систему счисления с основанием q
    FinalResult = _itoa(DecResult, FinalResult, q);
    //Выводим число на экран
    for (int i = 0; i < strlen(FinalResult); i++)
    {
        printf("%c", FinalResult[i]);
    }
    //Освобождаем выделенную память
    free(FinalResult);
}

void task6()
{
    //Основание системы счисления изначального числа, которое нужно будет перевести
    int p,
    //Основание системы счисления, в которую нам нужно будет перевести изначальное число
        q,
    //Количество знаков после запятой
         k;
    scanf_s("%i %i %i", &p, &q, &k);
    //Изначальное число
    char A[102];
    scanf("%s", A);
    //Количество цифр в целой части изначального числа
    int IntAmm = 0, 
    //Количество цифр в дробной части изначального числа
        DivAmm = 0,
    //Позиция точки, разделяющей изначальное число на целую и дробную часть
        DotPos = 0;
    //Считаем количество цифр в целой части изначального числа и количество цифр в дробной части изначального числа
    for (int i = 0; i < strlen(A); i++)
    {
        //Считаем количество цифр в целой части изначального числа
        if (A[i]!='.')
        {
            IntAmm += 1;
            //Если введенное число не коректно, то завершаем работу программы
            if (((int)A[i] >= 48) && ((int)A[i] <= 57))
            {
                if ((int)A[i] - 48 >= p)
                {
                    printf("NO");
                    return;
                }
            }
            else
            {
                if ((int)A[i] - 87 >= p)
                {
                    printf("NO");
                    return;
                }
            }
        }
        //Считаем количество цифр в дробной части изначального числа
        else
        {
            //Запоминаем позицию точки в изначальном числе
            DotPos = i;
            i += 1;
            for (int j = i; j < strlen(A); j++)
            {
                DivAmm += 1;
                if (((int)A[i] >= 48) && ((int)A[i] <= 57))
                {
                    if ((int)A[i] - 48 >= p)
                    {
                        printf("NO");
                        return;
                    }
                }
                else
                {
                    if ((int)A[i] - 87 >= p)
                    {
                        printf("NO");
                        return;
                    }
                }
                i++;
            }
        }

    }
    //Целая часть числа, которую мы получим при переводе
    char* IntPart = (char*)calloc(402, sizeof(char));
    //Если не смогли выделить память, то завершаем работу програмы
    if (!IntPart)
    {
        printf("Error there is no memory");
        return;
    }
    //Дробная часть числа, которую мы получим при переводе
    char* DevPart = (char*)calloc(404, sizeof(char));
    //Если не смогли выделить память, то завершаем работу програмы
    if (!DevPart)
    {
        printf("Error there is no memory");
        return;
    }
    DevPart[0] = '0';
    DevPart[1] = '.';
    //Результат перевода в десятичную систему счисления
    int IntDecResult = 0,
        //Множитель, на который мы умножаем при переводе
        Multiplier = 1;
    //Переводим в десятичную систему счисления целую часть изначального числа
    for (int i = IntAmm-1; i >= 0; i--)
    {
        //Если цифра от 1 до 9
        if (((int)A[i] >= 48) && ((int)A[i] <= 57))
        {
            IntDecResult += ((int)A[i] - 48) * Multiplier;
            Multiplier *= p;
        }
        //Если больше
        else
        {
            IntDecResult += ((int)A[i] - 87) * Multiplier;
            Multiplier *= p;
        }
    }
    //Переводим целую часть изначаьного числа в систему счисления с основанием q
    IntPart = _itoa(IntDecResult, IntPart, q);
    //Результат перевода дробной части в десятичную систему
    double DevDecResult = 0;
    //Если число имеет дробную часть, то переводим ее сначала в десятичную систему, а потом в систему счисления с основанием q
    if (DotPos != 0)
    {
        //Знаминатель множителя, используемого для перевода дроной части
        double DenomOfMultiplier = p;
        //Множитель, используемый для перевода дроной части
        double DevMultiplier = 1 / DenomOfMultiplier;
        //Переводим дробную часть в десятичную систему счисления
        for (int i = DotPos + 1; i < strlen(A); i++)
        {
            //Если цифра от 1 до 9
            if (((int)A[i] >= 48) && ((int)A[i] <= 57))
            {
                DevDecResult += ((int)A[i] - 48) * DevMultiplier;
                DenomOfMultiplier *= p;
                DevMultiplier = 1 / DenomOfMultiplier;
            }
            //Если больше
            else
            {
                DevDecResult += ((int)A[i] - 87) * DevMultiplier;
                DenomOfMultiplier *= p;
                DevMultiplier = 1 / DenomOfMultiplier;
            }
        }
        //Переводим дробную часть в систему счисления с основанием q
        for (int i = 2; i < k + 3; i++)
        {
            //Умножаем дробную часть изначального числа, переведенную в десятичную систему счисления, на основание системы счисления, в которую нужно перевести изначальное число
            DevDecResult *= q;
            //Округленный результат умножения
            int Temp = (int)DevDecResult;
            //Если округление произошло в большую сторону
            if (Temp > DevDecResult)
            {
                //Получаем целую часть путем отнимания от умноженного числа дробой части
                int Rounded = DevDecResult - (DevDecResult - (Temp - 1));
                DevDecResult -= (Temp - 1);
                //Если цифра от 1 до 9
                if (Rounded <= 9)
                {
                    DevPart[i] = Rounded + 48;
                }
                //Если больше
                else
                {
                    DevPart[i] = Rounded + 87;
                }
                //Если мы перевели дробную часть полносью, то чтобы не писать уточняющие нули, прерываем цикл 
                if (DevDecResult == 0)
                {
                    break;
                }
            }
            //Если округление произошло в меньшую сторону
            else
            {
                //Получаем целую часть путем отнимания от умноженного числа дробой части
                int Rounded = DevDecResult - (DevDecResult - Temp);
                DevDecResult -= Temp;
                //Если цифра от 1 до 9
                if (Rounded <= 9)
                {
                    DevPart[i] = Rounded + 48;
                }
                //Если больше
                else
                {
                    DevPart[i] = Rounded + 87;
                }
                //Если мы перевели дробную часть полносью, то чтобы не писать уточняющие нули, прерываем цикл 
                if (DevDecResult == 0)
                {
                    break;
                }
            }
        }
    }
    //Выводим целую часть
    for (int i = 0; i < strlen(IntPart); i++)
    {
        printf("%c", IntPart[i]);
    }
    //Вывдоим дробную часть, если есть
    if (DotPos != 0)
    {
        for (int i = 1; i < k + 2; i++)
        {
            printf("%c", DevPart[i]);
        }
    }
    //Освобождаем выделенную память
    free(IntPart);
    free(DevPart);
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
