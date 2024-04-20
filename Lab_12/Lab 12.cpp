#include <iostream>
#include <stack>
#include <vector>
#include <map>
#include <sstream>
#include <string>
#include <fstream>
using namespace std;


//Объявление вспомогательных функций

int priority(char op);

double applyOp(double a, double b, char op);

double evaluate(string expression);

bool isLISP(string str, map<char, int> priorities);

bool isLISP_1(string str, int * pArrCount =NULL);

//Класс, через который реализуется очередь
class Queue 
{
public:
	int max; //Максимальное коичество элементов в очереди
	int head;//Номер элемента, являющегося началом очереди
	int tail;//Номер элемента, являющегося концом очереди
	int* arr; //Массив, через который реалезуется очередь

public:
	//Конструктор очереди 
	Queue(int size) 
	{
		head = -1;
		tail = 0;
		max = size;
		arr = new int[size];
	}

	//Деструктор очереди
	~Queue() { delete[] arr; }

	//Показывает, пустой ли массив
	bool empty() { return (head == -1); } 

	//Показывает, переполнена ли память
	bool full() { return ((head == 0 && tail == max - 1) || head == tail + 1); }

	//Добавляет элемент в начало очереди
	void push_front(int item) 
	{
		if (full()) return;
		if (head == -1) head = tail = 0;
		else if (head == 0) head = max - 1;
		else head -= 1;
		arr[head] = item;
	}
	
	//Добавляет элемент в конец очереди
	void push_back(int item) 
	{
		if (full()) return;
		if (head == -1) head = tail = 0;
		else if (tail == max - 1) { tail = 0; }
		else tail += 1;
		arr[tail] = item;
	}

	//Возвращает и удаляет первый элемент очереди
	int pop_front() 
	{
		if (empty()) return 0;
		int item = arr[head];
		if (head == tail) head = tail = -1;
		else if (head == max - 1) head = 0;
		else head += 1;
		return item;
	}

	//Возвращает и удаляет последний элемент очереди
	int pop_back()
	{
		if (empty()) return 0;
		int item = arr[tail];
		if (head == tail) head = tail = -1;
		else if (tail == 0) tail = max - 1;
		else tail -= 1;
		return item;
	}

	//Возвращает размер очереди
	int size() 
	{
		if (empty()) return 0;
		if (head <= tail) return tail - head + 1;
		return max - head + tail + 1;
	}

	//Выводит и удаляет очередь
	void printAndClear() 
	{
		int s = size();
		cout << s << " ";
		for (int i = 0; i < s; i++) cout << pop_front() << ' ';
		cout << endl;
	}

};



//Необходимо написать программу, переводящую выражение, записанное в инфиксной форме, в постфиксную(обратную польскую) запись.
//Операндами в выражении могут быть только маленькие латинские буквы. Операции —, + , ˘  ,*, / .
void task1();
//В единственной строке входного файла записано выражение в обратной польской записи.
//Операнды — целые числа.Числа и знаки операций разделены пробелами.Длина строки не превосходит 2000.
void task2();
// Необходимо написать программу, моделирующую систему асинхронного сбора данных.Экспериментальные данные берутся из файла, содержащего целые числа.
//В том случае, если считано положительное число 𝑅, то следующие 𝑅 чисел относятся к экспериментальным данным, которые необходимо записать в кольцевой буфер(в конец очереди).
//В том случае, если встретилось отрицательное число 𝐾, то необходимо забрать −𝐾 первых ячеек данных из буфера и распечатать их среднее арифметическое.
// В случае, когда буфер переполнился, или в нем не оказалось данных, необходимо выдать диагностическое сообщение и продолжить работу.
void task3();
//Для перемешивания колод нужно выполнить 𝑀 заданных операций, каждая операция заключается в перекладывании одной карты.Каждая операция обозначается одной шестнадцатеричной цифрой в диапазоне от 0 до F(15) включительно.
//Операция определяется значениями четырёх битов в двоичной записи этой цифры :
// Если старший бит(8) единичный, то нужно взять карту из правой колоды, а иначе —
//из левой колоды.
// Если предпоследний бит(4) единичный, то нужно взять карту снизу колоды, а иначе
//— сверху колоды.
// Если второй бит(2) единичный, то нужно положить карту в правую колоды, а иначе
//— в левую.
// Если младший бит(1) единичный, то нужно положить карту в колоду снизу, а иначе
//— сверху.
//Если в какой - то момент нужно выполнить операцию, которая предписывает взять карту из
//пустой колоды, то такую операцию нужно пропустить, ничего не делая.
void task4();
//В данной задаче предлагается вычислить заданное арифметическое выражение. 
//Выражение состоит из целочисленных констант, над которыми выполняются операции сложения, вычитания, умножения и деления.
//Части выражения могут быть заключены в скобки. Унарный минус разрешается, если непосредственно до него нет знака другой операции. Между токенами может быть любое количество пробелов, а может и не быть пробелов.
//Вычислять выражение нужно в вещественных числах.Гарантируется, что не будет деления на ноль и пр
void task5();
//Необходимо определить для данной скобочной последовательности, является ли она корректной программой для Uncommon LISP v2
//пустая строка — правильная скобочная последовательность;
// правильная скобочная последовательность, взятая в скобки одного типа — правильная скобочная последовательность;
// правильная скобочная последовательность, к которой приписана слева или справа правильная скобочная последовательность — тоже правильная скобочная последовательность.
void task6();



