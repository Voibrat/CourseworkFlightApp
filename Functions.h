//
// Created by Дмитрий Филиппов on 29.04.2023.
//

#ifndef COURSEWORKFLIGHTAPP_FUNCTIONS_H
#define COURSEWORKFLIGHTAPP_FUNCTIONS_H
#endif //COURSEWORKFLIGHTAPP_FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <set>
#include <filesystem>
#include <locale>
#include <regex>
#include <limits>
#include <chrono>
#include <thread>
#include <cstdlib>

namespace fs = std::filesystem;

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
    std::filesystem::remove_all("airports");
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
            std::cout << "Ошибка создания директории 'airports'. Сохранение файлов не завершено\nДанные могут быть утеряны" << std::endl;
            return;
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

void displayFlightsTable()
{
    char sim = '=';

    std::cout << std::endl << "|" << string ( 111, '=') << "|" << std::endl;
    std::cout << "|" << std::left << std::setw(2) << "id" << "|"
              << std::left << std::setw(19) << "Название" << "|"
              << std::left << std::setw(27) << "Наименование" << "|"
              << std::left << std::setw(20) << "Номер" << "|"
              << std::left << std::setw(20) << "Время" << "|"
              << std::left << std::setw(24) << "Количество" << "|"
              << std::left << std::setw(23) << "Дистанция" << " км" << "|"
              << std::left << std::setw(22) << "Стоимость" << " $" << "|"
              << std::endl;
    std::cout << "|" << std::left << std::setw(2) << "  " << "|"
              << std::left << std::setw(20) << "аэропорта" << "|"
              << std::left << std::setw(20) << "рейса" << "|"
              << std::left << std::setw(20) << "рейса" << "|"
              << std::left << std::setw(21) << "вылета" << "|"
              << std::left << std::setw(20) << "кресел" << "|"
              << std::left << std::setw(20) << "полета" << " км" << "|"
              << std::left << std::setw(19) << "билета" << " $" << "|"
              << std::endl;
    std::cout << "|" << string ( 111, '-') << "|" << std::endl;
    for (int i = 0; i < flights.size(); i++)
    {
        flights[i].display(i);
        std::cout << "|" << string ( 111, '-') << "|" << std::endl;
    }
    std::cout << "|" << string ( 111, '=') << "|" << std::endl << std::endl;
    /*
    printf("%-40s %-40s %-25s %-25s %-40s %-25s %-25s\n", "| Название Аэропорта", "| Наименование рейса", "|Номер рейса", " | Время вылета", "| Количество кресел", "| Расстояние", "| Цена билета |");
    cout << endl;
    for (int i = 0; i < flights.size(); i++) {
        printf("%-18s %-15s %-7s %-13s %-13d %-13d %-13f\n", flights[i].getAirportName().c_str(), flights[i].getFlightName().c_str(), flights[i].getFlightNumber().c_str(), flights[i].getDepartureTime().c_str(), flights[i].getChairsAmount(), flights[i].getDistance(), flights[i].getTicketPrice());
    }
     */
}

