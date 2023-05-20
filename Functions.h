//
// Created by Дмитрий Филиппов on 4.05.2023.
//
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

#ifndef COURSEWORKFLIGHTAPP_FUNCTIONS_H
#define COURSEWORKFLIGHTAPP_FUNCTIONS_H

#endif //COURSEWORKFLIGHTAPP_FUNCTIONS_H

// для бинарников
std::vector <Flight> flights;
std::vector <std::string> files;

// Ошибка при чтении из files.txt
void loadFlights()
{
    files.clear();
    flights.clear();

    fs::path list_file_name = "files.txt";
    std::ifstream list_in(list_file_name);

    if (!list_in.is_open())
    {
        std::cerr << std::endl << "Невозможно открыть файл " << list_file_name << endl;
        return;
    }
    // Скорее всего где-то здесь, судя по отладчику
    std::string file_path;
    while (getline(list_in, file_path))
    {
        files.push_back(file_path);
    }
    list_in.close();

    for (int i = 0; i < files.size(); ++i)
    {
        std::ifstream fin(files[i], std::ios::binary);
        if (!fin.is_open())
        {
            std::cerr << std::endl << "Невозможно открыть файл " << files[i] << endl;
            continue;
        }

        while (!fin.eof())
        {
            Flight f;
            f.read(fin);
            if (f.getAirportName() != "")
            {
                flights.push_back(f);
            }
        }

        fin.close();
    }
    /*
    // удаление файлов
    for (auto& file_path : files)
    {
        fs::remove(file_path);
    }
    */
}


// Не работает trunc
void saveFlights()
{
    files.clear();

    fs::path folder_name = "airports";

    if (!fs::exists(folder_name)) {
        if (fs::create_directory(folder_name)) {
        }
        else {
            std::cout << "Ошибка создания директории 'airports'. Попробуйте сделать это вручную" << std::endl;
        }
    }


    for (int i = 0; i < flights.size(); ++i)
    {
        fs::path airport_name = flights[i].getAirportName();
        fs::path file_name = (airport_name.string() + ".bin");

        std::ofstream fout(folder_name / file_name, std::ios::binary);

        fs::path new_file = folder_name / file_name;
        files.push_back((new_file).string());


        if (fout.is_open())
        {
            flights[i].write(fout);
            fout.close();
        }
        else
        {
            std::cerr << std::endl << "Невозможно открыть файл " << file_name << std::endl;
        }
    }



    fs::path list_file_name = "files.txt";
    std::ofstream list_out(list_file_name, std::ios::trunc);
    if (list_out.is_open())
    {
        for (int i = 0; i < files.size(); ++i)
        {
            list_out << files[i] << std::endl;
        }
        list_out.close();
    }
    else
    {
        std::cerr << std::endl << "Невозможно открыть файл " << list_file_name << std::endl;
    }
}



// нужно реализовать проверку на конец файла
// для тхт
void loadFlightsTxt() {
    std::ifstream fin("flights.txt", std::ios::in);

    if (fin.is_open())
    {
        while (!fin.eof())
        {
            Flight f;
            f.read_text(fin);
            if (f.getAirportName() != "")
            {
                flights.push_back(f);
            }
        }

        fin.close();
    }
}

void saveFlightsTxt() {
    std::ofstream fout("flights.txt", std::ios::trunc);

    if (fout.is_open())
    {
        for (int i = 0; i < flights.size(); i++)
        {
            if ((flights[i].getAirportName() != "") && (flights[i].getFlightName() != "") && (flights[i].getFlightNumber() != "")
                && (flights[i].getDepartureTime() != "") && (flights[i].getDistance() != 0) && (flights[i].getTicketPrice() != 0.0))
            {
                flights[i].write_text(fout);
            }
        }

        fout.close();

    }
}


void addFlight()
{
    Flight f;
    f.read();
    flights.push_back(f);
    saveFlights();
    saveFlightsTxt();
}

void displayFlights()
{
    for (int i = 0; i < flights.size(); i++)
    {
        std::cout << i << ".";
        flights[i].display();
    }
}