int main()
{
    //task1();
    //task2();
    //task3();
    //task4();
    //task5();
    task6();
}

void task1()
{   
    //map с приоритетами операций
    map<char, int> prior = { {'(' , 1} , {')' , 2} , {'-' , 3} ,
                            {'+' ,  3} , {'˘' , 4} , {'*' , 5} , {'/' , 5} };
    string infix, //Изначальная строка
        postfix,  //Результирующая строка в постфиксном виде
        stack;    //Стек, в котором хранятся операции
    cin >> infix;
    //Строим строку в постфиксном виде
    for (int i = 0; i < infix.size(); i++)
    {
        if (infix[i] == '(') stack.insert(stack.begin(), '(');
        else if (infix[i] == ')')
        {
            while (stack[0] != '(')
            {
                postfix += stack[0];
                stack.erase(stack.begin());
            }
            stack.erase(stack.begin());
        }
        else if (infix[i] >= 'a' && infix[i] <= 'z')
        {
            postfix += infix[i];
        }
        else
        {
            stack.insert(stack.begin(), infix[i]);
            if (stack.size() > 1)
            {
                while (prior[stack[1]] >= prior[stack[0]])
                {
                    postfix += stack[1];
                    stack.erase(stack.begin() + 1);
                }
            }
            
        }
    }
    //Если что-то осталось в стеке, то записываем все это в результирующую строку
    if (!stack.empty())
    {
        while (!stack.empty())
        {
            postfix += stack[0];
            stack.erase(stack.begin());
        }
    }
    cout << postfix;
}

void task2()
{    
    string postfix; //Строка, которая поступает в постфиксной записи
    vector<int> stack; //Стек, в котором хранятся числа, считанные из строки в постфиксной записи
    while (cin >> postfix)
    {
        stringstream ss; //Строковый поток, с помощью которого переводим строку в число
        ss << postfix;
        int numand;
        //Если считали число, то помещаем его в стек
        if (ss >> numand) stack.insert(stack.begin(), numand);
        //Иначе проводим соотвествующую операцию над двумя первыми числами
        else
        {
            switch (postfix[0])
            {
            case '+':                
                stack.insert(stack.begin(), stack[1] + stack[0]);
                stack.erase(stack.begin() + 1);
                stack.erase(stack.begin() + 1);
                break;
            case '-':
                stack.insert(stack.begin(), stack[1] - stack[0]);
                stack.erase(stack.begin() + 1);
                stack.erase(stack.begin() + 1);
                break;
            case '*':
                stack.insert(stack.begin(), stack[1] * stack[0]);
                stack.erase(stack.begin() + 1);
                stack.erase(stack.begin() + 1);
                break;
            case '/':
                stack.insert(stack.begin(), stack[1] / stack[0]);
                stack.erase(stack.begin() + 1);
                stack.erase(stack.begin() + 1);
                break;
            }            
        }
        postfix.clear();
    }
    cout << stack[0];
}

