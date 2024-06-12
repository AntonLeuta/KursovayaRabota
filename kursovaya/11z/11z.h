#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <random>
#include <ctime>
#include <random>

class TICK
{
private:
    int num;
    double prize;

public:
    TICK(int num) : num(num), prize(0) {}

    double getNum() const { return num; }
    double getPrize() const { return prize; }

    void setPrize(double amount) { prize = amount; }
};

// ����� ��� ������������� �������
class lottereya
{
private:

    std::vector<TICK> tickets;

public:
    // ��������� ������� ��� �������
    void TICKgenerator(int numTickets)
    {
        tickets.clear();
        for (int i = 1; i < numTickets; ++i)
        {
            tickets.emplace_back(i); // ��������� ������� � 1
        }
    }
    // ��������� ���������� ������
    TICK& getRandTICK()
    {
        static std::mt19937 mt(std::time(nullptr)); // ��������� ��������� �����
        std::uniform_int_distribution<int> dist(0, tickets.size() - 1);
        return tickets[dist(mt)];
    }
};

// ����� ��� ������������� ������
class lottereyaDraw
{
private:

    std::list<TICK*> winningTickets;

public:
    // ���������� ���������
    void holdPrize(lottereya& lottery, int numWinners)
    {
        winningTickets.clear();
        static std::mt19937 mt1(std::time(nullptr)); // ��������� ��������� �����
        std::uniform_int_distribution<int> dist1(0, 1000);
        for (int i = 0; i < numWinners; ++i)
        {
            TICK& ticket = lottery.getRandTICK();
            ticket.setPrize(dist1(mt1)); // ������ ��������  
            winningTickets.push_back(&ticket);
        }
    }

    // ����� ������ �� ������
    TICK* TICKnumFinder(int number)
    {
        auto it = std::find_if(winningTickets.begin(), winningTickets.end(),
            [number](TICK* t) { return t->getNum() == number; });
        return (it != winningTickets.end()) ? *it : nullptr;
    }

    // ����� ������� �� �������� ��������
    std::vector<TICK*> findTicketsByPrize(double prize)
    {
        std::vector<TICK*> result;
        for (auto ticket : winningTickets)
        {
            if (ticket->getPrize() == prize)
            {
                result.push_back(ticket);
            }
        }
        return result;
    }
};