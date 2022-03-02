#include<iostream>
using namespace std;

class Tree
{	
	class Element
	{		
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRighit = nullptr) :Data(Data), pLeft(pLeft), pRight(pRighit)
		{
			cout << " EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDecstructor:\t" << this << endl;
			delete pLeft;
			delete pRight;				
		}
		friend class Tree;
	}*Root;
	int count=0;
public:
	
	Element* getRoot()
	{
		return Root;
	}
public:
	Tree()
	{
		count++;
		this->Root = nullptr;
		cout << "TConstructor:\t" << this << endl;
	}

	Tree(Tree&& other)noexcept
	{
		count++;
		this->Root = other.Root;
		other.Root = nullptr;
		cout << "MoveConstructor:\t" << this << endl;
	}
	Tree(const Tree& other) 
	{
		count++;		
		this->Root = other.Root;		
		cout << "CopyConstructor:\t" << this << endl;
	}
	~Tree()
	{
		cout << "TDestructor:\t" << this << endl;		
	    delete Root;
		count--;
	}

	Tree& operator=(Tree& other)
	{
		this->Root = other.Root;		
		return *this;
		count--;
	}
	void insert(int Data)
	{
		insert(Data, Root);
	}
	int minValue()const
	{
		return minValue(Root);
	}
	int maxValue()const
	{
		return maxValue(Root);
	}
	void print()const
	{
		print(Root);
	}
	int size()const
	{
		return size(Root);
	}
	int sum()const
	{
		return sum(Root);
	}
	double avg()
	{
		return avg(Root);
	}

private:

	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr) 
		{
			this->Root = new Element(Data);
			return;
		}
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << "\t";
		print(Root->pRight);
	}
	int minValue(Element* Root)const
	{
		if (Root == nullptr)return 0;
	/*	if (Root->pLeft == nullptr)
		{
			return Root->Data;
		}
		else
		{
			return minValue(Root->pLeft);
		}
		return Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);*/
		return Root->pLeft ? minValue(Root->pLeft):Root->Data;
    }
	int maxValue(Element* Root)const
	{
		if (Root == nullptr)return 0;
	/*	if (Root->pRight == nullptr)
		{
			return Root->Data;
		}
		else
		{
			return maxValue(Root->pRight);
		}*/
		return Root->pRight ? maxValue(Root->pRight) : Root->Data;
	}
	int size(Element* Root)const
	{
		//if (Root == nullptr)return 0;
		//return size(Root->pLeft) + size(Root->pRight)+1;
		return Root == nullptr ?0 : size(Root->pLeft) + size(Root->pRight) + 1;
	}
	int sum(Element* Root)const
	{
		//if (Root ==nullptr)return 0;		
		//return Root->Data + sum(Root->pLeft) +sum(Root->pRight);
		return Root==nullptr ?0 : Root->Data + sum(Root->pLeft) + sum(Root->pRight);
	}
	double avg(Element*Root)
	{
		if (Root == nullptr)return 0;	   
		int sum = Root->Data + avg(Root->pLeft) + avg(Root->pRight) ;
		if (!Root->pLeft && !Root->pRight)return sum;
		if (Root->pLeft && Root->pRight)return sum/3;
	   return sum/2; 		
	}

};


void main()
{
	
	setlocale(LC_ALL, "");
	int n;
	cout << " Введите размер дерева:"; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	tree.print();
	cout << endl;	
	cout << " Минимальное значение в дереве: "<<tree.minValue()  << endl;
	cout << " Максимальное значение в дереве: " <<tree.maxValue()<< endl;
	cout << " Количество элементов в дереве:" << tree.size() << endl;
	cout << " Сумма элементов дерева:" <<tree.sum()<< endl;
	cout << " Среднее арифметическое значение дерева:"<<tree.avg() << endl;
	
}