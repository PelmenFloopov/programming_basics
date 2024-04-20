#include <iostream>
#include <vector>
#include <string>
using namespace std;

//Элемент односвязного списка
typedef struct Element
{	
	int value = 0; //Значение элемента
	Element * next = NULL; //Ссылка на следующий элемент
	Element* prev = NULL; //Ссылка предыдущий элемент
	Element* nextNode = NULL; //Ссылка на следующий большой узел
}; 


//Класс, в котором реализуется односвязный список
class Array
{
//Объявление конструктора и деструктора
//Конструктор имеет 2 перегрузки. Для создания путого списка и для создания списка с некоторым количеством элементов
public:
	Array();
	//Array(int);
	~Array();

public:
	Element* head, * tail; //Указатели на первый и последний элементы списка

private:
	int nodeFreq = 1500; //Частота появления больших узлов в списке

public:
	//Метод, удаляющий первый элемент в списке, если он есть 
	void pop_front()
	{
		if (head == NULL) return;
		if (head == tail)
		{
			delete head;
			head = tail = NULL;
			return;
		}
		Element* tmp = head;
		head = head->next;
		delete tmp;		
	}

	//Добавляет новый элемент в начало списка
	void push_front(int val, int _size)
	{		
		if (head == NULL)
		{
			tail = new Element;
			head = tail;
			head->value = val;
			return;
		}
		Element* tmp = new Element;
		tmp->next = head;
		tmp->value = val;
		head->prev = tmp;
		tmp->nextNode = head->nextNode;
		head->nextNode=NULL;
		head = tmp;
		if (_size % nodeFreq == 0)
		{
			//Обновляем ссылки на все большие узлы
			if (head->nextNode != NULL)
			{
				Element* i = head;
				while (i->nextNode != NULL)
				{
					i->nextNode = i->nextNode->prev;
					i = i->nextNode;
					i->nextNode = i->next->nextNode;
					i->next->nextNode = NULL;
				}
			}
			//Добавляем ссылку на новый большой узел
			Element* itr = head;
			while (itr->nextNode != NULL) itr = itr->nextNode;
			itr->nextNode = tail;
		}
		else
		{
			//Обновляем ссылки на все большие узлы
			if (head->nextNode != NULL)
			{
				Element* i = head;
				while (i->nextNode != NULL)
				{					
					i->nextNode = i->nextNode->prev;
					i = i->nextNode;
					i->nextNode = i->next->nextNode;					
					i->next->nextNode = NULL;
				}												
			}
		}
	}

	//Удаляет последний элемент в списке, если он есть
	void pop_back()
	{
		if (tail == NULL) return;
		if (head == tail)
		{
			delete tail;
			head = tail = NULL;
			return;
		}
		Element* tmp = head;
		while (tmp->next != tail) tmp = tmp->next;
		tmp->next = NULL;
		delete tail;		
		tail = tmp;
	}

	//Добавляет элемент в конец списка
	void push_back(int val, int _size)
	{		
		if (tail == NULL)
		{
			head = new Element;
			tail = head;
			tail->value = val;
			return;
		}
		Element* tmp = new Element;
		tail->next = tmp;
		tmp->prev = tail;
		tmp->value = val;		
		tail = tmp;
		//Добавляем ссылку на новый большой узел
		if (_size % nodeFreq == 0)
		{
			Element* itr = head;
			while (itr->nextNode != NULL) itr = itr->nextNode;
			itr->nextNode = tail;
		}
	}

	//Метод, возвращающий количество элементов в нем
	int size()
	{
		if (head == NULL && tail == NULL) return 0;
		if (head == tail) return 1;
		Element* tmp = head;
		int amm = 0;
		while (tmp->nextNode != NULL)
		{
			amm += nodeFreq;
			tmp = tmp->nextNode;
		}
		if (head->nextNode != NULL) tmp = tmp->next; //Устранение погрешности рассчета
		while(tmp != NULL)
		{
			amm += 1;
			tmp = tmp->next;
		}
		return (amm);
	}

