#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <set>
#include <algorithm>
using namespace std;

//Объявление вспомогательных функций




//Посчитайте количество последовательностей длины 𝑁 из нулей и единиц, не содержащих двух единиц подряд.
void task1();

//
void task2();

//Имеется 𝑁 предметов, для каждого предмета известны его вес и его стоимость. Хочется унести набор предметов максимальной суммарной стоимости. 
//Однако унести предметы можно только в рюкзаке.Рюкзак один, и он выдерживает вес не более 𝑊.
//Требуется определить, какие предметы надо забрать, так чтобы рюкзак выдержал их суммарный вес, и чтобы их суммарная стоимость была максимальна.
void task3();

//
void task4();

//𝑁 гангстеров идут в ресторан. 𝑖-тый гангстер заходит в 𝑇𝑖-е время и имеет при себе 𝑃𝑖 денег.
//Дверь ресторана имеет 𝑘 + 1 стадий открытия, выраженных в целых числах от 0 до 𝐾.
//Состояние открытия может измениться на 1 в единицу времени, т.е.либо открыться на 1, либо закрыться на 1, либо остаться прежним.В начальный момент состояние двери закрытое = 0.
//𝑖 - тый гангстер может войти в ресторан, если дверь открыта специально для него, т.е состояние двери совпадает с шириной его плеч 𝑆𝑖.
// Если в момент времени, когда гангстер подошел к ресторану, состояние открытия двери не совпадает с шириной его плеч, то он уходит и никогда не возвращается.
//Ресторан работает в интервале времени[0, 𝑇].
//Цель: собрать в ресторане гангстеров с максимальным количеством денег.

void task5();

// Требуется написать программу, которая преобразует исходный цифровой номер телефона в соответствующую последовательность букв и цифр, содержащую как можно больше символов из названия фирмы.
// При этом буквы из названия фирмы должны быть указаны в полученном номере в той же последовательности, в которой они встречаются в названии фирмы
void task7();

//Дан массив из 𝑁 чисел. Нужно найти в этом массиве такую подпоследовательность, что:
//1. Числа этой подпоследовательности строго возрастают(слева направо).
//2. Количество элементов в этой подпоследовательности максимально возможное.
void task8();

int main()
{
	//task1();
	//task2();
	//task3();
	//task4();
	//task5();
	task7();
	//task8();
}

void task1()
{
	int N;
	cin >> N;
	int p1 = 3, p2 = 2, s;
	for (int i = 3; i <= N; i++) 
	{
		s = p1 + p2;
		p2 = p1;
		p1 = s;
	}
	if (N == 1)
	{
		cout << 2 << endl;
		return;
	}
	if (N == 2)
	{
		cout << 3 << endl;
		return;
	}
	cout << s << endl;
}

void task2()
{
	int n, k;
	cin >> n >> k;

	vector<int> nums(n + 1);
	vector<vector<bool>> delims(n + 1, vector<bool>(k));

	for (int i = 1; i <= n; i++) cin >> nums[i];

	delims[1][(nums[1] % k + k) % k] = 1;
	for (int i = 2; i <= n; i++) 
	{
		for (int j = 0; j < k; j++) 
		{
			if (delims[i - 1][j]) 
			{
				delims[i][(j + nums[i] % k + k) % k] = 1;
				delims[i][(j - nums[i] % k + k) % k] = 1;
			}
		}
	}

	if (delims[n][0]) printf("Divisible\n");

	else printf("Not divisible\n");
}

void task3()
{
	int n, // Количество предметов
		w; // Максимальный вес рюкзака
	cin >> n >> w;
	vector<int> weight(n + 1), // Массив весов
				cost(n + 1); // Массив стоимостей
	for (int i = 1; i <= n; i++) 
		cin >> weight[i] >> cost[i];

	vector<vector<int>> dp(n + 1, vector<int>(w + 1, 0)); // Максимальные стоимости разных выборок
	vector<vector<bool>> take(n + 1, vector<bool>(w + 1, 0)); // Массив предметов, которые мы берем в разных выборках

	// Составляем разные выборки
	for (int i = 1; i <= n; i++) 
	{
		for (int j = 1; j <= w; j++) 
		{
			if (weight[i] <= j) 
			{
				if (cost[i] + dp[i - 1][j - weight[i]] > dp[i - 1][j]) 
				{
					dp[i][j] = cost[i] + dp[i - 1][j - weight[i]];
					take[i][j] = 1;
				}
				else 
					dp[i][j] = dp[i - 1][j];
			}
			else 
				dp[i][j] = dp[i - 1][j];
		}
	}

	int k = 0, // Количество предметов в финальной выборке
		total_weight = 0, total_cost = 0;
	vector<int> items; // Финальная выборка
	for (int i = n; i > 0; i--) 
	{
		if (take[i][w]) 
		{
			k++;
			total_weight += weight[i];
			total_cost += cost[i];
			items.push_back(i);
			w -= weight[i];
		}
	}

	// Вывод
	cout << k << " " << total_weight << " " << total_cost << endl;
	for (vector<int>::reverse_iterator item = items.rbegin(); item != items.rend(); ++item)
		cout << *item << " ";
}

void task4()
{
	#define MOD 1'000'000'007
	int n; 
	cin >> n;

	vector<int> partitions(n + 1);
	partitions[0] = 1;

	// Считаем число разбиений для каждого числа от 1 до n
	for (int i = 1; i <= n; i++) 
	{
		for (int j = i; j <= n; j++) 
			partitions[j] = (partitions[j] + partitions[j - i]) % MOD;
	}
	// Вывод
	cout << partitions.back();

}

