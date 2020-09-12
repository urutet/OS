#include <iostream>
#include <stdio.h>
#include <string.h>
#include "windows.h"

using namespace std;

void fixed();
void floa();
void complex();
void algExpression();
void brackets();



template< class T >
class Stack {
private:
    int MAX;
    int top;
    T* items;

public:
    Stack(int size) {
        MAX = size;
        top = -1;
        items = new T[MAX];
    }

    ~Stack() { delete[] items; }

    void push(T c) {
        if (full()) {
            cout << "Stack Full!" << endl;
            exit(1);
        }

        items[++top] = c;
    }

    T pop() {
        if (empty()) {
            cout << "Stack Empty!" << endl;
            exit(1);
        }

        return items[top--];
    }

    int getTop() { return top; }

    int empty() { return top == -1; }

    int full() { return top + 1 == MAX; }
};
//Стек — это область оперативной памяти, которая создаётся для каждого потока. Работает в порядке Last In First Out
//в нем хранятся все переменные
//стек быстрее кучи, но обращение происходит только к самому "верхнему" элементу
//чтобы дойти до нужного элемента в стеке, нужно пройти элементы, которые были добавлены в стек перед ним

int main()
{
    int k = 0;
    do
    {
        cout << "1 - Fixed point" << endl;
        cout << "2 - Float" << endl;
        cout << "3 - Complex numbers" << endl;                      //меню
        cout << "4 - Algebraic expression" << endl;
        cout << "5 - Brackets" << endl;
        cout << "99 - Exit" << endl;
        cin >> k;
        switch (k)
        {
        case 1: fixed(); break;
        case 2: floa(); break;
        case 3: complex(); break;
        case 4: algExpression(); break;
        case 5: brackets(); break;
        }
    } while (k != 99);
}


void fixed()
{
    Stack<char> expr(256);
    int state = 0, numOfDots = 0, error = 0, length = 0, top = 0; //state отвечает за соответствие всех введенных символов
    //numOfDots считает кол-во точек, error - кол-во ошибок, length - длина строки, top - вершина стека
    char expression[256], prev = '\0';
    cout << "Enter the number: " << endl;
    getchar();
    cin.getline(expression, 256);
    for (int i = 0; i < strlen(expression); i++)
    {
        expr.push(expression[i]);
    }
    top = strlen(expression);
    length = top;

    while (!expr.empty())
    {
        char symbol = expr.pop();
        if (symbol >= '0' || symbol <= '9' || symbol == '.' || symbol == '-') //соответствие всех символов числу с фикс точкой
        {
            state++;
        }
        if (symbol == '.') //проверка кол-ва точек
        {
            numOfDots++;
        }
        if ((symbol == '.' || symbol == '-') && (prev == '.' || prev == '-')) //проверка синтаксиса (точка или минус не должны быть рядом)
        {
            error++;
        }
        if (symbol == '.' && prev == '/0') //точка не должна быть последним символом
        {
            error++;
        }
        prev = symbol;
                            //проход дальше по стеку
        top--; 
    }

    if (numOfDots != 0 && numOfDots != 1) //если есть более 1 точки, то это не соответствует числу с фикс точкой
        error++;

    if (state == length) //проверка, совпадают ли кол-во "верных" символов длине выражения
    {
        if (error != 0) //проверка на ошибки
            cout << "Error in the expression" << endl;
        else
            cout << "Expression is correct" << endl;
    }
    else
        cout << "Wrong expression" << endl;
}


void floa()
{
    Stack<char> expr(256); // создание стека
    int state = 0, numOfDots = 0, error = 0, length = 0, top = 0, plusCounter = 0, minusCounter = 0, eCounter = 0;
    //state отвечает за соответствие всех введенных символов
    //numOfDots считает кол-во точек, error - кол-во ошибок, length - длина строки, top - вершина стека
    char expression[256], prev = '\0';
    cout << "Enter the number" << endl;
    getchar();
    cin.getline(expression, 256);
    for (int i = 0; i < strlen(expression); i++)
    {
        expr.push(expression[i]); //ввод символа в стек
    }
    top = strlen(expression);
    length = top;

    while (!expr.empty())
    {
        char symbol = expr.pop();
        if (symbol >= '0' || symbol <= '9' || symbol == '.' || symbol == 'e' || symbol == '-' || symbol == '+') //соответствие всех символов числу с плав точкой
        {
            state++;
        }
        if (symbol == '+') //кол-во плюсов
        {
            plusCounter++;
        }
        if (symbol == '-') // кол-во минусов
        {
            minusCounter++;
        }
        if (symbol == 'e') //подсчет exp
            eCounter++;
        if (symbol == '.') // подсчет точек
            numOfDots++;

        if ((symbol == '+' || symbol == '-' || symbol == '.') && (prev == '+' || prev == '-' || prev == '.' || prev == 'e')) //эти символы не могут идти друг за другом
            error++;
        if (symbol == 'e' && prev == 'e') //не может быть 2 exp подряд
            error++;
        
        prev = symbol;
        top--;
    }
    //проверка количества знаков
    if (plusCounter > 2 || minusCounter > 2 || eCounter != 1 || (numOfDots != 1 && numOfDots != 0) || (plusCounter + minusCounter < 1) && (plusCounter + minusCounter > 2))
        error++;
    if (state == length) //проверка, совпадают ли кол-во "верных" символов длине выражения
    {
        if (error != 0) //проверка на ошибки
            cout << "Error in the expression" << endl;
        else
            cout << "Expression is correct" << endl;
    }
    else
        cout << "Wrong expression" << endl;
}


