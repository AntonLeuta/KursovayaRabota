
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <sstream>
#include <ctime>


struct Message
{
    std::string name;
    std::string time;
    std::string text;

    Message(const std::string& user, const std::string& t, const std::string& msg)
        : name(user), time(t), text(msg) {}

    friend std::ostream& operator<<(std::ostream& os, const Message& msg)
    {
        os << msg.name << " " << msg.time << msg.text;
        return os;
    }
};


struct MessageComparator
{
    bool operator()(const Message* lhs, const Message* rhs) const
    {
        if (lhs->name != rhs->name)
        {
            return lhs->name < rhs->name;
        }
        return lhs->time < rhs->time;
    }
};


class ProcessingOfMessages final
{
private:

    std::set<Message*, MessageComparator> messages;

public:

    ProcessingOfMessages() = default;

    ProcessingOfMessages(const ProcessingOfMessages& other)
    {
        for (auto msg : other.messages)
        {
            messages.insert(new Message(*msg));
        }
    }
    ProcessingOfMessages(ProcessingOfMessages&& other) noexcept
        : messages(std::move(other.messages)) {}

    ProcessingOfMessages& operator=(const ProcessingOfMessages& other)
    {
        if (this != &other)
        {

            for (auto msg : messages)
            {
                delete msg;
            }
            messages.clear();


            for (auto msg : other.messages)
            {
                messages.insert(new Message(*msg));
            }
        }
        return *this;
    }

    ProcessingOfMessages& operator=(ProcessingOfMessages&& other) noexcept
    {
        if (this != &other)
        {
            for (auto msg : messages)
            {
                delete msg;
            }
            messages.clear();

            messages = std::move(other.messages);
        }
        return *this;
    }

    ~ProcessingOfMessages()
    {
        for (auto msg : messages)
        {
            delete msg;
        }
        messages.clear();
    }
public:

    void InsertMessage(const std::string& user, const std::string& time, const std::string& text)
    {
        Message* msg = new Message(user, time, text);
        messages.insert(msg);
    }

    // ¬се сообщени€ конкретного заданного пользовател€
    void coutUserMessage(const std::string& User) const
    {
        for (auto msg : messages)
        {
            if (msg->name == User)
            {
                std::cout << *msg << std::endl;
            }
        }
    }

    // —ообщени€ конкретного заданного пользовател€ и интервала
    void printUserMessagesInTimeInterval(const std::string& user, const std::string& startTime, const std::string& endTime) const
    {
        for (auto msg : messages)
        {
            if (msg->name == user && msg->time >= startTime && msg->time <= endTime)
            {
                std::cout << *msg << std::endl;
            }
        }
    }

    // —ообщени€ из конкретного интервала
    void coutMsgInSomeInterval(const std::string& startTime, const std::string& endTime) const
    {
        for (auto msg : messages)
        {
            if (msg->time >= startTime && msg->time <= endTime)
            {
                std::cout << *msg << std::endl;
            }
        }
    }

    // ”даление сообщени€
    void deleteOfMessage(const std::string& user, const std::string& time)
    {
        for (auto it = messages.begin(); it != messages.end(); ++it)
        {
            if ((*it)->name == user && (*it)->time == time)
            {
                delete* it;
                messages.erase(it);
                return;
            }
        }
    }

    // ”даление всех сообщений заданного пользовател€
    void deleteUserMessages(const std::string& user)
    {
        for (auto it = messages.begin(); it != messages.end();)
        {
            if ((*it)->name == user)
            {
                delete* it;
                it = messages.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }
};