void task3()
{
    fstream fin("input.txt", ios::in);
    int n, //длина очереди  
        m; //Количество элементов в очереди
    fin >> n >> m;
    int r, //
        op; //Задает операцию, которая будет выполняться
    Queue q(n); //Буфер
    for (int i = 0; i < m; i++)
    {
        fin >> op;    
        //Если число больше 0, то записываем числа в буфер
        if (op > 0) 
        {            
            m -= op;                        
            do
            {
                //Если не хвататет памяти для всех чисел, то выводим сообщение и считываем оставшиеся числа с консоли, но никуда не записываем
                if (q.full())
                {
                    cout << "Memory overflow" << endl; 
                    while (op--) fin >> r;
                    break;
                }
                fin >> r;
                q.push_back(r);//запись в конец
            } while (--op);
        }
        //Если число меньше 0, то считается среднее арифметическое 
        else if (op < 0) 
        {
           int sum = 0, //Сумма чисел
               amm = 0; //Количество чисел
            op = -op;
            //Если в буфере достаточно чисел, то выводится среднее арифметическое
            if (n <= q.size())
            {
                for (int i = 0; i < op; i++)
                {
                    if (q.empty()) break;
                    sum += q.arr[q.head];
                    q.pop_front();
                    amm += 1;
                }
                cout << sum / amm << endl;
            }
            //Если в буфере недостаточно чисел, то выводится среднее арифметическое стольких чисел, сколько есть в буфере и выводит ошибку
            else
            {
                for (int i = 0; i < q.size(); i++)
                {
                    if (q.empty()) break;
                    sum += q.arr[q.head];
                    q.pop_front();
                    amm += 1;
                }
                if (!q.empty()) cout << sum / amm << endl;
                cout << "Empty queue" << endl;
            }                                     
        }
    }
}

void task4()
{    
    int n, //Количество запросов
        s, //Количество элементов
        operation;
    cin >> s >> n;
    Queue queR(s * 2 + 1), queL(s * 2 + 1); //Cоздаем колоды
    //Заполняем колоды
    for (int i = 1; i <= s; i++) 
    {
        queL.push_back(i);
        queR.push_back(-i);
    }
    cin.get();
    for (int i = 0; i < n; i++)
    {
        operation = cin.get();
        if (operation >= '0' && operation <= '9') operation -= 48;
        else operation -= 55;
        if (operation == 0 || operation == 5 || operation == 10 || operation == 15) continue;
        //Проверки на бит
        int takeR = operation & 8, takeUdr = operation & 4
            , putR = operation & 2, putud = operation & 1;

        operation = takeR ? (takeUdr ? queR.pop_back() : queR.pop_front()) : (takeUdr ? queL.pop_back() : queL.pop_front());
        if (operation) putR ? (putud ? queR.push_back(operation) : queR.push_front(operation)) : (putud ? queL.push_back(operation) : queL.push_front(operation));

    }
    queL.printAndClear();//Выводим и очищаем левую колоду
    queR.printAndClear();//Выводим и очищаем правую клоду
}

void task5()
{
    string preInfix,
        tmp,
        infix;     
    while (cin >> tmp) preInfix += tmp;
    if (!preInfix.empty())
    {
        infix.push_back(preInfix[0]);
        for (int i = 1; i < preInfix.length(); i++)
        {
            if (isdigit(preInfix[i]) || preInfix[i] == '(' || preInfix[i] == ')') infix.push_back(preInfix[i]);
            else if (preInfix[i] == '-')
            {
                if (preInfix[i - 1] == '(') infix.push_back(preInfix[i]);
                else
                {
                    infix.push_back(' ');
                    infix.push_back(preInfix[i]);
                    infix.push_back(' ');
                }
            }
            else
            {
                infix.push_back(' ');
                infix.push_back(preInfix[i]);
                infix.push_back(' ');
            }
        }
        double result = evaluate(infix);
        printf("%.20lf", result);
    }
}

