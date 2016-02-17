﻿/*Вопрос 1
Напишите функцию, которая перебирает натуральные числа от 1 до N включительно и раскладывает каждое число на простые множители.
Результат можно выводить на экран либо копить в любой структуре данных.*/



/*Поскольку в условии не сказано о том на сколько большим может быть N и как бистро должно происходить выполнение функции, был выбран именно этот алгоритм.
Он крайне прост и достаточно эффективен, для небольших чисел. Однако, при очень больших N и жестких требованиях к быстродействию, следует применять более сложные алгоритмы*/
#include <iostream>
void fact(long long &N)
{

    long long curNum; // текшее натуральное число
    long long d;// текущий делитель
    long long i;// натураль7ное число для вычисления делителя по формуле(6i+-1)
    bool minusFalg;// флаг для вычисления делителя на кодом шаге

    for(int i = 1; i  < 4; i++) //выводим 1 и первые простые числа.
        std::cout << i << " : " << std::endl;

    for(long long num = 4; num <= N; num++)
    {
        curNum = num;
        std::cout << curNum << ": = ";
        d = 2;
        i = 1;
        minusFalg = true;
        while(d * d <= curNum)
        {
            if(curNum % d == 0) //проверяем делитяся ли чичло на текуций делитель
            {
                curNum /= d;
                std::cout << d << " * ";
            }
            else
                if(d == 2) //тривиальный шаг, для проверки делителя 3.
                    d = 3;
                else
                    if(minusFalg) //шаг по формуле 6i -+ 1;
                    {
                        d = 6 * i - 1;
                        minusFalg = false;
                    }
                    else
                    {
                        d = 6 * i + 1;
                        i += 1;
                        minusFalg = true;
                    }
        }
        if(curNum > 1) // вывод последненго множителя, если нужно
            std::cout << curNum << std::endl;
    }
}


int main(int argc, char** argv) 
{
	
    long long N = 500; //тестовый пример

    fact(N);
    
    std::cin.get();
    return 0;
}