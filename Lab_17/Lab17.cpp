#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <set>
#include <vector>
using namespace std;

// Структура, описывающая бинарное дерево
typedef struct Tree;

//Объявление вспомогательных функций

void Print_up(Tree* tree, int& count);
void BackTreePrint(Tree* tree);
Tree* Add(Tree* tree, int value);
void Cache_up(Tree* tree, int height, int& vertexAmm, int requiredHieght);
int evaluate_expression(string& expression, int& index, ostream& output);
void NextTreePrint(Tree* tree);
void NextTreePrint(Tree* tree, FILE* fileW);

/// <summary>
/// По заданной последовательности целых чисел построить дерево двоичного поиска и обойти его в прямом и обратном порядках. 
/// Повторяющиеся числа в дерево не вставлять.
/// </summary>
void task1();

void task2();
void task3();
void task4();

/// <summary>
/// По заданным словам построить дерево двоичного поиска и обойти его в инфиксном порядке. Повторяющиеся слова в дерево не вставлять.
/// </summary>
void task5();

/// <summary>
/// Описать рекурсивную функцию, которая вычисляет (как целое число) значение дерева - формулы
/// </summary>
void task6();

/// <summary>
/// Ваша задача состоит в том, чтобы исходя из такой последовательности строк листьев дерева бинарного поиска символов, выдать префиксный обход этого дерева.
/// </summary>
void task7();
void task8();

/// <summary>
/// Имеется множество целых чисел 𝑋, изначально оно пустое. Нужно выполнить 𝑀 заданных операций над этим множеством.
//Есть три типа операций :
/// 1. add 𝑣 — добавить число 𝑣 в множество 𝑋.Если такого числа ещё не было в множестве,
/// надо его добавить и напечатать слово added.Если такое число уже есть в множестве, нужно напечатать слово dupe и ничего не делать.
/// 2. remove 𝑣 — удалить число 𝑣 из множества 𝑋.Если такое число есть в множестве, нужно его удалить и напечатать слово removed.А если такого числа нет, нужно напечатать слово miss и ничего не делать.
/// 3. lower 𝑣 — найти минимальное число в множестве 𝑋, которое больше или равно заданному 𝑣(т.е.lower_bound).Если такое число в множестве есть, нужно напечатать в файл.
/// А если его нет, то есть если 𝑣 больше всех чисел множества 𝑋, то нужно напечатать ###.
/// </summary>
void task9();


int main()
{
	//task1();
	//task2();
	//task3();
	//task4();
	//task5();
	//task6();
	//task7();
	task8();
	//task9();
	
	return 0;
}

void task1()
{
	int N;
	Tree* tree = NULL;
	while (cin >> N)
		//tree = AddTree(tree, N);
	//Print_up(tree);
	printf("\n");
	BackTreePrint(tree);
}

void task2()
{
	int N, // Текущее число
		requiredHieght = 0, // Максимальная высота в дереве
		currHeight = 0; // Высота для текущего элемента в дереве
	Tree* tree = NULL;
	while (cin >> N)
		//tree = AddTree(tree, N, requiredHieght, currHeight);
	cout << requiredHieght;
}

void task3()
{
	int N = 0;
	int count = 0;
	Tree* tree = NULL;
	while (cin >> N) tree = Add(tree, N);
	Print_up(tree, count);
	cout << count;
}

void task4()
{
	int N = 0;
	int height = 0;
	int vertexAmm = 0;
	Tree* tree = NULL;
	cin >> height;
	while (cin >> N) tree = Add(tree, N);
	Cache_up(tree, 0, vertexAmm, height);
	cout << vertexAmm;
}

void task5()
{
	string word;
	set<string> words;
	while (cin >> word)
		words.insert(word);
	while (!words.empty())
	{
		cout << *words.begin() << endl;
		words.erase(words.begin());
	}
}

void task6()
{
	string expression;
	cin >> expression;
	int index = 0;
	int result = evaluate_expression(expression, index, cout);
	cout << result << endl;
}

void task7()
{
	string vertexes,
		temp;
	while (cin >> temp) vertexes = temp + vertexes;

	Tree* tree = NULL;
	for (char& c : vertexes)
		tree = Add(tree, c);
	NextTreePrint(tree);
}

void task8()
{
	Tree* tree = NULL;
	int N;
	FILE* fileR = fopen("input.bin", "rb");
	fread(&N, sizeof(int), 1, fileR);
	for (int i = 0; i < N; i++)
	{
		int temp;
		fread(&temp, sizeof(int), 1, fileR);
		tree = Add(tree, temp);
	}

	FILE *fileW = fopen("output.bin", "wb");
	NextTreePrint(tree, fileW);
	//NextTreePrint(tree);
	fclose(fileR);
	fclose(fileW);
}