void task6()
{
    int n;
    cin >> n;
    string str;    

    map<char, int> priorities = { {'(',1} , {')',-1} , {'[',2} ,{']',-2},
        {'<',3} ,{'>',-3} ,{'{',4},{'}',-4} };
    getline(cin, str);
    for (int i = 0; i < n; i++)
    {
        getline(cin, str);
        isLISP(str, priorities) ? cout << "T" << endl : cout << "NIL" << endl;
/*
        int ArrCount[4] = { 0, 0, 0, 0 };
        if (isLISP_1(str, ArrCount))
        {
            cout << "T" << endl;
        }
        else
        {
            cout << "NIL" << endl;
        }

    }
*/
}

// Функция для получения приоритета оператора
int priority(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;    
    return 0;
}

// Функция для выполнения арифметической операции
double applyOp(double a, double b, char op)
{
    switch (op) {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    }
    return 0;
}

// Функция для вычисления значения выражения в инфиксной записи
double evaluate(string expression)
{
    stack<double> values;      // стек для хранения чисел
    stack<char> operators;  // стек для хранения операторов

    for (int i = 0; i < expression.length(); i++) {
        // Пропускаем пробелы
        if (expression[i] == ' ')
            continue;

        // Если текущий символ - число или минус, то извлекаем все цифры и помещаем число в стек значений
        if (isdigit(expression[i]) || expression[i] == '-')
        {            
            bool isNegative = false;
            if (expression[i] == '-')
            {
                isNegative = true;
                i++;
            }
            //Если минус операция, то выполняем операции, пока приоритет операции в стеке выше либо равен приоритету нашей операции
            if (isNegative && expression[i] == ' ')
            {
                i--;
                while (!operators.empty() && priority(operators.top()) >= priority(expression[i])) {
                    double val2 = values.top();
                    values.pop();

                    double val1 = values.top();
                    values.pop();

                    char op = operators.top();
                    operators.pop();

                    values.push(applyOp(val1, val2, op));
                }

                operators.push(expression[i]);
                continue;
            }
            //Если унарный минус стоит перед выражением
            if (isNegative && expression[i] == '(')
            {
                i++; //Пропускаем открывающую скобку
                string subExpr; //Подвыражение в скобках, которое мы считаем
                int bracketAmm = 0;
                while (true && expression[i] != '\n' && expression[i] != '\0')
                {
                    if (expression[i] == '(') bracketAmm++;
                    else if (expression[i] == ')' && bracketAmm > 0) bracketAmm--;
                    else if (expression[i] == ')' && bracketAmm == 0) break;
                    subExpr += expression[i];
                    i++;
                }                
                double val = -evaluate(subExpr);
                values.push(val);
                continue;
            }
            double val = 0;
            while (i < expression.length() && isdigit(expression[i])) {
                val = (val * 10) + (expression[i] - '0');
                i++;
            }
            if (isNegative) val = -val;
            values.push(val);
            i--;
        }

        // Если текущий символ - открывающая скобка, то помещаем ее в стек операторов
        else if (expression[i] == '(') {
            operators.push(expression[i]);
        }

        // Если текущий символ - закрывающая скобка, то выполняем все операции до открывающей скобки
        else if (expression[i] == ')') {
            while (!operators.empty() && operators.top() != '(') {
                double val2 = values.top();
                values.pop();

                double val1 = values.top();
                values.pop();

                char op = operators.top();
                operators.pop();

                values.push(applyOp(val1, val2, op));
            }
            //Удаляем открывающую скобку
            operators.pop();
        }

        // Если текущий символ - оператор, то выполняем операции, пока приоритет операции в стеке выше либо равен приоритету нашей операции
        else {
            while (!operators.empty() && priority(operators.top()) >= priority(expression[i])) {
                double val2 = values.top();
                values.pop();

                double val1 = values.top();
                values.pop();

                char op = operators.top();
                operators.pop();

                values.push(applyOp(val1, val2, op));
            }

            operators.push(expression[i]);
        }
    }
    // Выполняем оставшиеся операции
    while (!operators.empty()) {
        double val2 = values.top();
        values.pop();

        double val1 = values.top();
        values.pop();

        char op = operators.top();
        operators.pop();

        values.push(applyOp(val1, val2, op));
    }
    return values.top();
}

//Показывает, можно ли из заданной строки сделать правильную скобочную последовательность
bool isLISP(string str, map<char,int> priorities)
{
    if (str.empty()) return true; //Если строка пустая, то она правильная
    if (priorities[str[0]] < 0) return false; //Если на 1 месте стоит закрывающая скобка, то нельзя составить
    if (priorities[str.back()] > 0) return false; //Если на 1 месте стоит закрывающая скобка, то нельзя составить
    if (str.size() % 2 != 0) return false; //Если количество скобок нечетное, то нельзя составить
    //Счетчики для скобок
    int roundAmm = 0
        , arrowAmm = 0
        , squareAmm = 0
        , braceAmm = 0;
    //Проверяем первый символ
    switch (str[0])
    {
    case '(':
        roundAmm += 1;
        break;
    case ')':
        roundAmm -= 1;
        break;
    case '<':
        arrowAmm += 1;
        break;
    case '>':
        arrowAmm -= 1;
        break;
    case '[':
        squareAmm += 1;
        break;
    case ']':
        squareAmm -= 1;
        break;
    case '{':
        braceAmm += 1;
        break;
    case '}':
        braceAmm -= 1;
        break;
    }

    for (int i = 1; i < str.length() - 1; i++)
    {
        //Если открывающая скобка зажата между закрывающими, и при этом скобка ещё не стоит в своей паре, то нельзя составить правильную последовательность
        if (priorities[str[i - 1]] < 0 && priorities[str[i + 1]] < 0 && priorities[str[i]] > 0)
        {
            bool flag = false;
            for (int j = i + 1; j < str.length(); j++)
            {
                if (priorities[str[j]] > 0) return false;
                if (priorities[str[j]] == -priorities[str[i]])
                {
                    flag = true;
                    break;
                }
                if (flag) return false;
            }
        }
        //Если закрывающая скобка зажата между открывающимися, и при этом скобка ещё не стоит в своей паре, то нельзя составить правильную последовательность
        else if (priorities[str[i - 1]] > 0 && priorities[str[i + 1]] > 0 && priorities[str[i]] < 0)
        {
            for (int j = i - 1; j >= 0; j--)
            {
                bool flag = false;
                if (priorities[str[j]] < 0) return false;
                if (priorities[str[j]] == -priorities[str[i]])
                {
                    flag = true;
                    break;
                }
                if (flag) return false;
            }
        }
            
        switch (str[i])
        {
        case '(':
            roundAmm += 1;
            break;
        case ')':
            roundAmm -= 1;
            break;
        case '<':
            arrowAmm += 1;
            break;
        case '>':
            arrowAmm -= 1;
            break;
        case '[':
            squareAmm += 1;
            break;
        case ']':
            squareAmm -= 1;
            break;
        case '{':
            braceAmm += 1;
            break;
        case '}':
            braceAmm -= 1;
            break;
        }
        //Если мы встретили больше закрывающих скобок какого-либо вида, чем открывающих на своем пути, то нельзя составить правильную последовательность
        if (roundAmm < 0 || arrowAmm < 0 || squareAmm < 0 || braceAmm < 0)
            return false;        
    }

    //Проверяем последний символ
    switch (str.back())
    {
    case '(':
        roundAmm += 1;
        break;
    case ')':
        roundAmm -= 1;
        break;
    case '<':
        arrowAmm += 1;
        break;
    case '>':
        arrowAmm -= 1;
        break;
    case '[':
        squareAmm += 1;
        break;
    case ']':
        squareAmm -= 1;
        break;
    case '{':
        braceAmm += 1;
        break;
    case '}':
        braceAmm -= 1;
        break;
    }
    //Если правильное соотношение скобок и остальные проверки прошли, то последовательность можно сделать правильноый
    if (roundAmm == 0 && arrowAmm == 0 && squareAmm == 0 && braceAmm == 0)
        return true;
    //Если соотношение неправильное, то последовательность нельзя сделать правильноый
    else return false;
}

bool isLISP_1(string str, int * pArrCount)
{
    if (str.empty()) return true; //Если строка пустая, то она правильная
    for (int i = 0; i < str.length(); i++)
    {
        // Задаем шаг
        int     nStep = 1;
        // Индекс счетчика
        int     nCountIndex = -1;
        // Разбираем символ
        switch (str[i])
        {
        case '(':
        case ')':
            nCountIndex=0;
            if (str[i] == ')')nStep = -1;
            break;
        case '<':
        case '>':
            nCountIndex = 1;
            if (str[i] == '>')nStep = -1;
            break;
        case '[':
        case ']':
            nCountIndex = 2;
            if (str[i] == ']')nStep = -1;
            break;
        case '{':
        case '}':
            nCountIndex = 3;
            if (str[i] == '}')nStep = -1;
            break;
        }
        if (nCountIndex!=-1)
        {
            // Значит символ значащий
            pArrCount[nCountIndex] += nStep;
            if (pArrCount[nCountIndex] < 0)return false;
        }
    }
    // Когда прошли всю строку проверям счетчики, они все должны быть равны нулю
    for (int i = 0; i < 4; i++)
    {
        if (pArrCount[i] != 0)return false;
    }
    // Все Ок!
    return true;


/*
    if (priorities[str[0]] < 0) return false; //Если на 1 месте стоит закрывающая скобка, то нельзя составить
    if (priorities[str.back()] > 0) return false; //Если на 1 месте стоит закрывающая скобка, то нельзя составить
    if (str.size() % 2 != 0) return false; //Если количество скобок нечетное, то нельзя составить
    //Счетчики для скобок
    int roundAmm = 0
        , arrowAmm = 0
        , squareAmm = 0
        , braceAmm = 0;
    //Проверяем первый символ
    switch (str[0])
    {
    case '(':
        roundAmm += 1;
        break;
    case ')':
        roundAmm -= 1;
        break;
    case '<':
        arrowAmm += 1;
        break;
    case '>':
        arrowAmm -= 1;
        break;
    case '[':
        squareAmm += 1;
        break;
    case ']':
        squareAmm -= 1;
        break;
    case '{':
        braceAmm += 1;
        break;
    case '}':
        braceAmm -= 1;
        break;
    }

    for (int i = 1; i < str.length() - 1; i++)
    {
        //Если открывающая скобка зажата между закрывающими, и при этом скобка ещё не стоит в своей паре, то нельзя составить правильную последовательность
        if (priorities[str[i - 1]] < 0 && priorities[str[i + 1]] < 0 && priorities[str[i]] > 0)
        {
            bool flag = false;
            for (int j = i + 1; j < str.length(); j++)
            {
                if (priorities[str[j]] > 0) return false;
                if (priorities[str[j]] == -priorities[str[i]])
                {
                    flag = true;
                    break;
                }
                if (flag) return false;
            }
        }
        //Если закрывающая скобка зажата между открывающимися, и при этом скобка ещё не стоит в своей паре, то нельзя составить правильную последовательность
        else if (priorities[str[i - 1]] > 0 && priorities[str[i + 1]] > 0 && priorities[str[i]] < 0)
        {
            for (int j = i - 1; j >= 0; j--)
            {
                bool flag = false;
                if (priorities[str[j]] < 0) return false;
                if (priorities[str[j]] == -priorities[str[i]])
                {
                    flag = true;
                    break;
                }
                if (flag) return false;
            }
        }

        switch (str[i])
        {
        case '(':
            roundAmm += 1;
            break;
        case ')':
            roundAmm -= 1;
            break;
        case '<':
            arrowAmm += 1;
            break;
        case '>':
            arrowAmm -= 1;
            break;
        case '[':
            squareAmm += 1;
            break;
        case ']':
            squareAmm -= 1;
            break;
        case '{':
            braceAmm += 1;
            break;
        case '}':
            braceAmm -= 1;
            break;
        }
        //Если мы встретили больше закрывающих скобок какого-либо вида, чем открывающих на своем пути, то нельзя составить правильную последовательность
        if (roundAmm < 0 || arrowAmm < 0 || squareAmm < 0 || braceAmm < 0)
            return false;
    }

    //Проверяем последний символ
    switch (str.back())
    {
    case '(':
        roundAmm += 1;
        break;
    case ')':
        roundAmm -= 1;
        break;
    case '<':
        arrowAmm += 1;
        break;
    case '>':
        arrowAmm -= 1;
        break;
    case '[':
        squareAmm += 1;
        break;
    case ']':
        squareAmm -= 1;
        break;
    case '{':
        braceAmm += 1;
        break;
    case '}':
        braceAmm -= 1;
        break;
    }
    //Если правильное соотношение скобок и остальные проверки прошли, то последовательность можно сделать правильноый
    if (roundAmm == 0 && arrowAmm == 0 && squareAmm == 0 && braceAmm == 0)
        return true;
    //Если соотношение неправильное, то последовательность нельзя сделать правильноый
    else return false;
*/
}