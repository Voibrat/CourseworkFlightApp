#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <set>
#include <filesystem>
#include <locale.h>

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
        std::cout << "Введите название аэропорта: ";
        std::cin >> airport_name;
        std::cout << "Введите наименование рейса: ";
        std::cin >> flight_name;
        std::cout << "Введите номер рейса: ";
        std::cin >> flight_number;
        std::cout << "Введите время вылета: ";
        std::cin >> departure_time;

        // Проверка на правильный ввод chairs_amount
        while (true) {
            std::cout << "Введите количество кресел: ";
            if (std::cin >> chairs_amount) {
                break;
            }
            std::cout << "Некорректный ввод, повторите попытку.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        // Проверка на правильный ввод distance
        while (true) {
            std::cout << "Введите дистанцию: ";
            if (std::cin >> distance) {
                break;
            }
            std::cout << "Некорректный ввод, повторите попытку.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        // Проверка на правильный ввод ticket_price
        while (true) {
            std::cout << "Введите цену билета: ";
            if (std::cin >> ticket_price) {
                break;
            }
            std::cout << "Некорректный ввод, повторите попытку.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
        departure_time = value;
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

        if (!(fin >> chairs_amount)) {
            std::cerr << "Часть введенных данных некорректна, проверьте данные в файле" << std::endl;
            return;
        }
        if (!(fin >> distance)) {
            std::cerr << "Часть введенных данных некорректна, проверьте данные в файле" << std::endl;
            return;
        }
        if (!(fin >> ticket_price)) {
            std::cerr << "Часть введенных данных некорректна, проверьте данные в файле" << std::endl;
            return;
        }

        fin.ignore(); //игнор ньюлайнов
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
// для бинарников
std::vector <Flight> flights;
std::vector <std::string> files;

// нужно реализовать проверку на конец файла
void loadFlights()
{
    files.clear();
    flights.clear();

    fs::path list_file_name = "files.txt";
    std::ifstream list_in(list_file_name);

    if (!list_in.is_open())
    {
        std::cerr << std::endl << "Невозможно открыть файл " << list_file_name;
        return;
    }

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
            std::cerr << std::endl << "Невозможно открыть файл " << files[i];
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

    // удаление файлов
    for (auto& file_path : files)
    {
        fs::remove(file_path);
    }


    if (fs::is_empty("airports"))
    {
        fs:remove("airports");
    }

}


// Не работает trunc
void saveFlights()
{
    files.clear();

    fs::path folder_name = "airports";

    if (!fs::exists(folder_name)) {
        if (fs::create_directory(folder_name)) {
            std::cout << "Директория успешно создана" << std::endl;
        }
        else {
            std::cout << "Ошибка создания директории" << std::endl;
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
            if ((flights[i].getAirportName() != "") and (flights[i].getFlightName() != "") and (flights[i].getFlightNumber() != "")
                and (flights[i].getDepartureTime() != "") and (flights[i].getDistance() != 0) and (flights[i].getTicketPrice() != 0.0))
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
        std::cout << "Ошибка ввода." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
        std::cout << "Неверный номер рейса." << std::endl;
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
        std::cout << "Неверный номер рейса." << std::endl;
    }
}

void modificationFlight()
{
    std::ifstream fin("modifications.txt");
    if (!fin.is_open())
    {
        std::cout << "Ошибка открытия файла modifications.txt" << std::endl;
        return;
    }

    std::string name, number;
    double price;
    std::cout << "Измененные рейсы: " << std::endl;
    std::cout << std::endl;
    while (getline(fin, name) and getline(fin, number) and fin >> price)
    {
        fin.ignore();
        bool found = false;
        for (int i = 0; i < flights.size(); i++)
        {

            if (name == flights[i].getAirportName() and number == flights[i].getFlightName())
            {
                flights[i].setTicketPrice(price);
                found = true;
                std::cout << i << ".";
                flights[i].display();

                break;
            }
        }
        if (!found)
        {
            std::cout << "Аэропорт " << name << " и/или рейс " << number << " не были найдены." << std::endl;
        }
    }
    fin.close();

    std::ofstream fout("modifications.txt");
    fout.write("", 0);
    fout.close();

    saveFlightsTxt();
    saveFlights();
    std::cout << "Модификация окончена" << std::endl;
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
        std::cout << "Неправильный индекс." << std::endl;
    }
}

void findClosestAndFarthest()
{
    std::string airport_name;
    std::cout << "Введите название аэропорта (или введите 'all' чтобы показать все): ";
    std::cin >> airport_name;

    if (airport_name == "all" or airport_name == "All" or airport_name == "ALL")
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

    if (flight_name == "all" or flight_name == "All" or flight_name == "ALL")
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
        if ((flights[i].getAirportName() != "") and (flights[i].getFlightName() != "") and (flights[i].getFlightNumber() != "")
            and (flights[i].getDepartureTime() != "") and (flights[i].getDistance() != 0) and (flights[i].getTicketPrice() != 0.0))
        {
            //flights.pop_back();
            flights.erase(flights.begin() + i);
        }
    }
}



int main()
{
    setlocale(LC_ALL, "Russian");

    int choiceLoad = 0;

    std::cout << "Выберите вариант чтения данных:" << std::endl;
    std::cout << "1. Из txt файла" << std::endl;
    std::cout << "2. Из bin файла" << std::endl;
    std::cout << "Сделайте выбор: ";
    std::cin >> choiceLoad;
    std::cout << std::endl;

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
        std::cout << "Ошибка ввода, пожалуйста, попробуйте еще раз" << std::endl;
        return 0;
    }

    //удаляет последний элемент вектора классов, частично решает проблему пустых экземпляров класса FLight при чтении из файла
    //flights.pop_back();

    //emptyChecker();

    while (true)
    {
        std::cout << "===================================================" << std::endl;
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
                    else {std::cout << "Ошибка ввода" << std::endl;}
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
                        std::cout << "Ошибка ввода." << std::endl;
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
                    else { std::cout << "Ошибка ввода" << std::endl; }
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
                    else { std::cout << "Ошибка ввода" << std::endl; }
                }
                break;
            case 9:
                saveFlights();
                saveFlightsTxt();
                exit(0);
            default:
                std::cout << "Ошибка ввода" << std::endl;
                break;
        }

        std::cout << std::endl;
    }
}
