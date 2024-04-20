#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>

using namespace std;

void findBridges(int u, int& time, map<int, set<int>>& graph, vector<bool>& visited, vector<int>& low, vector<int>& discoveryTime, vector<int>& parent, vector<pair<int, int>>& bridges, set<int>& loops) 
{
    visited[u] = true;
    discoveryTime[u] = low[u] = ++time;

    int childCount = 0;  // Счетчик потомков

    for (int v : graph[u]) {
        if (!visited[v]) {
            parent[v] = u;
            findBridges(v, time, graph, visited, low, discoveryTime, parent, bridges, loops);
            low[u] = min(low[u], low[v]);

            if (low[v] > discoveryTime[u]) {
                bridges.push_back({ u, v });
            }

            // Увеличиваем счетчик потомков в случае разных поддеревьев
            if (low[v] >= discoveryTime[u] && parent[u] != -1) {
                childCount++;
            }
        }
        else if (v != parent[u] && discoveryTime[v] < discoveryTime[u]) {
            low[u] = min(low[u], discoveryTime[v]);
        }
    }

    //// Проверяем наличие петель
    //if (parent[u] == -1 && childCount > 1) {
    //    loops.insert(u);
    //}
}

set<pair<int, int>> findBridgesInGraph(int n, int m, const map<pair<int, int>, int>& edges) 
{
    map<int, set<int>> graph;
    vector<bool> visited(n + 1, false);
    vector<int> low(n + 1, 0);
    vector<int> discoveryTime(n + 1, 0);
    vector<int> parent(n + 1, -1);
    vector<pair<int, int>> bridges;
    set<int> loops;

    for (const auto& edge : edges) 
    {
        int u = edge.first.first;
        int v = edge.first.second;
        graph[u].insert(v);
        graph[v].insert(u);
    }

    int time = 0;
    for (int u = 1; u <= n; ++u) 
    {
        if (!visited[u]) 
            findBridges(u, time, graph, visited, low, discoveryTime, parent, bridges, loops);
    }

    // Удаляем ребра, инцидентные петлям
    set<pair<int, int>> filteredBridges;
    for (const auto& bridge : bridges) 
    {
        int u = bridge.first;
        int v = bridge.second;
        if (filteredBridges.find({ bridge.second,bridge.first }) == filteredBridges.end())//(loops.find(u) == loops.end() && loops.find(v) == loops.end())
        {
            filteredBridges.insert(bridge);
        }
        
    }

    return filteredBridges;
}

int main() 
{
    int n, m;
    cin >> n >> m;

    map<pair<int, int>, int> edges;
    for (int i = 0; i < m; ++i) 
    {
        int u, v;
        cin >> u >> v;
        edges[{v, u}] = i + 1;
        edges[{u, v}] = i + 1;
    }

    set<pair<int, int>> resultEdges = findBridgesInGraph(n, m, edges);
    set<int> result;
    cout << resultEdges.size() << endl;
    for (auto bridge : resultEdges) 
        result.insert(edges[bridge]);

    for (auto& i : result)
        cout << i << " ";
}

