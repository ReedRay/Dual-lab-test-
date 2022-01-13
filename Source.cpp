#include <iostream>
#include<algorithm>
#include <vector>
#include<string>
#include <fstream>
#include<iterator>
using namespace std;
class Overall              //класс описывающий основные параметры строки
{
private:
	string ArrTime;
	string DepTime;
	string comp_name;
	

public:
	int depTime = 0;//переменная для компаратора 
	bool Hour=0;    //переменная для компаратора
	void SetArrTime(string str) //сеттеры
	{
		ArrTime = str;
	} 
	void SetDepTime(string str)
	{
		DepTime = str;
	}
	void SetCompName(string str)
	{
		comp_name = str;
	}
	string GetArrTime()  //геттеры
	{
		return ArrTime;
	}
	string GetDepTime()
	{
		return DepTime;
	}
	string GetCompName()
	{
		return comp_name;
	}
	Overall()
	{
	}

	Overall(string time1,string time2,string comp) //конструктор лего 
	{
		ArrTime = time1;
		DepTime = time2;
		comp_name = comp;
	}
	friend void checkHour(vector<Overall> &data);
	friend void MainLogic(vector<Overall>& data);
	friend void mySort(vector<Overall>& data);
	friend bool compare(Overall it1, Overall it2);
}; 


void Fill(vector<string> &data,vector<Overall> &myClass)   //заполнить вектор объектами класса
{
	auto it = data.begin();
	Overall temp;
	
	do
	{
		temp.SetCompName(*it);
		it++;
		temp.SetDepTime(*it);
		it++;
		temp.SetArrTime(*it);
		it++;
		myClass.push_back(temp);

	} while (it!=data.end());
}

void checkHour(vector<Overall> &data) //
{
	int ahour = 0;
	int amin = 0;
	int dhour = 0;
	int dmin = 0;
	
	for (auto it = data.begin(); it!=data.end(); it++) 
	{
		ahour = stoi(it->ArrTime.substr(0, 2));//разбиение строки и получение числа из подстроки
		amin= stoi(it->ArrTime.substr(3, 5));
		dhour = stoi(it->DepTime.substr(0, 2));
		dmin = stoi(it->DepTime.substr(3, 5));
		if (ahour-dhour>=1 && amin-dmin>0)
		{
			it->Hour = 1; //условие для компаратора 
		}
	}
	data.erase(remove_if(begin(data), end(data), [](Overall data) {return data.Hour == 1;}), end(data)); //удаление ненужных элементов 



}
void print(vector<Overall>& myClass)  //ф-ия записи в файл
{

	bool GrottyCheck = false;
	fstream fileToWrite("D:\\MyProjects\\vs\\test\\fout.txt");   //Тут менять путь для файла!
	for (auto it = myClass.begin(); it != myClass.end(); it++)
	{
		
		if (myClass.begin()->GetCompName()!="Grotty"&&it->GetCompName() == "Grotty" && GrottyCheck == false) //отступ для грути
		{
			fileToWrite << "\n";
			GrottyCheck = true;    
		}
		fileToWrite << it->GetCompName()<<' ';
		fileToWrite << it->GetDepTime() << ' ';
		fileToWrite << it->GetArrTime()<<'\n';

		
	}
	fileToWrite.close();
}

void MainLogic(vector<Overall> &data) 
{
	
	auto it = data.begin();
	
		while (it != data.end())
		{

		
		int arrhour = stoi(it->ArrTime.substr(0, 2)) * 60;
		int arrmin = stoi(it->ArrTime.substr(3, 5));
		int dephour = stoi(it->DepTime.substr(0, 2)) * 60;
		int depmin = stoi(it->DepTime.substr(3, 5));
		int arrResult = arrhour + arrmin;
		int depResult = dephour + depmin;
		

		for (auto it1 = it + 1; it1 != data.end(); it1++)
		{
			/*cout << data.size() << " ";*/
			int arrhour1 = stoi(it1->ArrTime.substr(0, 2)) * 60;
			int arrmin1 = stoi(it1->ArrTime.substr(3, 5));
			int dephour1 = stoi(it1->DepTime.substr(0, 2)) * 60;
			int depmin1 = stoi(it1->DepTime.substr(3, 5));
			int arrResult1 = arrhour1 + arrmin1;
			int depResult1 = dephour1 + depmin1;
			if ((depResult == depResult1 && arrResult < arrResult1))
			{
				it1->Hour = 1;
				data.erase(remove_if(begin(data), end(data), [](Overall data) {return data.Hour == 1; }), end(data));
				continue;
			}
			else if ((depResult == depResult1) && (arrResult > arrResult1))
			{
				it->Hour = 1;
				data.erase(remove_if(begin(data), end(data), [](Overall data) {return data.Hour == 1; }), end(data));
				break;
			}
			if ((depResult == depResult1) && (arrResult == arrResult1))
			{
				if (it->comp_name == "Posh")
				{
					it1->Hour = 1;
					data.erase(remove_if(begin(data), end(data), [](Overall data) {return data.Hour == 1; }), end(data));
					break;
				}
				else
				{
					it->Hour = 1;
					data.erase(remove_if(begin(data), end(data), [](Overall data) {return data.Hour == 1; }), end(data));
					break;
				}
			}

			if ((depResult > depResult1) && (arrResult <= arrResult1))
			{
				it1->Hour = 1;
				data.erase(remove_if(begin(data), end(data), [](Overall data) {return data.Hour == 1; }), end(data));
				continue;
			}
			else if ((depResult < depResult1) && (arrResult >= arrResult1))
			{
				
				it->Hour = 1;
				data.erase(remove_if(begin(data), end(data), [](Overall data) {return data.Hour == 1; }), end(data));
				break;
			}

		}
		++it;
	}
}

bool compare(Overall it1, Overall it2) //компаратор
{
	if (it1.comp_name!=it2.comp_name)
	{
		return it1.comp_name > it2.comp_name;
	}
	else 
	{
		return it1.DepTime < it2.DepTime;
	}
}
void mySort(vector<Overall>& data)
{
	for (auto it = data.begin(); it != data.end(); it++)
	{
		int dhour = stoi(it->DepTime.substr(0, 2)) * 60;
		int dmin = stoi(it->DepTime.substr(3, 5));
		it->depTime = dhour + dmin;

	}
	sort(begin(data), end(data), [](Overall x1, Overall x2) {return compare(x1,x2); }); //

}
 
int main() 
{
	fstream inputFile; //Файл для чтения 
	inputFile.open("fin.txt");
	vector<string> data;
	string buffer;
	vector<Overall> myOver;
	while (!inputFile.eof())
	{
		inputFile >> buffer;
		data.push_back(buffer);
	}
	
	Fill(data, myOver);
	checkHour(myOver);
	MainLogic(myOver);
	
	mySort(myOver);
	print(myOver);
	inputFile.close();


	return 0;
}