	//Удаляет элемент по индексу
	void erase(int index)
	{
		if ((index >= 0) && (index < size()))
		{
			if (&this->operator[](index) == head)
			{
				pop_front();
				return;
			}
			if (&this->operator[](index) == tail)
			{
				pop_back();
				return;
			}
			Element* tmp = &this->operator[](index);
			this->operator[](index - 1).next = &this->operator[](index + 1);			
			delete tmp;
		}
		else
		{
			throw "Index is out of range";
		}
	}

	//Удаляет элемент, принимая указатель на предыдущий и следующий
	void erase(Element* left, Element* right)
	{
		if (left != NULL)
		{
			if (left->next == tail)
			{
				pop_back();
				return;
			}
			Element* tmp = left->next;
			left->next = right;
			delete tmp;
		}		
	}

	//Удаляет все повторяющиеся элементы в списке 
	void unique()
	{
		if (head != tail)
		{
			for (Element* i = head; (i != tail) && (i != NULL); i = i->next)
			{			
				while ((i != tail) && (i->value == i->next->value)) erase(i, i->next->next);
			}
		}
	}

	//Вставляет элемент перед indexовым элементом
	void insert(int index, int val, int _size)
	{		
		if (index == 0)
		{
			push_front(val, _size);
			return;
		}
		if (index == _size - 1)
		{
			push_back(val, _size);
			return;
		}
		if ((index > 0) && (index < _size - 1))
		{
			Element* tmp = head;
			//Идем по большим узлам
			for (int i = 0; i < (index + 1) / nodeFreq; i++)
			{
				tmp = tmp->nextNode;
			}
			int remain = index + 1 < nodeFreq ? index : (index - ((index + 1) / nodeFreq) * nodeFreq) + 1; //Оставшееся количество элементов после перехода по большим узлам
			for (int i = 0; i < remain; i++) tmp = tmp->next; //Проходим оставшиеся элементы
			//Создаем новый элемент и подключаем ссылки
			Element* newEl = new Element;
			newEl->value = val;
			newEl->next = tmp;
			tmp->prev->next = newEl;
			newEl->prev = tmp->prev;
			tmp->prev = newEl;
			if (_size % nodeFreq == 0)
			{
				//Обновляем все ссылки на большие узлы, следующие за вставленным элементом
				if (head->nextNode != NULL)
				{
					Element* itr = head;
					for (int i = 0; i < index / nodeFreq; i++)
					{
						itr = itr->nextNode;
					}
					while (itr->nextNode != NULL)
					{
						itr->nextNode = itr->nextNode->prev;
						itr = itr->nextNode;
						itr->nextNode = itr->next->nextNode;
						itr->next->nextNode = NULL;
					}
				}
				//Добавляем ссылку на новый большой узел
				Element* itr = head;
				while (itr->nextNode != NULL) itr = itr->nextNode;
				itr->nextNode = tail;
			}
			else 
			{
				//Обновляем все ссылки на большие узлы, следующие за вставленным элементом
				if (head->nextNode != NULL)
				{
					Element* itr = head;
					for (int i = 0; i < index / nodeFreq; i++)
					{
						itr = itr->nextNode;
					}												
					while (itr->nextNode != NULL)
					{
						itr->nextNode = itr->nextNode->prev;
						itr = itr->nextNode;
						itr->nextNode = itr->next->nextNode;
						itr->next->nextNode = NULL;
					}
				}
			}
		}		
		else
		{
			throw "Index is out of range";
		}
	}

	////Помещает элемент перед тем что передается по ссылке
	//void insert(Element* right, int val)
	//{
	//	if (right == head)
	//	{
	//		push_front(val);
	//		return;
	//	}
	//	else if (right == NULL)
	//	{
	//		push_back(val);
	//		return;
	//	}
	//	Element* i = head;
	//	while (i->next != right) i = i->next;
	//	Element* tmp = new Element;
	//	tmp->value = val;
	//	tmp->next = right;
	//	i->next = tmp;
	//}

