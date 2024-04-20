#include <iostream>
#include <set>
#include <map>
#include <algorithm>
#include <queue>
#include <string>
#include <vector>

using namespace std;


// Объявление вспомогательных функций

set<char> detect_overlay(vector<string>& field, char frameLetter, int upperBorderPos, int downBorderPos, int leftBorderPos, int rightBorderPos);
void output_in_alphabetical_order(vector<string> field, map<char, vector<int>> graph, char previousVertex, string currAnswer, set<string> &answers);

// Объявление функций с задачами
/// <summary>
/// Имеется 𝑁 лекционных тем, пронумерованных числами от 1 до 𝑁. За одну лекцию можно целиком рассказать одну тему, смешивать темы на лекции нельзя.
/// Некоторые темы зависят от других тем.Если тема 𝐴 зависит от темы 𝐵, то это означает, что нельзя рассказывать тему 𝐴, не рассказав предварительно тему 𝐵.
/// Требуется определить, в каком порядке нужно рассказывать темы на лекции, чтобы соблюсти все зависимости.
/// Если есть несколько подходящих порядков, нужно выбрать лексикографически наименьший из них.
/// То есть номер первой рассказываемой темы должен быть минимально возможный, среди таких порядков нужно выбрать такой, у которого номер темы на второй лекции минимально возможный, 
/// далее нужно минимизировать номер темы на третьей лекции, и так далее.
/// </summary>
void task1();

/// <summary>
/// Имеется 𝑁 лекционных тем, пронумерованных числами от 1 до 𝑁. За одну лекцию можно целиком рассказать одну тему, смешивать темы на лекции нельзя.
/// Некоторые темы зависят от других тем.Если тема 𝐴 зависит от темы 𝐵, то это означает, что нельзя рассказывать тему 𝐴, не рассказав предварительно тему 𝐵.
/// Требуется определить, в каком порядке нужно рассказывать темы на лекции, чтобы соблюсти все зависимости.
/// Если есть несколько подходящих порядков, нужно выбрать лексикографически наименьший из них.
/// То есть номер первой рассказываемой темы должен быть минимально возможный, среди таких порядков нужно выбрать такой, у которого номер темы на второй лекции минимально возможный, 
/// далее нужно минимизировать номер темы на третьей лекции, и так далее. 
/// </summary>
void task2();

/// <summary>
/// Определить порядок, в каком рамки накладывались друг на друга, начиная снизу по заданной картинке результирующей стопки рамок.
/// Правила следующие : 
/// 1. Ширина рамки — это одна литера, а стороны рамки не могут быть короче 3 литер.
/// 2. По крайней мере, часть каждой из четырех сторон рамки можно увидеть.
/// 3. Угол показывает две стороны.Рамки обозначаются заглавными латинскими буквами.Разные рамки обозначаются разными буквами.
/// </summary>
void task3();

int main()
{
    //task1();
    //task2();
    task3();
}

void task1()
{
    int N, // Количество тем 
        M; // Количество зависимостей
    cin >> N >> M;

    vector<vector<int>> graph(N); // Граф, описывающий темы и их зависимости друг от друга, представленный списком смежностей
    vector<int> dependentThemesAmm(N); // Количества тем, от которых темы зависят 
    string result; // Результат топологической сортировки
    priority_queue<int, vector<int>, greater <int>> que; // Очередь с приоритетами, с помощью которой будет формироваться ответ

    // Вносим данные
    for (int i = 0; i < M; i++)
    {
        int dependentTheme, // Зависимая тема
            themeOnWрichdepens; // Тема от которой она зависит
        cin >> themeOnWрichdepens >> dependentTheme;
        dependentThemesAmm[dependentTheme - 1]++;
        graph[themeOnWрichdepens - 1].push_back(dependentTheme - 1);
    }

    // Записываем в очередь только темы, которые не зависят ни от каких других
    for (int i = 0; i < N; i++)
    {
        if (dependentThemesAmm[i] == 0)
            que.push(i);
    }

    // Формируем ответ, проверяя зависимости тем
    while (!que.empty())
    {
        int out = que.top();
        result += to_string(out + 1) + ' ';
        que.pop();
        dependentThemesAmm[out] = -1;
        for (int i = 0; i < graph[out].size(); i++)
        {
            int s = graph[out][i];
            dependentThemesAmm[s]--;
            if (dependentThemesAmm[s] == 0)
                que.push(s);
        }
    }

    // Проверяем, все ли зависимости правильно составлены
    for (int i = 0; i < N; i++)
    {
        if (dependentThemesAmm[i] != -1)
        {
            cout << "bad course";
            return;
        }
    }
    // Если все зависимости правильные, то выводим результат
    cout << result;
}

