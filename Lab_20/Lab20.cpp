//#include <iostream>
//#include <vector>
//#include <cmath>
//#include <algorithm>
//#include <set>
//
//using namespace std;
//
///// <summary>
///// Содержит информацию о городах
///// </summary>
//struct City 
//{
//    int x, // Координата x
//        y, // Координата y
//        id; // Номер города
//};
//
///// <summary>
///// Содежрит информацию о дорогах меду городами
///// </summary>
//struct Edge 
//{
//    int u, v; // Какие города соиденяет
//    double weight; // Длина дороги
//    // Перегрузка оператора < для проведения сортировки
//    bool operator<(Edge& other)
//    {
//        return this->weight < other.weight;
//    }
//};
//
///// <summary>
///// </summary>
///// <param name="a"></param>
///// <param name="b"></param>
///// <returns> Расстояние между городами a и b</returns>
//double distance(const City& a, const City& b) 
//{
//    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
//}
//
///// <summary>
///// Рекурсивно ищет наиболее далекий город, из которого можно приехать в данный
///// </summary>
///// <param name="parent"> Массив наиболее далеких городов </param>
///// <param name="x"> Номер города, для которого мы ищем другой город, из которого можно приехать </param>
///// <returns> Наиболее далекий город, из которого можно приехать в данный</returns>
//int find(vector<int>& parent, int x) 
//{
//    if (parent[x] != x) 
//        parent[x] = find(parent, parent[x]);
//    
//    return parent[x];
//}
//
///// <summary>
///// Устанавливает общий город, из которого можно попасть в город под номерами x и y
///// </summary>
///// <param name="parent"> Массив наиболее далеких городов </param>
///// <param name="x"></param>
///// <param name="y"></param>
//void setGeneralPrent(vector<int>& parent, int x, int y) 
//{
//    int rootX = find(parent, x);
//    int rootY = find(parent, y);
//    parent[rootY] = rootX;
//}
//
//int main() 
//{
//    int n; // Количество городов
//    cin >> n;
//
//    vector<City> cities(n); // Массив городов
//    vector<int> parent(n); // Показывает наиболее далекий город, из которого можно приехать в данный
//    // Заполняем информацию о городах и инициализируем вектор parent
//    for (int i = 0; i < n; ++i) 
//    {
//        cin >> cities[i].x >> cities[i].y;
//        cities[i].id = i;
//        parent[i] = i;
//    }
//
//    int m; // Изначальное количество дорог между городами
//    cin >> m;
//    for (int i = 0; i < m; ++i) 
//    {
//        int u, v;
//        cin >> u >> v;
//        setGeneralPrent(parent, u - 1, v - 1);
//    }
//
//    vector<Edge> edges; // Массив, содержащий информацию о всех возможных дорогах между городами
//    for (int i = 0; i < n; ++i) 
//    {
//        for (int j = i + 1; j < n; ++j) 
//        {
//            edges.push_back({ cities[i].id, cities[j].id, distance(cities[i], cities[j]) });
//        }
//    }
//    // Сортируем дороги для работы сначала с городами, у которых расстояние жду друг другом наименьшее
//    sort(edges.begin(), edges.end());
//
//    vector<Edge> result; // Массив, в котором будет храниться информация о минимальном наборе необходимых новых дорог
//    // Смотрим у всех ли городов есть общий город, из которого можно приехать в остальные
//    for (const auto& edge : edges) 
//    {
//        // Если общего города из которого можно приехать в оба нет, то добавляем новую дорогу между ними и выставляем новый общий город, из которого можно приехать в эти 
//        if (find(parent, edge.u) != find(parent, edge.v)) 
//        {
//            result.push_back(edge);
//            setGeneralPrent(parent, edge.u, edge.v);
//        }
//    }
//    // Вывод
//    for (const auto& edge : result) 
//        cout << edge.u + 1 << " " << edge.v + 1 << endl;
//
//    return 0;
//}

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <queue>

using namespace std;

// Объявление вспомогательных функций

void getMinWay(map<int, set<int>>&, const int&, const int&, vector<int>&, set<int>&);

// Объявление функций с задачами

/// <summary>
/// Дан ориентированный граф 𝐺 без весов. В графе есть 𝑁 вершин, пронумерованных числами от 1 до 𝑁, и 𝑀 дуг между некоторыми парами вершин.
/// Требуется найти кратчайший путь от вершины номер 1 до всех остальных вершин.
/// </summary>
void task1();
/// <summary>
/// Для заданного лабиринта найти кратчайший путь от входа до выхода.
/// В первой строке входного файла находятся целые числа 𝑀 и 𝑁 — высота и ширина лабиринта (1 ⩽ 𝑀, 𝑁 ⩽ 100).
/// Каждая из следующих 𝑀 строк содержит 𝑁 символов, при этом символ ‘.’ обозначает пустую клетку, символ ‘X’ — блок, символ ‘S’ — начальную клетку, символ ‘F’ — конечную клетку
/// Выведите в выходной файл минимальное число шагов, за которое можно добраться от начальной клетки до конечной, 
/// каждый раз переходя на соседнюю по стороне клетку и не ступая на блоки, либо число −1, если это невозможно.
/// </summary>
void task2();