	//Выводит список на экран
	void print()
	{
		for (Element* i = head; i != NULL; i = i->next)
		{
			cout << i->value << " ";
		}
	}
	//Перегрузка оператора индексации []
	//Возвращает ссылку на элемент списка по индексу
	Element& operator[] (int index)
	{
		//if ((index >= 0) && (index < size()))
		{
			Element* tmp = head;
			for (int i = 0; i < (index + 1) / nodeFreq; i++)
			{
				tmp = tmp->nextNode;
			}
			int remain = index + 1 < nodeFreq ? index : (index - ((index + 1) / nodeFreq) * nodeFreq) + 1;
			for (int i = 0; i < remain; i++)
			{
				tmp = tmp->next;
			}
			return (*tmp);
		}
		/*else
		{
			throw "Index is out of range";
		}*/		
	}	
};

//Конструктор списка из определенного количества элементов
//Array::Array(int elAmm) {
//	if (elAmm == 0)
//	{
//		head->next = tail->next = NULL;
//		return;
//	}
//	if (elAmm == 1)
//	{
//		tail = new Element;
//		head = tail;		
//		return;
//	}
//	if (elAmm >= 2)
//	{
//		head = new Element;
//		head->value = 0;
//		tail = new Element;
//		tail->value = 0;
//		head->next = tail;		
//		for (int i = 0; i < elAmm - 2; i++) push_front(0);
//	}
//}
//Конструктор пустого списка
Array::Array() { head = tail = NULL;}
//Деструкор списка
Array::~Array() { while (head != NULL) pop_front();}

typedef struct CycleEl
{
	int value = 0; //Значение элемента
	CycleEl* next = NULL; //Ссылка на следующий элемент
	CycleEl* prev = NULL; //Ссылка на предыдущий элемент
};

class CycleLst
{
public:
	CycleEl* head, * tail;

public:
	CycleLst();
	~CycleLst();
public:
	//Удаляет последний элемент в списке, если он есть
	void pop_back()
	{
		if (tail == NULL) return;
		if (head == tail)
		{
			delete tail;
			head = tail = NULL;
			return;
		}
		CycleEl* tmp = tail;		
		tail->prev->next = head;
		tail = tail->prev;
		head->prev = tail;
		delete tmp;		
	}

	//Добавляет элемент в конец списка
	void push_back(int val)
	{
		if (tail == NULL)
		{
			head = new CycleEl;
			tail = head;
			tail->value = val;
			tail->next = head;
			head->prev = tail;
			return;
		}
		CycleEl* tmp = new CycleEl;
		tail->next = tmp;
		tmp->value = val;
		tmp->next = head;
		tmp->prev = tail;
		head->prev = tmp;
		tail = tmp;
	}

	//Удаляет элемент, принимая указатель на этот элемент
	void erase(CycleEl* delEl)
	{		
		if (delEl == head) head = head->next;
		else if (delEl == tail) tail = tail->prev;
		CycleEl* tmp = delEl;
		delEl->prev->next = delEl->next;
		delEl->next->prev = delEl->prev;
		delete tmp;		
	}

	
};

CycleLst::CycleLst()
{
	head = tail = NULL;
}

CycleLst::~CycleLst(){ while (head != NULL) pop_back(); }

//Стурктура для 8 задачи
typedef struct Map
{
	int key = -1;
	vector<string> values;
};