void searchFlights()
{
    std::string flight_name;
    std::string departure_time;
    double ticket_price;

    std::cout << "Введите номер рейса (или введите 'any' для отображения всех): ";
    std::cin >> flight_name;
    std::cout << "Введите время вылета (или введите 'any' для отображения любого): ";
    std::cin >> departure_time;
    std::cout << "Введите стоимость билета (или введите '-1' для любой цены): ";
    if (!(std::cin >> ticket_price)) {
        std::cerr << "Ошибка ввода." << std::endl;
        std::string temp;
        std::getline(std::cin >> std::ws, temp);
        return;
    }

    for (int i = 0; i < flights.size(); i++) {
        if (flight_name == "any" || departure_time == "Any" || departure_time == "ANY" ||
            flights[i].getFlightName() == flight_name) {
            if (departure_time == "any" || departure_time == "Any" || departure_time == "ANY" ||
                flights[i].getDepartureTime() == departure_time) {
                if (ticket_price == -1 || flights[i].getTicketPrice() == ticket_price) {
                    std::cout << "  ";
                    flights[i].display();
                }
            }
        }
    }
}


// переписать для работы с векторами
// Ввод данных для поиска и модификации производить с клавиатуры.
// Выбор варианта модификации определяется из диалога.
// upd: функция цундерит - меняет правильно, но говорит что неправильный номер
// upd2: починил
void editTimeFlight()
{
    setlocale(LC_ALL, "Russian");
    std::string number;
    bool flag = false;

    displayFlights();

    std::cout << "Введите номер рейса рейса чтобы изменить время вылета: ";
    std::cin >> number;

    for (int i = 0; i < flights.size(); i++) {
        if (number == flights[i].getFlightNumber()) {
            std::string Time = "";
            std::cout << "Введите новое время вылета: ";
            std::cin >> Time;
            flights[i].setDepartureTime(Time);
            saveFlights();
            saveFlightsTxt();
            flag = true;
            break;
        }
    }
    if (flag != true) {
        std::cerr<< "Неверный номер рейса." << std::endl;
    }
}

// переписать для работы с векторами
void editPriceFlight()
{
    std::string name;
    bool flag = false;

    displayFlights();

    std::cout << "Введите наименование рейса чтобы изменить его стоимость: ";
    std::cin >> name;


    for (int i = 0; i < flights.size(); i++)
    {
        if (name == flights[i].getFlightName())
        {
            double price;
            std::cout << "Введите новую стоимость билета: ";
            std::cin >> price;
            flights[i].setTicketPrice(price);
            saveFlights();
            saveFlightsTxt();
        }
    }
    if (flag != true) {
        std::cerr << "Неверный номер рейса." << std::endl;
    }
}

void modificationFlight()
{
    std::ifstream fin("modifications.txt");
    if (!fin.is_open())
    {
        std::cerr << "Ошибка открытия файла modifications.txt" << std::endl;
        return;
    }

    std::string name, number;
    double price;
    int counter = 0;

    std::cout << "Измененные рейсы: " << std::endl;
    std::cout << std::endl;

    while (getline(fin, name) && getline(fin, number) && fin >> price)
    {
        fin.ignore();
        bool found = false;
        for (int i = 0; i < flights.size(); i++)
        {

            if (name == flights[i].getAirportName() && number == flights[i].getFlightName())
            {
                flights[i].setTicketPrice(price);
                found = true;
                std::cout << i << ".";
                flights[i].display();
                counter++;
                break;
            }
        }
        if (!found)
        {
            std::cerr << "Аэропорт " << name << " и/или рейс " << number << " не были найдены" << std::endl;
        }
    }
    if (fin.peek() == EOF) {cout << "Файл модификации пуст" << endl;}
    fin.close();

    std::ofstream fout("modifications.txt");
    fout.write("", 0);
    fout.close();

    saveFlightsTxt();
    saveFlights();

    std::cout << "Модификация успешно завершена!\nИзменено " << counter << " рейсов" << std::endl;
}

void deleteFlight()
{
    std::cout << "  " << std::endl;
    displayFlights();
    int index;
    std::cout << "Введите индекс рейса чтобы удалить его: ";
    std::cin >> index;

    if (index >= 0 && index < flights.size())
    {
        flights.erase(flights.begin() + (index));
        saveFlights();
        saveFlightsTxt();
    }
    else
    {
        std::cerr << "Неправильный индекс." << std::endl;
    }
}