void searchFlights(std::string choice)
{
    std::string flightName;
    std::string departureTime;
    double ticketPrice;

    std::cout << "Введите номер рейса (или введите 'any' для отображения всех): ";
    std::cin >> flightName;
    std::cout << "Введите время вылета (или введите 'any' для отображения любого): ";
    std::cin >> departureTime;

    std::cout << "Введите стоимость билета (или введите '-1' для любой цены): ";
    if (!(std::cin >> ticketPrice)) {
        std::cerr << "Ошибка ввода." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        return;
        }
    std::cout << std::endl << "Результат поиска: " << std::endl;

    if (choice == "2") {
        std::cout << "|" << string(111, '=') << "|" << std::endl;
        std::cout << "|" << std::left << std::setw(2) << "id" << "|"
                  << std::left << std::setw(19) << "Название" << "|"
                  << std::left << std::setw(27) << "Наименование" << "|"
                  << std::left << std::setw(20) << "Номер" << "|"
                  << std::left << std::setw(20) << "Время" << "|"
                  << std::left << std::setw(24) << "Количество" << "|"
                  << std::left << std::setw(23) << "Дистанция" << " км" << "|"
                  << std::left << std::setw(22) << "Стоимость" << " $" << "|"
                  << std::endl;
        std::cout << "|" << std::left << std::setw(2) << "  " << "|"
                  << std::left << std::setw(20) << "аэропорта" << "|"
                  << std::left << std::setw(20) << "рейса" << "|"
                  << std::left << std::setw(20) << "рейса" << "|"
                  << std::left << std::setw(21) << "вылета" << "|"
                  << std::left << std::setw(20) << "кресел" << "|"
                  << std::left << std::setw(20) << "полета" << " км" << "|"
                  << std::left << std::setw(19) << "билета" << " $" << "|"
                  << std::endl;
        std::cout << "|" << string(111, '-') << "|" << std::endl;
    }

    for (int i = 0; i < flights.size(); i++) {
        if (flightName == "any" || departureTime == "Any" || departureTime == "ANY" || flights[i].getFlightName() == flightName) {
            if (departureTime == "any" || departureTime == "Any" || departureTime == "ANY" || flights[i].getDepartureTime() == departureTime) {
                if (ticketPrice == -1 || flights[i].getTicketPrice() == ticketPrice) {

                    if (choice == "1") {
                        std::cout << i << ".";
                        flights[i].display();}
                    else if (choice == "2") {
                        flights[i].display(i);
                        std::cout << "|" << string(111, '-') << "|" << std::endl;
                    }

                }
            }
        }
    }

    if (choice == "2") {
        std::cout << "|" << string(111, '=') << "|" << std::endl;
    }
}



void editTimeFlight(std::string choice)
{
    std::string number;
    bool flag = false;

    if (choice == "1") {displayFlights();}
    else if (choice == "2") {displayFlightsTable();}

    std::cout << "Введите номер рейса рейса чтобы изменить время вылета: ";
    std::cin >> number;

    for (auto & flight : flights) {
        if (number == flight.getFlightNumber()) {
            std::string Time = "";
            std::cout << "Введите новое время вылета: ";
            std::cin >> Time;
            std::regex time_regex("^([0-1]?[0-9]|2[0-3]):([0-5][0-9])$");
            if (std::regex_match(Time, time_regex)) {
                flight.setDepartureTime(Time);
                saveFlights();
                saveFlightsTxt();
                flag = true;
                return;
            } else {
                Time = "";
                std::cerr << "Ошибка в формате времени!\n";
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                return;
            }
        }
    }
    std::cerr<< "Неверный номер рейса." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

// переписать для работы с векторами
void editPriceFlight(std::string choice)
{
    std::string name;
    if (choice == "1") {displayFlights();}
    else if (choice == "2") {
        std::cout << std::endl;
        displayFlightsTable();
    }

    std::cout << std::endl << "Введите наименование рейса чтобы изменить его стоимость: ";
    std::cin >> name;


    for (auto &flight: flights)
    {
        if (name == flight.getFlightName())
        {
            double price;
            std::cout << "Введите новую стоимость билета: ";
            std::cin >> price;
            flight.setTicketPrice(price);
            saveFlights();
            saveFlightsTxt();
            return;
        }
    }
    std::cerr << "Неверное наименование рейса." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

void modificationFlight(std::string choice)
{
    std::ifstream fin("modifications.txt");
    if (!fin.is_open())
    {
        std::cerr << "Ошибка открытия файла modifications.txt" << std::endl;
        return;
    }
    if (fin.peek() == EOF) {cout << "Файл модификации пуст" << endl;}
    std::string name, number;
    double price;
    int counter = 0;

    if (fin.peek() != EOF) {
        std::cout << "Измененные рейсы: " << std::endl;
        std::cout << std::endl;
    }

    if (choice == "2" && fin.peek() != EOF) {
        std::cout << std::endl << "|" << string(111, '=') << "|" << std::endl;
        std::cout << "|" << std::left << std::setw(2) << "id" << "|"
                  << std::left << std::setw(19) << "Название" << "|"
                  << std::left << std::setw(27) << "Наименование" << "|"
                  << std::left << std::setw(20) << "Номер" << "|"
                  << std::left << std::setw(20) << "Время" << "|"
                  << std::left << std::setw(24) << "Количество" << "|"
                  << std::left << std::setw(23) << "Дистанция" << " км" << "|"
                  << std::left << std::setw(22) << "Стоимость" << " $" << "|"
                  << std::endl;
        std::cout << "|" << std::left << std::setw(2) << "  " << "|"
                  << std::left << std::setw(20) << "аэропорта" << "|"
                  << std::left << std::setw(20) << "рейса" << "|"
                  << std::left << std::setw(20) << "рейса" << "|"
                  << std::left << std::setw(21) << "вылета" << "|"
                  << std::left << std::setw(20) << "кресел" << "|"
                  << std::left << std::setw(20) << "полета" << " км" << "|"
                  << std::left << std::setw(19) << "билета" << " $" << "|"
                  << std::endl;
        std::cout << "|" << string(111, '-') << "|" << std::endl;
    }
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
                /*
                if (choice == "1") {displayFlights();}
                else if (choice == "2") {displayFlightsTable();}
                */
                if (choice == "1") {
                    std::cout << i << ".";
                    flights[i].display();
                }
                else if (choice == "2") {

                    flights[i].display(i);
                    std::cout << "|" << string ( 111, '-') << "|" << std::endl;
                }
                counter++;
                break;
            }
        }
        if (!found)
        {
            std::cerr << "Аэропорт " << name << " и/или рейс " << number << " не были найдены" << std::endl;
        }
    }
    if (choice == "2" && fin.peek() != EOF) {
        std::cout << "|" << string ( 111, '=') << "|" << std::endl;
    }
    fin.close();

    std::ofstream fout("modifications.txt");
    fout.write("", 0);
    fout.close();

    saveFlightsTxt();
    saveFlights();

    std::cout << "Модификация успешно завершена!\nИзменено " << counter << std::endl;
}

