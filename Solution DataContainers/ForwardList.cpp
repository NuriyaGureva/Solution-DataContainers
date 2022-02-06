#include <iostream>
using namespace std;

#define tab "\t"

class Element
{
	int Data;	//�������� ��������
	Element* pNext;//����� ���������� ��������
	static int count;

public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
		cout << "EConstrcutor:\t" << this << endl;
	}
	
	~Element()
	{
		count--;
		cout << "EDestrcutor:\t" << this << endl;
	}
	friend class ForwardList;
};

int Element::count = 0;

class  ForwardList//����������� ������
{
	Element* Head;//������ ������-��������� �� ��������� ������� ������

	unsigned int size;
public:
	ForwardList()
	{
		Head = nullptr;//���� ������ ��������� �� 0,�� ������ �����
		size = 0;
		cout << "LConstructor:\t"<< this << endl;
	}
	
	~ForwardList()
	{
		while (Head)pop_front();		
		cout << "LDestructor:\t" << this << endl;
	}

	void push_front(int Data)
	{
		Element* New = new Element(Data);//������� ����� ������� � �������� ��� Data
		New->pNext = Head;//����������� ����� ������� � ������ ������
		Head = New;//��������� ������ �� ����� �������
		size++;
	}

	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		//������� ����� �������
		Element* New = new Element(Data);
		//������� �� ����� ������
		Element* Temp = Head;
		while (Temp->pNext)//����,pNext �������� ��������
		Temp = Temp->pNext;//��������� �� ��������� �������
		//������ �� ��������� � ��������� ��������
		//������������ ����� ������� � ����������
		Temp->pNext = New;
		size++;
	}
	void insert(int index, int Data)
	{		
		if (index==0 || Head == nullptr) return push_front(Data);
		if (index > size )return;
		Element* New = new Element(Data);
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)
		Temp = Temp->pNext;
		New->pNext = Temp->pNext;
		Temp->pNext = New;
		size++;
	}
	//void erase(int index)
	//{
	//	if (index > size)return;
	//	if (index == 0)return pop_front();
	//	if (Head == nullptr)return;
	//	Element* Erased = Head;
	//	Element* prev = nullptr;

	//	for (int i = 0; i < index; i++) {
	//		prev = Erased;
	//		Erased = Erased->pNext;
	//	}

	//	if (prev != nullptr) 
	//	{
	//		prev->pNext = Erased->pNext;
	//	}

	//	delete Erased;
	//	size--;
	//}
	//     Removing elements;
	void erase(int index)
	{
		if (index > size)return;
		if (index == 0)return pop_front();
		//1) ������� �� ������� ��������:
		Element* Temp = Head;	//������� ��������, � ������� � ������ ����� ������.
		//������ � ��������� ����� ��������� ��������.
		for (int i = 0; i < index - 1; i++)Temp = Temp->pNext;
		//2) ���������� ����� ���������� ��������:
		Element* Erased = Temp->pNext;
		//3) ��������� ������� �� ������:
		//Temp->pNext = Temp->pNext->pNext;
		Temp->pNext = Erased->pNext;
		//4) ������� ������� �� ������:
		delete Erased;
		size--;
	}
	void pop_front()
	{
		if (Head == nullptr)return;
		//���������� ����� ���������� ��������
		Element* Erased = Head;
		//��������� ������� �� ������
		Head = Erased->pNext;
		//�������
		delete Erased;
		size--;
	}
	void pop_back()
	{
		if (Head == nullptr)return;
		if (Head->pNext == nullptr)return pop_front();
		//������� �� ���������� ��������
		Element* Temp = Head;
		while (Temp->pNext->pNext)Temp = Temp->pNext;
		//������� ������� �� ������
		delete Temp->pNext;
		//�������� ����� ���������� �������� �����
		Temp->pNext = nullptr;
		size--;
	}

	void reverse()//������ ��������
	{	
		Element* current = Head;
		Element* next = nullptr;

		while (current != nullptr) 
		{
			Element* Temp = current->pNext;
			current->pNext = next;
			next = current;
			current = Temp;

			if (current == nullptr)
				Head = next;
		}
	}

	void unigue()//������� ����������� �������� � ������
	{
		Element* current = Head;
		while (current != nullptr)
		{
			Element* elem = Head;
			Element* prev = nullptr;
			while (elem != nullptr)
			{
				if (current == elem || current->Data != elem->Data)
				{
					prev = elem;
					elem = elem->pNext;
				}
				else 				{
					
					prev->pNext = elem->pNext;
					delete elem;
					elem = prev->pNext;
				}
			}

			current = current->pNext;
		}				
	}
	void print()const
	{
		Element* Temp = Head;//temp-��� ��������
		//��������- ��� ���������,��� ������ �������� ����� �������� ������
		//� ��������� ��������� ������.
		while (Temp)//���� ��������� �������� ��������� �����
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;
		}
		cout << " ���������� ��������� ������:" << size << endl;
		cout << "����� ��������� ������:" << Head->count << endl;
	}
};
 #define BASE_CHECK
//#define DESTRUCTOR_CHECK
//#define HOME_WORK_1
//#define HOME_WORK_2

void main()
{
    setlocale(LC_ALL, "");

#ifdef   BASE_CHECK
	int n;
	//cout << "������� ������ ������: "; cin >> n;
	ForwardList list;
	//list.pop_front
	//for (int i = 0; i < n; i++)
	//{
	//	//list.push_front(rand() % 100);
	//	//list.push_back(rand() % 100);

	//}
	list.push_back(1);
	list.push_back(1);
	list.push_back(2);
	list.push_back(2);
	list.push_back(3);

	list.print();
	//list.push_back(123);
	//list.pop_front();
	//list.pop_back();
	int index;
	int value;
	
	/*cout << " ������� ������ ������������ ��������:";
	cin >> index;
	cout << " ������� �������� ������������ ��������:";
	cin >> value;
	list.insert(index, value);
	list.print();
	cout << "������� ������ ���������� ��������:";
	cin >> index;
	list.erase(index);
	list.print();	*/
	cout << "�������� ������:" << endl;	
	list.reverse();
	list.print();	
	cout << "���������� �����:"<<endl;
	list.unigue();
	list.print();

#endif //  BASE_CHECK
//	ForwardList list1;
//	list1.push_back(3);
//	list1.push_back(5);
//	list1.push_back(8);
//	list1.push_back(13);
//	list1.push_back(21);
//	list1.print();
//	ForwardList list2;
//	list2.push_back(34);
//	list2.push_back(55);
//	list2.push_back(89);
//	list2.print();

#ifdef DESTRUCTOR_CHECK

	int n;
	cout << " ������� ������ ������:"; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand());
	}
	cout << "������ ��������:" << endl;
	list.print();
#endif //DESTRUCTOR_CHECK


#ifdef HOME_WORK_1

	int n;
cout << "������� ������ ������:"; cin >> n;
ForwardList list(n);
for( int i=0;  i< n; i++)
{
	list[i] = rand() % 100;
}
for (int i = 0; i < n; i++)
{
	cout << list[i] << tab ;
}
cout << endl; 
#endif // HOME_WORK_1

#ifdef HOME_WORK_2

	ForwardList list = { 3,5,8,13,21 };
	list.print();
#endif // HOME_WORK_2
}


