#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <list>
#include <queue>
#include <vector>
#include <unordered_map>
#include <set>
#include <algorithm>

using namespace std;

/// <summary>
/// В базе данных роутера хранится информация о нескольких серверах, некоторые из них связаны между собой напрямую, другие — только опосредованно.
/// Получая электронное письмо от сервера с номером 𝑀(отправителя), предназначенное для сервера с номером 𝑁(получателя), 
/// роутер должен найти в своей базе данных самый короткий путь пересылки этого письма по сети.
/// Напишите программу, которая, зная информацию о всевозможных соединениях и их длительности, осуществляла бы поиск самого короткого пути пересылки и выдавала бы информацию о времени, 
/// за которое письмо преодолеет весь этот путь.
/// </summary>
void task1();


void task2();

/// <summary>
/// Дано бинарное отношение 𝑅 над множеством чисел 𝑋 = {1, 2, 3, . . . ,𝑁}. Требуется найти его рефлексивно - транзитивное замыкание.
/// </summary>
void task3();

/// <summary>
/// Для каждого из 𝐾 друзей Вовочки нужно вывести оптимальный путь до его дома, в порядке задания этих домов во входных данных.Каждый путь описывается в отдельной строке.
/// Сначала должен быть записан вес пути, который должен быть минимально возможным, за - тем количество вершин в пути, и наконец номера всех этих вершин в порядке прохождения по пути.
///Гарантируется, что до каждого друга можно добраться по дорожкам.
/// </summary>
void task4();


void task5();


void task6();

struct Match
{
	struct Point
	{
		int x, y;
	};

	Point p1, p2;
};

// Обьявление вспомогательных функций

void dijkstra(int, vector<int>&, vector<vector<pair<int, int>>>&);

void minWay(const int, const int, vector<pair<int, int>>&, vector<vector<pair<int, int>>>&, list<int>&);



bool intersect(const Match&, const Match&);

void dfs(int, const int&, const vector<vector<int>>&, vector<bool>&);

const uint32_t INF = 1e9 + 7;

int main()
{
	//task1();
	task2();
	//task3();
	//task4();
	//task5();
	//task6();
}

void task1()
{
	int n, s1, s2;
	cin >> n >> s1 >> s2;
	s1--; s2--;

	vector < vector < pair<int, int>>> edgeList(n);
	vector<int> distances(n, INF);

	int from, to, k;
	while (cin >> from >> to >> k)
	{
		from--; to--;
		edgeList[from].push_back({ to, k });
		edgeList[to].push_back({ from, k });
	}

	dijkstra(s1, distances, edgeList);

	if (distances[s2] == INF)
		cout << "no" << endl;
	else
		cout << distances[s2] << endl;
}


struct Edge
{
	uint16_t to;
		uint32_t cost;
};


bool operator>(const Edge& Left, const Edge& Right)
{
	return tie(Left.cost,Left.to) > tie(Right.cost, Right.to);
}

bool operator<(const Edge& Left, const Edge& Right)
{
	return tie(Left.cost, Left.to) < tie(Right.cost, Right.to);
}

void task2()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	uint16_t n, // Количество пунктов
		m, // Количество дорог
		p, // Количество запросов на кратчайший путь
		k; // Количество запросов на мин. время
	cin >> n >> m >> p >> k;

	unordered_map<uint16_t, vector<Edge>> graph;
	for (uint16_t i = 0; i < m; i++)
	{
		uint16_t from,
			to;
			uint32_t time;
		cin >> from >> to >> time;
		graph[from].push_back({ to,time });
		graph[to].push_back({ from,time });
	}

	unordered_map<uint16_t, pair<vector<unsigned int>*, vector<short>*>> cash; // Кэширует кратчайшие расстояния от вершины и пути от неё

	for (uint16_t i = 0; i < p; i++)
	{
		uint16_t from,
			to;
		cin >> from >> to;

		// Если мы не встречали раньше эту вершину
		if (!cash[from].first)
		{
			vector<unsigned int>* distances = new vector<unsigned int>(n + 1, INF);
			vector<short>* parents = new vector<short>(n + 1, -1);
			set<uint16_t> pq;

			distances[0][from] = 0;
			pq.insert(from);
			while (!pq.empty())
			{
				uint16_t currVertex = *pq.begin();
				pq.erase(currVertex);

				for (const auto& edge : graph[currVertex])
				{
					if (distances[0][edge.to] > distances[0][currVertex] + edge.cost)
					{
						distances[0][edge.to] = distances[0][currVertex] + edge.cost;
						pq.insert(edge.to);
						parents[0][edge.to] = currVertex;
					}
				}
			}

			list<uint16_t> path;
			for (short i = to; i != -1; i = parents[0][i])
				path.push_front(i);

			cout << distances[0][to] << " " << path.size() << " ";
			for (const auto& vertex : path)
				cout << vertex << " ";

			cout << endl;

			cash[from] = { distances, parents };
		}

		// Если встречали вршину ранее
		else
		{
			cout << cash[from].first[0][to] << " ";

			list<uint16_t> path;
			for (short i = to; i != -1; i = cash[from].second[0][i])
				path.push_front(i);

			cout << path.size() << " ";
			for (const auto& vertex : path)
				cout << vertex << " ";

			cout << endl;
		}

	}

	for (uint16_t i = 0; i < k; i++)
	{
		uint16_t from,
			to;
		cin >> from >> to;

		// Если мы не встречали раньше эту вершину
		if (!cash[from].first)
		{
			vector<unsigned int>* distances = new vector<unsigned int>(n + 1, INF);
			set<uint16_t> pq;

			distances[0][from] = 0;
			pq.insert(from);
			while (!pq.empty())
			{
				uint16_t currVertex = *pq.begin();
				pq.erase(currVertex);

				for (const auto& edge : graph[currVertex])
				{
					if (distances[0][edge.to] > distances[0][currVertex] + edge.cost)
					{
						distances[0][edge.to] = distances[0][currVertex] + edge.cost;
						pq.insert(edge.to);
					}
				}
			}


			cout << distances[0][to] << endl;

			cash[from] = { distances, nullptr };
		}

		// Если встречали вршину ранее
		else
		{
			cout << cash[from].first[0][to] << endl;
		}

	}

	for (auto& [vertex, cashData] : cash)
	{
		auto& [distances, parents] = cashData;
		delete distances;
		delete parents;
	}
}

