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

	unsigned int size;
public:
	ForwardList()
	{
		Head = nullptr;//усли голова указывает на 0,то список пустс
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
		Element* New = new Element(Data);//Создаем новый элемент и помещаем его Data
		New->pNext = Head;//Привязываем новый элемент к началу списка
		Head = New;//Переводим Голову на новый элемент
		size++;
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
		//1) Доходим до нужного элемента:
		Element* Temp = Head;	//Создаем Итератор, и заходим в список через Голову.
		//Теперь в Итераторе адрес головного элемента.
		for (int i = 0; i < index - 1; i++)Temp = Temp->pNext;
		//2) Запоминаем адрес удаляемого элемента:
		Element* Erased = Temp->pNext;
		//3) Исключаем элемент из списка:
		//Temp->pNext = Temp->pNext->pNext;
		Temp->pNext = Erased->pNext;
		//4) Удаляем элемент из памяти:
		delete Erased;
		size--;
	}
	void pop_front()
	{
		if (Head == nullptr)return;
		//Запоминаем адрес удаляемого элемента
		Element* Erased = Head;
		//Исключаем элемент из списка
		Head = Erased->pNext;
		//удаляем
		delete Erased;
		size--;
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
		size--;
	}

	void reverse()//Список наоборот
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

	void unigue()//удаляет повторяющее значение в списке
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
		Element* Temp = Head;//temp-это итератор
		//Итератор- это указатель,при помощи которого можно получить доступ
		//к элементам структуры данных.
		while (Temp)//Пока Интератор содержит ненулевой адрес
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;
		}
		cout << " Количество элементов списка:" << size << endl;
		cout << "Общее элементов списка:" << Head->count << endl;
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
	//cout << "Введите размер списка: "; cin >> n;
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
	
	/*cout << " Введите индекс добавляемого элемента:";
	cin >> index;
	cout << " Введите значение добавляемого элемента:";
	cin >> value;
	list.insert(index, value);
	list.print();
	cout << "Введите индекс удаляемого элемента:";
	cin >> index;
	list.erase(index);
	list.print();	*/
	cout << "Обратный список:" << endl;	
	list.reverse();
	list.print();	
	cout << "Уникальные числа:"<<endl;
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
	cout << " Введите размер списка:"; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand());
	}
	cout << "Список заполнен:" << endl;
	list.print();
#endif //DESTRUCTOR_CHECK


#ifdef HOME_WORK_1

	int n;
cout << "Введите размер списка:"; cin >> n;
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


