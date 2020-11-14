#include <string>
#include <vector>
#include <iostream>
#include <cmath>
using namespace std;


string* spliting(string data, char a) //a.char a로 split해주는 함수
{
	int N = 3;
	int data_length = data.length();

	string* result = new string[N]; // ' '일시는 처리정보 -> 1.날짜 2. 시간 3. 처리지속시간
									// ':'일시는 시간 -> 1.시 2.분 3.초. 어느쪽이나 3개씩 나온다.
	int index = 0;
	int result_index = 0;

	try {

		for (int i = 0; i < N; i++)
		{
			int index_end = data.find(a);

			index_end = (index_end == string::npos) ? data_length : index_end;
			result[i] = data.substr(index, index_end); //.substr을 이용하였다.
			data = data.substr(index_end + 1, data_length);
		}
	}

	catch (exception e)
	{
		//cout << e.what() << endl;
	}

	return result;
}



class data_split
{
public:
	string day_a; //b. 네이밍이 조금 이상하지만 날짜 정보
	string day_b; // 시간(시 : 분 : 초)
	string day_c;//처리지속시간을 의미
	data_split* next1;

	data_split(string a, string b, string c)
	{
		this->day_a = a;
		this->day_b = b;
		this->day_c = c;
		this->next1 = NULL;
	}

};


class Time_stack
{
public:
	int hour1 = 0;
	int minute1 = 0;
	float second1 = 0;
	Time_stack* starting;
	Time_stack* ending;


	Time_stack()
	{

	}

	Time_stack(int hour, int minute, float start_second, float end_second)
	{
		this->starting = new Time_stack(hour, minute, start_second);
		this->ending = new Time_stack(hour, minute, end_second);
	}


	Time_stack(int hour, int minute, float second)
	{
		this->starting = NULL;
		this->ending = NULL;

		if (second >= 60)
		{
			second -= 60;
			minute += 1;
		}

		if (minute >= 60)
		{
			minute -= 60;
			hour += 1;
		}


		if (second < 0)
		{
			second += 60;
			minute -= 1;
		}

		if (minute < 0)
		{
			minute += 60;
			hour -= 1;
		}


		this->hour1 = hour;
		this->minute1 = minute;
		this->second1 = second;
	}

	Time_stack* operator+(Time_stack &a) {
		Time_stack* result = new Time_stack(this->hour1 + a.hour1, this->minute1 + a.minute1, this->second1 + a.second1);
		return result;
	}

	Time_stack* operator-(Time_stack &a) {
		Time_stack* result = new Time_stack(this->hour1 - a.hour1, this->minute1 - a.minute1, this->second1 - a.second1);
		return result;
	}

	bool operator<=(Time_stack &a)
	{

		if (this->hour1 < a.hour1)
			return true;

		else if (this->hour1 == a.hour1)
		{
			if (this->minute1 < a.minute1)
				return true;

			else if (this->minute1 == a.minute1)
			{
				if (this->second1 <= a.second1)
					return true;

				else
					return false;
			}
		}

		return false;
	}


	bool operator>=(Time_stack &a)
	{


		if (this->hour1 > a.hour1)
			return true;

		else if (this->hour1 == a.hour1)
		{
			if (this->minute1 > a.minute1)
				return true;

			else if (this->minute1 == a.minute1)
			{
				if (this->second1 >= a.second1)
					return true;

				else
					return false;
			}
		}

		return false;
	}

	bool operator<(Time_stack &a)
	{

		if (this->hour1 < a.hour1)
			return true;

		else if (this->hour1 == a.hour1)
		{
			if (this->minute1 < a.minute1)
				return true;

			else if (this->minute1 == a.minute1)
			{
				if (this->second1 < a.second1)
					return true;

				else
					return false;
			}
		}

		return false;
	}


	bool operator>(Time_stack &a)
	{


		if (this->hour1 > a.hour1)
			return true;

		else if (this->hour1 == a.hour1)
		{
			if (this->minute1 > a.minute1)
				return true;

			else if (this->minute1 == a.minute1)
			{
				if (this->second1 > a.second1)
					return true;

				else
					return false;
			}
		}

		return false;
	}


	void print()
	{
		cout << hour1 << " m" << minute1 << " s" << second1 << endl;

		if (this->starting != NULL)
		{
			this->starting->print();
		}


		else if (this->ending != NULL)
		{
			this->ending->print();
		}
	}
};


class calcurate
{

public:
	int time_stack[24][60][60] = { 0 };
	int max = 0;
	int n = 0;
	Time_stack* stack_01;
	int stack_index = 0;


	calcurate(int n)
	{
		this->make_Timestack(n);
	}