//По заданной последовательности целых чисел построить односвязный динамический список. Каждое новое число добавлять в начало списка.
//память освободить.
//Затем пройти по построенному списку и посчитать количество отрицательных чисел, входящих в список, кратных 7. 
void task1();
//По заданной последовательности целых чисел построить односвязный динамический список. Каждое новое число добавлять в конец списка. Затем пройти по построенному списку
//и посчитать среднее арифметическое чисел, входящих в список. После этого память освободить
void task2();
//Требуется написать программу, которая из целых чисел, записанных во входном файле,строит динамический список.Числа должны располагаться в списке в том же порядке, что и во входном файле.
//Затем из полученного списка нужно удалить все повторяющиеся элементы, после чего пройтись по преобразованному списку и в выходной файл выдать через пробел оставшиеся числа.
//В конце программы память освободить
void task3();
//По заданной последовательности целых чисел построить односвязный список. Каждое новое число добавлять в начало списка.
//Затем пройти по построенному списку и удалить элемент, предшествующий элементу, содержащему заданное число, для всех таких вхождений.
//После этого распечатать полученный список, память освободить.
void task4();
//По заданной последовательности целых чисел построить односвязный динамический список. Каждое новое число добавлять в список так, чтобы он оставался упорядоченным по возрастанию.
//Если такое число в списке уже есть, то его не добавлять.Затем пройти по построенному списку от начала до конца и распечатать его элементы.
//После этого память освободить.
void task5();
//Исключать из группы, первоначально состоящей из 𝑁 элементов, каждого 𝐾 - го до тех пор, пока в ней не останется один элемент.
//Для решения ее нужно использовать двусвязный циклический список.
void task6();
//Дано два односвязных упорядоченных по неубыванию списка, содержащих целые числа.
//Нужно эти два списка слить в один, упорядоченный по невозрастанию, т.е.построить этот список из элементов двух данных.
//Новой памяти не выделять
void task7();
//Требуется вывести ровно те же самые 𝑁 записей, но в другом порядке. Записи должны быть упорядочены по возрастанию ключа. 
//Если у нескольких записей ключ равный, то нужно упорядочить их в том порядке, в котором они встречаются по входном файле.
void task8();
//Предлагается реализовать эту структуру данных, и обработать с её помощью серию из 𝑁 запросов двух типов(в описаниях 𝐿 — текущее количество узлов в списке) :
/*0. Вставить на 𝑘 - ую позицию новый узел с заданным значением 𝑉.Гарантируется, что во всех запросах 𝑘 лежит в пределах от 0 до 𝐿.
1. Вывести значение узла, находящегося на 𝑘 - ой позиции в списке.Гарантируется, что во всех запросах 𝑘 лежит в пределах от 0 до 𝐿 − 1*/
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
	//task8();
	task9();

}