void task3();
/// <summary>
/// Рассмотрим лабиринт, состоящий из комнат. Между любыми двумя комнатами изначально может быть коридор (но его может и не быть). 
/// Необходимо по коридорам как можно быстрее добраться из комнаты номер 𝑆 в комнату номер 𝐹.
/// Однако лабиринт не простой, в нём также существуют волшебные комнаты : попадая в такую комнату можно совершить(но можно и не совершать) немного магии : 
/// все коридоры, которые существовали до этого, исчезают, однако если между двумя комнатами раньше коридора не существовало, то он появляется.
/// В выходной файл необходимо вывести одно целое число — минимальное количество коридоров, которое придётся преодолеть, чтобы добраться из комнаты номер 𝑆 в комнату номер 𝐹. 
/// Если из команты 𝑆 невозможно попасть в комнату 𝐹, то нужно вывести слово IMPOSSIBLE.
/// </summary>
void task4();


int main()
{
    //task1();
    //task2();
    //task3();
    task4();
}

void task1()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n + 1);
    for (int i = 0; i < m; i++) 
    {
        int from, to;
        cin >> from >> to;
        graph[from].push_back(to);
    }

    vector<int> distances(n + 1, -1); // Расстояния от 1 вершины до остальных
    distances[1] = 0;

    queue<int> q; // Очередь для обхода в ширину
    q.push(1);
    // Проходим по графу алгоритмом обхода в ширину и считаем расстояния до вершин
    while (!q.empty()) 
    {
        int v = q.front();
        q.pop();

        for (int u : graph[v]) 
        {
            if (distances[u] == -1) 
            {
                distances[u] = distances[v] + 1;
                q.push(u);
            }
        }
    }
    // Вывод
    for (int i = 1; i <= n; i++) 
        cout << distances[i] << endl;
}

void task2()
{
    int m, 
        n;
    cin >> m >> n;
    vector<string> field(m, string(n, ' ')); // Поле, на котором расположен лабиринт

    pair<int, int> start, // Координаты начала лабиринта
                   finish; // Координаты конца лабиринта
    // Заполняем поле
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> field[i][j];
            if (field[i][j] == 'S')
                start = { i,j };
            else if(field[i][j] == 'F')
                finish = { i,j };
        }
    }

    vector<vector<int>> distances(m, vector<int>(n, -1)); // Расстояния от финиша до данной клетки
    distances[finish.first][finish.second] = 0;
    
    queue<pair<int, int>> q;
    q.push(finish);
    // Обходим лабиринт в ширину с финиша до старта и считаем минимальные расстояния до каждой клетки
    while (!q.empty())
    {
        pair<int, int> v = q.front();
        q.pop();

        int dx[] = { 0, 1, 0, -1 }; 
        int dy[] = { 1, 0, -1, 0 };

        for (int i = 0; i < 4; i++)
        {
            if (v.first + dy[i] >= 0 && v.first + dy[i] < m && v.second + dx[i] >= 0 && v.second + dx[i] < n)
            {
                if (field[v.first + dy[i]][v.second + dx[i]] != 'X' && distances[v.first + dy[i]][v.second + dx[i]] == -1)
                {
                    distances[v.first + dy[i]][v.second + dx[i]] = distances[v.first][v.second] + 1;
                    q.push({ v.first + dy[i] ,v.second + dx[i] });
                }
            }
            
        }
    }
    // Вывод
    cout << distances[start.first][start.second];
}

void task3()
{

}

void task4()
{
    int n, // Количество комнат
        m, // Количество коридоров
        s, // Стартовая комната 
        f, // Конечная комната
        w; // Количество волшебых комнат
    cin >> n >> m >> s >> f >> w;
   
    set<int> magicRooms; // Множество магических комнат
    for (int i = 0; i < w; i++)
    {
        int roomNumber;
        cin >> roomNumber;
        magicRooms.insert(roomNumber);
    }

    map<int, set<int>> graph; // Граф, показывающий связи между комнатами
    for (int i = 0; i < m; i++)
    {
        int from,
            to;
        cin >> from >> to;
        graph[from].insert(to);
        graph[to].insert(from);
    }

    vector<int> distances(n + 1, _I32_MAX - 1); // Расстояния от стартовой комнаты
    distances[s] = 0;

    getMinWay(graph, s, f, distances, magicRooms);

    // Если смогли добраться до конечной комнаты, то объявляем минимальное расстояние
    if (distances[f] < _I32_MAX - 1)
        cout << distances[f];
    // Если добраться до конечной комнаты невозможно, то пишем об этом
    else
        cout << "IMPOSSIBLE"; 
}

