#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <set>
#include <filesystem>
#include <locale.h>
#include <regex>
#include <limits>
#include <chrono>
#include <thread>
#include <cstdlib>
#include "Flight.h"
#include "Functions.h"

using namespace std;
namespace fs = std::filesystem;

int main()
{
    setlocale(LC_ALL, "Russian");

    int choiceLoad = 0;

    std::cout << "Выберите вариант чтения данных:" << std::endl;
    std::cout << "1. Из txt файла" << std::endl;
    std::cout << "2. Из bin файла" << std::endl;
    std::cout << "Сделайте выбор: ";
    std::cin >> choiceLoad;

    if (choiceLoad == 1) {
        loadFlightsTxt();
        if (!flights.empty())
        {
            //flights.pop_back();
        }
    }
    else if (choiceLoad == 2) {
        loadFlights();
        //удаляет последний элемент вектора классов, решает проблему пустых экземпляров класса FLight при чтении из файла
        if (!flights.empty())
        {
            //flights.pop_back();
        }
    }
    else {
        std::cerr << "Ошибка ввода, пожалуйста, попробуйте еще раз" << std::endl;
        return 0;
    }

    //удаляет последний элемент вектора классов, частично решает проблему пустых экземпляров класса FLight при чтении из файла
    //flights.pop_back();

    //emptyChecker();
    std::cout << "Подождите, идет загрузка данных..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));


    while (true)
    {
        std::cout << std::endl << "===================================================" << std::endl;
        std::cout << "____________FLIGHTS CONSOLE APPLICATION____________" << std::endl;
        std::cout << "===================================================" << std::endl;
        std::cout << "1. Добавить рейс" << std::endl;
        std::cout << "2. Показать все рейсы" << std::endl;
        std::cout << "3. Поиск рейсов" << std::endl;
        std::cout << "4. Редактировать рейс" << std::endl;
        std::cout << "5. Удалить рейс" << std::endl;
        std::cout << "6. Найти самые короткий и длинный рейсы" << std::endl;
        std::cout << "7. Найти самые дешевые и самые дорогие авиабилеты" << std::endl;
        std::cout << "8. Модификация данных из файла" << std::endl;
        std::cout << "9. Выход" << std::endl;
        std::cout << "Сделайте выбор: ";

        int choice;
        std::string modChoice, editChoice;
        std::cin >> choice;
        std::cout << std::endl;
        switch (choice)
        {
        case 1:
            while (true) {
                std::cout << "Вы уверены что хотите продолжить?" << std::endl;
                std::cout << "1. Продолжить" << std::endl;
                std::cout << "2. Вернуться" << std::endl;
                std::cout << "Сделайте выбор: ";
                std::cin >> modChoice;
                std::cout << "  " << std::endl;
                if (modChoice == "1") {
                    addFlight();
                    break;
                }
                else if (modChoice == "2")
                {
                    break;
                }
                else { std::cerr << "Ошибка ввода" << std::endl; }
            }
            break;
        case 2:
            displayFlights();
            break;
        case 3:
            searchFlights();
            break;
        case 4:
            while (true)
            {
                std::cout << "1. Изменить время вылета" << std::endl;
                std::cout << "2. Изменить цену авиабилета" << std::endl;
                std::cout << "3. Вернуться в меню" << std::endl;
                std::cout << "Сделайте выбор: ";
                std::cin >> editChoice;
                if (editChoice == "1")
                {
                    editTimeFlight();
                    break;
                }
                else if (editChoice == "2") {
                    editPriceFlight();
                    break;
                }
                else if (editChoice == "3") {
                    break;
                }
                else
                {
                    std::cerr << "Ошибка ввода." << std::endl;
                }
            }
            break;
        case 5:
            while (true) {
                std::cout << "Вы уверены что хотите продолжить?" << std::endl;
                std::cout << "1. Продолжить" << std::endl;
                std::cout << "2. Вернуться" << std::endl;
                std::cout << "Сделайте выбор: ";
                std::cin >> modChoice;
                if (modChoice == "1") {
                    deleteFlight();
                    break;
                }
                else if (modChoice == "2")
                {
                    break;
                }
                else { std::cerr << "Ошибка ввода" << std::endl; }
            }
            break;

        case 6:
            findClosestAndFarthest();
            break;
        case 7:
            findCheapestAndMostExpensive();
            break;
        case 8:
            while (true) {
                std::cout << "Вы уверены что хотите модифицировать данные из внешнего файла?" << std::endl;
                std::cout << "1. Продолжить" << std::endl;
                std::cout << "2. Вернуться" << std::endl;
                std::cout << "Сделайте выбор: ";
                std::cin >> modChoice;
                if (modChoice == "1") {
                    modificationFlight();
                    break;
                }
                else if (modChoice == "2")
                {
                    break;
                }
                else { std::cerr << "Ошибка ввода" << std::endl; }
            }
            break;
        case 9:
            saveFlights();
            saveFlightsTxt();
            exit(0);
        default:
            std::cerr << "Ошибка ввода" << std::endl;
            break;
        }

        std::cout << std::endl;
    }
}
