#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <set>

using namespace std;

class Flight
{
private:
    string airport_name, flight_name, flight_number, departure_time;
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
    void setAirportName(string name)
    {
        airport_name = name;
    }

    void setFlightName(string name)
    {
        flight_name = name;
    }

    void setFlightNumber(string number)
    {
        flight_number = number;
    }

    void setDepartureTime(string time)
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
    string getAirportName()
    {
        return airport_name;
    }

    string getFlightName()
    {
        return flight_name;
    }

    string getFlightNumber()
    {
        return flight_number;
    }

    string getDepartureTime()
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
    int getValue(std::string query)
    {
        int value;
        std::cout << query.c_str();
        while(!(std::cin >> value))
        {
            if(std::cin.eof())
            { throw "eof"; }
            std::cin.clear();
            std::cin.ignore(1000,'\n');
            std::cout << "Try again: ";
        }
        return value;
    }
    */
    void read()
    {
        cout << "Введите название аэропорта: ";
        cin >> airport_name;
        cout << "Введите наименование рейса: ";
        cin >> flight_name;
        cout << "Введите номер рейса: ";
        cin >> flight_number;
        cout << "Введите время вылета: ";
        cin >> departure_time;

        // Проверка на правильный ввод chairs_amount
        while (true) {
            cout << "Введите количество кресел: ";
            if (cin >> chairs_amount) {
                break;
            }
            cout << "Некорректный ввод, повторите попытку.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        // Проверка на правильный ввод distance
        while (true) {
            cout << "Введите дистанцию: ";
            if (cin >> distance) {
                break;
            }
            cout << "Некорректный ввод, повторите попытку.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        // Проверка на правильный ввод ticket_price
        while (true) {
            cout << "Введите цену билета: ";
            if (cin >> ticket_price) {
                break;
            }
            cout << "Некорректный ввод, повторите попытку.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    //запись для бинарников
    void write(ofstream& fout)
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
    void read(ifstream& fin)
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
    void write_text(ofstream& fout) {
        fout << airport_name << endl;
        fout << flight_name << endl;
        fout << flight_number << endl;
        fout << departure_time << endl;
        fout << chairs_amount << endl;
        fout << distance << endl;
        fout << ticket_price << endl;
    }

    void read_text(ifstream& fin) {
        getline(fin, airport_name);
        if (airport_name.empty()) {
            return;
        }
        getline(fin, flight_name);
        getline(fin, flight_number);
        getline(fin, departure_time);

        if (!(fin >> chairs_amount)) {
            cout << "Часть введенных данных некорректна, проверьте данные в файле" << endl;
            return;
        }
        if (!(fin >> distance)) {
            cout << "Часть введенных данных некорректна, проверьте данные в файле" << endl;
            return;
        }
        if (!(fin >> ticket_price)) {
            cout << "Часть введенных данных некорректна, проверьте данные в файле" << endl;
            return;
        }

        fin.ignore(); //игнор ньюлайнов
    }


    void display()
    {
        cout << "Название Аэропорта: " << airport_name << endl;
        cout << "  Наименование рейса: " << flight_name << endl;
        cout << "  Номер рейса: " << flight_number << endl;
        cout << "  Время вылета: " << departure_time << endl;
        cout << "  Количество кресел: " << chairs_amount << endl;
        cout << "  Расстояние: " << distance << " км" << endl;
        cout << "  Цена билета: " << ticket_price << " $" << endl;
        cout << endl;
    }
};

vector<Flight> flights;

// нужно реализовать проверку на конец файла
void loadFlights()
{
    ifstream fin("flights.bin", ios::binary);

    if (fin.is_open())
    {
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
}

// для бинарников
vector <string> files;

void saveFlights()
{

    for (int i = 0; i < flights.size(); ++i)
    {
        string airport_name = flights[i].getAirportName();
        string file_name = airport_name + ".bin";

        ofstream fout(file_name, ios::binary | ios::trunc);
        files.push_back(file_name);
        if (fout.is_open())
        {
            flights[i].write(fout);
            fout.close();
        }
        else
        {
            cerr << "Невозможно открыть файл " << file_name << endl;
        }
    }
    ofstream fout("files.txt");

}


// нужно реализовать проверку на конец файла
// для тхт
void loadFlightsTxt() {
    ifstream fin("flights.txt", ios::in);

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
    ofstream fout("flights.txt", ios::trunc);

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
        cout << i << ".";
        flights[i].display();
    }
}

void searchFlights()
{
    string flight_name;
    string departure_time;
    double ticket_price;

    cout << "Введите номер рейса (или введите 'any' для отображения всех): ";
    cin >> flight_name;
    cout << "Введите время вылета (или введите 'any' для отображения любого): ";
    cin >> departure_time;
    cout << "Введите стоимость билета (или введите '-1' для любой цены): ";
    if (!(cin >> ticket_price)) {
        cout << "Ошибка ввода." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    for (int i = 0; i < flights.size(); i++) {
        if (flight_name == "any" || departure_time == "Any" || departure_time == "ANY" ||
            flights[i].getFlightName() == flight_name) {
            if (departure_time == "any" || departure_time == "Any" || departure_time == "ANY" ||
                flights[i].getDepartureTime() == departure_time) {
                if (ticket_price == -1 || flights[i].getTicketPrice() == ticket_price) {
                    cout << "  ";
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
    string number;
    bool flag = false;

    displayFlights();

    cout << "Введите номер рейса рейса чтобы изменить время вылета: ";
    cin >> number;

    for (int i = 0; i < flights.size(); i++) {
        if (number == flights[i].getFlightNumber()) {
            string Time = "";
            cout << "Введите новое время вылета: ";
            cin >> Time;
            flights[i].setDepartureTime(Time);
            saveFlights();
            saveFlightsTxt();
            flag = true;
            break;
        }
    }
    if (flag != true) {
        cout << "Неверный номер рейса." << endl;
    }
}

// переписать для работы с векторами
void editPriceFlight()
{
    string name;
    bool flag = false;

    displayFlights();

    cout << "Введите наименование рейса чтобы изменить его стоимость: ";
    cin >> name;


    for (int i = 0; i < flights.size(); i++)
    {
        if (name == flights[i].getFlightName())
        {
            double price;
            cout << "Введите новую стоимость билета: ";
            cin >> price;
            flights[i].setTicketPrice(price);
            saveFlights();
            saveFlightsTxt();
        }
    }
    if (flag != true) {
        cout << "Неверный номер рейса." << endl;
    }
}

void modificationFlight()
{
    ifstream fin("modifications.txt");
    if (!fin.is_open())
    {
        cout << "Ошибка открытия файла modifications.txt" << endl;
        return;
    }

    string name, number;
    double price;
    cout << "Измененные рейсы: " << endl;
    cout << endl;
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
                cout << i << ".";
                flights[i].display();

                break;
            }
        }
        if (!found)
        {
            cout << "Аэропорт " << name << " и/или рейс " << number << " не были найдены." << endl;
        }
    }
    fin.close();

    ofstream fout("modifications.txt");
    fout.write("", 0);
    fout.close();

    saveFlightsTxt();
    saveFlights();
    cout << "Модификация окончена" << endl;
}

void deleteFlight()
{
    cout << "  " << endl;
    displayFlights();
    int index;
    cout << "Введите индекс рейса чтобы удалить его: ";
    cin >> index;

    if (index >= 0 && index < flights.size())
    {
        flights.erase(flights.begin() + (index));
        saveFlights();
        saveFlightsTxt();
    }
    else
    {
        cout << "Неправильный индекс." << endl;
    }
}

void findClosestAndFarthest()
{
    string airport_name;
    cout << "Введите название аэропорта (или введите 'all' чтобы показать все): ";
    cin >> airport_name;

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

        cout << "Самый короткий перелет: " << endl;
        cout << "  ";
        flights[min_index].display();
        cout << "Самый длинный перелет: " << endl;
        cout << "  ";
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

        cout << "Самый короткий перелет: " << endl;
        cout << "  ";
        flights[min_index].display();
        cout << "Самый длинный перелет: " << endl;
        cout << "  ";
        flights[max_index].display();
    }
}

void findCheapestAndMostExpensive()
{
    string flight_name;
    cout << "Введите наименование рейса (или введите 'all' чтобы показать все): ";
    cin >> flight_name;

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

        cout << "Самый дешевый авиабилет: " << endl;
        cout << "  ";
        flights[min_index].display();
        cout << "Самый дорогой авиабилет: " << endl;
        cout << "  ";
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

        cout << "Самый дешевый авиабилет: ";
        cout << "  ";
        flights[min_index].display();
        cout << "Самый дорогой авиабилет: ";
        cout << "  ";
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

    cout << "Выберите вариант чтения данных:" << endl;
    cout << "1. Из txt файла" << endl;
    cout << "2. Из bin файла" << endl;
    cout << "Сделайте выбор: ";
    cin >> choiceLoad;
    cout << endl;

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
        cout << "Ошибка ввода, пожалуйста, попробуйте еще раз" << endl;
        return 0;
    }

    //удаляет последний элемент вектора классов, частично решает проблему пустых экземпляров класса FLight при чтении из файла
    //flights.pop_back();

    //emptyChecker();

    while (true)
    {
        cout << "===================================================" << endl;
        cout << "____________FLIGHTS CONSOLE APPLICATION____________" << endl;
        cout << "===================================================" << endl;
        cout << "1. Добавить рейс" << endl;
        cout << "2. Показать все рейсы" << endl;
        cout << "3. Поиск рейсов" << endl;
        cout << "4. Редактировать рейс" << endl;
        cout << "5. Удалить рейс" << endl;
        cout << "6. Найти самые короткий и длинный рейсы" << endl;
        cout << "7. Найти самые дешевые и самые дорогие авиабилеты" << endl;
        cout << "8. Модификация данных из файла" << endl;
        cout << "9. Выход" << endl;
        cout << "Сделайте выбор: ";

        int choice;
        string modChoice, editChoice;
        cin >> choice;
        cout << endl;
        switch (choice)
        {
            case 1:
                while (true) {
                    cout << "Вы уверены что хотите продолжить?" << endl;
                    cout << "1. Продолжить" << endl;
                    cout << "2. Вернуться" << endl;
                    cout << "Сделайте выбор: ";
                    cin >> modChoice;
                    cout << "  " << endl;
                    if (modChoice == "1") {
                        addFlight();
                        break;
                    }
                    else if (modChoice == "2")
                    {
                        break;
                    }
                    else { cout << "Ошибка ввода" << endl; }
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
                    cout << "1. Изменить время вылета" << endl;
                    cout << "2. Изменить цену авиабилета" << endl;
                    cout << "3. Вернуться в меню" << endl;
                    cout << "Сделайте выбор: ";
                    cin >> editChoice;
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
                        cout << "Ошибка ввода." << endl;
                    }
                }
                break;
            case 5:
                while (true) {
                    cout << "Вы уверены что хотите продолжить?" << endl;
                    cout << "1. Продолжить" << endl;
                    cout << "2. Вернуться" << endl;
                    cout << "Сделайте выбор: ";
                    cin >> modChoice;
                    if (modChoice == "1") {
                        deleteFlight();
                        break;
                    }
                    else if (modChoice == "2")
                    {
                        break;
                    }
                    else { cout << "Ошибка ввода" << endl; }
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
                    cout << "Вы уверены что хотите модифицировать данные из внешнего файла?" << endl;
                    cout << "1. Продолжить" << endl;
                    cout << "2. Вернуться" << endl;
                    cout << "Сделайте выбор: ";
                    cin >> modChoice;
                    if (modChoice == "1") {
                        modificationFlight();
                        break;
                    }
                    else if (modChoice == "2")
                    {
                        break;
                    }
                    else { cout << "Ошибка ввода" << endl; }
                }
                break;
            case 9:
                exit(0);
            default:
                cout << "Ошибка ввода" << endl;
                break;
        }

        cout << endl;
    }

    return 0;
}