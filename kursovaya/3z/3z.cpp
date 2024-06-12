﻿#include <iostream>
#include <random>
#include <string>
#include <vector>

// Перечисление для классов персонажей
enum class PersonClass
{
    Defender = 1,
    Healer,
    MeleeFighter,
    RangedFighter
};


// Базовый класс элементов экипировки
class Equiper
{
public:
    virtual ~Equiper() {}
    virtual void applyStats(PersonStats& stats) const = 0;
};

// случайная генерация
class GenEduipment
{
public:
    virtual ~GenEduipment() {}
    virtual Equiper* generateEquipment() = 0;
};

// Структура для характеристик персонажа
struct PersonStats
{
    int health;
    int armor;
    int strength;
    int intelligence;
    int agility;
    int accuracy;
    int luck;
    int mastery;
};

// элемент экипировки 
class Weapon : public Equiper
{
private:
    int damage;
public:
    Weapon(int damage) : damage(damage) {}

    void applyStats(PersonStats& stats) const override
    {
        stats.strength += damage;
    }
};

// Пример элемента экипировки - броня
class Armor : public Equiper
{
private:
    int armorValue;
public:
    Armor(int armorValue) : armorValue(armorValue) {}

    void applyStats(PersonStats& stats) const override
    {
        stats.armor += armorValue;
    }
};

// случайное оружие
class WeaponGenerator : public GenEduipment
{
public:
    Equiper* generateEquipment() override
    {
        // Генерация случайного урона для оружия
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 10); // Пример диапазона урона
        int damage = dis(gen);
        return new Weapon(damage);
    }
};

// случайная броня
class ArmorGenerator : public GenEduipment
{
public:
    Equiper* generateEquipment() override
    {
        // Генерация случайного значения брони
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 20); 
        int armorValue = dis(gen);
        return new Armor(armorValue);
    }
};

// Класс для игрового персонажа
class Character
{
private:
    PersonClass characterClass;
    PersonStats stats;
    std::vector<Equiper*> equipment;
public:

    Character(PersonClass characterClass) : characterClass(characterClass)
    {
        // Инициализация характеристик в зависимости от класса персонажа
        switch (characterClass)
        {
        case PersonClass::Defender:
            stats.health = 100;
            stats.armor = 50;
            stats.strength = 10;
            stats.intelligence = 10;
            stats.agility = 5;
            stats.mastery = 15;
            stats.luck = 10;
            break;
        case PersonClass::Healer:
            stats.health = 50;
            stats.armor = 50;
            stats.strength = 10;
            stats.intelligence = 100;
            stats.agility = 5;
            stats.mastery = 15;
            stats.luck = 20;
            break;
        case PersonClass::MeleeFighter:
            stats.health = 50;
            stats.armor = 50;
            stats.strength = 100;
            stats.intelligence = 10;
            stats.agility = 50;
            stats.mastery = 15;
            stats.luck = 30;
            break;
        case PersonClass::RangedFighter:
            stats.health = 50;
            stats.armor = 50;
            stats.strength = 10;
            stats.intelligence = 100;
            stats.agility = 5;
            stats.mastery = 15;
            stats.luck = 40;
            break;
        }
    }

    // Функция для добавления элемента экипировки
    void equip(Equiper* item)
    {
        equipment.push_back(item);
        item->applyStats(stats);
    }

    int calculateDamage() const
    {
        return stats.strength + stats.mastery;
    }

    int calculateProtection() const
    {
        return stats.health + stats.luck;
    }

    int calculateTherapy() const
    {
        return stats.intelligence + stats.luck;
    }

    int calculateEndurance() const
    {
        return stats.mastery + stats.luck;
    }

    int calculateRange() const
    {
        return stats.agility + stats.luck;
    }
};

int main()
{
    system("color F0");

    // Создание персонажа
    int character;

    std::cout << "Character:\n1)Defender\n2)Healer\n3)MeleeFighter\n4)RangedFighter\nTake character's class: ";
    std::cin >> character;

    PersonClass charclass = PersonClass(character);
    Character player(charclass);

    // Создание генератора для оружия и брони
    WeaponGenerator weaponGenerator;
    ArmorGenerator armorGenerator;

    // Генерация случайного оружия и брони
    Equiper* weapon = weaponGenerator.generateEquipment();
    Equiper* armor = armorGenerator.generateEquipment();

    // Экипировка персонажа
    player.equip(weapon);
    player.equip(armor);

    // Расчет урона
    int damage = player.calculateDamage();
    int protection = player.calculateProtection();
    int therapy = player.calculateTherapy();
    int endurance = player.calculateEndurance();
    int range = player.calculateRange();

    switch (character)
    {
    case 1:
        std::cout << "You choose the Defender class!\n";
        std::cout << "Damage: " << damage << std::endl;
        std::cout << "Protection: " << protection << std::endl;
        break;
    case 2:
        std::cout << "You choose the Healer class!\n";
        std::cout << "Damage: " << damage << std::endl;
        std::cout << "Protection: " << protection << std::endl;
        std::cout << "Therapy: " << therapy << std::endl;
        break;
    case 3:
        std::cout << "You choose the MeleeFighter class!\n";
        std::cout << "Damage: " << damage << std::endl;
        std::cout << "Protection: " << protection << std::endl;
        std::cout << "Endurance: " << endurance << std::endl;
        break;
    case 4:
        std::cout << "You have choose the RangedFighter class!\n";
        std::cout << "Damage: " << damage << std::endl;
        std::cout << "Protection: " << protection << std::endl;
        std::cout << "Range: " << range << std::endl;
        break;
    default:
        break;
    }
    // Очистка памяти
    delete weapon;
    delete armor;

    return 0;
}