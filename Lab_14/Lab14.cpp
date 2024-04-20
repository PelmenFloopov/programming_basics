#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <conio.h>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <string>
#include <vector>

using namespace std;

//
void task1();

//В данной задаче нужно найти, с какого момента начнётся повторение у заданного квадратичного конгруентного генератора.
void task2();

//
void task3();

// Нужно раскрасить все эти подстроки в цвета, так чтобы одинаковые подстроки имели одинаковый цвет, а разные подстроки — разный цвет
void task4();


//Инициализирование вспомогательных функций  

uint64_t generator(uint64_t s, int a, int b, int c, uint64_t M);
uint32_t Hash(uint32_t key);


int main()
{
    task1();
    //task2();
    //task3();
    //task4();
}

void task1()
{    
    ifstream fin("input.bin", ios::binary | ios::in); //Открываем файловый поток, чтобы считать числа
    int n,  //Количество чисел в файле
        temp;
    fin.read((char*)&n, sizeof(n));
    unordered_set<int> arr(n); //Множество значений в файле
                            //Используется класс unordered_set для того, чтобы сохранять уникальные значения, идущие в том же порядке что и в файле
    //Считываем значения из файла в множество
    for (int i = 0; i < n; i++)
    {        
        fin.read((char*)&temp, sizeof(temp));
        arr.insert(temp);
    }
    fin.close(); //Закрываем файловый поток, т.к. считали все числа
    ofstream fout("output.bin", ios::binary | ios::out); //Открываем поток на запись
    int k = arr.size(); //Количество элементов множества
    fout.write((char*)&k, sizeof(k));
    for (int i : arr) fout.write((char*)&i, sizeof(i));
    fout.close();  
}

void task2()
{
    //Параметры для вычисления хэша
    int a, b, c;
    uint64_t M;
    cin >> M;
    cin >> a >> b >> c;
    unordered_map<uint64_t, pair<bool, int>> hashTable; //Хэш таблица, состаящая из ключа и пары. Первый элемент пары показывает, встречался ли элемент с таким же хэш кодом ранее, второй его индекс
    uint64_t key = generator(1, a, b, c, M); //Ключ хэш таблицы
    hashTable[1] = { true , 0 };
    if (hashTable[key].first)
    {
        cout << hashTable[key].second << ' ' << 1;
        return;
    }
    hashTable[key] = { true , 1 }; //Создаем первую пару в таблице    
    for (int i = 2; i < 2000002; i++)
    {
        //Вычисляем хэш код для нового элемента
        key = generator(key, a, b, c, M);
        //Если такой хэш код уже раньше встречался, то выводим индекс текущего элемента, и элемента, на котором он встретился
        if (hashTable[key].first)
        {
            cout << hashTable[key].second << ' ' << i;
            return;
        }
        //Если такой хэш еще не встречался, то делаем новую запись в таблице
        else
        {
            hashTable[key].first = true;
            hashTable[key].second = i;
        }
    }
}

void task3()
{
    unordered_map<uint32_t, pair<uint32_t, bool>> Map; //По хэш коду хранит индекс элемента и факт того, что мы его раньше встречали
    for (uint32_t i = 1; i < 20000000; i++)
    {
        uint32_t key;
        printf("eval %u", i);
        printf("\n");
        fflush(stdout);
        scanf_s("%u", &key);
        printf("\n");
        fflush(stdout);
        key = Hash(key);
        //Если элемент с таким хэшкодом уже встречался, то выводим ответ
        if (Map[key].second)
        {
            printf("answer %u %u", Map[key].first, i);
            break;
        }
        //Если элемент с таким хэшкодом еще не встречался, то добавляем его в Map
        else
        {
            Map[key].first = i;
            Map[key].second = true;
        }
    }

}

void task4()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int N; //Количество символов в строке
    int B; //Длина подстроки
    string S; //Строка
    cin >> N >> B >> S;
    //getline(cin, S);    
    unordered_map<string, pair<int, bool>> colours; //Хранит по хэш коду числа, которые соответствуют подстрокам и тот факт, встречались ли они в строке
    //hash<string> subStr_hash; //Считает хэш код подстроки    
    int num_substrings = N - B + 1; //Количество подстрок длины B
    int hash_index = 0; //Число, соответствующее определенной подстроке
    //Идем по подстрокам и выводим, число, соответствующее подстроке
    for (int i = 0; i < num_substrings; i++)
    {           
        string key = S.substr(i, B);
        if (!colours[key].second)
        {
            colours[key].first = hash_index;
            colours[key].second = true;
            //cout << colours[key].first << " ";
            printf("%i ", colours[key].first);
            hash_index++;
        }

        else
        {
            //cout << colours[key].first << " ";
            printf("%i ", colours[key].first);
        }
    }
}


//Генерирует хэш код (для 2 задачи)
uint64_t generator(uint64_t s, int a, int b, int c, uint64_t M) {
    return (s * s * a + s * b + c) % M;
}

//Генерирует хэш код (для 3 задачи)
uint32_t Hash(uint32_t key)
{
    return key >> 10;
}
