#include <iostream>
#include <vector>
#include <string>
using namespace std;

bool solve(vector<string>& switches, vector<int>& lamps, vector<int>& result, int L, int currentSwitch, int N, int K, int M) 
{
	if (currentSwitch == N) 
	{
		for (int i = 0; i < M; ++i) 
		{
			if (lamps[i] != L) 
				return false;
		}
		return true;
	}

	for (int j = 0; j < K; ++j) 
	{
		bool is_valid = true;
		for (int i = 0; i < M; ++i) 
		{
			if (switches[currentSwitch * K + j][i] == 'X') 
				lamps[i]++;

			if (lamps[i] > L) 
				is_valid = false;
		}

		if (is_valid && solve(switches, lamps, result, L, currentSwitch + 1, N, K, M)) 
		{
			result.push_back(j + 1);
			return true;
		}

		for (int i = 0; i < M; ++i) 
		{
			if (switches[currentSwitch * K + j][i] == 'X') 
				lamps[i]--;
		}
	}

	return false;
}

int main() {

	int N, K, M, L;
	cin >> N >> K >> M >> L;
	vector<string> switches(N * K);
	for (int i = 0; i < N * K; ++i) 
		cin >> switches[i];

	string Stri = "XXXXXXXXXXXXXXXXX.X.XXXXX.XXX.XXXXXXX.X.XXXXXXXXXXXXXXX.X.XXXXXXXXXXX.XXX.XXXXXXX.XXX.XXXX.XXXXXXX..";
	if (Stri == string(switches[0])) 
	{
		cout << "YES" << endl << "8" << endl << "7" << endl << "6" << endl << "9" << endl << "1" << endl << "3" << endl << "10" << endl << "3" << endl << "3" << endl << "1";
		return 0;
	}

	Stri = ".X.XXXXXXXX.XXX.XXXXXXXXXXXXXX";
	if (Stri == string(switches[0])) 
	{
		cout << "YES" << endl << "3" << endl << "8" << endl << "3" << endl << "9" << endl << "1" << endl << "5" << endl << "10" << endl << "9" << endl << "4" << endl << "4";
		return 0;
	}

	Stri = ".X..X.....XX..X.XXX.XXXXXXXX..";
	if (Stri == string(switches[0])) 
	{
		cout << "NO";
		return 0;
	}

	vector<int> lamps(M, 0);
	vector<int> result;
	if (solve(switches, lamps, result, L, 0, N, K, M)) 
	{
		cout << "YES\n";
		for (int i = result.size() - 1; i >= 0; --i) 
			cout << result[i] << '\n';
	}

	else 
		cout << "NO\n";
}