void task3()
{
	int n;
	cin >> n;

	vector < vector < bool>> R(n, vector<bool>(n, 0));

	for (int i = 0; i < n; i++) 
	{
		for (int j = 0; j < n; j++) 
		{
			char c;
			cin >> c;
			R[i][j] = c - '0';
		}
	}

	// Рефлексивное замыкание
	for (int i = 0; i < n; i++) 
		R[i][i] = 1;
	
	// Транзитивное замыкание (алгоритм Флойда-Уоршалла)
	for (int k = 0; k < n; k++) 
	{
		for (int i = 0; i < n; i++) 
		{
			if (R[i][k])
			{
				for (int j = 0; j < n; j++)
				{
					if (R[k][j])
						R[i][j] = 1;
				}
			}
		}
	}

	for (int i = 0; i < n; i++) 
	{
		for (int j = 0; j < n; j++) 
		{
			cout << R[i][j];
		}
		cout << endl;
	}
}

void task4()
{
	struct Edge 
	{
		int from, to, cost;
	};

	int n, // Количество вершин
		m, // Количество дорожек
		k; // Количество друзей
	cin >> n >> m >> k;

	vector<int> friendlyVertexes(k);
	for (int i = 0; i < k; i++)
		cin >> friendlyVertexes[i];

	vector<Edge> edges(m);
	for (int i = 0; i < m; i++)
		cin >> edges[i].from >> edges[i].to >> edges[i].cost;

	vector<int> distances(n + 1, INF);
	vector<int> parents(n + 1, -1);

	distances[1] = 0;
	for (int i = 0; i < n; i++) 
	{
		for (Edge currEdge : edges) 
		{
			if (distances[currEdge.from] < INF && distances[currEdge.to] > distances[currEdge.from] + currEdge.cost) 
			{
				distances[currEdge.to] = distances[currEdge.from] + currEdge.cost;
				parents[currEdge.to] = currEdge.from;
			}
		}
	}

	for (int friend_vertex : friendlyVertexes) 
	{
		list<int> path;
		for (int v = friend_vertex; v != -1; v = parents[v])
			path.push_front(v);

		cout << distances[friend_vertex] << " " << path.size();

		for (int v : path)
			cout << " " << v;
		cout << "\n";
	}
}

void task5()
{
	int N, 
		M,
		K; // Количество домохозяек
	cin >> N >> M >> K;
	vector < vector < pair<int, int>>> graph(N + 1);
	vector < pair<int, int>> queries(K);

	for (int i = 0; i < K; i++) 
		cin >> queries[i].first >> queries[i].second;
	

	for (int i = 0; i < M; i++) 
	{
		int a, b, t;
		cin >> a >> b >> t;
		graph[a].emplace_back( b, t );
		graph[b].emplace_back(a, t);
	}

	for (auto& query : queries) 
	{
		int from = query.first;
		int to = query.second;

		vector<int> distances(N + 1, INF);
		vector<int> parent(N + 1, -1);
		distances[from] = 0;
		priority_queue < pair<int, int>, vector < pair<int, int>>, greater<pair<int, int>>> pq;
		pq.emplace(0, from);

		while (!pq.empty()) 
		{
			int u = pq.top().second;
			int d = pq.top().first;
			pq.pop();

			for (auto& edge : graph[u]) 
			{
				int v = edge.first;
				int w = edge.second;

				if (distances[u] + w < distances[v]) 
				{
					distances[v] = distances[u] + w;
					parent[v] = u;
					pq.emplace(distances[v], v);
				}
			}
		}

		if (distances[to] == INF) 
			cout << "NO\n";
		
		else 
		{
			cout << "YES " << distances[to];
			list<int> path;
			for (int u = to; u != -1; u = parent[u]) 
				path.push_front(u);
			
			cout << " " << path.size();
			for (int u : path) 
				cout << " " << u;
			
			cout << "\n";
		}
	}
}