void deleteFlight(std::string choice)
{
    std::cout << "  ";
    if (choice == "1") {
        std::cout << std::endl;
        displayFlights();
    }
    else if (choice == "2") {displayFlightsTable();}
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
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

}

// сделать разные варианты вывода через choice
void findClosestAndFarthest(std::string choice)
{
    std::string airportName;
    std::cout << "Введите название аэропорта (или введите 'all' чтобы показать все): ";
    std::cin >> airportName;

    if (airportName == "all" || airportName == "All" || airportName == "ALL")
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

        std::cout << std::endl << "Самый короткий перелет: " << std::endl;
        if (choice == "1") {
            std::cout << "  ";
            flights[min_index].display();
        }
        else if (choice == "2") {
            std::cout << "|" << string ( 111, '=') << "|" <<  std::endl;
            std::cout << "|" << std::left << std::setw(2) << "id" << "|"
                      << std::left << std::setw(19) << "Название" << "|"
                      << std::left << std::setw(27) << "Наименование" << "|"
                      << std::left << std::setw(20) << "Номер" << "|"
                      << std::left << std::setw(20) << "Время" << "|"
                      << std::left << std::setw(24) << "Количество" << "|"
                      << std::left << std::setw(23) << "Дистанция" << " км" << "|"
                      << std::left << std::setw(22) << "Стоимость" << " $" << "|"
                      << std::endl;
            std::cout << "|" << std::left << std::setw(2) << "  " << "|"
                      << std::left << std::setw(20) << "аэропорта" << "|"
                      << std::left << std::setw(20) << "рейса" << "|"
                      << std::left << std::setw(20) << "рейса" << "|"
                      << std::left << std::setw(21) << "вылета" << "|"
                      << std::left << std::setw(20) << "кресел" << "|"
                      << std::left << std::setw(20) << "полета" << " км" << "|"
                      << std::left << std::setw(19) << "билета" << " $" << "|"
                      << std::endl;
            std::cout << "|" << string ( 111, '-') << "|" << std::endl;
            flights[min_index].display(min_index);
            std::cout << "|" << string ( 111, '=') << "|" << std::endl;
        }
        std::cout << "Самый длинный перелет: " << std::endl;

        if (choice == "1") {
            std::cout << "  ";
            flights[max_index].display();
        }
        else if (choice == "2") {
            std::cout << "|" << string ( 111, '=') << "|" <<  std::endl;
            std::cout << "|" << std::left << std::setw(2) << "id" << "|"
                      << std::left << std::setw(19) << "Название" << "|"
                      << std::left << std::setw(27) << "Наименование" << "|"
                      << std::left << std::setw(20) << "Номер" << "|"
                      << std::left << std::setw(20) << "Время" << "|"
                      << std::left << std::setw(24) << "Количество" << "|"
                      << std::left << std::setw(23) << "Дистанция" << " км" << "|"
                      << std::left << std::setw(22) << "Стоимость" << " $" << "|"
                      << std::endl;
            std::cout << "|" << std::left << std::setw(2) << "  " << "|"
                      << std::left << std::setw(20) << "аэропорта" << "|"
                      << std::left << std::setw(20) << "рейса" << "|"
                      << std::left << std::setw(20) << "рейса" << "|"
                      << std::left << std::setw(21) << "вылета" << "|"
                      << std::left << std::setw(20) << "кресел" << "|"
                      << std::left << std::setw(20) << "полета" << " км" << "|"
                      << std::left << std::setw(19) << "билета" << " $" << "|"
                      << std::endl;
            std::cout << "|" << string ( 111, '-') << "|" << std::endl;
            flights[max_index].display(max_index);
            std::cout << "|" << string ( 111, '=') << "|" << std::endl;
        }
    }
    else
    {
        double min_distance = 1e9, max_distance = -1e9;
        int min_index = -1, max_index = -1;

        for (int i = 0; i < flights.size(); i++)
        {
            if (flights[i].getAirportName() == airportName)
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

        if (choice == "1") {
            std::cout << "  ";
            flights[min_index].display();
        }
        else if (choice == "2") {
            std::cout << "|" << string ( 111, '=') << "|" <<  std::endl;
            std::cout << "|" << std::left << std::setw(2) << "id" << "|"
                      << std::left << std::setw(19) << "Название" << "|"
                      << std::left << std::setw(27) << "Наименование" << "|"
                      << std::left << std::setw(20) << "Номер" << "|"
                      << std::left << std::setw(20) << "Время" << "|"
                      << std::left << std::setw(24) << "Количество" << "|"
                      << std::left << std::setw(23) << "Дистанция" << " км" << "|"
                      << std::left << std::setw(22) << "Стоимость" << " $" << "|"
                      << std::endl;
            std::cout << "|" << std::left << std::setw(2) << "  " << "|"
                      << std::left << std::setw(20) << "аэропорта" << "|"
                      << std::left << std::setw(20) << "рейса" << "|"
                      << std::left << std::setw(20) << "рейса" << "|"
                      << std::left << std::setw(21) << "вылета" << "|"
                      << std::left << std::setw(20) << "кресел" << "|"
                      << std::left << std::setw(20) << "полета" << " км" << "|"
                      << std::left << std::setw(19) << "билета" << " $" << "|"
                      << std::endl;
            std::cout << "|" << string ( 111, '-') << "|" << std::endl;
            flights[min_index].display(min_index);
            std::cout << "|" << string ( 111, '=') << "|" << std::endl;
        }

        std::cout  << "Самый длинный перелет: " << std::endl;

        if (choice == "1") {
            std::cout << "  ";
            flights[max_index].display();
        }
        else if (choice == "2") {
            std::cout << "|" << string ( 111, '=') << "|" <<  std::endl;
            std::cout << "|" << std::left << std::setw(2) << "id" << "|"
                      << std::left << std::setw(19) << "Название" << "|"
                      << std::left << std::setw(27) << "Наименование" << "|"
                      << std::left << std::setw(20) << "Номер" << "|"
                      << std::left << std::setw(20) << "Время" << "|"
                      << std::left << std::setw(24) << "Количество" << "|"
                      << std::left << std::setw(23) << "Дистанция" << " км" << "|"
                      << std::left << std::setw(22) << "Стоимость" << " $" << "|"
                      << std::endl;
            std::cout << "|" << std::left << std::setw(2) << "  " << "|"
                      << std::left << std::setw(20) << "аэропорта" << "|"
                      << std::left << std::setw(20) << "рейса" << "|"
                      << std::left << std::setw(20) << "рейса" << "|"
                      << std::left << std::setw(21) << "вылета" << "|"
                      << std::left << std::setw(20) << "кресел" << "|"
                      << std::left << std::setw(20) << "полета" << " км" << "|"
                      << std::left << std::setw(19) << "билета" << " $" << "|"
                      << std::endl;
            std::cout << "|" << string ( 111, '-') << "|" << std::endl;
            flights[max_index].display(max_index);
            std::cout << "|" << string ( 111, '=') << "|" << std::endl;
        }

    }
}

