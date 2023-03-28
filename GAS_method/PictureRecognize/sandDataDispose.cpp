#pragma once
#include"sandDataDispose.h"
#define FIELD_DATA
void sandDataD()
{
	while (true)
	{
#ifndef FIELD_DATA
		std::cout << "Please enter the path to the sand diameter file!" << std::endl;
		std::string inputAllSandA, inputManualMaxMinA;
		std::cin >> inputAllSandA;
		std::cout << "Please enter the file path for the maximum and minimum grain size of the manually measured sand grains!" << std::endl;
		std::cin >> inputManualMaxMinA;
		std::multiset<double> minManualD, maxManualD, averageManualD;
		std::map<int, std::tuple<double, double, double>> allData, rightAllData;
		readManualMeasureDiameter(inputManualMaxMinA, minManualD, maxManualD, averageManualD);
		mergeManualData(rightAllData, maxManualD, minManualD, averageManualD);
		readTextData(inputAllSandA, allData);

#endif
#ifdef FIELD_DATA
		std::cout << "Please enter the path to the sand diameter file!" << std::endl;
		std::string inputAllSandA, inputWrongSandA, inputManualMaxMinA;
		std::cin >> inputAllSandA;
		std::cout << "Please enter the wrong sand diameter file path!" << std::endl;
		std::cin >> inputWrongSandA;
		std::map<int, std::tuple<double, double, double>> allData, rightAllData, wrongAllData;
		std::vector<int>wrongData;
		std::multiset<double>wrongMaxD, wrongMinD, wrongAverageD;
		readTextData(inputAllSandA, inputWrongSandA, allData, wrongData);
		rightAllData = allData;
		for (int i = 0; i < wrongData.size(); i++)
		{
			wrongAllData.insert(std::pair<int, std::tuple<double, double, double>>(wrongData[i], rightAllData[wrongData[i]]));
			rightAllData.erase(wrongData[i]);
		}
		for (auto it = wrongAllData.begin(); it != wrongAllData.end(); it++)
		{
			double valueMax = std::get<0>(it->second) * 10;
			double valueMin = std::get<1>(it->second) * 10;
			double valueAverage = std::get<2>(it->second) * 10;
			wrongMaxD.insert(valueMax);
			wrongMinD.insert(valueMin);
			wrongAverageD.insert(valueAverage);
		}
#endif
		std::multiset<double>allMaxD, allMinD, allAverageD, rightMaxD, rightMinD, rightAverageD;
		std::multiset<double>allMaxDMassA, allMinDMassA, allAverageDMassA, rightMaxDMassA, rightMinDMassA, rightAverageDMassA;
		std::multiset<double>allMaxDMass, allMinDMass, allAverageDMass, rightMaxDMass, rightMinDMass, rightAverageDMass;
		double allMaxV = 0;
		double allMinV = 0;
		double allAverageV = 0;
		double rightMaxV = 0;
		double rightMinV = 0;
		double rightAverageV = 0;
#ifdef FIELD_DATA
		for (auto it = allData.begin(); it != allData.end(); it++)
		{
			double valueMax = std::get<0>(it->second) * 10;
			double valueMin = std::get<1>(it->second) * 10;
			double valueAverage = std::get<2>(it->second) * 10;
			allAverageV += valueAverage * valueAverage * PI / 4;
			allMaxV += valueMax * valueMax * PI / 4;
			allMinV += valueMin * valueMin * PI / 4;
			allMaxD.insert(valueMax);
			allMinD.insert(valueMin);
			allAverageD.insert(valueAverage);
		}
		for (auto it = rightAllData.begin(); it != rightAllData.end(); it++)
		{
			double valueMax = std::get<0>(it->second) * 10;
			double valueMin = std::get<1>(it->second) * 10;
			double valueAverage = std::get<2>(it->second) * 10;
			rightAverageV += valueAverage * valueAverage * PI / 4;
			rightMaxV += valueMax * valueMax * PI / 4;
			rightMinV += valueMin * valueMin * PI / 4;
			rightMaxD.insert(valueMax);
			rightMinD.insert(valueMin);
			rightAverageD.insert(valueAverage);
		}
#endif
#ifndef FIELD_DATA
		for (auto it = allData.begin(); it != allData.end(); it++)
		{
			double valueMax = std::get<0>(it->second)*10 ;
			double valueMin = std::get<1>(it->second)*10 ;
			double valueAverage = std::get<2>(it->second)*10 ;
			allAverageV += valueAverage * valueAverage * PI / 4;
			allMaxV += valueMax * valueMax * PI / 4;
			allMinV += valueMin * valueMin * PI / 4;
			allMaxD.insert(valueMax);
			allMinD.insert(valueMin);
			allAverageD.insert(valueAverage);
		}
		for (auto it = rightAllData.begin(); it != rightAllData.end(); it++)
		{
			double valueMax = std::get<0>(it->second) ;
			double valueMin = std::get<1>(it->second) ;
			double valueAverage = std::get<2>(it->second);
			rightAverageV += valueAverage * valueAverage * PI / 4;
			rightMaxV += valueMax * valueMax * PI / 4;
			rightMinV += valueMin * valueMin * PI / 4;
			rightMaxD.insert(valueMax);
			rightMinD.insert(valueMin);
			rightAverageD.insert(valueAverage);
		}
#endif
		calculateAccumulateCurveHorizon(allMaxD, allMaxDMassA, allMaxDMass, allMaxV);
		calculateAccumulateCurveHorizon(allMinD, allMinDMassA, allMinDMass, allMinV);
		calculateAccumulateCurveHorizon(allAverageD, allAverageDMassA, allAverageDMass, allAverageV);
		calculateAccumulateCurveHorizon(rightMaxD, rightMaxDMassA, rightMaxDMass, rightMaxV);
		calculateAccumulateCurveHorizon(rightMinD, rightMinDMassA, rightMinDMass, rightMinV);
		calculateAccumulateCurveHorizon(rightAverageD, rightAverageDMassA, rightAverageDMass, rightAverageV);
		std::string workAddress, allMaxAddress, allMinAddress, allAverageAddress, rightMaxAddress
			, rightMinAddress, rightAverageAddress;
		auto pos = inputAllSandA.find_last_of("//\\");
		workAddress = inputAllSandA.substr(0, pos);
		allMaxAddress = workAddress + "\\allMax.txt";
		allMinAddress = workAddress + "\\allMin.txt";
		allAverageAddress = workAddress + "\\allAverage.txt";
		rightMaxAddress = workAddress + "\\rightMax.txt";
		rightMinAddress = workAddress + "\\rightMin.txt";
		rightAverageAddress = workAddress + "\\rightAverage.txt";
#ifdef FIELD_DATA
		std::string wrongAllAddress, wrongMaxAddress, wrongMinAddress, wrongAverageAddress;
		wrongAllAddress += workAddress + "\\wrongAll.txt";
		wrongMaxAddress += workAddress + "\\wrongMax.txt";
		wrongMinAddress += workAddress + "\\wrongMin.txt";
		wrongAverageAddress += workAddress + "\\wrongAverage.txt";
		writeWrongText(wrongMaxAddress, wrongMaxD);
		writeWrongText(wrongMinAddress, wrongMinD);
		writeWrongText(wrongAverageAddress, wrongAverageD);
		void writeWtongText(const std::string & address, const std::map<int, std::tuple<double, double, double>> & wrongAllData);
#endif

		writeTextDiameter(allMaxAddress, allMaxDMassA, allMaxD);
		writeTextDiameter(allMinAddress, allMinDMassA, allMinD);
		writeTextDiameter(allAverageAddress, allAverageDMassA, allAverageD);
		writeTextDiameter(rightMaxAddress, rightMaxDMassA, rightMaxD);
		writeTextDiameter(rightMinAddress, rightMinDMassA, rightMinD);
		writeTextDiameter(rightAverageAddress, rightAverageDMassA, rightAverageD);
		std::string rouAddress = workAddress + "\\rou.txt";
		std::ofstream rou(rouAddress);
		double  rou_allMaxD = calculateTwoCurveCorrelation(allMaxD, allMaxDMass,
			rightMaxD, rightMaxDMass, workAddress);
		rou << "Correlation coefficient for the maximum particle size of sand =" << rou_allMaxD << std::endl;
		double rou_allMinD = calculateTwoCurveCorrelation(allMinD, allMinDMass,
			rightMinD, rightMinDMass, workAddress);
		rou << "Correlation coefficient for the smallest particle size of sand =" << rou_allMinD << std::endl;
		double rou_allAverageD = calculateTwoCurveCorrelation(allAverageD, allAverageDMass,
			rightAverageD, rightAverageDMass, workAddress);
		rou << "Correlation coefficient for the average particle size of sand =" << rou_allAverageD << std::endl;
		rou << "Correct number of particles =" << rightAllData.size() << std::endl;
		rou << "Number of full particles =" << allData.size() << std::endl;
#ifdef FIELD_DATA
		rou << "Number of error particles =" << wrongData.size() << std::endl;
#endif
		double rou_wrongRate_allMax = calculateWrongRate(allMaxD, allMaxDMassA,
			rightMaxD, rightMaxDMassA);
		rou << "Relative error in the maximum particle size of sand =" << rou_wrongRate_allMax << std::endl;
		double rou_wrongRate_allMin = calculateWrongRate(allMinD, allMinDMassA,
			rightMinD, rightMinDMassA);
		rou << "Relative error in the minimum particle size of sand =" << rou_wrongRate_allMin << std::endl;
		double rou_wrongRate_allAverage = calculateWrongRate(allAverageD, allAverageDMassA,
			rightAverageD, rightAverageDMassA);
		rou << "Relative error in the mean particle size of sand =" << rou_wrongRate_allAverage << std::endl;
	}
};
void readTextData(const std::string& inputAllSandD, const std::string& inputWrongSandD,
	std::map<int, std::tuple<double, double, double>>& allData, std::vector<int>& wrongeData)
{
	std::ifstream allSandD(inputAllSandD);
	if (!allSandD.is_open())
	{
		std::cout << "No full data file opened!" << std::endl;
		exit(-1);
	}
	std::ifstream wrongSandD(inputWrongSandD);
	if (!wrongSandD.is_open())
	{
		std::cout << "No error sand data file opened!" << std::endl;
		exit(-1);
	}
	std::string line, sandNumber, intermediateData;
	while (std::getline(allSandD, line))
	{
		std::vector<std::string>oneSand;
		std::istringstream oneSandData(line);
		for (int i = 0; i < SAND_DATA_NUMBER; i++)
		{
			oneSandData >> intermediateData;
			if (i == 0)
			{
				readSandNumber( intermediateData,  sandNumber);
				oneSand.push_back(sandNumber);
			}
			else
			{
				oneSand.push_back(intermediateData);
			}
		}
		allData.insert(std::pair<int, std::tuple<double, double, double>>
			(stoi(oneSand[0]), 
			std::tuple<double, double, double>(stod(oneSand[1]), stod(oneSand[2]), stod(oneSand[3]))));
	}
	while (std::getline(wrongSandD, line))
	{
		wrongeData.push_back(stoi(line));
		std::cout << line << std::endl;
	}
};
void readSandNumber(const std::string& intermediateData, std::string& sandNumber)
{
	std::string numbers("0123456789");
	auto pos = intermediateData.find_first_of(numbers);
	auto end = intermediateData.find_last_not_of(numbers);
	sandNumber = intermediateData.substr(pos,end-pos);
};
void writeTextDiameter(const std::string& address, std::multiset<double>& MaxDMassA, const std::multiset<double>& rightV)
{
	std::ofstream allSandD(address);
	auto itt = MaxDMassA.begin();
	for (auto it = rightV.begin(); it != rightV.end(); it++,itt++)
	{
		allSandD << (*it) <<"    "<<(*itt)<< std::endl;
	}
};
void getMaxMinDiameter(const std::multiset<double>& allD, const std::multiset<double>& rightD, double& maxTwoD, double& minTwoD)
{
	double first = *(allD.begin());
	double second = *(rightD.begin());
	if (first >= second)
	{
		minTwoD = first;
	}
	else
	{
		minTwoD = second;
	}
	first = *(--allD.end());
	second = *(--rightD.end());
	if (first >= second)
	{
		maxTwoD = second;
	}
	else
	{
		maxTwoD = first;
	}
};
void readManualMeasureDiameter(const std::string& inputManualMaxMinA, std::multiset<double>& minManualD,
	std::multiset<double>& maxManualD, std::multiset<double>& averageManualD)
{
	std::ifstream ManualSandD(inputManualMaxMinA);
	if (!ManualSandD.is_open())
	{
		std::cout << "No full data file opened!" << std::endl;
		exit(-1);
	}
	std::string line,maxD,minD;
	while (std::getline(ManualSandD, line))
	{
		std::istringstream oneSandData(line);
		oneSandData >> maxD >> minD;
		maxManualD.insert(stod(maxD));
		minManualD.insert(stod(minD));
		averageManualD.insert(sqrtf(stod(maxD)* stod(minD)));
	}
};
double calculateTwoCurveCorrelation(std::multiset<double>firstHorizontalCurve, std::multiset<double> firstCurveVertical,
	std::multiset<double>secondHorizontalCurve, std::multiset<double>secondCurveVertical
	, const std::string& workAddress)
{
	double maxTwoD, minTwoD;
	getMaxMinDiameter(firstHorizontalCurve, secondHorizontalCurve, maxTwoD, minTwoD);
	std::map<double, double>firstCurveM;
	std::map<double, double>secondCurveM;
	 mergeData(firstHorizontalCurve,  firstCurveVertical,firstCurveM);
	 mergeData(secondHorizontalCurve, secondCurveVertical, secondCurveM);
	double average_x = 0;
	double average_y = 0;
	double begin_p = minTwoD;
	double cov = 0;
	double var_x = 0;
	double var_y = 0;
	double interval = (maxTwoD - minTwoD) / DIVIDE_NUMBER;
	 calculateAverageDiameter(firstCurveM,secondCurveM, average_x,average_y, maxTwoD, minTwoD);
	for (int i = 0; i < DIVIDE_NUMBER; i++)
	{
		double position = begin_p + i * interval;
		cov += (position - average_x) * (position-average_y);
		var_x += (position - average_x) * (position - average_x);
		var_y+= (position - average_y)* (position - average_y);
	}
	return cov / (sqrtf(var_x)*sqrtf(var_y));
};
void calculateAccumulateCurveHorizon(const std::multiset<double>& MaxD, std::multiset<double>& MaxDMassA, std::multiset<double>& MaxDMass,
	const double totalValue)
{
	double sum = 0;
	for (auto it = MaxD.begin(); it != MaxD.end(); it++)
	{
		double value = (*it)*(*it) *PI/4/ totalValue;
		MaxDMass.insert(value);
		sum += value;
		MaxDMassA.insert(sum);
	}
};
void mergeData(const std::multiset<double>& horizontalCurve, const std::multiset<double>& AccumulateCurve,
	std::map<double, double>& CurveM)
{
	for (auto it = horizontalCurve.begin(), itt = AccumulateCurve.begin(); it != horizontalCurve.end(); it++, itt++)
	{
		CurveM.insert(std::pair<double, double>((*it),(*itt)));
	}
};
void findIntervalInCurveM(const std::map<double, double>& CurveM, std::pair<double, double>& first,
	std::pair<double, double>& second,double position)
{
	auto end = CurveM.end()--;
	auto next = CurveM.begin()++;
	for (auto it=CurveM.begin();it!=end;it++,next++)
	{
		if (position >= it->first && position <= next->first)
		{
			first = *it;
			second = *next;
			return;
		}
	}
	std::cout << "position=" << position << std::endl;
	std::cout << "No suitable interval found, data error occurred!";
	exit(-1);
};
void calculateAverageDiameter(const std::map<double, double>& firstCurveM, const std::map<double, double>& secondCurveM,
	double& average_x, double& average_y, const double& maxTwoD, const double& minTwoD)
{
	average_x = 0;
	for (auto it = firstCurveM.begin(); it != firstCurveM.end(); it++)
	{
		if ((it->first >= minTwoD && it->first <= maxTwoD))
		{
			average_x += it->first * it->second;
		}
	}
	
		average_y = 0;
		for (auto it = secondCurveM.begin(); it != secondCurveM.end(); it++)
		{
			if ((it->first >= minTwoD && it->first <= maxTwoD))
			{
				average_y += it->first * it->second;
			}
		}
};
void readTextData(const std::string& inputAllSandD,
	std::map<int, std::tuple<double, double, double>>& allData)
{
	std::ifstream allSandD(inputAllSandD);
	if (!allSandD.is_open())
	{
		std::cout << "No full data file opened!" << std::endl;
		exit(-1);
	}

	std::string line, sandNumber, intermediateData;
	while (std::getline(allSandD, line))
	{
		std::vector<std::string>oneSand;
		std::istringstream oneSandData(line);
		for (int i = 0; i < SAND_DATA_NUMBER; i++)
		{
			oneSandData >> intermediateData;
			if (i == 0)
			{
				readSandNumber(intermediateData, sandNumber);
				oneSand.push_back(sandNumber);
			}
			else
			{
				oneSand.push_back(intermediateData);
			}
		}
		allData.insert(std::pair<int, std::tuple<double, double, double>>
			(stoi(oneSand[0]),
				std::tuple<double, double, double>(stod(oneSand[1]), stod(oneSand[2]), stod(oneSand[3]))));
	}
};
void mergeManualData(std::map<int, std::tuple<double, double, double>>& rightAllData, const std::multiset<double>& maxManualD, const std::multiset<double>& minManualD
	, const std::multiset<double>& averageManualD)
{
	int number = 0;
	for (auto it_max = maxManualD.begin(),it_min=minManualD.begin(),it_average=averageManualD.begin(); it_max != maxManualD.end(); it_max++,it_min++,it_average++,number++)
	{
		rightAllData.insert(std::pair<int,std::tuple<double,double,double>>(number,std::tuple<double,double,double>(*it_max,*it_min,*it_average)));
	}
};
double calculateWrongRate(std::multiset<double>&firstHorizontalCurve, std::multiset<double>& firstCurveVertical,
	std::multiset<double>&secondHorizontalCurve, std::multiset<double>&secondCurveVertical)
{
	std::map<double, double>allData;
	std::map<double, double>rightData;
	mergeData(firstHorizontalCurve, firstCurveVertical, allData);
	mergeData(secondHorizontalCurve, secondCurveVertical,rightData);
	double minD = *firstHorizontalCurve.begin(), maxD = *(--firstHorizontalCurve.end());
	if (*secondHorizontalCurve.begin() > minD)
	{
		minD = *secondHorizontalCurve.begin();
	}
	if (*(--secondHorizontalCurve.end()) < maxD)
	{
		maxD = *(--secondHorizontalCurve.end());
	}
	std::set<double>allV,rightV;
	double interal = (maxD - minD) / DIVIDE_NUMBER;
	for (int i=0;i< DIVIDE_NUMBER;i++)
	{
		double position = minD + interal * i;
		std::pair<double, double>A_bg, A_ed,R_bg,R_ed;
		 findIntervalInCurve(allData,position,A_bg,A_ed);
		 findIntervalInCurve(rightData, position, R_bg, R_ed);
		 double A_value = (position - A_ed.first) / (A_bg.first - A_ed.first) * A_bg.second + (position - A_bg.first)/(A_ed.first-A_bg.first) * A_ed.second;
		 allV.insert(A_value);
		 double R_value = (position - R_ed.first) / (R_bg.first - R_ed.first) * R_bg.second + (position - R_bg.first) / (R_ed.first - R_bg.first) * R_ed.second;
		 rightV.insert(R_value);
	}
	double error = 0;
	double sum = 0;
	for (auto it = allV.begin(), itt = rightV.begin(); it != allV.end(); it++, itt++)
	{
		error += abs(*it - *itt);
		sum += *itt;
	}
	return error / sum;
};
void  findIntervalInCurve(const std::map<double, double>& allData, const double position, std::pair<double,double>& bg, std::pair<double, double>& ed)
{
	for (auto it = allData.begin(),itt= ++allData.begin(); itt != allData.end(); it++,itt++)
	{
		if (position >= it->first && position <= itt->first)
		{
			bg = *it;
			ed = *itt;
			return;
		}

	}
};
void writeWrongText(const std::string& Address, const std::multiset<double>& wrongData)
{
	std::ofstream allSandD(Address);
	for (auto it = wrongData.begin(); it != wrongData.end(); it++)
	{
		allSandD << (*it) << "    " << std::endl;
	}
};
void writeWtongText(const std::string& address, const std::map<int, std::tuple<double, double, double>>& wrongAllData)
{
	std::ofstream allSandD(address);
	for (auto it = wrongAllData.begin(); it != wrongAllData.end(); it++)
	{
		allSandD << "No." <<it->first<<"Grain of sand:"<<" "<< std::get<0>(it->second) * 10 << "   "
			<< std::get<1>(it->second) * 10 <<"   "<< std::get<2>(it->second) * 10 << std::endl;
	}
};