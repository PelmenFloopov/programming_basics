// Lab10.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <map>
using namespace std;

void task1();
void task2();
void task3();
void task4();
void task5();
void task6();
void task7();
void task8();
void task9();
void task10();

//Инициализируем вспомагательные функции

//Принимает строку, в которой записано время, разделитель в строке и и ссылку на массив, в который нужно записать значения часов, минут и секунд
//Возвращает истину, если время введено корректно и его можно считать, иначе ложь, а также записывает часы минуты и секунды в массив arr
bool readTime(string str, char delim, vector<int>& arr);
//Принимает строку, в которой нужно посчитать количество букв и цифр и ссылки на переменные, в которых хранятся количества строчных букв, заглавных букв и цифр
//Возвращает общее количество символов
int calcLetters(string iStr, int* oLowerCnt, int* oUpperCnt, int* oDigitsCnt);

void createString(vector<string>& strArr);

void delString(vector<string>& strArr, int index);

void printString(vector<string>& strArr, int index);

void symbolAmm_InString(vector<string>& strArr, int index, char symbol);

int main()
{
    //task1();
    //task2();
    //task3();
    //task4();
    //task5();
    //task6();
    //task7();
    //task8();
    //task9();
    task10();
}

void task1()
{
    //Количество наборов времен
    int N;
    //Текущее время
    vector<int>currTime(3);
    cin >> N;
    //Массив, содержащий наборы времен
    vector<vector<int>>Mat(N);
    //Заполняем массив наборами времен
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < currTime.size(); j++)
        {
            cin >> currTime[j];
        }
        Mat[i] = currTime;
    }
    //Выводим наборы времен
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < Mat[i].size(); j++)
        {
            if (j < Mat[i].size() - 1)
            {
                printf("%02d:", Mat[i][j]);
            }
            else
            {
                printf("%02d", Mat[i][j]);
            }
        }
        cout << "\n";
    }
}

void task2()
{
    //Строка, из которой мы считываем время 
    string str;
    cin >> str;
    //Разделитель между часами, минутами и секундами
    char delim = ':';
    //Массив, в котором хранится значение часов, минут и секунд
    vector<int> currTime(3, 0);
    currTime.reserve(0);
    //Обозначает, корректно ли записано время и можно ли его считать
    bool isCorrectTime = readTime(str, delim, currTime);
    //Вывод
    for (int i = currTime.size(); i > 0; i--)
    {
        cout << isCorrectTime << " ";
        for (int j = 0; j < i; j++)
        {
            cout << currTime[j] << " ";
        }
        cout << '\n';
    }
}

void task4()
{
    //Структура подписи
    typedef struct Label_s {
        string name; //имя автора (заканчивается нулём)
        int age; //возраст автора (сколько лет)
    } Label;

    //Структура статистики имен
    typedef struct NameStats_s {
        int cntTotal; //сколько всего подписей
        int cntLong; //сколько подписей с именами длиннее 10 букв
    } NameStats;

    //Структура статистики возрастов
    typedef struct AgeStats_s {
        int cntTotal; //сколько всего подписей
        int cntAdults; //сколько подписей взрослых (хотя бы 18 лет)
        int cntKids; //сколько подписей детей (меньше 14 лет)
    } AgeStats;
    //Количество участников
    int n;
    cin >> n;
    //Массив подписей 
    vector<Label> labes(n);
    labes.reserve(0);
    {
        string tmpStr;
        for (int i = 0; i < n; i++)
        {
            cin >> labes[i].name;
            cin >> labes[i].age;

            cin >> tmpStr;
        }
    }
    //Статистика имен
    NameStats nStat;
    nStat.cntTotal = n;
    nStat.cntLong = 0;
    //Статистика возрастов
    AgeStats aStat;
    aStat.cntTotal = n;
    aStat.cntAdults = 0;
    aStat.cntKids = 0;
    //Составляем статистики по именам и возрастам
    for (int i = 0; i < n; i++)
    {
        nStat.cntLong += (labes[i].name.size() > 10) ? 1 : 0;
        if (labes[i].age >= 18) aStat.cntAdults += 1;
        if (labes[i].age < 14) aStat.cntKids += 1;
    }
    //Вывод статистик
    printf("names: total = %i\n", nStat.cntTotal);
    printf("names: long = %i\n", nStat.cntLong);
    printf("ages: total = %i\n", aStat.cntTotal);
    printf("ages: adult = %i\n", aStat.cntAdults);
    printf("ages: kid = %i\n", aStat.cntKids);
}

