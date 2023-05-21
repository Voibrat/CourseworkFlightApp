//
// Created by Дмитрий Филиппов on 29.04.2023.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <set>
#include <filesystem>
#include <locale>
#include <chrono>
#include <thread>
#include <cstdlib>
#include "Flight.h"
#include "Functions.h"

int main()
{

    int choiceLoad = 0;
    std::string tableChoice = "1";
    std::cout << "Выберите вариант чтения данных:" << std::endl;
    std::cout << "1. Из txt файла" << std::endl;
    std::cout << "2. Из bin файла" << std::endl;
    std::cout << "Сделайте выбор: ";
    std::cin >> choiceLoad;

    if (choiceLoad == 1) {loadFlightsTxt();}
    else if (choiceLoad == 2) {loadFlights();}
    else {
        std::cerr << "Ошибка ввода, пожалуйста, попробуйте еще раз" << std::endl;
        return 0;
    }

    vectorSort();

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
        std::cout << "9. Изменение отображения данных о рейсах" << std::endl;
        std::cout << "10. Выход" << std::endl;
        std::cout << "Сделайте выбор: ";

        int choice;
        std::string modChoice, editChoice, tableChoiceEdit;
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
            vectorSort();
            if (tableChoice == "1") {displayFlights();}
            else if (tableChoice == "2") {displayFlightsTable();}
            break;
        case 3:
            searchFlights(tableChoice);
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
                    editTimeFlight(tableChoice);
                    break;
                }
                else if (editChoice == "2") {
                    editPriceFlight(tableChoice);
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
                    deleteFlight(tableChoice);
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
            findClosestAndFarthest(tableChoice);
            break;
        case 7:
            findCheapestAndMostExpensive(tableChoice);
            break;
        case 8:
            while (true) {
                std::cout << "Вы уверены что хотите модифицировать данные из внешнего файла?" << std::endl;
                std::cout << "1. Продолжить" << std::endl;
                std::cout << "2. Вернуться" << std::endl;
                std::cout << "Сделайте выбор: ";
                std::cin >> modChoice;

                if (modChoice == "1") {
                    if (tableChoice == "1") {modificationFlight("1");}
                    else if (tableChoice == "2") {modificationFlight("2");}
                    break;
                }
                else if (modChoice == "2")
                {
                    break;
                }
                else { std::cerr << "Ошибка ввода" << std::endl; }
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
            break;
        case 9:
            while (true) {
                std::cout << "Вы уверены что хотите изменить способ вывода?" << std::endl;
                std::cout << "В данный момент выбран вариант: ";
                if (tableChoice == "1") {std::cout << "Лаконичный" << std::endl;}
                else if (tableChoice == "2") {std::cout << "Табличный" << std::endl;}

                std::cout << "1. Продолжить" << std::endl;
                std::cout << "2. Вернуться" << std::endl;
                std::cout << "Сделайте выбор: ";
                std::cin >> tableChoiceEdit;

                if (tableChoiceEdit == "1") {
                    if (tableChoice == "1") {tableChoice = "2";}
                    else if (tableChoice == "2") {tableChoice = "1";}
                }
                else if (tableChoiceEdit == "2")
                {
                    tableChoiceEdit = "0";
                    break;
                }
                else { std::cerr << "Ошибка ввода" << std::endl; }

            }
            break;
        case 10:
            saveFlights();
                saveFlightsTxt();
                exit(0);
        default:
            std::cerr << "Ошибка ввода";
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            break;
        }

        std::cout << std::endl;
    }
}
