/*Вопрос 3*/


#include <iostream>
#include <string>
#include <vector>
#include "string.h"

enum {no_argument, required_argument, optional_argument};

struct option
{
    std::string name;
    int hasArg;
    bool required;
};

struct parsedOption
{
    std::string name;
    std::string value;
};

std::string generateHelpMessage(std::vector<option> *optList)
{
    std::string resString;
    std::string bufStr;
    for(std::vector<option>::size_type i = 0; i < optList->size(); i++)
    {
	bufStr = optList->at(i).name;
	bufStr = bufStr;
	if(optList->at(i).hasArg != no_argument)
	{
	    if(optList->at(i).hasArg == optional_argument)
		bufStr = bufStr + " [argument] ";
	    else
		bufStr = bufStr + " argument ";
	}

	if(i % 4 == 0)
	   resString = resString + "\n";

	if(!optList->at(i).required)
	    resString = resString + "[" + bufStr + "] ";
	else
	    resString = resString + bufStr + " ";
    }
    return resString;
}
std::vector<parsedOption> mygetop(int argc, char *argv[], std::vector<option> *optList)
{
    std::vector<parsedOption> resList;

    if(argc < 1 || !argv || !optList) //не корректные полученные данные
	return resList;

    parsedOption parsOpt;

    parsOpt.name = "file name";     //запоминаем имя программы
    parsOpt.value = *argv;
    resList.push_back(parsOpt);

    for(int pos = 1; pos < argc;)
    {
	if(argv[pos][0] != '-' || argv[pos][1] != '-')   //параметр не соотвествует формату
	{
	    resList.resize(1);
	    resList.at(0).name = "error";
	    resList.at(0).value = "wrong option format";
	    return resList;
	}
	else
	{
	    char *curOpt = argv[pos] += 2; //пропускаем "--"
	    char *hasEqual = NULL;
	    int curOptLen = 0;

	    if(*curOpt == '\0') //пустой параметр
	    {
		resList.resize(1);
		resList.at(0).name = "error";
		resList.at(0).value = "empty option";
		return resList;
	    }

	    hasEqual = strchr(curOpt, '='); //проверяем на наличие знака = (текщая строка может содержать и параметр и его аргумент)
	    if(hasEqual)//вычисляем длину параметра
	    {
		curOptLen = hasEqual - curOpt;
		hasEqual += 1;
	    }
	    else
		curOptLen = strlen(curOpt);

	    std::vector<struct option>::size_type i = 0; // ищем параметр в полученом списке
	    for(bool stopFlag = false; i < optList->size() && !stopFlag;)
		if(!strncmp(curOpt, optList->at(i).name.c_str(), curOptLen) && (curOptLen == (int)optList->at(i).name.size()))
		    stopFlag = true;
		else
		    i += 1;

	    if(i < optList->size()) //параметр найден  в списке
	    {
		if(optList->at(i).name == "help")
		{
		    resList.resize(1);
		    resList.at(0).name = "help message";
		    resList.at(0).value = generateHelpMessage(optList);
		    return resList;
		}

		parsOpt.value.clear();
		parsOpt.name = curOpt;
		parsOpt.name.resize(curOptLen);
		if(optList->at(i).hasArg != no_argument)
		{
		    if(hasEqual)
			parsOpt.value = hasEqual;
		    else
		    {
			if((pos + 1) < argc)
			    if((argv[pos + 1][0] != '-') && (argv[pos + 1][1] != '-'))
				parsOpt.value = argv[++pos];
		    }

		    if(optList->at(i).hasArg == required_argument && parsOpt.value.empty()) //требовался параметр, но его не было
		    {
			resList.resize(1);
			resList.at(0).name = "error";
			resList.at(0).value = optList->at(i).name + " no required argument";
			return resList;
		    }
		}
		resList.push_back(parsOpt);
		pos += 1;
	    }
	    else
	    {
		resList.resize(1);
		resList.at(0).name = "error";
		resList.at(0).value = curOpt;
		resList.at(0).value.resize(curOptLen);
		resList.at(0).value = resList.at(0).value + " not in the options";
		return resList;
	    }
	}
    }
    return resList;
}

int main(int argc, char** argv)
{

    std::vector<option> optList; //тестовый пример
    option newOption;

    newOption.name = "one";
    newOption.hasArg = required_argument;
    newOption.required = true;
    optList.push_back(newOption);

    newOption.name = "two";
    newOption.hasArg = optional_argument;
    newOption.required = false;
    optList.push_back(newOption);

    newOption.name = "three";
    newOption.hasArg = no_argument;
    newOption.required = true;
    optList.push_back(newOption);

    newOption.name = "four";
    newOption.hasArg = optional_argument;
    newOption.required = false;
    optList.push_back(newOption);

    newOption.name = "help";
    newOption.hasArg = no_argument;
    newOption.required = false;
    optList.push_back(newOption);

    std::vector<parsedOption> parsed = mygetop(argc, argv, &optList);

    for(std::vector<parsedOption>::size_type i = 0; i < parsed.size(); i++)
	std::cout << parsed.at(i).name << "     " << parsed.at(i).value <<std::endl;

    std::cin.get();
    return 0;
}