void task5()
{
    //Массив считанных с консоли строк 
    vector<string> text;
    string currStr;
    //Считываем строки с консоли и записываем их в массив
    while(getline(cin, currStr, '\n')) text.push_back(currStr);            
    currStr.reserve(0);
    //Количество строчных букв в строке
    int oLowerCnt = 0,
        //Количество заглавных букв в строке
        oUpperCnt = 0,
        //Количество цифр строке
        oDigitsCnt = 0;
    //Вывод информации о строках
    for (int i = 0; i < text.size(); i++)
    {
        int letAmm = calcLetters(text[i], &oLowerCnt, &oUpperCnt, &oDigitsCnt);
        printf("Line %i has %i chars: %i are letters (%i lower, %i upper), %i are digits.\n", i + 1, letAmm, oUpperCnt + oLowerCnt, oLowerCnt, oUpperCnt, oDigitsCnt);
        oLowerCnt = 0;
        oUpperCnt = 0;
        oDigitsCnt = 0;
    }
}

void task6()
{
    //Количество строк, которые нужно развернуть
    int N;
    cin >> N;
    //Массив строк, которые нужно развернуть
    vector<string> text(N);
    text.reserve(0);
    //Заполняем массив
    for (int i = 0; i < N; i++)
    {
        cin >> text[i];
    }
    //Разворачиваем и выводим строки
    for (int i = 0; i < N; i++)
    {
        reverse(text[i].begin(), text[i].end());
        cout << text[i] << endl;
    }
}

void task7()
{
    //Класс, в котором хранится количество слов и их массив
    class Tokens {
    public:
        Tokens() {};
        ~Tokens() {};
    public:      
        //Количество слов в строке
        int num = 0;
        //Массив слов (каждый элемент – строка)
        vector<string> arr; 
        //Метод, который считает количество слов между разделителями и записывает слова в массив
        void tokensSplit(Tokens* tokens, string str, string delims)
        {
            string currWord;
            for (int i = 0; i < str.size(); i++)
            {
                bool flag = false;
                for (int j = 0; j < delims.size(); j++)
                {
                    if (str[i] == delims[j])
                    {
                        flag = true;
                        break;
                    }
                }
                if ((!flag) && ((str[i] >= 'a' && str[i] <= 'z') || ((str[i] >= 'A' && str[i] <= 'Z'))))currWord += str[i];
                else
                {
                    if (!currWord.empty())
                    {
                        tokens->arr.push_back(currWord);
                        currWord.clear();
                    }                    
                }
                if (i == str.size() - 1 && !currWord.empty()) tokens->arr.push_back(currWord);
            }
            tokens->num = tokens->arr.size();
        }            
    };
    //Строка, в которой нужно найти количество слов и сами слова
    string str;
    cin >> str;
    //Разделители в строке
    string delims = ".,;:";
    Tokens* tokens = new Tokens();
    tokens -> tokensSplit(tokens, str, delims);
    //Вывод
    cout << tokens->num << endl;
    for (int i = 0; i < tokens->num; i++)
    {
        cout << tokens->arr[i] << endl;
    }
    //Освобождаем выделенную память
    delete tokens;
}

