/*Вопрос 4
Имеется простой односвязный список размера N. Необходимо реализовать алгоритм, который перепаковывает список так,
чтобы за первым элеметом следовал последний, затем второй, затем предпоследний и т. д. Пример работы алгоритма:
исходный список: 1-2-3-4-5-6-7-8
перепакованный список: 1-8-2-7-3-6-4-5.
Оценить сложность предложенного алгоритма.*/


/*Для выполениея данного алгоритма потребуется память для n/2 указателей типа список
 и 2.5n операций присвоения (из которых n - предворитльные манипуляции, а 1.5n - сама перестановка)*/


#include <iostream>
#include <stack>

struct testList // простейлая структура для соданиея простого списка
{
    int data;
    testList *next;
};

bool RepackList(testList **listHead, std::stack<testList*>::size_type &listSize)
{

    if(listSize < 2)
        return false;

    std::stack<testList*> bufStack; //буферный стек для храрнения указателей второй половины списка, при перепаковке
    std::stack<testList*>::size_type midleIndex; // индекс  первого элмента, который будет переммещен в списке
    testList* curListElement = *listHead;

    if(listSize % 2)
        midleIndex = listSize / 2 + 1;
    else
       midleIndex = listSize / 2;

    for(std::stack<testList*>::size_type i = 0; i < midleIndex && curListElement; i++, curListElement = curListElement->next); //поиск середины списка

    if(!curListElement) //проверка возможной не корректности длины списка
        return false;

    while (curListElement) // запись указателей на вторую половину списка
    {
        bufStack.push(curListElement);
        curListElement = curListElement->next;
    }

    if(bufStack.size() != (listSize / 2)) //проверка возможной не корректности длины списка
        return false;

    curListElement = *listHead;
    while (!bufStack.empty()) //сама перепаковка
    {
        bufStack.top()->next = curListElement->next;
        curListElement->next = bufStack.top();
        curListElement = curListElement->next->next;
        bufStack.pop();
    }
    curListElement->next = NULL;
    return true;
}

int main(int argc, char** argv) 
{
	testList *cur, *first; //тестовый пример
    std::stack<testList*>::size_type size = 8;

    first = new testList;
    first->data = 1;
    cur = first;
    for(std::stack<testList*>::size_type i = 1; i < size; i++)
    {
        cur->next = new testList;
        cur = cur->next;
        cur->data = i + 1;
    }
    cur->next = NULL;

    bool mist = RepackList(&first, size);
    if(mist)
    {
        cur = first;
        while(cur)
        {
            std::cout << " - " << cur->data;
            cur = cur->next;
        }
    }
    else
	std::cout << mist;
    std::cin.get();
    return 0;
}