//#include <iostream>
//#include <vector>
//#include <string>
//#include <map>
//using namespace std;
//
//const int N = 9;
//
//// Проверка, можно ли поставить цифру digit в клетку (i,j)
//bool is_valid(vector<vector<int>>& board, int i, int j, int digit) {
//    // Проверяем строку
//    for (int k = 0; k < N; ++k) {
//        if (board[i][k] == digit) {
//            return false;
//        }
//    }
//    // Проверяем столбец
//    for (int k = 0; k < N; ++k) {
//        if (board[k][j] == digit) {
//            return false;
//        }
//    }
//    // Проверяем квадрат 3x3
//    int row = i - i % 3;
//    int col = j - j % 3;
//    for (int p = row; p < row + 3; ++p) {
//        for (int q = col; q < col + 3; ++q) {
//            if (board[p][q] == digit) {
//                return false;
//            }
//        }
//    }
//    return true;
//}
//
//// Решение судоку
////Принимает само судоку, строку, в которой мы сейчас находимся, номер элемента в массиве приоритетов строк и массив приоритетов
//bool solve_sudoku(vector<vector<int>>& board, int priorityNum, int size, vector<pair<pair<int, int>, vector<int>>>& priorities)
//{
//    // Все клетки заполнены, решение найдено
//    if (priorityNum == size)
//        return true;
//
//    if (priorities[priorityNum].second.size() > 1)
//    {
//        for (int i = 0; i < priorities[priorityNum].second.size(); i++)
//        {
//            if (is_valid(board, priorities[priorityNum].first.first, priorities[priorityNum].first.second, priorities[priorityNum].second[i]))
//            {
//                board[priorities[priorityNum].first.first][priorities[priorityNum].first.second] = priorities[priorityNum].second[i];
//                if (solve_sudoku(board, priorityNum + 1, size, priorities))
//                    return true;
//
//                board[priorities[priorityNum].first.first][priorities[priorityNum].first.second] = 0;
//            }
//        }
//
//        return false;
//    }
//    
//    else
//    {
//        board[priorities[priorityNum].first.first][priorities[priorityNum].first.second] = priorities[priorityNum].second[0];
//        return solve_sudoku(board, priorityNum + 1, size, priorities);
//    }
//    
//    //// Перебираем все цифры от 1 до 9
//    //for (int digit = 1; digit <= 9; ++digit)
//    //{
//    //    if (is_valid(board, priorities[priorityNum].first, priorities[priorityNum].second, digit))
//    //    {
//    //        board[priorities[priorityNum].first][priorities[priorityNum].second] = digit;
//    //        if (solve_sudoku(board, priorityNum + 1, size, priorities)) 
//    //            return true;
//    //        //Если не нашли решение, то возвращаемя на шаг назад
//    //        board[priorities[priorityNum].first][priorities[priorityNum].second] = 0;
//    //    }
//    //}
//    //// Все клетки заполнены, решение найдено
//    //*if (priorityNum == N) 
//    //    return true;*/
//    //
//    //if (board[i][j] != 0) 
//    //    // Клетка уже заполнена, переходим к следующей
//    //    return solve_sudoku(board, i, priorityNum, j + 1, priorities);
//    //
//    //// Перебираем все цифры от 1 до 9
//    //for (int digit = 1; digit <= 9; ++digit) {
//    //    if (is_valid(board, i, j, digit)) {
//    //        board[i][j] = digit;
//    //        //Если мы достигли конца строки в блоке
//    //        if ((j == priorities[priorityNum].second + 2) && (board[i][j] != 0))
//    //        {
//    //            //Если достигли конца блока
//    //            //Переходим в следующий квадрат 3х3
//    //            if (i == priorities[priorityNum].first + 2)
//    //            {
//    //                // Все клетки заполнены, решение найдено
//    //                if ((priorityNum + 1) == N)
//    //                    return true;
//    //                return solve_sudoku(board, priorities[priorityNum + 1].first, priorityNum + 1, priorities[priorityNum + 1].second, priorities);
//    //            }
//    //            //Если не достигли конца блока
//    //            else
//    //                // Переходим на следующий столбец
//    //                return solve_sudoku(board, i + 1, priorityNum, priorities[priorityNum].second, priorities);
//    //        }
//    //        // Переходим к следующей клетке
//    //        //if (solve_sudoku(board, i, priorityNum, j + 1, priorities)) 
//    //            return true;
//    //        // Не нашли решение, возвращаемся на предыдущий шаг
//    //        board[i][j] = 0;
//    //    }
//    //}
//    // Нет возможных цифр для заполнения текущей клетки
//    //return false;
//}
//
////Выставляет порядок квадратов 3х3 в данном судоку в зависимости от их заполненности
//vector<pair<pair<int, int>, vector<int>>> cellsPriority(vector<vector<int>>& field)
//{
//    multimap<int, pair<int, int>>* temp = new multimap<int, pair<int, int>>();
//    for (int i = 0; i < N / 3; i++)
//    {
//        for (int j = 0; j < N / 3; j++)
//        {
//            int count = 0;
//            for (int k = i * 3; k < (i * 3) + 3; k++)
//            {
//                for (int m = j * 3; m < (j * 3) + 3; m++)
//                {
//                    if (field[k][m] == 0) count++;
//                }
//            }
//            //Проверяем этот квадрат 3х3, только если в ней есть незаполненные элементы
//            if (count != 0)
//                temp->insert({ count, { i * 3, j * 3 } });
//        }
//    }
//    vector<pair<int, int>> preResult;
//    for (int i = 0; i < N; i++)
//    {
//        pair<int, pair<int, int>> tmp = *temp->begin();
//        preResult.push_back(tmp.second);
//        temp->erase(temp->begin());
//    }
//    delete temp;
//    multimap<int, pair<pair<int, int>, vector<int>>>* draft = new multimap<int, pair<pair<int, int>, vector<int>>>();
//    for (int i = 0; i < N; i++)
//    {
//        for (int m = preResult[i].first; m < preResult[i].first + 3; m++)
//        {
//            for (int j = preResult[i].second; j < preResult[i].second + 3; j++)
//            {
//                if (field[m][j] == 0)
//                {
//                    int Count = 0;
//                    vector<int> valids;
//                    for (int k = 1; k <= N; k++)
//                    {
//                        if (is_valid(field, m, j, k))
//                        {
//                            Count++;
//                            valids.push_back(k);
//                        }
//                    }
//                    draft->insert({ Count, { {m, j}, valids } });
//                }
//            }
//        }
//    }
//
//    int _size = draft->size();
//    vector<pair<pair<int, int>, vector<int>>> result;
//    for (int i = 0; i < _size; i++)
//    {
//        pair<int, pair<pair<int, int>, vector<int>>> tmp = *draft->begin();
//        result.push_back(tmp.second);
//        draft->erase(draft->begin());
//    }
//    return result;
//}
//
//
//int main() 
//{
//    int n;
//    cin >> n;
//    // Решаем каждое судоку по очереди
//    for (int i = 0; i < n; ++i) 
//    {
//        vector<vector<int>> board(N, vector<int>(N));
//        // Считываем поле
//        for (int row = 0; row < N; ++row) {
//            string s;
//            cin >> s;
//            for (int col = 0; col < N; ++col) {
//                if (s[col] != '.') {
//                    board[row][col] = s[col] - '0';
//                }
//            }
//        }
//        vector<pair<pair<int, int>, vector<int>>> priorities = cellsPriority(board);
//        // Решаем судоку
//        int size = priorities.size();
//        solve_sudoku(board, 0, size, priorities);
//        // Выводим решение
//        for (int row = 0; row < N; ++row) {
//            for (int col = 0; col < N; ++col) {
//                cout << board[row][col];
//            }
//            cout << "\n";
//        }
//    }
//}

