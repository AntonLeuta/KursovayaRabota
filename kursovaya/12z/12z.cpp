#include "12z.h"

int main()
{
    system("color F0");
    ProcessingOfMessages processing;
    std::fstream inputFile("messages.txt");

    if (!inputFile.is_open())
    {
        std::cout << "ERROR: file is not open or found." << std::endl;
        return 1;
    }

    std::string line;
    while (getline(inputFile, line))
    {
        std::stringstream ss(line);
        std::string user, time, Text;

        ss >> user;
        ss >> time;

        // Оставшаяся часть строки считывается как текст сообщения
        getline(ss, Text); 
        processing.InsertMessage(user, time, Text);
    }
    inputFile.close();

    std::string name;
    std::string timestart;
    std::string timestop;2;
    std::cout << "Enter the name of the user whose messages you want to see:" << std::endl;
    std::cin >> name;

    // Использование методов класса "ProcessingOfMessages"
    std::cout << "All messages of user" << name << "':" << std::endl;
    processing.coutUserMessage(name);

    // Пользователь и время
    std::cout << "\nEnter the name of the user whose messages you want to see during this time period::" << std::endl;
    std::cin >> name;

    //Начало отправки сообщений пользователя
    std::cout << "Enter the start time of sending the message to the nearest milliseconds: ";
    std::cin >> timestart;

    //Конец отправки сообщений пользователя
    std::cout << "Enter the end time of sending the message to the nearest milliseconds: ";
    std::cin >> timestop;

    //Сообщения пользователя между:
    std::cout << "Messages of user '" << name << "' between " << timestart << " and " << timestop << std::endl;
    processing.printUserMessagesInTimeInterval(name, timestart, timestop);

    std::cout << "\nEnter the time interval within which you want to display messages from all users: ";
    std::cin >> timestart;
    std::cout << "and ";
    std::cin >> timestop;

    std::cout << "All messages between " << timestart << " and " << timestop << std::endl;
    processing.coutMsgInSomeInterval(timestart, timestop);

    std::cout << "\nEnter the username of the message whose message you want to delete: ";
    std::cin >> name;
    processing.deleteUserMessages(name);

    std::cout << "\nEnter the username and time of the message you want to delete: ";
    std::cin >> name >> timestart;
    processing.deleteOfMessage(name, timestart);

    return 0;
}