#include<iostream>
using namespace std;
#define tab "\t"

class List
{
	class Element
	{
		int Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr) :
			Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << " EDestructor:\t" << this << endl;
		}
		friend class List;
	}*Head,*Tail;
	size_t size;//size_t-unsigned int
public:
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << " LConsructor:\t" << this << endl;
	}
	~List()
	{
		cout << "LDestructor:\t" << this << endl;
	}
	     //Adding elements:
	void push_front(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
		   size++;
		   return;
		}
	Element* New = new Element(Data);
	New->pNext = Head;
	Head->pPrev = New;
	Head = New;
	//Head=Head->pPrev=new Element(Data,Head)
	size++;
	}

	// Methods:
	void print()const
	{
	   cout << "Количество элементов списка: " << size <<endl;
	   for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	}
	void revers_print()const
	{
		cout << "Количество элементов списка: " << size <<endl;
		for(Element* Temp=Tail; Temp; Temp=Temp->pPrev)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	}
	void push_back(int Data)
	{
	/*	if(Tail==nullptr)
		Tail = Tail->pNext = new Element( Data,Tail);
		size++;*/
		if (Tail == nullptr)return push_front(Data);				
		Element* Temp = Tail;
		while (Temp->pNext)
		Temp = Temp->pNext;			
		Temp->pNext = new Element(Data);
		size++;

	}
	void pop_back()
	{
		/*if (Tail == nullptr)return;		
		Element* Temp = Tail;
		while (Temp->pNext->pNext)Temp = Temp->pNext;		
		delete Temp->pNext;		
		Temp->pNext = nullptr;
		size--;*/

		if (Tail == nullptr)return;
		Element* Temp = Tail;
	    Tail= Temp->pNext;
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;

	}
	void pop_front() 
	{
		if (Head == nullptr)return;		
		Element* Temp = Head;		
		Head = Temp->pNext;		
		delete Temp;
		size--;
	}
	void insert(int index, int Data)
	{
		if (index == 0 || Head == nullptr) return push_front(Data);
		if (index > size)return;		
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)
		Temp = Temp->pNext;	
		Temp->pNext = new Element(Data, Temp->pNext);
		size++;
	}
	void erase(int index)
	{	
	if (index == 0||Head==nullptr )return pop_front();	
	Element* Temp = Head;
	Element* pPrev = nullptr;

	for (int i = 0; i < index; i++) {
		pPrev = Temp;
		Temp = Temp->pNext;
	}
	if (pPrev != nullptr) 
	{
		pPrev->pNext =Temp->pNext;
	}
	delete Temp;
	size--;
}
};
void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
		//list.push_back(rand() % 100);
	}
	list.print();
	list.push_front(100);
	list.print();
	list.revers_print();
	list.push_back(100);
	list.print();
	list.pop_back();
	list.print();
	list.pop_front();
	list.print();

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