	int getting_max()
	{
		Time_stack* time1 = new Time_stack(0, 0, 0.999);//처리량의 개수가 변하는 시점은 새로운 작업이 추가되거나 끝나는 시점 뿐. 이것을 이용하여 
		max = 0;			//i번째의 작업이 들어갔을 때, 끝났을 때 작업 중인 j번째 함수가 몇 개인지 구함 그 중 최대값이 해당 시간에서의 최대 작업 갯수 

		for (int i = 0; i < n; i++)
		{
			Time_stack* example = stack_01[i].starting;
			Time_stack* example_ending = *example + *time1;
			example->print();
			example_ending->print();


			Time_stack* example2 = stack_01[i].ending;
			Time_stack* example2_ending = *example2 + *time1;
			example2->print();
			example2_ending->print();

			cout << endl;

			int max_exe = 0;
			int max_exe2 = 0;

			for (int j = 0; j < n; j++)
			{
				Time_stack* obj = stack_01[j].starting;
				Time_stack* obj_ending = stack_01[j].ending;

				if (!(*example_ending < *obj || *example > *obj_ending))
				{
					max_exe++;
				}


				if (!(*example2_ending < *obj || *example2 >= *obj_ending))
				{
					cout << j << endl;
					max_exe2++;
				}

			}

			max = (max_exe > max) ? max_exe : max;
			max = (max_exe2 > max) ? max_exe2 : max;
		}

		return max;
	}



	void push_Timestack(Time_stack data)
	{
		stack_01[stack_index] = data;
		stack_index++;
	}


	void make_Timestack(int n1)
	{
		this->n = n1;
		stack_01 = new Time_stack[n1];
	}


	void spending(int hour, int minute, float start_second, float end_second) //시, 분, 초 , 처리시간을 가지는 time*stack을 만들어준다.
	{
		Time_stack* time = new Time_stack(hour, minute, start_second, end_second);
		this->push_Timestack(*time);
	}



	void plus_traffic(string b, string c) // c.2. 시간정보를  1.시 , 2분 , 3초로 나눌 함수이다. 아까 사용하였던 spliting함수를 이용
	{
		string* data = spliting(b, ':');
		string travel = c.substr(0, c.length() - 1);

		float start_time = stof(data[2]) - stof(travel) + 0.001;
		spending(stoi(data[0]), stoi(data[1]), start_time, stof(data[2])); //data[0],[1]은 각각 시 분, start_time은 처리 시작 시간, data[2]는 초를 의미한다.
	}
};



class SPLIT
{
public:
	int n = 0;
	data_split *d_s;
	data_split *front;
	calcurate* cal;

	SPLIT(vector<string> lines)
	{
		n = lines.size();
		for (int i = 0; i < n; i++)
		{
			string* data = spliting(lines[i], ' '); // a.처음에 case 분류를 하는 작업. 1. 날짜, 2. 시간 , 3. 처리 지속시간으로 분할한다.

			if (i == 0)
			{
				d_s = new data_split(data[0], data[1], data[2]); //b. 처리정보를 나타내는 list에 넣어주었다.
				front = d_s;
			}

			else
			{
				d_s->next1 = new data_split(data[0], data[1], data[2]);
				d_s = d_s->next1;
			}
		}


		//그런다음 solution에서는 print를 호출한다.
		//여기서 호출 안 하는 이유는 print값이 문제의 최종값을 return하기 때문. 따라서 solution에서 바로 그 값을 쓸려고ㅎㅎ
	}

	int print()
	{
		data_split* exe = front;
		cal = new calcurate(n); 

		int i = 0;
		while (exe->next1 != NULL)
		{
			cal->plus_traffic(exe->day_b, exe->day_c); //c. 이 문제에서 날짜는 필요없다. 2.시간정보와 3.처리 지속시간만 필요하므로 이것을 떼서 계산용 calcular에 넣어준다.
			exe = exe->next1;
			i++;
		}

		cal->plus_traffic(exe->day_b, exe->day_c);
		int result = cal->getting_max();

		return result;
	}
};




SPLIT *split1;
vector<string> line2 = {
	"2016-09-15 20:59:57.421 0.351s", "2016-09-15 20:59:58.233 1.181s", "2016-09-15 20:59:58.299 0.8s", "2016-09-15 20:59:58.688 1.041s", "2016-09-15 20:59:59.591 1.412s", "2016-09-15 21:00:00.464 1.466s", "2016-09-15 21:00:00.741 1.581s", "2016-09-15 21:00:00.748 2.31s", "2016-09-15 21:00:00.966 0.381s", "2016-09-15 21:00:02.066 2.62s"
};


vector<string> line3 = {
	"2016-09-15 01:00:04.002 2.0s", "2016-09-15 01:00:07.000 2s"
};

vector<string> line4 = { "2016-09-15 01:00:04.001 2.0s", "2016-09-15 01:00:07.000 2s" };



int solution(vector<string> lines) {
	int answer = 0;
	split1 = new SPLIT(lines);

	answer = split1->print();
	cout << answer << endl;

	return answer;
}



int main(void)
{

	solution(line4);


	system("pause");
	return 0;
}
