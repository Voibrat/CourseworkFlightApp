//
// Created by Дмитрий Филиппов on 29.04.2023.
//

#ifndef COURSEWORKFLIGHTAPP_FLIGHT_H
#define COURSEWORKFLIGHTAPP_FLIGHT_H
#endif //COURSEWORKFLIGHTAPP_FLIGHT_H

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

using namespace std;
namespace fs = std::filesystem;

class Flight
{
private:
    std::string airport_name, flight_name, flight_number, departure_time;
    int distance, chairs_amount;
    double ticket_price;

public:
    Flight()
    {
        airport_name = "";
        flight_name = "";
        flight_number = "";
        departure_time = "";
        distance = 0;
        chairs_amount = 0;
        ticket_price = 0.0;

    }

    // Сеттеры
    void setAirportName(std::string name)
    {
        airport_name = name;
    }

    void setFlightName(std::string name)
    {
        flight_name = name;
    }

    void setFlightNumber(std::string number)
    {
        flight_number = number;
    }

    void setDepartureTime(std::string time)
    {
        departure_time = time;
    }

    void setChairsAmount(int c)
    {
        chairs_amount = c;
    }

    void setDistance(int d)
    {
        distance = d;
    }

    void setTicketPrice(double price)
    {
        ticket_price = price;
    }

    // Геттеры
    std::string getAirportName()
    {
        return airport_name;
    }

    std::string getFlightName()
    {
        return flight_name;
    }

    std::string getFlightNumber()
    {
        return flight_number;
    }

    std::string getDepartureTime()
    {
        return departure_time;
    }

    int getChairsAmount()
    {
        return chairs_amount;
    }

    int getDistance()
    {
        return distance;
    }

    double getTicketPrice()
    {
        return ticket_price;
    }

    // Функции
    /*
    int getValue(string query)
    {
        int value;
        cout << query.c_str();
        while(!(cin >> value))
        {
            if(cin.eof())
            { throw "eof"; }
            cin.clear();
            cin.ignore(1000,'\n');
            cout << "Try again: ";
        }
        return value;
    }
    */
    void read()
    {
        std::string input;
        std::regex time_regex("^([0-1]?[0-9]|2[0-3]):([0-5][0-9])$");

        std::cout << "Введите название аэропорта: ";
        std::cin >> airport_name;
        std::cout << "Введите наименование рейса: ";
        std::cin >> flight_name;
        std::cout << "Введите номер рейса: ";
        std::cin >> flight_number;
        // проверка на правильный ввод времени
        while (true) {
            std::cout << "Введите время вылета: ";
            std::cin >> input;
            if (std::regex_match(input, time_regex)) {
                departure_time = input;
                break;
            } else {
                std::cout << "Ошибка формата времени!\nПожалуйста повторите ввод" << std::endl;
            }
        }
        // Проверка на правильный ввод chairs_amount
        while (true) {
            std::cout << "Введите количество кресел: ";
            if (std::cin >> chairs_amount) {
                break;
            }
            std::cout << "Некорректный ввод, повторите попытку.\n";
            std::string temp;
            std::getline(std::cin >> std::ws, temp);
        }

        // Проверка на правильный ввод distance
        while (true) {
            std::cout << "Введите дистанцию: ";
            if (std::cin >> distance) {
                break;
            }
            std::cout << "Некорректный ввод, повторите попытку.\n";
            std::string temp;
            std::getline(std::cin >> std::ws, temp);

        }

        // Проверка на правильный ввод ticket_price
        while (true) {
            std::cout << "Введите цену билета: ";
            if (std::cin >> ticket_price) {
                break;
            }
            std::cout << "Некорректный ввод, повторите попытку.\n";
            std::string temp;
            std::getline(std::cin >> std::ws, temp);
        }
    }