void task3()
{
    int height, // Высота поля
        width; // Ширина поля
    // Считываем все тесты
    while (cin >> height >> width)
    {
        vector<string> field(height); // Поле, на котором находятся рамки
        map<char, vector<int>> graph; // Словарь букв, из которых состоит рамка, и её границ рамки
        getline(cin, field[0]); // Нужно, чтобы правильно считать поле
        // Считываем поле
        for (int i = 0; i < height; i++)
            getline(cin, field[i]);
        // Проходим по полю и и заполняем словарь данными
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                char currSymbol = field[i][j];
                if (currSymbol != '.')
                {
                    if (graph[currSymbol].empty())
                        graph[currSymbol] = { i,j,i,j };
                    else
                    {
                        graph[currSymbol][1] = min(j, graph[currSymbol][1]);
                        graph[currSymbol][2] = max(i, graph[currSymbol][0]);
                        graph[currSymbol][3] = max(j, graph[currSymbol][3]);
                    }
                }
            }
        }
        string currAnswer; // Строка, в которой будет храниться ответ
        set<string> answers;
        output_in_alphabetical_order(field, graph, ' ', currAnswer, answers);
        for (auto& ans : answers)
        {
            cout << ans << endl;
        }
    }
    
#pragma region OldVersion
    while (cin >> height >> width)
    {
        vector<string> field(height); // Поле, на которое наложены рамки
        multimap <unsigned int, pair<char, set<char>>, greater<unsigned int>> graph;
        set<char> findedLetters;
        set<pair<int, char>> result; // Результат 

        // Заполняем поле
        for (int i = 0; i < height; i++)
            cin >> field[i];
        // 
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                char currLetter = field[i][j];
                if (currLetter != '.')
                {
                    if (findedLetters.find(currLetter) == findedLetters.end())
                    {
                        int iStart = i, jStart,
                            iFinish, jFinish,
                            mostLeftUp = j, mostRightUp = j,
                            mostLeftDown, mostRightDown;

                        for (int l = j + 1; l < width; l++)
                        {
                            if (field[i][l] == currLetter)
                                mostRightUp = l;
                        }

                        for (int k = height - 1; k >= 0; k--)
                        {
                            bool flag = false;
                            for (int l = width - 1; l >= 0; l--)
                            {
                                if (field[k][l] == currLetter)
                                {
                                    iFinish = k;
                                    mostRightDown = l;
                                    mostLeftDown = l;
                                    for (int o = l - 1; o >= 0; o--)
                                    {
                                        if (field[k][o] == currLetter)
                                            mostLeftDown = o;
                                    }
                                    flag = true;
                                    break;
                                }
                            }
                            if (flag)
                                break;
                        }
                        set<char> overlays = detect_overlay(field, currLetter, iStart, iFinish, min(mostLeftUp, mostLeftDown), max(mostRightUp, mostRightDown));
                        graph.insert({ overlays.size(), {currLetter, overlays } });
                        //result.insert({ detect_overlay(field,currLetter,iStart,iFinish,min(mostLeftUp,mostLeftDown),max(mostRightUp,mostRightDown)), currLetter });
                        findedLetters.insert(currLetter);
                    }
                }
            }
        }

        vector<string> results;
        priority_queue<int, vector<int>, greater <int>> que; // Очередь с приоритетами, с помощью которой будет формироваться ответ
    }
#pragma endregion
}

