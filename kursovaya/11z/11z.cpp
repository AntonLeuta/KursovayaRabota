#include "11z.h"

int main()
{
    system("color F1");

    unsigned long count_ticket;

    std::cout << "Enter count tickets: ";
    std::cin >> count_ticket;

    lottereya lott;
    lott.TICKgenerator(count_ticket);

    lottereyaDraw draw;
    draw.holdPrize(lott, 50);

    unsigned long find_ticket;

    std::cout << "Enter ticket's number: ";
    std::cin >> find_ticket;

    // Пример поиска билета по номеру и вывода выигрышей
    TICK* ticket = draw.TICKnumFinder(find_ticket);
    if (ticket)
    {
        std::cout << "Ticket " << ticket->getNum() << " won $" << ticket->getPrize() << std::endl;
    }
    else
    {
        std::cout << "Ticket not found." << std::endl;
    }

    return 0;
}