//void task1()
//{
//	Array arr;
//	int temp, //Переменная, в которой временно хранится значение, введенное на консоль
//		amm = 0; //Количество отрицательных чисел, кратных 7
//	while (cin >> temp) arr.push_front(temp);
//	for (int i = 0; i < arr.size(); i++)
//	{
//		if ((arr[i].value % 7 == 0) && (arr[i].value < 0))amm += 1;
//	}
//	cout << amm;
//}
//
//void task2()
//{
//	Array arr;
//	int temp, //Переменная, в которой временно хранится значение, введенное на консоль
//		sum = 0; //Сумма всех элементов списка
//	while (cin >> temp) arr.push_back(temp);
//	for (int i = 0; i < arr.size(); i++)
//	{
//		sum += arr[i].value;
//	}
//	int average = sum / arr.size(); //Среднее арифметическое всех элементов списка
//	cout << average;
//	arr.~Array();
//}
//
//void task3()
//{
//	Array arr;
//	int temp; //Переменная, в которой временно хранится значение, введенное на консоль
//	while (cin >> temp) arr.push_back(temp);
//	//Удаляем из масива повторяющиеся объекты
//	arr.unique();
//	arr.print();
//	arr.~Array();
//}
//
//void task4()
//{
//	Array arr;
//	//
//	int delEl , //Число перед которым нужно будет удалить элемент
//		temp; //Переменная, в которой временно хранится значение, введенное на консоль
//	cin >> delEl;
//	while (cin >> temp) arr.push_front(temp);	
//	for (int i = 0; i < arr.size() - 1; i++)
//	{
//		if (arr[i + 1].value == delEl)
//		{
//			arr.erase(i);
//			i -= 1;
//		}
//	}
//	arr.print();
//}
//
//void task5()
//{
//	Array arr;
//	int temp; //Переменная, в которой временно хранится значение, введенное на консоль
//	while (cin >> temp)
//	{
//		int _size = arr.size();
//		//Если список пустой, то ничего не проверяем
//		if (_size == 0) arr.push_front(temp); 
//		//Иначе проверяем есть ли элементы меньше считанного и повторяется ли он
//		else
//		{
//			bool flag = false;
//			for (int i = 0; i < _size; i++)
//			{
//				if (arr[i].value > temp)
//				{
//					arr.insert(i, temp);
//					flag = true;
//					break;
//				}
//				if (arr[i].value == temp)
//				{
//					flag = true;
//					break;
//				}
//			}
//			//Если он больше всех и он не повторяется, то добавляем его в конец списка
//			if (!flag) arr.push_back(temp);
//		}
//	}
//	arr.print();
//}
//
//void task6()
//{
//	CycleLst arr;
//	//Количество элементов в списке
//	int n,
//	//Номер каждого удаляемого элемента
//		k;
//	cin >> n >> k;
//	for (int i = 0; i < n; i++)
//	{
//		arr.push_back(i + 1);
//	}
//	CycleEl* iter = arr.head;
//	while (arr.head != arr.tail)
//	{
//		for (int i = 0; i < k; i++) iter = iter->next;		
//		arr.erase(iter->prev);
//	}
//	cout << arr.head->value;
//}
//
//void task7()
//{
//	//Массивы, которые нужно соеденить
//	Array arr1, arr2;
//	int n, //Размер 1 массива
//		m; //Размер 2 массива
//	cin >> n >> m;
//	for (int i = 0; i < n; i++)
//	{
//		int temp;
//		cin >> temp;
//		arr1.push_front(temp);
//	}
//	for (int i = 0; i < m; i++)
//	{
//		int temp;
//		cin >> temp;
//		arr2.push_front(temp);
//	}
//	Element* i1 = arr1.head,
//		* i2 = arr2.head;
//	//Сравниваем элементы в массивах, пока не дойдем до конца одного из них
//	while (i1 != NULL && i2 != NULL)
//	{
//		//Если элемент второго массива больше, чем в первом, то добавляем его в первый
//		if (i1->value < i2->value)
//		{
//			arr1.insert(i1, i2->value);
//			if (i2 != NULL) i2 = i2->next;
//		}
//		//Если элемент первого массива больше, то начинаем сравивать следующий
//		else if (i2->value < i1->value)
//		{
//			if (i1 != NULL) i1 = i1->next;
//		}
//		//Если элементы равны, то записываем элемент из второго массива в первый и сравниваем следующие элементы этих массивов
//		else
//		{
//			arr1.insert(i1, i2->value);
//			if (i1 != NULL) i1 = i1->next;
//			if (i2 != NULL) i2 = i2->next;
//		}
//	}
//	//Если первый массив закончился раньше второго, то добавляем оставшиеся элементы в конец
//	if (i2 != NULL)
//		while (i2 != NULL)
//		{
//			arr1.insert(nullptr, i2->value);
//			i2 = i2->next;
//		}
//	arr2.~Array();
//	arr1.print();
//	arr1.~Array();
//}
//
//void task8()
//{
//	int n; //Количество записей
//	cin >> n;
//	Map* records = new Map[1000001]; //Массив записей
//	//Считываем ключ и по нему добавляем запись
//	for (int i = 0; i < n; i++)
//	{
//		int key;
//		cin >> key;
//		string str;
//		cin >> str;
//		if (records[key].key == -1) records[key].key = key;
//		records[key].values.push_back(str);
//	}
//	//Выводим все записи и неотрицательными ключами
//	for (int i = 0; i < 1000001; i++)
//	{
//		if (records[i].key != -1)
//		{
//			for (int j = 0; j < records[i].values.size(); j++)
//			{
//				cout << records[i].key << ' ' << records[i].values[j] << '\n';
//			}
//		}
//	}
//}

void task9()
{
	Array arr;
	int n  //Количество операций
		, size = 0;
	cin >> n;
	for (int i = 0; i < n; i++)
	{		
		int opType; //Тип операции
		cin >> opType;
		switch (opType)
		{
		//Вставляем элемент перед элементом с указанным индексом
		case 0:
			int idx,
				val;
			cin >> idx >> val;
			size += 1;
			arr.insert(idx, val, size);
			break;
		//Выводим элемент с указанным индексом
		case 1:			
			cin >> idx;
			cout << arr[idx].value << '\n';
			break;
		}
	}
}