void task8()
{
    int N;
    cin >> N;
    string resStr, currStr;
    for (int i = 0; i < N; i++)
    {
        cin >> currStr;
        resStr += currStr;
    }
    cout << resStr;
}

void task9()
{
    int n, index;
    cin >> n;
    vector<string> strArr;
    for (int i = 0; i < n; i++)
    {
        int operType;
        cin >> operType;
        switch (operType)
        {        
        case 0:
            int strSize;
            cin >> strSize;
            createString(strArr);
            break;
        case 1:            
            cin >> index;
            delString(strArr, index);
            break;
        case 2:            
            cin >> index;
            printString(strArr, index);
            break;
        case 3:            
            char symbol;
            cin >> index >> symbol;
            symbolAmm_InString(strArr, index, symbol);
            break;
        }
    }
}

void task10()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int p, q;        
        unsigned long long m;
        scanf_s("%i/%i xor %llx", &p, &q, &m);
        double x = double(p / q);    
        unsigned long long* x_bits = (unsigned long long*) & x;
        *x_bits ^= m;
        printf("%0.15g\n", x);
    }
}

bool readTime(string str, char delim, vector<int>& arr)
{ 
    //Строковый поток, в котором хранится строка со временем
    stringstream sStr;
    sStr << str;    
    //Временный строковый поток, для записи в него частей основной строки
    stringstream tmp_sStr;
    //Индекс элемента массива, с которым мы работаем
    int i = 0;
    //Пока не кончилась сторка, считываем её часть до разделителя
    while(getline(sStr, str, delim))
    {
        
        tmp_sStr.clear(); //Очищаем временный строковый поток, для возможности записать туда новую часть основной строки
        tmp_sStr << str;
        if (tmp_sStr >> arr[i])
        {
                
        }
        //Если не получилось считать число, то заполняем массив отрицательными значениями и завершаем работу фунцкции
        else
        {
            for (int j = 0; j < arr.size(); j++)
            {
                arr[j] = -1;
            }
            return 0;
        }
        i += 1;
    }        
    //Проверка корректности введеного и считанного времени
    for (int i = 0; i < arr.size(); i++)
    {
        if (i == 0)
        {
            if (arr[i] < 0 || arr[i] > 23)
            {
                for (int j = 0; j < arr.size(); j++)
                {
                    arr[j] = -1;
                }
                return 0;
            }
        }
        else
        {
            if (arr[i] < 0 || arr[i] > 59)
            {
                for (int j = 0; j < arr.size(); j++)
                {
                    arr[j] = -1;
                }
                return 0;
            }
        }
    }
    //Если все введено корректно, то возвращаем 1
    return 1;
}

int calcLetters(string iStr, int* oLowerCnt, int* oUpperCnt, int* oDigitsCnt)
{
    for (int i = 0; i < iStr.size(); i++)
    {
        if ((iStr[i] >= 'a') && (iStr[i] <= 'z'))
        {
            (*oLowerCnt) += 1;
        }
        else if ((iStr[i] >= 'A') && (iStr[i] <= 'Z'))
        {
            (*oUpperCnt) += 1;
        }
        else if ((iStr[i] >= '0') && (iStr[i] <= '9'))
        {
            (*oDigitsCnt) += 1;
        }
        
    }
    return iStr.size();
}

void createString(vector<string>& strArr)
{ 
    string newStr;
    newStr.size();
    cin >> newStr;
    newStr.reserve(0);
    strArr.push_back(newStr);
    return;
}

void delString(vector<string>& strArr, int index)
{
    strArr[index].clear();    
    return;
}

void printString(vector<string>& strArr, int index)
{
    cout << strArr[index] << endl;
    return;
}

void symbolAmm_InString(vector<string>& strArr, int index, char symbol)
{
    int amm = 0;
    for (int i = 0; i < strArr[index].size(); i++)
    {        
        if (strArr[index][i] == symbol) amm += 1;                
    }
    cout << amm << endl;    
    return;
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