// сделать разные варианты вывода через choice
void findCheapestAndMostExpensive(std::string choice)
{
    std::string flightName;
    std::cout << "Введите наименование рейса (или введите 'all' чтобы показать все): ";
    std::cin >> flightName;

    if (flightName == "all" || flightName == "All" || flightName == "ALL")
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

        std::cout << std::endl << "Самый дешевый авиабилет: " << std::endl;
        if (choice == "1") {
            std::cout << "  ";
            flights[min_index].display();
        }
        else if (choice == "2") {
            std::cout << "|" << string ( 111, '=') << "|" <<  std::endl;
            std::cout << "|" << std::left << std::setw(2) << "id" << "|"
                      << std::left << std::setw(19) << "Название" << "|"
                      << std::left << std::setw(27) << "Наименование" << "|"
                      << std::left << std::setw(20) << "Номер" << "|"
                      << std::left << std::setw(20) << "Время" << "|"
                      << std::left << std::setw(24) << "Количество" << "|"
                      << std::left << std::setw(23) << "Дистанция" << " км" << "|"
                      << std::left << std::setw(22) << "Стоимость" << " $" << "|"
                      << std::endl;
            std::cout << "|" << std::left << std::setw(2) << "  " << "|"
                      << std::left << std::setw(20) << "аэропорта" << "|"
                      << std::left << std::setw(20) << "рейса" << "|"
                      << std::left << std::setw(20) << "рейса" << "|"
                      << std::left << std::setw(21) << "вылета" << "|"
                      << std::left << std::setw(20) << "кресел" << "|"
                      << std::left << std::setw(20) << "полета" << " км" << "|"
                      << std::left << std::setw(19) << "билета" << " $" << "|"
                      << std::endl;
            std::cout << "|" << string ( 111, '-') << "|" << std::endl;
            flights[min_index].display(min_index);
            std::cout << "|" << string ( 111, '=') << "|" << std::endl;
        }

        std::cout << "Самый дорогой авиабилет: " << std::endl;
        if (choice == "1") {
            std::cout << "  ";
            flights[max_index].display();
        }
        else if (choice == "2") {
            std::cout << "|" << string ( 111, '=') << "|" <<  std::endl;
            std::cout << "|" << std::left << std::setw(2) << "id" << "|"
                      << std::left << std::setw(19) << "Название" << "|"
                      << std::left << std::setw(27) << "Наименование" << "|"
                      << std::left << std::setw(20) << "Номер" << "|"
                      << std::left << std::setw(20) << "Время" << "|"
                      << std::left << std::setw(24) << "Количество" << "|"
                      << std::left << std::setw(23) << "Дистанция" << " км" << "|"
                      << std::left << std::setw(22) << "Стоимость" << " $" << "|"
                      << std::endl;
            std::cout << "|" << std::left << std::setw(2) << "  " << "|"
                      << std::left << std::setw(20) << "аэропорта" << "|"
                      << std::left << std::setw(20) << "рейса" << "|"
                      << std::left << std::setw(20) << "рейса" << "|"
                      << std::left << std::setw(21) << "вылета" << "|"
                      << std::left << std::setw(20) << "кресел" << "|"
                      << std::left << std::setw(20) << "полета" << " км" << "|"
                      << std::left << std::setw(19) << "билета" << " $" << "|"
                      << std::endl;
            std::cout << "|" << string ( 111, '-') << "|" << std::endl;
            flights[max_index].display(max_index);
            std::cout << "|" << string ( 111, '=') << "|" << std::endl;
        }
    }
    else
    {
        double min_price = 1e9, max_price = -1e9;
        int min_index = -1, max_index = -1;

        for (int i = 0; i < flights.size(); i++)
        {
            if (flights[i].getFlightName() == flightName)
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

        flights[min_index].display(min_index);
        std::cout << "Самый дорогой авиабилет: ";
        std::cout << "  ";
        flights[max_index].display(max_index);
    }
}
void vectorSort() {
    // Сортировка вектора для вывода в порядке возрастания времени вылета
    std::sort(flights.begin(), flights.end(), [](Flight a, Flight b) {
        return a.getDepartureTime() < b.getDepartureTime();
    });
}