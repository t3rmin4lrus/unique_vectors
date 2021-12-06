#ifndef ARRAYINT_H
#define ARRAYINT_H

#include <iostream>
#include <vector>
#include <cassert>
#include <string>
#include <numeric>
#include <algorithm>

//Задание 1:

class ArrayInt
{
private:
    int m_length;
    int* m_data;

public:
    ArrayInt() :
        m_length(0), m_data(nullptr)
    {
    }

    ArrayInt(int length) :
        m_length(length)
    {
        assert(length >= 0);
        if (length > 0)
            m_data = new int[length];
        else
            m_data = nullptr;
    }

    ~ArrayInt()
    {
        delete[] m_data;
    }

    void erase()
    {
        delete[] m_data;
        m_data = nullptr;
        m_length = 0;
    }

    int& operator[](int index)
    {
        assert(index >= 0 && index < m_length);
        return m_data[index];
    }

    void reallocate(int newLength)
    {

        erase();

        if (newLength <= 0)
            return;

        m_data = new int[newLength];
        m_length = newLength;
    }

    void resize(int newLength)
    {
        if (newLength == m_length)
            return;

        if (newLength <= 0)
        {
            erase();
            return;
        }

        int* data = new int[newLength];

        if (m_length > 0)
        {
            int elementsToCopy = (newLength > m_length) ? m_length : newLength;

            for (int index = 0; index < elementsToCopy; ++index)
                data[index] = m_data[index];
        }

        delete[] m_data;

        m_data = data;
        m_length = newLength;
    }

    void insertBefore(int value, int index)
    {
        assert(index >= 0 && index <= m_length);

        int* data = new int[m_length + 1];

        for (int before = 0; before < index; ++before)
            data[before] = m_data[before];

        data[index] = value;

        for (int after = index; after < m_length; ++after)
            data[after + 1] = m_data[after];

        delete[] m_data;
        m_data = data;
        ++m_length;
    }

    void remove(int index)
    {
        assert(index >= 0 && index < m_length);

        if (m_length == 1)
        {
            erase();
            return;
        }

        int* data = new int[m_length - 1];

        for (int before = 0; before < index; ++before)
            data[before] = m_data[before];

        for (int after = index + 1; after < m_length; ++after)
            data[after - 1] = m_data[after];

        delete[] m_data;
        m_data = data;
        --m_length;
    }

    void push_front(int value) { insertBefore(value, 0); }
    void push_back(int value) { insertBefore(value, m_length); }

    int getLength() { return m_length; }
};

#endif

// Задание 3:
//Часть задания с прошлого урока по классу Card

class Card
{
public:
	enum rank { ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };
	enum suit { CLUBS, DIAMONDS, HEARTS, SPADES };
	friend std::ostream& operator<<(std::ostream& os, const Card& aCard);

	Card(rank r = ACE, suit s = SPADES, bool ifu = true);

	int GetValue() const;

	void Flip();

private:
	rank m_Rank;
	suit m_Suit;
	bool m_IsFaceUp;
};

Card::Card(rank r, suit s, bool ifu) : m_Rank(r), m_Suit(s), m_IsFaceUp(ifu) {}

int Card::GetValue() const
{
	int value = 0;
	if (m_IsFaceUp)
	{
		value = m_Rank;
		if (value > 10)
		{
			value = 10;
		}
		return value;
	}
}

void Card::Flip()
{
	m_IsFaceUp = !(m_IsFaceUp);
}

class Hand
{
public:
	Hand();
	virtual ~Hand();
	void Add(Card* pCard);
	void Clear();
	int GetTotal() const;
protected:
	std::vector<Card*> m_Cards;
};

Hand::Hand()
{
	m_Cards.reserve(7);
}
Hand::~Hand()
{
	Clear();
}

void Hand::Add(Card* pCard)
{
	m_Cards.push_back(pCard);
}

void Hand::Clear()
{
	std::vector<Card*>::iterator iter = m_Cards.begin();
	for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
	{
		delete* iter;
		*iter = 0;
	}
	m_Cards.clear();
}

int Hand::GetTotal() const
{
	if (m_Cards.empty())
	{
		return 0;
	}
	if (m_Cards[0]->GetValue() == 0)
	{
		return 0;
	}
	int total = 0;
	std::vector<Card*>::const_iterator iter;
	for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
	{
		total += (*iter)->GetValue();
	}

	bool containsAce = false;
	for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
	{
		if ((*iter)->GetValue() == Card::ACE)
		{
			containsAce = true;
		}
	}

	if (containsAce && total <= 11)
	{
		total += 10;
	}
	return total;
}


int main(int argc, char* argv[])
{
	//Задание 1:
   
	ArrayInt array(10);

	for (int i = 0; i < 10; i++)
		array[i] = i + 1;

	array.resize(7);

	array.insertBefore(15, 4);

	array.remove(5);

	array.push_back(35);
	array.push_front(50);

    for (int j = 0; j < array.getLength(); j++)
        std::cout << array[j] << " ";
	
    //Задание 2:

    std::vector<int> xy = { 10, 15, 30, 25, 40, 40, 25, 32, 31, 2, 30 };
    sort(xy.begin(), xy.end(), [](const int& a, const int& b) { return a > b; });
    std::cout << "\nSorted vector is: ";
    for (int i = 0; i < xy.size(); i++)
        std::cout << xy[i] << " ";

    int mean = std::accumulate(xy.begin(), xy.end(), 0) / xy.size();
    int count = std::count(xy.begin(), xy.end(), mean);
    std::cout << "\n Mean: " << mean << '\n' << "\n Unique: " << count << '\n';

    return 0;
}