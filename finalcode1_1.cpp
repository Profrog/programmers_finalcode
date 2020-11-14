#include <string>
#include <vector>
#include <iostream>

using namespace std;


class node //��ũ�� ����Ʈ�� ���� �� ���(������ �ǹ�)
{
public:
	node* front; //�ش� ������ �տ� �ִ� ������ �ּ�
	node* back; // �ش� ������ �ڿ� �ִ� ������ �ּ�
	int data = 0; //�ش� ������ �켱����
	int answer = 0; //anser�� ���� 0���� ũ�� �����ڰ� �ñ����ϴ� ����, �ƴ� ��� �׹��� ����

	node(int data)
	{
		this->front = NULL;
		this->back = NULL;
		this->data = data;
		this->answer = 0;
	}

	node(int data, int answer) //����ڰ� ������ ������ ��� ���� ���� �����ڸ� �̿��Ͽ� answer���� �ִ´�.
	{
		this->front = NULL;
		this->back = NULL;
		this->data = data;
		this->answer = answer;
	}

};




class calculator //��� �ϱ� ���� class
{
public:

	int index = 0;
	int return_value = 1; // �� ���� ����� �ߴ� �� ���, �׸��� �� class�� return�Ͽ��� �� ���� ��
	int original_value = 0;
	int max = 9; // �켱����
	int n; //��ü ����
	int sum = 0;
	int last_num = 0;
	int i = 0;

	node* first;
	node* current;
	node* end;


	void back_push(node* a) //�ش� a������ �ڷ� �� ��� ����ϴ� �Լ�
	{
		try {

			if (a->front == NULL && n > 1) //n>1�� �˻��ϴ� ������ 1���� �������� push�� �ǹ̰� ����..
			{
				first = a->back; 
				a->back->front = NULL;
				end->back = a;
				a->front = end; //first�� end�� ���� A����� ���� ��尡 FIRST, END���� A�� �ȴ�. ���� ���� ������ ���� �ڷ� ���ϱ�
				a->back = NULL;

				end = a;
				current = first;
				return;
			}


		}

		catch (exception e)
		{
			e.what();
		}
	}



	void pop(node *a) //�ش� a������ ����ϴ� ��� ����ϴ� �Լ�
	{
		try {

			this->n--; //��ü ������ ������ ����, ����ϰ� ��� ��Ͽ��� ������ϱ�
			this->i = -1;
			this->sum -= a->data;
			this->last_num = a->data;

			if (a->front == NULL) //���� ���� ������ ���, ��� �� �� ��츸 ����Ѵ�.
			{
				first = a->back;
				a->back->front = NULL; //node���� ���� �׸��� first�� a�� �ٲ��.
				return_value++;
				current = first;
				return;
			}


			else if (a->back == NULL)
			{
				end = a->front;
				a->front->back = NULL;
				return_value++;
				return;
			}

			else
			{
				a->front->back = a->back;
				a->back->front = a->front;
				return_value++;
				current = a->back;
				return;
			}


		}

		catch (exception e)
		{
			e.what();
		}
	}


	calculator(vector<int> data1, int index) { //calculator�� ������
		this->index = index; //�� index ��ġ��  data1���� �������� ��������, answer�� 0�� �ƴ� ����
		original_value = data1[index];
		this->n = data1.size();
		this->sum = 0;


		for (int i = 0; i < n; i++)
		{
			sum += data1[i];

			if (i == 0)
			{
				current = new node(data1[i]);

				if (i == index)
					current->answer = 1;

				first = current;
				end = current;
			}

			else
			{
				current->back = new node(data1[i]);

				if (i == index)
					current->back->answer = 1;

				current->back->front = current;
				current = current->back;
				end = current;
			}
		} //vector�� ��ũ�� ����Ʈ�� ����µ� o(n) //�迭�� �״�� ����ϰ��� �ϸ� �� ���α׷����� o(n*n)�� �ǰ� �ȴ�. 
		//���� ���� ������ �����ϰ� �ڷ� ���� �� ������ �������� ������ ����� �� o(n)�� �ɸ��� ����.





		while (max > 0) // �������� 1~9�����̴�. 
		{
			
			//���� while�� �̿� 9~1���� �ݺ����� ������, max���� ���� ��쿡�� pop�� �����ְ�
			//������ ��쿡�� back_push�� �����ָ� �켱 ���� ��� queue�� ������ �� �ִ�. 

			current = first; //ù ��° ������ ������ ������.

			for (this->i = 0; this->i < this->n; (this->i)++) //�ִ� o(n)
			{
				if (current->data == max)
				{
					if (current->answer > 0) //�ش� ������ �߰��Ͽ��� ���� �� �Լ��� ����. 
					{
						//�������� ��� ������ �߰� �Ǿ����� + 1���� �����ָ� �ȴ�.
						return;
					}

					else
					{
						pop(current);
					}
				}

				else
				{
					back_push(current);
				}
			}

			max--;
		}

	} //max�� ����� ������ ���⵵ o(n) ���� �� o(n)�� �ð��� �ʿ��ϴ�.


};

int solution(vector<int> priorities, int location) {

	calculator* exe = new calculator(priorities, location);
	int answer = exe->return_value;
	return answer;
}

vector<int> data1 = { 2, 1, 3, 2 };
vector<int> data2 = { 1, 1, 9, 1, 1, 1 };


int main(void)
{
	//cout << solution(data1, 2) << endl;
	cout << solution(data2, 1) << endl;


	system("pause");
}