    //запись для бинарников
    void write(std::ofstream& fout)
    {
        int len = airport_name.length();
        fout.write((char*)&len, sizeof(int));
        fout.write(airport_name.c_str(), len);

        len = flight_name.length();
        fout.write((char*)&len, sizeof(int));
        fout.write(flight_name.c_str(), len);

        len = flight_number.length();
        fout.write((char*)&len, sizeof(int));
        fout.write(flight_number.c_str(), len);

        len = departure_time.length();
        fout.write((char*)&len, sizeof(int));
        fout.write(departure_time.c_str(), len);

        fout.write((char*)&chairs_amount, sizeof(int));
        fout.write((char*)&distance, sizeof(int));
        fout.write((char*)&ticket_price, sizeof(double));
    }

    //чтение для бинарников
    void read(std::ifstream& fin)
    {
        int len;
        char* value;

        fin.read((char*)&len, sizeof(int));
        value = new char[len + 1];
        fin.read(value, len);
        airport_name = value;
        delete[] value;
        if (airport_name == "") {return;}

        fin.read((char*)&len, sizeof(int));
        value = new char[len + 1];
        fin.read(value, len);
        flight_name = value;
        delete[] value;

        fin.read((char*)&len, sizeof(int));
        value = new char[len + 1];
        fin.read(value, len);
        flight_number = value;
        delete[] value;

        fin.read((char*)&len, sizeof(int));
        value = new char[len + 1];
        fin.read(value, len);

        // проверка на правильный ввод времени
        std::regex time_regex("^([0-1]?[0-9]|2[0-3]):([0-5][0-9])$");
        if (std::regex_match(value, time_regex)) {
            departure_time = value;
        } else {
            departure_time = "";
            std::cerr << "\nОшибка в формате времени!\n";
        }

        delete[] value;

        fin.read((char*)&chairs_amount, sizeof(int));
        fin.read((char*)&distance, sizeof(int));
        fin.read((char*)&ticket_price, sizeof(double));
    }


    //функции для записи и чтения в обычном формате
    void write_text(std::ofstream& fout) {
        fout << airport_name << std::endl;
        fout << flight_name << std::endl;
        fout << flight_number << std::endl;
        fout << departure_time << std::endl;
        fout << chairs_amount << std::endl;
        fout << distance << std::endl;
        fout << ticket_price << std::endl;
    }

    void read_text(std::ifstream& fin) {
        std::getline(fin, airport_name);
        if (airport_name.empty()) {
            return;
        }
        std::getline(fin, flight_name);
        std::getline(fin, flight_number);
        std::getline(fin, departure_time);

        // проверка на правильный ввод времени
        std::string tmp;
        std::regex time_regex("^([0-1]?[0-9]|2[0-3]):([0-5][0-9])$");
        if (!std::regex_match(departure_time, time_regex)) {
            std::cerr << "\nОшибка в формате времени!\nПроверьте и измените введеные данные через консоль!" << std::endl;
            std::cerr << "Аэропорт " << airport_name <<std::endl;
            std::cerr << "Рейс №" << flight_number;
            departure_time = "";
        }

        if (!(fin >> chairs_amount)) {
            std::cerr << "\nЧасть введенных данных некорректна, проверьте данные в файле\nЛибо измените введеные данные через консоль";

        }
        fin.ignore(); // пропустить символ новой строки

        if (!(fin >> distance)) {
            std::cerr << "\nЧасть введенных данных некорректна, проверьте данные в файле\nЛибо измените введеные данные через консоль";
        }
        fin.ignore(); // пропустить символ новой строки

        if (!(fin >> ticket_price)) {
            std::cerr << "\nЧасть введенных данных некорректна, проверьте данные в файле\nЛибо измените введеные данные через консоль";

        }
        fin.ignore(); // игнор ньюлайнов
    }



    void display()
    {
        std::cout << "Название Аэропорта: " << airport_name << std::endl;
        std::cout << "  Наименование рейса: " << flight_name << std::endl;
        std::cout << "  Номер рейса: " << flight_number << std::endl;
        std::cout << "  Время вылета: " << departure_time << std::endl;
        std::cout << "  Количество кресел: " << chairs_amount << std::endl;
        std::cout << "  Расстояние: " << distance << " км" << std::endl;
        std::cout << "  Цена билета: " << ticket_price << " $" << std::endl;
        std::cout << std::endl;
    }
};