/// <summary>
/// Считает минимальные расстояния от стартовой вершины до остальных с помощью алгоритма обхода в ширину, с учётом магических комнат
/// </summary>
/// <param name="graph"> Граф, в котором нужно найти расстояния </param>
/// <param name="start"> Стартовая вершина </param>
/// <param name="finish"> Конечная вершина </param>
/// <param name="distances"> Массив, в который записываются расстояния</param>
/// <param name="magicRooms"> Множество вершин, которые являются волшебными </param>
void getMinWay(map<int, set<int>>& graph, const int& start, const int& finish, vector<int>& distances, set<int>& magicRooms)
{   
    queue<int> q;
    q.push(start);
    while (!q.empty())
    {
        int currVertex = q.front();
        q.pop();

        for (auto& u : graph[currVertex])
        {
            if (distances[u] == _I32_MAX - 1)
            {
                distances[u] = distances[currVertex] + 1;
                q.push(u);
            }
        }
    }
    // Выясняем, можем ли мы срезать путь с помощью магии
    for (auto& i : magicRooms)
    {
        distances[finish] = min(distances[finish], distances[i] + 1);
    }
}


//#include <iostream>
//#include <vector>
//#include <queue>
//#include <unordered_set>
//#include <unordered_map>
//#include <limits>
//
//using namespace std;
//
//const int INF = numeric_limits<int>::max();
//
//void removeCorridors(vector<vector<int>>& graph, int u, int v) {
//    unordered_set<int> connectedRooms;
//    for (int neighbor : graph[u]) {
//        connectedRooms.insert(neighbor);
//    }
//
//    for (int neighbor : graph[v]) {
//        connectedRooms.insert(neighbor);
//    }
//
//    for (int room1 : connectedRooms) {
//        for (int room2 : connectedRooms) {
//            if (room1 != room2) {
//                graph[room1].push_back(room2);
//            }
//        }
//    }
//
//    graph[u].clear();
//    graph[v].clear();
//}
//
//int findShortestPath(int n, int m, int start, int end, const unordered_set<int>& magicRooms, const vector<pair<int, int>>& corridors) {
//    vector<vector<int>> graph(n + 1);
//    for (const auto& corridor : corridors) {
//        int u = corridor.first;
//        int v = corridor.second;
//        graph[u].push_back(v);
//        graph[v].push_back(u);
//    }
//
//    queue<int> q;
//    q.push(start);
//
//    unordered_map<int, int> previousRoom;
//    unordered_map<int, int> previousCorridor;
//    previousRoom[start] = -1;
//    int corridorCount = 0;
//
//    while (!q.empty()) {
//        int currentRoom = q.front();
//        q.pop();
//
//        if (currentRoom == end) {
//            break;
//        }
//
//        if (magicRooms.find(currentRoom) != magicRooms.end()) {
//            for (int neighbor : graph[currentRoom]) {
//                if (magicRooms.find(neighbor) == magicRooms.end()) {
//                    removeCorridors(graph, currentRoom, neighbor);
//                }
//            }
//        }
//
//        for (int neighbor : graph[currentRoom]) {
//            if (previousRoom.find(neighbor) == previousRoom.end()) {
//                q.push(neighbor);
//                previousRoom[neighbor] = currentRoom;
//                previousCorridor[neighbor] = corridorCount;
//                corridorCount++;
//            }
//        }
//    }
//
//    if (previousRoom.find(end) == previousRoom.end()) {
//        cout << "IMPOSSIBLE" << endl;
//        return 0;
//    }
//
//    vector<int> path;
//    int room = end;
//    while (room != -1) {
//        path.push_back(previousCorridor[room]);
//        room = previousRoom[room];
//    }
//
//    cout << path.size() - 1 << endl;
//    return 0;
//}
//
//int main() {
//    int n, m;
//    cin >> n >> m;
//
//    int start, end;
//    cin >> start >> end;
//
//    int magicRoomCount;
//    cin >> magicRoomCount;
//
//    unordered_set<int> magicRooms;
//    for (int i = 0; i < magicRoomCount; ++i) {
//        int room;
//        cin >> room;
//        magicRooms.insert(room);
//    }
//
//    vector<pair<int, int>> corridors;
//    for (int i = 0; i < m; ++i) {
//        int u, v;
//        cin >> u >> v;
//        corridors.push_back({ u, v });
//    }
//
//    findShortestPath(n, m, start, end, magicRooms, corridors);
//
//    return 0;
//}