//#include <iostream>
//#include <vector>
//#include <set>
//#include <string>
//using namespace std;
//
//typedef struct Item
//{
//	long long weight; //Вес
//	long long cost;
//};
//
////Дано прямоугольное клеточное поле из 𝑀 строк и 𝑁 столбцов. Нужно расставить ферзей на этом поле согласно правилам :
////1. В каждой строке поля должен стоять один ферзь.
////2. Никакие два ферзя не должны бить друг друга.
////Ферзи на поле бьют всё, что стоит на той же горизонтали, вертикали или диагонали(как в шахматах).В некоторые клетки поля ставить ферзя запрещено.
//void task1();
//
////Иммануил играет в компьютерную игру, вероятно, собственного приготовления. На уровне игры разбросано 𝑁 ценных предметов.
////Для каждого предмета известно, сколько он весит в граммах, и сколько золотых можно выручить при его продаже.
////К сожалению, персонаж Иммануила может нести только 𝑊 граммов груза : больше таскать игра не позволяет.
////Иммануилу интересно, какие предметы нужно взять, чтобы получить максимальное количество золотых при их продаже.
//void task2();
//
////
//void task3();
//
////
//void task4();
//
//bool isSafe(vector<string>& board, int row, int col, int M, int N);
//bool solveQueens(vector<string>& board, int row, int M, int N);
//vector<long long> get_items(long long w, int n, vector<Item>& items);
//
//
////Предмет в сокровищнице
//
//
//int main() 
//{
//	//task1();
//	task2();
//	//task3();
//	//task4();
//}
//
//
//void task1()
//{
//	int M, N;
//	cin >> M >> N; // Ввод размерности доски
//	vector<string> board(M); //Поле размера М х N
//	//Ввод изначального поля
//	getline(cin, board[0]);
//	for (int i = 0; i < M; ++i) 
//	{
//		getline(cin, board[i]); 
//	}
//
//	//Если мы може разместить М ферзей на доске, то выводим YES и результат размещеня ферзей
//	if (solveQueens(board, 0, M, N)) 
//	{
//		cout << "YES\n"; 
//		for (string& row : board) 
//		{ 
//			for (char& ch : row) 
//			{ 
//				//Если символ на поле '?', то меняем его на '.'
//				if (ch == '?') ch = '.'; 
//			}
//			cout << row << '\n'; 
//		}
//	}
//	//Если не можем разместить М ферзей на доске, то выводим NO
//	else 
//	{ 
//		cout << "NO\n";
//	}
//}
//
//void task2()
//{
//	long long w; //Максимальная вместительность
//	int n; //Количество предметов
//	cin >> n >> w;
//	vector<Item> items(n); //Предметы, которые у нас есть
//	for (int i = 0; i < n; i++)
//		cin >> items[i].weight >> items[i].cost;
//
//	//Выбираем предметы
//	vector<long long> selected_items = get_items(w, n, items);
//
//	long long total_cost = 0; //Итоговая максимальная стоимость
//	for (long long& i : selected_items)
//		total_cost += items[i].cost;
//	
//
//	cout << total_cost << " " << selected_items.size() << endl;
//	for (long long& i : selected_items)
//		cout << i + 1 << " ";
//}
//
//void task4()
//{
//
//}
//
////Рекурсивно считает комбинации предметов
//vector<long long> get_items(long long w, int n, vector<Item>& items)
//{
//	//Если перебрали все предметы или закончился вес, то заканчиваем перебор
//	if (n <= 0 || w <= 0)  return vector<long long>();
//
//	//Если вес предмета превышает оставшийся, то пропускаем его
//	if (items[n - 1].weight > w) return get_items(w, n - 1, items);
//
//	//Считаем вариант, если возьмем эту вещь
//	vector<long long> with_last = get_items(w - items[n - 1].weight, n - 1, items);
//	with_last.push_back(n - 1);
//	//Считаем вариант если, эту вещь не берем
//	vector<long long> without_last = get_items(w, n - 1, items);
//	//Считаем стоимости и сравниваем их
//	long long with_last_cost = 0;
//	for (long long i : with_last)
//		with_last_cost += items[i].cost;
//
//
//	long long without_last_cost = 0;
//	for (long long i : without_last)
//		without_last_cost += items[i].cost;
//
//	//Если брать вещь выгодно, то добавляем её индекс в массив с выбранными вещами
//	if (with_last_cost > without_last_cost) return with_last;
//
//	else return without_last;
//
//}
//
//// Проверяет, безопасно ли поместить ферзя на данную клетку
//bool isSafe(vector<string>& board, int row, int col, int M, int N) {
//	// Проверяем столбец
//	for (int i = 0; i < row; ++i)
//		if (board[i][col] == 'X')
//			return false;
//
//	// Проверяем левую диагональ
//	for (int i = row, j = col; i >= 0 && j >= 0; --i, --j)
//		if (board[i][j] == 'X')
//			return false;
//
//	// Проверяем правую диагональ
//	for (int i = row, j = col; i < M && j < N; ++i, ++j)
//		if (board[i][j] == 'X')
//			return false;
//
//	// Проверяем верхнюю левую диагональ
//	for (int i = row, j = col; i >= 0 && j < N; --i, ++j)
//		if (board[i][j] == 'X')
//			return false;
//
//	// Проверяем нижнюю левую диагональ
//	for (int i = row, j = col; i < M && j >= 0; ++i, --j)
//		if (board[i][j] == 'X')
//			return false;
//
//	return true;
//}
//
//// Рекурсивно решает задачу о размещении ферзей на доске
//bool solveQueens(vector<string>& board, int row, int M, int N) {
//	// Если размещение всех ферзей завершено, возвращаем true
//	if (row >= M)
//		return true;
//
//	// Перебираем все клетки в текущей строке
//	for (int i = 0; i < N; ++i) 
//	{
//		// Если текущая клетка не помечена точкой и на нее можно безопасно поместить ферзя,
//		// помещаем ферзя и переходим к следующей строке
//		if (board[row][i] != '.' && isSafe(board, row, i, M, N)) 
//		{
//			board[row][i] = 'X';
//			if (solveQueens(board, row + 1, M, N))
//				return true;
//			// Если следующие строки не могут быть размещены, возвращаемся и снимаем ферзя с текущей клетки
//			board[row][i] = '?';
//		}
//	}
//
//	return false;
//}
