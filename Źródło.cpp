#include <iostream>

using namespace std;

class Heap
{
private:
	int* kopiec; //tablica dynamiczna przechowujaca elementy kopca
	int capacity; //maksymalny rozmiar tablicy (kopca)
	int heap_size; //liczba elementow w tablicy, czyli liczna elementow kopca
public:
	Heap(int c); //konstruktor, tworzy pusty kopiec o pojemnosci c
	Heap(); //konstruktor do testow kopca - nalezy utworzyc kopiec z nast. zawartoscia: 1,2,3,5,7,9,10,9,9,12
	bool empty(); //zwraca true, jesli kopiec jest pusty, false w przeciwnym razie
	bool full(); //zwraca true, jesli kopiec jest pelny, false w przeciwnym razie
	int left(int i); //zwraca pozycje lewego syna
	int right(int i); //zwraca pozycje prawego syna
	int parent(int i); //zwraca pozycje ojca
	int getSize(); //zwraca rozmiar kopca
	void setHeapSize(int s); //ustawia rozmiar kopca
	int get(int i); //zwraca wartosc z pozycji i
	void set(int i, int x); //na pozycji i ustawia wartosc x
	void up(int i); //przywraca wlasnosc kopca metoda wynurzania
	void down(int i); //przywraca wlasnosc kopca metoda zatapiania
	friend ostream& operator<<(ostream& out, Heap& h); //wyswietla kopiec na ekranie
};

Heap::Heap(int c)
{
	kopiec = new int[c];
	capacity = c;
	heap_size = 0;
}

Heap::Heap()
{
	capacity = 20;
	kopiec = new int[capacity] {1, 2, 3, 5, 7, 9, 10, 9, 9, 12};
	heap_size = 10;
}

bool Heap::empty()
{
	if (heap_size == 0)
		return true;
	else
		return false;
}

bool Heap::full()
{
	if (heap_size == capacity)
		return true;
	else
		return false;
}

int Heap::left(int i)
{
	if (!empty())
		return 2 * i + 1;
	else
		return NULL;
}

int Heap::right(int i)
{
	if (!empty())
		return 2 * i + 2;
	else
		return NULL;
}

int Heap::parent(int i)
{
	//jesli i jest korzeniem to nie ma ojca
	if (!empty())
	{
		if ((i - 1) / 2 >= 0 && i < heap_size)
			return (i - 1) / 2;
		else
			return NULL;
	}
	else
		return NULL;
}

int Heap::getSize()
{
	return heap_size;
}

void Heap::setHeapSize(int s)
{
	heap_size = s;
}

int Heap::get(int i)
{
	if (!empty())
	{
		if (i >= 0 && i < heap_size)
			return kopiec[i];
		else
			return NULL;
	}
	else
		return NULL;
}

void Heap::set(int i, int x)
{
	kopiec[i] = x;
}

void Heap::up(int i) //i to pozycja, od ktorej zaczynamy wynurzanie
{
	int wartosc_na_pozycji_i;
	int pozycja_ojca_i;
	int wartosc_ojca_i;

	wartosc_na_pozycji_i = get(i);
	pozycja_ojca_i = parent(i);
	wartosc_ojca_i = get(pozycja_ojca_i);

	if (i > 0 && wartosc_ojca_i > wartosc_na_pozycji_i)
	{
		swap(kopiec[pozycja_ojca_i], kopiec[i]);
		up(pozycja_ojca_i); //rekurencja
	}
}

void Heap::down(int i) //i to pozycja, od której zaczynamy zatapianie kopca
{
	int pozycja_lewego_syna;
	int pozycja_prawego_syna;
	int temp;

	pozycja_lewego_syna = left(i);
	pozycja_prawego_syna = right(i);
	temp = i;

	if (get(pozycja_lewego_syna) < get(i) && pozycja_lewego_syna < heap_size)
		temp = pozycja_lewego_syna;
	if (get(pozycja_prawego_syna) < get(temp) && pozycja_prawego_syna < heap_size)
		temp = pozycja_prawego_syna;

	if (temp != i)
	{
		swap(kopiec[i], kopiec[temp]);
		down(temp); //rekurencja
	}
}

ostream& operator<<(ostream& out, Heap& h)
{
	if (h.empty())
		return out;
	for (int i = 0; i < h.heap_size; i++)
	{
		out << h.kopiec[i] << " ";
	}
	return out;
}