////#include <iostream>
////#include <algorithm>
////#include <vector>
////#include <map>
////#include <set>
////
////using namespace std;
////
////void findBridges(int u, int& time, const vector<vector<int>>& graph, vector<bool>& visited, vector<int>& low, vector<int>& discoveryTime, vector<int>& parent, vector<pair<int, int>>& bridges, set<int>& loops) {
////    visited[u] = true;
////    discoveryTime[u] = low[u] = ++time;
////
////    int childCount = 0;  // Счетчик потомков
////
////    for (int v : graph[u]) {
////        if (!visited[v]) {
////            parent[v] = u;
////            findBridges(v, time, graph, visited, low, discoveryTime, parent, bridges, loops);
////            low[u] = min(low[u], low[v]);
////
////            if (low[v] > discoveryTime[u]) {
////                bridges.push_back({ u, v });
////            }
////
////            // Увеличиваем счетчик потомков в случае разных поддеревьев
////            if (low[v] >= discoveryTime[u] && parent[u] != -1) {
////                childCount++;
////            }
////        }
////        else if (v != parent[u] && discoveryTime[v] < discoveryTime[u]) {
////            low[u] = min(low[u], discoveryTime[v]);
////        }
////    }
////
////    // Проверяем наличие петель
////    if (parent[u] == -1 && childCount > 1) {
////        loops.insert(u);
////    }
////}
////
////vector<pair<int, int>> findBridgesInGraph(int n, int m, const map<pair<int, int>, int>& edges) {
////    vector<vector<int>> graph(n + 1);
////    vector<bool> visited(n + 1, false);
////    vector<int> low(n + 1, 0);
////    vector<int> discoveryTime(n + 1, 0);
////    vector<int> parent(n + 1, -1);
////    vector<pair<int, int>> bridges;
////    set<int> loops;
////
////    for (const auto& edge : edges) {
////        int u = edge.first.first;
////        int v = edge.first.second;
////        graph[u].push_back(v);
////        graph[v].push_back(u);
////    }
////
////    int time = 0;
////    for (int u = 1; u <= n; ++u) {
////        if (!visited[u]) {
////            findBridges(u, time, graph, visited, low, discoveryTime, parent, bridges, loops);
////        }
////    }
////
////    // Удаляем ребра, инцидентные петлям
////    vector<pair<int, int>> filteredBridges;
////    for (const auto& bridge : bridges) {
////        int u = bridge.first;
////        int v = bridge.second;
////        if (loops.find(u) == loops.end() && loops.find(v) == loops.end()) {
////            filteredBridges.push_back(bridge);
////        }
////    }
////
////    return filteredBridges;
////}
////
////int main() {
////    int n, m;
////    cin >> n >> m;
////
////    map<pair<int, int>, int> edges;
////    for (int i = 0; i < m; ++i) {
////        int u, v;
////        cin >> u >> v;
////        edges[{v, u}] = i + 1;
////        edges[{u, v}] = i + 1;
////    }
////
////    vector<pair<int, int>> resultEdges = findBridgesInGraph(n, m, edges);
////    set<int> result;
////    cout << resultEdges.size() << endl;
////    for (auto bridge : resultEdges) {
////        result.insert(edges[bridge]);
////    }
////    for (auto& i : result)
////    {
////        cout << i << " ";
////    }
////}
//
//#include <iostream>
//#include <vector>
//#include <stack>
//#include <set>
//#include <map>
//#include <string>
//#include <queue>
//#include <unordered_map>
//#include <unordered_set>
//
//using namespace std;
//
//enum class State
//{
//	NOT_VISITED,
//	VISITING,
//	VISITED
//};
//
//
//// Объявление вспомогательных функций
//
//bool seek(vector<short>* , short , short , short);
//
//void familar(vector<short>* , short* , short );
//
//void dfs(vector<int>* , int* , int , int );
//
//void dfs4(vector<string>& , int , int , vector<vector<bool>>&, int);
//
//int countInaccessibleAreas(vector<string>& , int );
//
//void dfs7_1(int, vector<bool>&, vector<vector<int>>&, vector<int>&);
//
//void dfs7_2(int, int, vector<int>&, vector<vector<int>>&);
//
//void findArticulationPoints(int, int&, const vector<vector<int>>&, vector<bool>&, vector<int>&, vector<int>&, vector<bool>&, int);
//
//vector<int> getArticulationPoints(const vector<vector<int>>&);
//
//bool has_cycle(const string&, unordered_map<string, vector<string>>&, unordered_map<string, State>&);
//
//// Объявление функций с задачами
//
///// <summary>
///// Племена обитают в непроходимом лесу, в котором есть полянки, на которых кто-нибудь живет — шаман или же обычный дикарь.
///// Некоторые полянки соединены между собой тропами, по которым можно свободно перемещаться.
///// Вам необходимо определить, смогут ли шаманы собраться вместе и предотвратить угрозу.
///// </summary>
//void task1();
//
///// <summary>
///// Определить минимальное возможное число людей 𝐾, такое, чтобы при любом выборе 𝐾 человек из 𝑁 имеющихся среди них гарантированно встретились хотя бы двое хоть как - то знакомых.
///// </summary>
//void task2();
//
//void task3();
//
//void task4();
//
//void task5();
//
//void task6();
//
///// <summary>
///// Вам задан ориентированный граф с 𝑁 вершинами и 𝑀 ребрами. Возможно, в граф закрались петли и кратные ребра. 
///// Определите компоненты сильной связности заданного графа.
///// </summary>
//void task7();
//
//void task8();
//
//void task9();
//
//int main()
//{
//	//task1();
//	//task2();
//	//task3();
//	//task4();
//	//task5();
//	//task6();
//	//task7();
//	//task8();
//	task9();
//}
//
//void task1()
//{
//	short N, // Количество полянок
//		M; // Количество тропинок между полянками
//	cin >> N >> M;
//	vector<short>* field = new vector<short>[N]; // Показывает связи между полянками 
//	// Заполняем информацию о связях полянок
//	for (short i = 0; i < M; i++) 
//	{
//		short to, from;
//		cin >> from >> to;
//		field[to - 1].push_back(from - 1);
//		field[from - 1].push_back(to - 1);
//	}
//
//	short curS, // Поляна с текущим шаманом
//		toS, // Поляна, куда нужно попасть текущему шаману
//		S; // Количество шаманов
//	cin >> S;
//	cin >> curS;
//	for (short j = 0; j < S - 1; j++) 
//	{
//		cin >> toS;
//		if (!seek(field, curS - 1, toS - 1, N)) 
//		{
//			cout << "NO" << endl;
//			return;
//		}
//	}
//	cout << "YES" << endl;
//}
//
//void task2()
//{
//	short n,  // Количество людей
//		k{1}; // Минимальное число людей, в котором есть хотя бы 1 знакомый
//	cin >> n;
//	vector<short>* graph = new vector<short>[n]; // Граф, показывающий знакомства людей друг с другом
//	short to, from;
//	while (cin>> from >> to) 
//	{
//		graph[to - 1].push_back(from - 1);
//		graph[from - 1].push_back(to - 1);
//	}
//	short* transitiveFamiliarity = new short[n] {0}; // Массив, показывающий какие люди транзитивно знакомы с остальными
//	// Отмечаем, какие люди знакомы друг с другом. Если встретили человека, которого не отметили, то увеличиваем счётчик
//	for (int i = 0; i < n; i++) 
//	{
//		if (transitiveFamiliarity[i] == 0) 
//		{
//			familar(graph, transitiveFamiliarity, i);
//			k++;
//		}
//	}
//	// Вывод
//	cout << k;
//}
//
//void task3()
//{
//	int n, m, t = 0, l = 1;
//	cin >> n >> m;
//	vector<int>* graph = new vector<int>[n];
//	for (int i = 0; i < m; i++) 
//	{
//		int to, from;
//		cin >> from >> to;
//		graph[to - 1].push_back(from - 1);
//		graph[from - 1].push_back(to - 1);
//	}
//	int* r = new int[n] {0};
//	for (int i = 0; i < n; i++) 
//	{
//		if (r[i] == 0)
//		{
//			dfs(graph, r, i, l++);
//			t++;
//		}
//		
//	}
//	cout << t << endl;
//	for (int i = 0; i < n; i++) 
//		cout << r[i] << " ";
//}
//
//void task4()
//{
//	short n;
//	cin >> n;
//	vector<string> field(n);
//	getline(cin, field[0]);
//	for (int i = 0; i < n; i++)
//		getline(cin, field[i]);
//
//	int inaccessibleAreas = countInaccessibleAreas(field, n);
//	cout << inaccessibleAreas << endl;
//}
//
//void task5()
//{
//	int n, // Количество чисел
//		m; // Количество неравенств
//	cin >> n >> m;
//	vector<vector<int>> graph(n);
//	vector<int> in_degree(n, 0); // Хранит количество чисел, меньших данного 
//	vector<int> result(n);
//	// Считываем неравенства
//	for (int i = 0; i < m; i++) 
//	{
//		int u, v;
//		cin >> u >> v;
//		u--, v--;
//		graph[u].push_back(v);
//		in_degree[v]++;
//	}
//	
//	priority_queue<int, vector<int>, greater<int>> q; // Очередь с приоритетами для обхода графа в глубину
//	// Находим самое маленькое число
//	for (int i = 0; i < n; i++) 
//	{
//		if (in_degree[i] == 0) 
//			q.push(i);
//	}
//
//	int cnt = 0; // Количество чисел в ответе
//	// Проходим по графу и формируем ответ
//	while (!q.empty()) 
//	{
//		int u = q.top();
//		q.pop();
//		result[u] = ++cnt;
//		for (int v : graph[u]) 
//		{
//			in_degree[v]--;
//			if (in_degree[v] == 0) 
//				q.push(v);
//		}
//	}
//	// Если количество чисел в ответе не совпадает с общим количеством чисел, то система не решается
//	if (cnt != n) 
//		cout << "NO\n";
//	// Если всё в порядке, то выводим результат обхода в глубину
//	else 
//	{
//		cout << "YES\n";
//		for (int i = 0; i < n; i++) 
//			cout << result[i] << ' ';
//	}
//	
//}
//
//void task6()
//{
//	int n; // Количество понятий
//	cin >> n;
//
//	unordered_map<string, vector<string>> graph;
//	unordered_set<string> defined_concepts; // Множество определенных понятий
//	bool multiple_definition = false;
//	// Вносим информацию о понятиях
//	for (int i = 0; i < n; i++) 
//	{
//		string concept; // Название понятия
//		int num_dependencies; // Количество зависимостей у данного понятия
//		cin >> concept >> num_dependencies;
//		// Если происходит повтор определений понятий, то выходим из цикла
//		if (defined_concepts.count(concept) > 0)
//		{
//			multiple_definition = true;
//			break;
//		}
//		
//		defined_concepts.insert(concept);
//		for (int j = 0; j < num_dependencies; j++) 
//		{
//			string dependency;
//			cin >> dependency;
//			graph[concept].push_back(dependency);
//		}
//	}
//	// Вывод сообщения о множественном определении
//	if (multiple_definition) 
//		cout << "multiple definition" << endl;
//	// Проверяем понятия на циклические зависимости
//	else 
//	{
//		unordered_map<string, State> visited;
//		bool loop_detected = false;
//		for (const auto& entry : graph) 
//		{
//			if (visited[entry.first] == State::NOT_VISITED && has_cycle(entry.first, graph, visited)) 
//			{
//				loop_detected = true;
//				break;
//			}
//		}
//
//		if (loop_detected) 
//			cout << "loop detected" << endl;
//		
//		else 
//			cout << "correct" << endl;
//		
//	}
//	
//}
//
//void task7()
//{
//	int n, // Количество вершин
//		m; // Количество ребер
//	cin >> n >> m;
//	vector<vector<int>> graph(n), // Изначальный ориентированный граф
//		invertedGraph(n); // Инвертированный граф
//	vector<bool> visited(n, false); // Вспомагательный массив, показывающий, какие вершины посещены, а какие нет
//	vector<int> order, // Порядок вершин, обратный тому, в котором мы будем перебирать их при вычислении компонент сильной связи
//		components(n, -1);
//	// Настраиваем связи
//	for (int i = 0; i < m; i++)
//	{
//		int edgeBegin,
//			edgeEnd;
//		cin >> edgeBegin >> edgeEnd;
//		edgeBegin--;
//		edgeEnd--;
//		graph[edgeBegin].push_back(edgeEnd);
//		invertedGraph[edgeEnd].push_back(edgeBegin);
//	}
//	// Выстраиваем порядок вершин для выяснения компонент сильной связи
//	for (int i = 0; i < n; i++)
//	{
//		if (!visited[i])
//			dfs7_1(i, visited, graph, order);
//	}
//	// Выясняем количество КСС и вершины, которые им принадлежат
//	int componentsAmmount = 0; // Количество компонент сильной связи
//	for (auto vertex = order.rbegin(); vertex != order.rend(); ++vertex)
//	{
//		if (components[*vertex] == -1)
//		{
//			dfs7_2(*vertex, componentsAmmount, components, invertedGraph);
//			componentsAmmount++;
//		}
//	}
//	// Вывод
//	cout << componentsAmmount << endl;
//	for (int comp : components)
//		cout << comp + 1 << " ";
//}
//
//void task8()
//{
//	int n, // Количество вершин
//		m; // Количество ребер
//	cin >> n >> m;
//	map<int, set<int>> graph; 
//	map<pair<int,int>,int> edges; // Множество ребер
//	for (int i = 0; i < m; i++)
//	{
//		int from,
//			to;
//		cin >> from >> to;
//		graph[from].insert(to);
//		graph[to].insert(from);
//		edges.insert({ {from,to},i + 1 });
//		edges.insert({ {to,from},i + 1 });
//	}
//
//}
//
//void task9()
//{
//	int n, // Количество вершин
//		m; // Количество ребер
//	cin >> n >> m;
//	vector<vector<int>> graph(n + 1);
//	for (int i = 0; i < m; i++)
//	{
//		int from,
//			to;
//		cin >> from >> to;
//		graph[from].push_back(to);
//		graph[to].push_back(from);
//	}
//	vector<int> articurationPoins = getArticulationPoints(graph);
//	cout << articurationPoins.size() << endl;
//	for (auto& vertex : articurationPoins)
//	{
//		cout << vertex << " ";
//	}
//}
//
///// <summary>
///// 
///// </summary>
///// <param name="field"> Граф, содержащий информацию о полянах и их связях</param>
///// <param name="beg"> Поляна, из которой нужно попасть в другую</param>
///// <param name="end"> Поляна, в которую нужно попасть</param>
///// <param name="n"> Количество полянок</param>
///// <returns> Можно ли из одной полянки попасть в другую</returns>
//bool seek(vector<short>* field, short beg, short end, short n)
//{
//	stack<short> stk;
//	short* go = new short[n] {0};
//	stk.push(beg);
//	while (!stk.empty()) {
//		short cur = stk.top();
//		stk.pop();
//		go[cur] = 1;
//		for (short i = 0; i < field[cur].size(); i++) {
//			short temp = field[cur][i];
//			if (temp == end) return true;
//			if (go[temp] == 0) stk.push(temp);
//		}
//	}
//	return false;
//}
//
//void familar(vector<short>* graph, short* transitiveFamiliarity, short beg) 
//{
//	stack<short> stk;
//	stk.push(beg);
//	while (!stk.empty()) 
//	{
//		short cur = stk.top();
//		stk.pop();
//		transitiveFamiliarity[cur] = 1;
//		for (short i = 0; i < graph[cur].size(); i++) 
//		{
//			short k = graph[cur][i];
//			if (transitiveFamiliarity[k] == 0) stk.push(k);
//		}
//	}
//}
//
//void dfs(vector<int>* graph, int* r, int beg, int l) 
//{
//	stack<int> stk;
//	stk.push(beg);
//	while (!stk.empty()) 
//	{
//		int cur = stk.top();
//		stk.pop();
//		r[cur] = l;
//		for (int i = 0; i < graph[cur].size(); i++) 
//		{
//			int temp = graph[cur][i];
//			if (r[temp] == 0) stk.push(temp);
//		}
//	}
//}
//
//void dfs4(vector<string>& labyrinth, int x, int y, vector<vector<bool>>& visited, int n) 
//{
//	if (x < 0 || x >= n || y < 0 || y >= n) return;
//	if (labyrinth[x][y] == '*' || visited[x][y]) return;
//
//	visited[x][y] = true;
//	// Рекурсивный вызов для соседних клеток (влево, вправо, вверх, вниз)
//	dfs4(labyrinth, x - 1, y, visited, n);  // Влево
//	dfs4(labyrinth, x + 1, y, visited, n);  // Вправо
//	dfs4(labyrinth, x, y - 1, visited, n);  // Вверх
//	dfs4(labyrinth, x, y + 1, visited, n);  // Вниз
//}
//
//int countInaccessibleAreas(vector<string>& labyrinth, int n) 
//{
//	// Создаем массив посещенных клеток и заполняем его false
//	vector<vector<bool>> visited(n, vector<bool>(n, false));
//
//	int Count = 0;
//	// Ищем вход в лабиринт
//	for (int j = 0; j < n; ++j) 
//	{
//		if (labyrinth[0][j] == ' ') 
//		{
//			dfs4(labyrinth, 0, j, visited, n);
//			break;
//		}
//	}
//
//	// Считаем количество недоступных областей
//	for (int i = 0; i < n; ++i) 
//	{
//		for (int j = 0; j < n; ++j) 
//		{
//			if (labyrinth[i][j] == ' ' && !visited[i][j]) 
//			{
//				++Count;
//				dfs4(labyrinth, i, j, visited, n);
//			}
//		}
//	}
//	return Count;
//}
//
///// <summary>
///// С помощью алгоритма обхода графа в глубину определяет, есть ли в нем циклическая зависимость данного понятия
///// </summary>
///// <param name="concept"> Понятие, повторение которого нужно найти</param>
///// <param name="graph"> Граф, в котором нужно найти повтор понятия </param>
///// <param name="visited"> Информация о состоянии вершин графа </param>
///// <returns> Есть ли повтор понятия в данном графе </returns>
//bool has_cycle(const string& concept, unordered_map<string, vector<string>>& graph, unordered_map<string, State>& visited)
//{
//	visited[concept] = State::VISITING;
//	for (const auto& child : graph[concept])
//	{
//		if (visited[child] == State::VISITING || (visited[child] == State::NOT_VISITED && has_cycle(child, graph, visited))) 
//			return true;
//		
//	}
//	visited[concept] = State::VISITED;
//	return false;
//}
//
//void dfs7_1(int v, vector<bool>& visited, vector<vector<int>>& graph, vector<int>& order) 
//{
//	visited[v] = true;
//	for (int u : graph[v]) 
//	{
//		if (!visited[u]) 
//			dfs7_1(u, visited, graph, order);
//	}
//	order.push_back(v);
//}
//
//void dfs7_2(int vertex, int comp, vector<int>& components, vector<vector<int>>& invertedGraph)
//{
//	components[vertex] = comp;
//	for (int u : invertedGraph[vertex]) 
//	{
//		if (components[u] == -1) 
//			dfs7_2(u, comp, components, invertedGraph);
//	}
//}
//
//void findArticulationPoints(int u, int& time, const vector<vector<int>>& graph, vector<bool>& visited, vector<int>& discoveryTime, vector<int>& lowTime, vector<bool>& isArticulationPoint, int parent = -1) 
//{
//	visited[u] = true;
//	discoveryTime[u] = lowTime[u] = ++time;
//	int childCount = 0;
//
//	for (int v : graph[u]) 
//	{
//		if (!visited[v]) 
//		{
//			++childCount;
//			findArticulationPoints(v, time, graph, visited, discoveryTime, lowTime, isArticulationPoint, u);
//			lowTime[u] = min(lowTime[u], lowTime[v]);
//
//			if (parent != -1 && lowTime[v] >= discoveryTime[u])
//				isArticulationPoint[u] = true;
//		}
//		else if (v != parent) 
//			lowTime[u] = min(lowTime[u], discoveryTime[v]);
//		
//	}
//
//	if (parent == -1 && childCount > 1)
//		isArticulationPoint[u] = true;
//}
//
//vector<int> getArticulationPoints(const vector<vector<int>>& graph) 
//{
//	int n = graph.size();
//	vector<bool> visited(n, false);
//	vector<int> discoveryTime(n, 0);
//	vector<int> lowTime(n, 0);
//	vector<bool> isArticulationPoint(n, false);
//	int time = 0;
//
//	for (int u = 0; u < n; ++u) 
//	{
//		if (!visited[u]) 
//			findArticulationPoints(u, time, graph, visited, discoveryTime, lowTime, isArticulationPoint);
//	}
//
//	vector<int> articulationPoints;
//	for (int u = 0; u < n; ++u) 
//	{
//		if (isArticulationPoint[u])
//			articulationPoints.push_back(u);
//	}
//
//	return articulationPoints;
//}
//
