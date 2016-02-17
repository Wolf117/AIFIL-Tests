/*Данный алгоритм это реализация метода оптимизации хука-дживса.
Он использовался в моей дипломной работе на тему:
"Разработка программы оптимизации параметров системы виброудароизоляции конструкции радиоэлектронной аппаратуры"
Собственно этот алгоритм и отвечал за оптимизацию. И являлся частью методов класса отвечающего за вычисления ключевых параметров.
Он был написан в Qt с и использованием его библиотек */

void calcModule::startOptimization() //метод оптимизации хуко-дживса
{
    double z, z1; //значения целевой функции
    bool bPointFlag; //флаг базовой точки
    bool decrFlag;   //флаг уменьшения целевой функции
    double *basePoint, *lastBasePoint, *newMinPont;
    double step;
    double minStep = 1e-3;
    double startStep;
    struct demper *demper; //структура храняцаая данные об оптимизируеом объекте
    int massCount = demperList.size();

    curStepParam[1] = 0; //массив парметров состояния процеса передавемых в основной поток

    basePoint = new double[massCount]; //инициализация стартовых данных
    lastBasePoint = new double[massCount];
    newMinPont = new double[massCount];
    for(int i = 0; i < massCount; i++)
    {
	basePoint[i] = demperList.at(i)->paramTn[directInflu];
	lastBasePoint[i] = basePoint[i];
	newMinPont[i] = basePoint[i];
    }

    z = optStep(); // вычисление значения целевой функции
    curStepParam[2] = z;
    bPointFlag = true;
    decrFlag = false;
    startStep = basePoint[0] / 100;
    step = startStep;

    while(step >= minStep && !stopFlag)
    {
	decrFlag = false;
	step = startStep;
	while(step >= minStep && !decrFlag)
	{
	    for(int i = 0; i < massCount; i++) //вычисляем значения целевой функции +шагом и -шагом, Меньшее станет возможной новой базовой точкой
	    {
	       demper = demperList.at(i);
	       demper->paramTn[directInflu] = newMinPont[i] + step;
	       demper->recalcParam(directInflu, temp3);
	       z1 = optStep();
	       if(z1 >= z)
	       {
		   demper->paramTn[directInflu] = newMinPont[i] - step;
		   demper->recalcParam(directInflu, temp3);
		   z1 = optStep();
		   if(z1 >= z)
		   {
		       demper->paramTn[directInflu] = newMinPont[i];
		       demper->recalcParam(directInflu, temp3);
		   }
		   else
		   {
		       newMinPont[i] = demper->paramTn[directInflu];
		   }
	       }
	       else
	       {
		    newMinPont[i] = demper->paramTn[directInflu];
	       }
	    }
	    z1 = optStep();
	    if(z - z1 > 1e-5) //возможная новая точкой меньше предыдущей на значимое число, то продолжаем алгоритм, если нет, повторяем предыдущий анализ c уменьшеными шагом
		decrFlag = true;
	    else
		step /= 10;
	}
	if(bPointFlag)  //если новая точка вычислялась на оcнове базовой
	{
	    if(decrFlag)
	    {
		z = z1;
		bPointFlag = false;
		for(int i = 0; i < massCount; i++)
		{
		    demper = demperList.at(i);
		    lastBasePoint[i] = demper->paramTn[directInflu];
		    demper->paramTn[directInflu] = basePoint[i] + 2 * (demper->paramTn[directInflu] - basePoint[i]);
		    demper->recalcParam(directInflu, temp3);
		}
	    }
	}
	else //если новая точка вычислялась на очнове промежуточной
	{
	    curStepParam[1] += 1;
	    if(decrFlag) //если новая точка меньше предыдущей
	    {
		bPointFlag = true;
		z = z1;
		for(int i = 0; i < massCount; i++)
		{
		    demper = demperList.at(i);
		    basePoint[i] = demper->paramTn[directInflu];
		}
	    }
	    else //если не меньше
	    {
		bPointFlag = true;
		for(int i = 0; i < massCount; i++)
		{
		    demper = demperList.at(i);
		    demper->paramTn[directInflu] = lastBasePoint[i];
		    basePoint[i] = lastBasePoint[i];
		}
	    }
	}
	curStepParam[0] = z1;
	emit updStepParam(curStepParam); //создание сигнала с данными для основного потока
    }
    if (z == 1e37) //провека результата оптимизации
	resFlag = false; //запись результата.
    else
	resFlag = true;
    emit updStepParam(curStepParam); //создание сигнала с данными для основного потока

    delete [] basePoint;
    delete [] lastBasePoint;
    delete [] newMinPont;
}