class PriorityQueue
{
	private:
		Heap h; //korzystam z klasy heap
	public:
		PriorityQueue(int c); //konstruktor, tworzy pusty kopiec o pojemnosci c
		bool empty(); //zwraca true, jesli kolejka jest pusta, false w przeciwnym razie
		bool full(); //zwraca true, jesli kolejka jest pelna, false w przeciwnym razie
		void insert(int x); //wstawia element z priorytetem x
		int minimum(); //zwraca element z najnizszym priorytetem
		void deleteMin(); //usuwa element z najnizszym priorytetem
		void del(int i); //usuwa element z pozycji i
		void increasePriority(int i); //zwieksza priorytet elementu na pozycji i
		void decreasePriority(int i); //zmniejsza priorytet elementu na pozycji i
		friend ostream& operator<<(ostream& out, PriorityQueue& q); //wyswietla kolejke na ekranie
};

PriorityQueue::PriorityQueue(int c)
{
	Heap temp(c);
	h = temp;
}

bool PriorityQueue::empty()
{
	if (h.empty())
		return true;
	else
		return false;
}

bool PriorityQueue::full()
{
	if(h.full())
		return true;
	else
		return false;
}

void PriorityQueue::insert(int x)
{
	if (!full())
	{
		h.set(h.getSize(), x); //wstawiam nowy element jako lisc
		h.setHeapSize(h.getSize() + 1); //zwiekszam heap_size
		h.up(h.getSize() - 1); //przywracam wlasnosc kopca metoda wynurzania
	}
	return;
}

int PriorityQueue::minimum()
{
	if (!empty())
		return h.get(0); //zwracam wartosc z korzenia kopca
	return NULL;
}

void PriorityQueue::deleteMin()
{
	if (!empty())
	{
		h.set(0, h.get(h.getSize() - 1)); //ustawiam na miejscu korzenia ostatni z lisci
		h.setHeapSize(h.getSize() - 1); //usuwam ostatni lisc poprzez zmniejszenie heap_size
		h.down(0); //przywracam wlasnosc kopca metoda zatapiania
	}
}

void PriorityQueue::del(int i)
{
	if (i >= 0 && i < h.getSize())
	{
		if (i == 0) //jesli i jest korzeniem
		{
			deleteMin();
			return;
		}
		else if (2 * i + 2 > h.getSize()) //jesli i jest lisciem
		{
			h.setHeapSize(h.getSize() - 1);
			return;
		}
		else
		{
			h.set(i, h.get(h.getSize() - 1)); //na pozycji i wstawiam ostatniego z lisci
			h.setHeapSize(h.getSize() - 1); //zmniejszam heap_size
			h.down(i); //przywracam wlasnosc kopca metoda zatapiania
		}
	}
}

void PriorityQueue::increasePriority(int i)
{
	if (!empty())
	{
		h.set(i, h.get(i) + 1); //zwiekszam priorytet
		h.down(i); //przywracam wlasnosc kopca metoda zatapiania
	}
}

void PriorityQueue::decreasePriority(int i)
{
	if (!empty())
	{
		h.set(i, h.get(i) - 1); //zmniejszam priorytet
		h.up(i); //wynurzam kopiec
	}
}

ostream& operator<<(ostream& out, PriorityQueue& q)
{
	if (q.empty())
		return out;
	for (int i = 0; i < q.h.getSize(); i++)
	{
		out << q.h.get(i) << " ";
	}
	return out;
}

int main()
{
	PriorityQueue kolejka = PriorityQueue(10);

	cout << kolejka << endl;

	/**kolejka.insert(12);
	kolejka.insert(1);
	kolejka.insert(4);
	kolejka.insert(6);
	kolejka.insert(22);
	kolejka.insert(8);

	cout << kolejka << endl;

	kolejka.deleteMin();

	cout << kolejka << endl;

	kolejka.del(1);

	cout << kolejka << endl;

	kolejka.increasePriority(1);

	cout << kolejka << endl;**/

	kolejka.insert(8);
	kolejka.insert(2);
	kolejka.insert(6);
	kolejka.insert(5);
	kolejka.insert(2);

	cout << kolejka << endl;

	kolejka.decreasePriority(1);

	cout << kolejka << endl;
	
	/**Heap kopiec = Heap();

	cout << kopiec << endl;

	kopiec.set(8, 4);

	kopiec.up(8);

	cout << kopiec << endl;

	kopiec.set(0, 15);

	kopiec.down(0);

	cout << kopiec << endl;**/

	return 0;
}