void task9()
{
	int m;
	cin >> m;
	set<int> X;
	for (int i = 0; i < m; i++) {
		string op;
		int v;
		cin >> op >> v;
		if (op == "add") {
			auto ret = X.insert(v);
			if (ret.second) cout << "added\n";
			else cout << "dupe\n";
		}
		else if (op == "remove") {
			bool cnt = X.erase(v);
			if (cnt) cout << "removed\n";
			else cout << "miss\n";
		}
		else if (op == "lower") {
			auto it = X.lower_bound(v);
			if (it != X.end()) cout <<* it << "\n";
			else cout << "###\n";
		}
	}
}

typedef struct Tree 
{
	int most; // Значение элемента
	Tree* R; // Указатель на большего потомка
	Tree* L; // Указатель на меньшего потомка
};

/// <summary>
/// Рекурсивно считает количество листов в дереве
/// </summary>
/// <param name="tree"> Дерево, которое нужно вывести</param>
void Print_up(Tree* tree, int& count) 
{
	if (tree != NULL) {
		if (tree->L == NULL && tree->R == NULL)
			count++;
		Print_up(tree->L, count);
		Print_up(tree->R, count);
	}
}

/// <summary>
/// Рекурсивно выводит дерево в обратном порядке
/// </summary>
/// <param name="tree"> Дерево, которое нужно вывести</param>
void BackTreePrint(Tree* tree) 
{
	if (tree != NULL) 
	{
		BackTreePrint(tree->L);
		BackTreePrint(tree->R);
		printf("%d ", tree->most);
	}
}

/// <summary>
/// Рекурсивно считает количество вершин на определенном уровне дерева
/// </summary>
/// <param name="tree"> Дерево, в котором мы ищем вершины</param>
/// <param name="currHeight"> Текущая высота, на которой мы находимся</param>
/// <param name="vertexAmm"> Количество вершин на данном уровне</param>
/// <param name="requiredHieght"> Нужная высота, на которой нужно посчитать количество вершин</param>
void Cache_up(Tree* tree, int currHeight, int& vertexAmm, int requiredHieght)
{
	if (tree != NULL) 
	{
		if (currHeight == requiredHieght)
		{
			vertexAmm++;
			return;
		}
		currHeight++;
		Cache_up(tree->L, currHeight, vertexAmm, requiredHieght);
		Cache_up(tree->R, currHeight, vertexAmm, requiredHieght);
	}
}

/// <summary>
/// Рекурсивно добавляет число в дерево поиска 
/// </summary>
/// <param name="tree"> Дерево, в которое нужно добавить число</param>
/// <param name= "value"> Число, которое нужно добавить</param>
/// <returns> Указатель на новый элемент дерева, который мы только что добавили</returns>
/// 
Tree* Add(Tree* tree, int value) 
{
	if (tree == NULL)
	{
		tree = (Tree*)malloc(sizeof(Tree));
		tree->most = value;
		tree->L = NULL;
		tree->R = NULL;
	}
	else if (value < tree->most)
	{
		tree->L = Add(tree->L, value);
	}
	else
	{
		tree->R = Add(tree->R, value);
	}
	return(tree);
}

/// <summary>
/// Рекурсивно считает значение выражения, записанного в строке
/// </summary>
/// <param name="expression"></param>
/// <param name="index"></param>
/// <param name="output"></param>
/// <returns></returns>
int evaluate_expression(string& expression, int& index, ostream& output) 
{
	char c = expression[index];
	index++;
	if (isdigit(c)) 
		return c - '0';
	
	else {

		int left = evaluate_expression(expression, index, output);
		int right = evaluate_expression(expression, index, output);
		switch (c) {
		case '+':
			return left + right;
		case '-':
			return left - right;
		case '*':
			return left * right;
		case '/':
			if (right == 0) 
			{
				output << "NO" << endl;
				exit(0);
			}
			return left / right;
		}
	}
	return 0;
}

/// <summary>
/// Выводит дерево в прямом порядке
/// </summary>
/// <param name="tree"></param>
void NextTreePrint(Tree* tree)
{
	if (tree != NULL) 
	{
		NextTreePrint(tree->L);
		printf("%i ", tree->most);
		NextTreePrint(tree->R);
	}
}

void NextTreePrint(Tree* tree, FILE* fileW)
{
	if (tree != NULL)
	{
		NextTreePrint(tree->L);
		fwrite(&tree->most, sizeof(int), 1, fileW);
		NextTreePrint(tree->R);		
	}
}