void findClosestAndFarthest()
{
    std::string airport_name;
    std::cout << "Введите название аэропорта (или введите 'all' чтобы показать все): ";
    std::cin >> airport_name;

    if (airport_name == "all" || airport_name == "All" || airport_name == "ALL")
    {
        double min_distance = 1e9, max_distance = -1e9;
        int min_index = -1, max_index = -1;

        for (int i = 0; i < flights.size(); i++)
        {
            if (flights[i].getDistance() < min_distance)
            {
                min_distance = flights[i].getDistance();
                min_index = i;
            }

            if (flights[i].getDistance() > max_distance)
            {
                max_distance = flights[i].getDistance();
                max_index = i;
            }
        }

        std::cout << "Самый короткий перелет: " << std::endl;
        std::cout << "  ";
        flights[min_index].display();
        std::cout << "Самый длинный перелет: " << std::endl;
        std::cout << "  ";
        flights[max_index].display();
    }
    else
    {
        double min_distance = 1e9, max_distance = -1e9;
        int min_index = -1, max_index = -1;

        for (int i = 0; i < flights.size(); i++)
        {
            if (flights[i].getAirportName() == airport_name)
            {
                if (flights[i].getDistance() < min_distance)
                {
                    min_distance = flights[i].getDistance();
                    min_index = i;
                }

                if (flights[i].getDistance() > max_distance)
                {
                    max_distance = flights[i].getDistance();
                    max_index = i;
                }
            }
        }

        std::cout << "Самый короткий перелет: " << std::endl;
        std::cout << "  ";
        flights[min_index].display();
        std::cout << "Самый длинный перелет: " << std::endl;
        std::cout << "  ";
        flights[max_index].display();
    }
}

void findCheapestAndMostExpensive()
{
    std::string flight_name;
    std::cout << "Введите наименование рейса (или введите 'all' чтобы показать все): ";
    std::cin >> flight_name;

    if (flight_name == "all" || flight_name == "All" || flight_name == "ALL")
    {
        double min_price = 1e9, max_price = -1e9;
        int min_index = -1, max_index = -1;

        for (int i = 0; i < flights.size(); i++)
        {
            if (flights[i].getTicketPrice() < min_price)
            {
                min_price = flights[i].getTicketPrice();
                min_index = i;
            }

            if (flights[i].getTicketPrice() > max_price)
            {
                max_price = flights[i].getTicketPrice();
                max_index = i;
            }
        }

        std::cout << "Самый дешевый авиабилет: " << std::endl;
        std::cout << "  ";
        flights[min_index].display();
        std::cout << "Самый дорогой авиабилет: " << std::endl;
        std::cout << "  ";
        flights[max_index].display();
    }
    else
    {
        double min_price = 1e9, max_price = -1e9;
        int min_index = -1, max_index = -1;

        for (int i = 0; i < flights.size(); i++)
        {
            if (flights[i].getFlightName() == flight_name)
            {
                if (flights[i].getTicketPrice() < min_price)
                {
                    min_price = flights[i].getTicketPrice();
                    min_index = i;
                }

                if (flights[i].getTicketPrice() > max_price)
                {
                    max_price = flights[i].getTicketPrice();
                    max_index = i;
                }
            }
        }

        std::cout << "Самый дешевый авиабилет: ";
        std::cout << "  ";
        flights[min_index].display();
        std::cout << "Самый дорогой авиабилет: ";
        std::cout << "  ";
        flights[max_index].display();
    }
}
void emptyChecker() {
    for (int i = 0; i < flights.size(); i++)
    {
        if ((flights[i].getAirportName() != "") && (flights[i].getFlightName() != "") && (flights[i].getFlightNumber() != "")
            && (flights[i].getDepartureTime() != "") && (flights[i].getDistance() != 0) && (flights[i].getTicketPrice() != 0.0))
        {
            //flights.pop_back();
            flights.erase(flights.begin() + i);
        }
    }
}