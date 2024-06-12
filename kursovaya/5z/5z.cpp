#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>


using namespace std;

struct Contract
{
    string number;
    string startDate;
    string endDate;
    string work;
    int cost;
};

struct Employee
{
    string lastName;
    string firstName;
    string middleName;
    vector<Contract> contracts;
};

map<string, Employee> employees; // Ассоциативный контейнер для хранения информации о сотрудниках 

void parseAndStoreData(const string& filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "ERROR: file is not open." << endl;
        return;
    }

    string line;
    Employee currentEmployee;

    while (getline(file, line))
    {
        if (line.empty()) continue;
        if (line.back() == '}')
        {
            // Сохранение данных о сотруднике
            string key = currentEmployee.lastName + " " + currentEmployee.firstName + " " + currentEmployee.middleName;
            employees[key] = currentEmployee;
            key = "";
            currentEmployee = Employee(); // Сброс данных для следующего сотрудника 
        }
        else if (line.back() == ' ')
        {
            // Имя сотрудника
            stringstream ss(line);
            ss >> currentEmployee.lastName >> currentEmployee.firstName >> currentEmployee.middleName;
            getline(file, line);
        }
        else
        {
            // data
            Contract contract;
            stringstream ss(line);
            string temp;
            ss >> temp; // "Договор"
            ss >> contract.number;
            ss >> temp; // "нач."
            ss >> contract.startDate;
            ss >> temp; // "кон."
            ss >> contract.endDate;
            ss >> temp; // "Работа"            
            ss >> contract.work;
            ss >> temp; // "Стоимость"        
            ss >> contract.cost;
            currentEmployee.contracts.push_back(contract);
           
        }
    }
    file.close();
}

// Функция для подсчета стоимости всех договоров сотрудника
int TotalCostOf(const Employee& employee)
{
    int totalCost = 0;
    for (const auto& contract : employee.contracts)
    {
        totalCost += contract.cost;
    }
    return totalCost;
}

// Функция для получения списка договоров сотрудника
vector<Contract> Contracts(const Employee& employee)
{
    return employee.contracts;
}

// Функция для нахождения самого продолжительного договора сотрудника
Contract DuringOfContract(const Employee& employee)
{
    auto during = max_element(employee.contracts.begin(), employee.contracts.end(),
        [](const Contract& a, const Contract& b)
        {
            return a.endDate < b.endDate;
        });
    return *during;
}

// Функция для удаления информации о сотруднике
void removeEmployee(const string& lastName, const string& firstName, const string& middleName)
{
    string key = lastName + firstName + middleName;
    employees.erase(key);
}

// Функция для нахождения самого дорогого договора сотрудника
Contract ExpensiveContract(const Employee& employee)
{
    auto ExpensiveContract = max_element(employee.contracts.begin(), employee.contracts.end(),
        [](const Contract& a, const Contract& b)
        {
            return a.cost < b.cost;
        });
    return *ExpensiveContract;
}


int main()
{
    system("color F0");
    // Пример чтения данных из файла
    parseAndStoreData("data.txt");

    // Пример использования функций
    for (const auto& pair : employees)
    {
        cout << "Employee: " << pair.first << endl;
        cout << "Total cost of contracts: " << TotalCostOf(pair.second) << endl;

        cout << "Contracts:" << endl;
        for (const auto& contract : Contracts(pair.second))
        {
            cout << contract.number << " - " << contract.cost << endl;
        }

        cout << "Longest contract: " << DuringOfContract(pair.second).number << endl;
        cout << "Most expensive contract: " << ExpensiveContract(pair.second).number << endl;

        cout << endl;
    }

    return 0;
}