#include <string>
#include <vector>
#include <iostream>

using namespace std;


class node //링크드 리스트를 위한 각 노드(문서를 의미)
{
public:
	node* front; //해당 문서의 앞에 있는 문서의 주소
	node* back; // 해당 문서의 뒤에 있는 문서의 주소
	int data = 0; //해당 문서의 우선순위
	int answer = 0; //anser의 값이 0보다 크면 질문자가 궁금해하는 문서, 아닐 경우 그밖의 문서

	node(int data)
	{
		this->front = NULL;
		this->back = NULL;
		this->data = data;
		this->answer = 0;
	}

	node(int data, int answer) //사용자가 선택한 문서일 경우 위와 같은 생성자를 이용하여 answer값을 넣는다.
	{
		this->front = NULL;
		this->back = NULL;
		this->data = data;
		this->answer = answer;
	}

};




class calculator //계산 하기 위한 class
{
public:

	int index = 0;
	int return_value = 1; // 몇 개의 출력을 했는 지 기록, 그리고 이 class가 return하여야 할 최종 값
	int original_value = 0;
	int max = 9; // 우선순위
	int n; //전체 문서
	int sum = 0;
	int last_num = 0;
	int i = 0;

	node* first;
	node* current;
	node* end;


	void back_push(node* a) //해당 a문서가 뒤로 갈 경우 사용하는 함수
	{
		try {

			if (a->front == NULL && n > 1) //n>1을 검사하는 이유는 1개의 문서에는 push가 의미가 없다..
			{
				first = a->back; 
				a->back->front = NULL;
				end->back = a;
				a->front = end; //first와 end를 갱신 A노드의 다음 노드가 FIRST, END노드는 A가 된다. 제일 앞의 문서가 제일 뒤로 가니까
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



	void pop(node *a) //해당 a문서를 출력하는 경우 사용하는 함수
	{
		try {

			this->n--; //전체 문서의 개수가 감소, 출력하고 대기 목록에서 사라지니까
			this->i = -1;
			this->sum -= a->data;
			this->last_num = a->data;

			if (a->front == NULL) //제일 앞의 문서의 경우, 사실 상 이 경우만 사용한다.
			{
				first = a->back;
				a->back->front = NULL; //node간의 관계 그리고 first가 a로 바뀐다.
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


	calculator(vector<int> data1, int index) { //calculator의 생성자
		this->index = index; //이 index 위치의  data1값은 질문자의 문서이자, answer이 0이 아닌 문서
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
		} //vector를 링크드 리스트로 만드는데 o(n) //배열을 그대로 사용하고자 하면 위 프로그래밍은 o(n*n)이 되게 된다. 
		//제일 앞의 문서를 삭제하고 뒤로 넣을 때 사이의 문서들을 앞으로 땡기는 데 o(n)이 걸리기 때문.





		while (max > 0) // 사용순서는 1~9까지이다. 
		{
			
			//따라서 while을 이용 9~1까지 반복문을 돌리되, max값이 같은 경우에는 pop을 시켜주고
			//나머지 경우에는 back_push를 시켜주면 우선 순위 대로 queue를 정리할 수 있다. 

			current = first; //첫 번째 노드부터 끝까지 돌린다.

			for (this->i = 0; this->i < this->n; (this->i)++) //최대 o(n)
			{
				if (current->data == max)
				{
					if (current->answer > 0) //해당 문서를 발견하였을 때는 이 함수를 종료. 
					{
						//이전까지 몇개의 문서가 발견 되었는지 + 1개를 돌려주면 된다.
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

	} //max가 상수기 때문에 여기도 o(n) 따라서 총 o(n)의 시간이 필요하다.


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
