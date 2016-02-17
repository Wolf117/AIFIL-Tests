/* Вопрос 2
Напишите код, который решает следующую задачу:
Имеется вектор размера N. Необходимо разделить его на M < N равных частей (то есть чтобы количество элементов в каждой части было одинаковым). 
Части не должны пересекаться и должны покрывать весь вектор (исключение - допускаются промежутки от начала вектора до начала первой части 
и от конда последней части до конца вектора, но в этом случае необходимо добиться, чтобы разница в величине этих промежутков была минимальной).*/

#include <iostream>
#include <vector>

std::vector<int> SplVectToNParts (std::vector<int>::size_type vecorSize, std::vector<int>::size_type &partCount)
{
	std::vector<int> resVect; // вектрр для хранения результата.
	std::vector<int>::size_type partSize; // рамре одной части.
    int beginGap; // длина возможного промежутка от начала до первой части.
	
    if(partCount >= vecorSize)
    {
	resVect.push_back(-1); // введены некорекные данные, сообщаем об ошибке.
        return resVect;
    }

    partSize = vecorSize / partCount;	// вычисляем размер одной части и возможные пропуски с краев вектора.
    beginGap = (vecorSize % partCount) / 2;
	
    for(int  i = 0; i < partCount; i++) //занесение результата в выходной список
    {
        resVect.push_back(beginGap);
        beginGap += partSize;
        resVect.push_back(beginGap - 1);
    }
    return resVect;
}

int main(int argc, char** argv) 
{
	
	std::vector<int> mass; //тестовый пример

    for(int i = 0; i < 24; i++)
        mass.push_back(i);

    std::vector<int>::size_type parts = 5;    
    mass = SplVectToNParts(mass.size(), parts);

    parts = mass.size();
    for(int  i = 0; i < parts; i += 2)
		std::cout << mass.at(i) << "	" << mass.at(i + 1) << std::endl;
		
    std::cin.get();
    return 0;
}