void task5()
{
	int n, k, t;
	cin >> n >> k >> t;

	vector<vector<int>> gangsters(n, vector<int>(3)); // Массив гангстеров, имеющих время прибытия, деньги и ширину плеч 
	for (int i = 0; i < n; i++)
		cin >> gangsters[i][0];
	for (int i = 0; i < n; i++)
		cin >> gangsters[i][1];
	for (int i = 0; i < n; i++)
		cin >> gangsters[i][2];

	for (int i = 0; i < n; i++)
		if (gangsters[i][0] < gangsters[i][2])
			gangsters[i][1] = 0;

	// Сортируем гангстеров по времени прибытия
	sort(gangsters.begin(), gangsters.end());

	vector<int> maxPrices(n); // Максимальные суммы для разного количества гангстеров
	// Вычисляем максимальные суммы для разного количества гангстеров
	for (int i = 0; i < n; i++)
	{
		int cur_max_price = gangsters[i][1]; // Максимальная сумма для текущего количества ганстеров
		for (int j = 0; j < i; j++)
		{
			// Проверяем только если гангстер может войти
			if (gangsters[i][1] != 0)
			{
				if(abs(gangsters[i][0]- gangsters[j][0])>= abs(gangsters[i][2] - gangsters[j][2]))
					cur_max_price = max(cur_max_price, maxPrices[j] + gangsters[i][1]);
			}
		}

		maxPrices[i] = cur_max_price;
	}

	cout << *max_element(maxPrices.begin(), maxPrices.end());
}

void task7()
{
	string name, // Название компании
		number;  // Номер компании
	cin >> name >> number;

	int n = number.size(); // Количество цифр в номере компании
	int m = name.size(); // Количество символов в названии компании
	vector<vector<int>> operationsOnTransform(n + 1, vector<int>(m + 1)); // Таблица с минимальнм количеством действий для преобразования одной строки в другую

	// Расставляем минимальные количества действий для получения исходных строк из пустой строки
	for (int i = 1; i < n + 1; i++)
		operationsOnTransform[i][0] = i;
	for (int i = 1; i < m + 1; i++)
		operationsOnTransform[0][i] = i;

	// Меняем буквы в исходной строке на их эквивалент на расклаке телефона
	for (int i = 0; i < name.length(); i++)
	{
		if (name[i] >= 'A' && name[i] <= 'C')
		{ 
			name[i] = '2';
		}
		else if (name[i] >= 'D' && name[i] <= 'F')
		{
			name[i] = '3';
		}
		else if (name[i] >= 'G' && name[i] <= 'I')
		{
			name[i] = '4';
		}
		else if (name[i] >= 'J' && name[i] <= 'L')
		{
			name[i] = '5';
		}
		else if (name[i] >= 'M' && name[i] <= 'N')
		{
			name[i] = '6';
		}
		else if (name[i] == 'P' || name[i] == 'R' || name[i] == 'S')
		{
			name[i] = '7';
		}
		else if (name[i] == 'T' || name[i] == 'U' || name[i] == 'V')
		{
			name[i] = '8';
		}
		else if (name[i] == 'X' || name[i] == 'W' || name[i] == 'Y')
		{
			name[i] = '9';
		}
		else if (name[i] == 'O' || name[i] == 'Q' || name[i] == 'Z')
		{
			name[i] = '0';
		}
	}

	// Заполняем таблицу с минимальнм количеством действий для преобразования одной строки в другую
	for (int i = 1; i < n + 1; i++)
	{
		for (int j = 1; j < m + 1; j++)
		{
			if (number[i] == name[j])
				operationsOnTransform[i][j] = min(operationsOnTransform[i - 1][j - 1], min(operationsOnTransform[i - 1][j] + 1, operationsOnTransform[i][j - 1] + 1));

			else
				operationsOnTransform[i][j] = min(operationsOnTransform[i - 1][j], operationsOnTransform[i][j - 1]) + 1;

		}
	}

	// Вывод результата
	int result = abs(n + m - operationsOnTransform[n][m]) / 2;
	cout << result;
	
}

void task8()
{
	int n; // Количество чисел
	cin >> n;

	vector<int>* arr = new vector<int>(n); // Числа 
	for (int i = 0; i < n; i++)
		cin >> arr->operator[](i);

	vector<int>* subseq = new vector<int>; // Вектор, нужный для составлени подстроки
	vector<int>* prev = new vector<int>(n, -1); // Вектор, с помощью которого мы соберем подстроку
	vector<int>* index = new vector<int>(n); // Индексы элементов

	//Составляем подстроку
	for (int i = 0; i < n; i++)
	{
		vector<int>::iterator it = lower_bound(subseq->begin(), subseq->end(), arr->operator[](i));
		if (it == subseq->end())
		{
			prev->operator[](i) = subseq->empty() ? -1 : index->operator[](subseq->size() - 1);
			index->operator[](subseq->size()) = i;
			subseq->push_back(arr->operator[](i));
		}
		else
		{
			*it = arr->operator[](i);
			prev->operator[](i) = it == subseq->begin() ? -1 : index->operator[]((it - subseq->begin()) - 1);
			index->operator[](it - subseq->begin()) = i;
		}
	}

	//Записываем подпоследовательность (сначала в обратном порядке)
	vector<int>* ans = new vector<int>;
	int i = index->operator[](subseq->size() - 1);
	while (i >= 0)
	{
		ans->push_back(i);
		i = prev->operator[](i);
	}
	//Переписываем последовательность в правильном порядке
	//Вывод подпоследовательности
	cout << ans->size() << '\n';
	for (int& i : *ans)
		cout << "A[" << i + 1 << "] = " << arr->operator[](i) << '\n';
}