void complex()
{
    Stack<char> expr(256); // создание стека
    int state = 0, numOfDots = 0, error = 0, length = 0, top = 0, plusCounter = 0, minusCounter = 0, iCounter = 0;
    //state отвечает за соответствие всех введенных символов
    //numOfDots считает кол-во точек, error - кол-во ошибок, length - длина строки, top - вершина стека
    char expression[256], prev = '\0';
    cout << "Enter the number" << endl;
    getchar();
    cin.getline(expression, 256);
    for (int i = 0; i < strlen(expression); i++)
    {
        expr.push(expression[i]);
    }
    top = strlen(expression);
    length = top;

    while (!expr.empty())
    {
        char symbol = expr.pop();
        if ((symbol >= '0' && symbol <= '9') || symbol == '.' || symbol == 'i' || symbol == '-') //соответствие всех символов комплексному числу
        {
            state++;
        }
        if (symbol == '+') //подсчет кол-ва плюсов
        {
            plusCounter++;
        }
        if (symbol == '-') //подсчет кол-ва минусов
        {
            minusCounter++;
        }
        if (symbol == 'i') //подсчет кол-ва i
        {
            iCounter++;
        }
        if (symbol == '.') //подсчет кол-ва точек
        {
            numOfDots++;
        }
        prev = symbol;
        top--;
    }
    //проверка количества знаков
    if (plusCounter > 2 || minusCounter > 2 || (iCounter != 1 && iCounter != 0) || (plusCounter + minusCounter < 1) && (plusCounter + minusCounter > 2))
        error++;
    if (state == length) //проверка, совпадают ли кол-во "верных" символов длине выражения
    {
        if (error != 0) //проверка ошибок
            cout << "Error in the expression" << endl;
        else
            cout << "Expression is correct" << endl;
    }
    else
        cout << "Wrong expression" << endl;
}


void algExpression()
{
    Stack<char> expr(256); // создание стека
    int state = 0, error = 0, length = 0, top = 0;
    //state отвечает за соответствие всех введенных символов
    //numOfDots считает кол-во точек, error - кол-во ошибок, length - длина строки, top - вершина стека
    char expression[256], prev = '\0';
    cout << "Enter the number" << endl;
    getchar();
    cin.getline(expression, 256);
    for (int i = 0; i < strlen(expression); i++)
    {
        expr.push(expression[i]);
    }
    top = strlen(expression);
    length = top;

    while (!expr.empty())
    {
        char symbol = expr.pop();
        if ((symbol >= 'A' && symbol <= 'z') || symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/') //соответствие всех символов алгебраическому выражению
        {
            state++;
        }
        if ((symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/') && (prev == '+' || prev == '-' || prev == '*' || prev == '/')) //проверка порядка следования символов (за буквой обязательно операция или наоборот)
        {
            error++;
        }

        if (symbol >= '[' && symbol <= '`')     //между прописными и строчными есть доп символы, которые нужно исключить
            error++;

        if ((symbol >= 'A' && symbol <= 'z') && (prev >= 'A' && prev <= 'z')) //проверка порядка следования символов (за буквой обязательно операция или наоборот)
        {
            error++;
        }

        if ((top == 0 && (symbol == '*' || symbol == '/' || symbol == '+' || symbol == '-'))) //операция не может быть началом выражения
        {
            error++;
        }

        if ((prev == '\0' && (symbol == '*' || symbol == '/' || symbol == '+' || symbol == '-'))) //операция не может быть концом выражения
        {
            error++;
        }

        prev = symbol;
        top--;
    }

    if (state == length) //проверка, совпадают ли кол-во "верных" символов длине выражения
    {
        if (error != 0) //проверка ошибок
            cout << "Error in the expression" << endl;
        else
            cout << "Expression is correct" << endl;
    }
    else
        cout << "Wrong expression" << endl;
}


void brackets()
{
    Stack<char> expr(256); // создание стека
    int state = 0, brackets = 0, error = 0, top = 0, length = 0;
    //state отвечает за соответствие всех введенных символов
    //numOfDots считает кол-во точек, error - кол-во ошибок, length - длина строки, top - вершина стека
    char expression[256], prev = '\0';
    cout << "Enter the expression " << endl;
    getchar();
    cin.getline(expression, 256);
    for (int i = 0; i < strlen(expression); i++)
    {
        expr.push(expression[i]);
    }
    top = strlen(expression);
    length = top;

    while (!expr.empty())
    {
        char symbol = expr.pop();
        if ((symbol >= 'a' && symbol <= 'z') || symbol == '+' || symbol == '-' || symbol == '(' || symbol == ')' || symbol == '*' || symbol == '/') //соответствие всех символов алгебраическому выражению
            state++;

        if (symbol == '(') //подсчет открывающих скобок
            brackets++;
        if (symbol == ')') //подсчет закрывающих скобок (уменьшает выражение)
            brackets--;

        if (prev == '\0' && symbol == '(') //закрывающая скобка не может быть первой
            error++;
        if (top == 0 && symbol == ')') //открывающая скобка не может быть последней
            error++;
        //if (prev == '(' && symbol == ')')             //Выражение ())(() пройдет проверку, но условие убьет верные
        //                                                //выражения типа ()()
        //                                                
        //    error++;

        prev = symbol;
        top--;
    }

    if (brackets != 0) //проверка количества скобок (0, если количество открывающих и закрывающих совпадает)
        error++;

    if (state == length) //проверка, совпадают ли кол-во "верных" символов длине выражения
    {
        if (error != 0) //проверка ошибок
            cout << "Error in the expression" << endl;
        else
            cout << "Expression is correct" << endl;
    }
    else
        cout << "Wrong expression" << endl;
        
}