/// <summary>
/// Выводит все варианты расположения рамок в алфавитном порядке. Работает рекурсивно
/// </summary>
/// <param name="field">Копия поля, на котором находятся рамки</param>
/// <param name="graph">Копия словаря, в котором соержится информация о рамках</param>
/// <param name="currAnswer">Строка, в которую записывается ответ</param>
/// <param name="previousVertex">Предыдущая вершина, которую мы добавили в ответ</param>
void output_in_alphabetical_order(vector<string> field, map<char, vector<int>> graph, char previousVertex, string currAnswer, set<string> &answers)
{
    // Помечаем все вершины, которые мы добавили в ответ символом '*'
    if (graph.find(previousVertex) != graph.end())
    {
        for (int i = graph[previousVertex][0]; i <= graph[previousVertex][2]; i++)
            field[i][graph[previousVertex][1]] = '*';

        for (int i = graph[previousVertex][0]; i <= graph[previousVertex][2]; i++)
            field[i][graph[previousVertex][3]] = '*';

        for (int i = graph[previousVertex][1]; i <= graph[previousVertex][3]; i++)
            field[graph[previousVertex][0]][i] = '*';

        for (int i = graph[previousVertex][1]; i <= graph[previousVertex][3]; i++)
            field[graph[previousVertex][2]][i] = '*';
    }
    // Удаляем добавленную вершину из рассматриваемых
    graph.erase(previousVertex);
    // Если мы удалили все вершины, то ответ готов, печатаем его
    if (graph.empty())
    {
        answers.insert(currAnswer);
        return;
    }
    // Проходим по рамкам в алфавитном порядке и смотрим на какие нет  наложений
    for (auto& vertex : graph)
    {
        bool flag = false;
        for (int i = vertex.second[0]; i <= vertex.second[2]; i++)
        {
            if (field[i][vertex.second[1]] != vertex.first && field[i][vertex.second[1]] != '*')
            {
                flag = true;
                break;
            }
        }
        if (!flag)
        {
            for (int i = vertex.second[0]; i <= vertex.second[2]; i++)
            {
                if (field[i][vertex.second[3]] != vertex.first && field[i][vertex.second[3]] != '*')
                {
                    flag = true;
                    break;
                }
            }
        }
        if (!flag)
        {
            for (int i = vertex.second[1]; i <= vertex.second[3]; i++)
            {
                if (field[vertex.second[0]][i] != vertex.first && field[vertex.second[0]][i] != '*')
                {
                    flag = true;
                    break;
                }
            }
        }
        if (!flag)
        {
            for (int i = vertex.second[1]; i <= vertex.second[3]; i++)
            {
                if (field[vertex.second[2]][i] != vertex.first && field[vertex.second[2]][i] != '*')
                {
                    flag = true;
                    break;
                }
            }
        }
        // Если наложений на данную рамку нет, то записываем букву в ответ и идем по оставшимся
        if (!flag)
        {
            currAnswer = vertex.first + currAnswer;
            output_in_alphabetical_order(field, graph, vertex.first, currAnswer, answers);
            currAnswer.erase(currAnswer.begin());
        }
    }
}

/// <summary>
/// Определяет рамки, наложенные на данную
/// </summary>
/// <param name="field"> Поле, на котором мы определяем количество наложений на данную рамку</param>
/// <param name="frameLetter"> Буква, которая составяет данную рамку</param>
/// <param name="upperBorderPos"> Верхняя граница рамки</param>
/// <param name="downBorderPos"> Нижняя граница рамки</param>
/// <param name="leftBorderPos"> Левая граница рамки</param>
/// <param name="rightBorderPos"> Правая граница рамки</param>
/// <returns> Множество букв, рамки из которых наложены на данную</returns>
set<char> detect_overlay(vector<string>& field, char frameLetter, int upperBorderPos, int downBorderPos, int leftBorderPos, int rightBorderPos)
{
    int count = 0;
    set<char> findedLetters;


    for (int i = upperBorderPos; i < downBorderPos; i++)
    {
        if (field[i][leftBorderPos] != '.')
        {
            if (!(field[i][leftBorderPos] == frameLetter))
            {
                if (findedLetters.find(field[i][leftBorderPos]) == findedLetters.end())
                {
                    count++;
                    findedLetters.insert(field[i][leftBorderPos]);
                }

            }
        }
    }

    for (int i = upperBorderPos; i < downBorderPos; i++)
    {
        if (field[i][rightBorderPos] != '.')
        {
            if (!(field[i][rightBorderPos] == frameLetter))
            {
                if (findedLetters.find(field[i][rightBorderPos]) == findedLetters.end())
                {
                    count++;
                    findedLetters.insert(field[i][rightBorderPos]);
                }

            }
        }
    }

    for (int i = leftBorderPos; i < rightBorderPos; i++)
    {
        if (field[upperBorderPos][i] != '.')
        {
            if (!(field[upperBorderPos][i] == frameLetter))
            {
                if (findedLetters.find(field[upperBorderPos][i]) == findedLetters.end())
                {
                    count++;
                    findedLetters.insert(field[upperBorderPos][i]);
                }

            }
        }
    }

    for (int i = leftBorderPos; i < rightBorderPos; i++)
    {
        if (field[downBorderPos][i] != '.')
        {
            if (!(field[downBorderPos][i] == frameLetter))
            {
                if (findedLetters.find(field[downBorderPos][i]) == findedLetters.end())
                {
                    count++;
                    findedLetters.insert(field[downBorderPos][i]);
                }

            }
        }
    }

    return findedLetters;
}