void task6()
{
	int n;
	while (cin >> n, n != 0) 
	{
		vector<Match> matches(n + 1);
		for (int i = 1; i <= n; i++) 
			cin >> matches[i].p1.x >> matches[i].p1.y >> matches[i].p2.x >> matches[i].p2.y;
		
		vector < vector < int>> graph(n + 1);
		for (int i = 1; i <= n; i++) 
		{
			for (int j = i + 1; j <= n; j++) 
			{
				if (intersect(matches[i], matches[j])) 
				{
					graph[i].push_back(j);
					graph[j].push_back(i);
				}
			}
		}

		int from, to;
		while (cin >> from >> to, from != 0 && to != 0) 
		{
			vector<bool> visited(n + 1);
			dfs(from, to, graph, visited);
			cout << (visited[to] ? "CONNECTED\n" : "NOT CONNECTED\n");
		}
	}

}

/// <summary>
/// Считает самые короткие пути от стартоой вершины до всех остальных с помощью алгоритма Дейкстры
/// </summary>
/// <param name="start"> Номер стартовой вершины </param>
/// <param name="distances"> Массив расстояний </param>
/// <param name="edgeList"> Массив ребер </param>
void dijkstra(int start, vector<int>& distances, vector < vector < pair<int, int>>>& edgeList)
{
	distances[start] = 0;

	priority_queue < pair<int, int>, vector < pair<int, int>>, greater<pair<int, int>>> pq;
	pq.push({ 0, start });

	while (!pq.empty())
	{
		int node = pq.top().second;
		int distance = pq.top().first;
		pq.pop();

		for (const auto& edge : edgeList[node])
		{
			int to = edge.first;
			int len = edge.second;

			if (distances[node] + len < distances[to])
			{
				distances[to] = distances[node] + len;
				pq.push({ distances[to], to });
			}
		}
	}
}

void minWay(const int start, const int finish, vector<pair<int, int>>& distances, vector< vector<pair<int, int>>>& edgeList, list<int>& way)
{
	priority_queue < pair<int, int>, vector < pair<int, int>>, greater<pair<int, int>>> pq;
	pq.push({ 0, start });

	while (!pq.empty())
	{
		int node = pq.top().second;
		int distance = pq.top().first;
		pq.pop();

		for (const auto& edge : edgeList[node])
		{
			int to = edge.first;
			int len = edge.second;

			if (distances[node].first + len < distances[to].first)
			{
				distances[to].first = distances[node].first + len;
				distances[to].second = node;
				pq.push({ distances[to].first , to });
			}
		}
	}
	
	int tmp = finish;
	while (tmp != -1)
	{
		way.push_front(tmp);
		tmp = distances[tmp].second;
	}

	cout << distances[finish].first << " " << way.size() << " ";
	for (const auto& i : way)
	{
		cout << i << " ";
	}
	cout << endl;
}

bool intersect(const Match& m1, const Match& m2) 
{
	int t1 = (m2.p1.x - m1.p1.x) * (m1.p2.y - m1.p1.y) - (m2.p1.y - m1.p1.y) * (m1.p2.x - m1.p1.x);
	int t2 = (m2.p2.x - m1.p1.x) * (m1.p2.y - m1.p1.y) - (m2.p2.y - m1.p1.y) * (m1.p2.x - m1.p1.x);
	int t3 = (m1.p1.x - m2.p1.x) * (m2.p2.y - m2.p1.y) - (m1.p1.y - m2.p1.y) * (m2.p2.x - m2.p1.x);
	int t4 = (m1.p2.x - m2.p1.x) * (m2.p2.y - m2.p1.y) - (m1.p2.y - m2.p1.y) * (m2.p2.x - m2.p1.x);

	if (t1 * t2 < 0 && t3 * t4 < 0) return true;

	if (t1 == 0 && ((m2.p1.x - m1.p1.x) * (m2.p1.x - m1.p2.x) <= 0 && (m2.p1.y - m1.p1.y) * (m2.p1.y - m1.p2.y) <= 0)) return true;
	if (t2 == 0 && ((m2.p2.x - m1.p1.x) * (m2.p2.x - m1.p2.x) <= 0 && (m2.p2.y - m1.p1.y) * (m2.p2.y - m1.p2.y) <= 0)) return true;
	if (t3 == 0 && ((m1.p1.x - m2.p1.x) * (m1.p1.x - m2.p2.x) <= 0 && (m1.p1.y - m2.p1.y) * (m1.p1.y - m2.p2.y) <= 0)) return true;
	if (t4 == 0 && ((m1.p2.x - m2.p1.x) * (m1.p2.x - m2.p2.x) <= 0 && (m1.p2.y - m2.p1.y) * (m1.p2.y - m2.p2.y) <= 0)) return true;

	return false;
}

void dfs(int u, const int& finish, const vector<vector<int>>& graph, vector<bool>& visited) 
{
	if (visited[finish]) return;

	visited[u] = true;
	for (int v : graph[u]) 
	{
		if (visited[finish]) return;

		if (!visited[v]) 
			dfs(v, finish, graph, visited);
	}
}