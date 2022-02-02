#include <iostream>
using namespace std;

#define tab "\t"

class Element
{
	int Data;	//Значение элемента
	Element* pNext;//Адрес следующего элемента
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

class  ForwardList//Односвязный список
{
	Element* Head;//Голова списка-указывает на начальный элемент списка
public:
	ForwardList()
	{
		Head = nullptr;//усли голова указывает на 0,то список пуст
		cout << "LConstructor:\t"<< this << endl;
	}
	
	~ForwardList()
	{
		cout << "LDestructor:\t" << this << endl;
	}

	void push_front(int Data)
	{
		Element* New = new Element(Data);//Создаем новый элемент и помещаем его Data
		New->pNext = Head;//Привязываем новый элемент к началу списка
		Head = New;//Переводим Голову на новый элемент
	}

	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		//Создает новый элемент
		Element* New = new Element(Data);
		//доходим до конца списка
		Element* Temp = Head;
		while (Temp->pNext)//Пока,pNext текущего элемента
		Temp = Temp->pNext;//переходим на следующий элемент
		//Теперь мы находимся в последнем элементе
		//Присоединяем новый элемент к последнему
		Temp->pNext = New;
	}
	void insert(int index, int Data)
	{		
		if (index==0 || Head == nullptr) return push_front(Data);
		if (index > Head->count)return;
		Element* New = new Element(Data);
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)
		Temp = Temp->pNext;
		New->pNext = Temp->pNext;
		Temp->pNext = New;
	}
	void erase(int index)
	{
		if (Head == nullptr)return;
		Element* Erased = Head;
		Element* prev = nullptr;

		for (int i = 0; i < index; i++) {
			prev = Erased;
			Erased = Erased->pNext;
		}

		if (prev != nullptr) 
		{
			prev->pNext = Erased->pNext;
		}

		delete Erased;
	}
	//     Removing elements;

	void pop_front()
	{
		if (Head == nullptr)return;
		//Запоминаем адрес удаляемого элемента
		Element* Erased = Head;
		//Исключаем элемент из списка
		Head = Erased->pNext;
		//удаляем
		delete Erased;
	}
	void pop_back()
	{
		if (Head == nullptr)return;
		if (Head->pNext == nullptr)return pop_front();
		//Доходим до последнего элемента
		Element* Temp = Head;
		while (Temp->pNext->pNext)Temp = Temp->pNext;
		//Удаляем элемент из памяти
		delete Temp->pNext;
		//Затираем адрес удаленного элемента нулем
		Temp->pNext = nullptr;
	}
	void print()const
	{
		Element* Temp = Head;//temp-это итератор
		//Итератор- это указатель,при помощи которого можно получить доступ
		//к элементам структуры данных.
		while (Temp)//Пока Интератор содержит ненулевой адрес
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;
		}
		cout << " Количество элементов списка:" << Head->count << endl;
	}
};


void main()
{
    setlocale(LC_ALL, "");
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	//list.pop_front
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	//list.push_back(123);
	//list.pop_front();
	//list.pop_back();
	int index;
	int value;
	cout << " Введите индекс добавляемого элемента:";
	cin >> index;
	cout << " Введите значение добавляемого элемента:";
	cin >> value;
	list.insert(index, value);
	list.print();
	cout << "Введите индекс удаляемого элемента:";
	cin >> index;
	list.erase(index);
	list.print();
}
