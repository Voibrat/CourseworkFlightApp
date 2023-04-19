#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;
// тут была кошка и все поломала
class Flight
{
private:
    string airport_name, flight_name, flight_number, departure_time;
    int distance;
    double ticket_price;

public:
    Flight()
    {
        airport_name = "";
        flight_name = "";
        flight_number = "";
        departure_time = "";
        distance = 0;
        ticket_price = 0.0;

    }

    friend istream& operator>>(istream& is, Flight& f)
    {
        is >> f.airport_name >> f.flight_name >> f.flight_number >> f.departure_time >> f.distance >> f.ticket_price;
        return is;
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

    int getDistance()
    {
        return distance;
    }

    double getTicketPrice()
    {
        return ticket_price;
    }

    // Функции
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
        cout << "Введите дистанцию: ";
        cin >> distance;
        cout << "Введите цену билета: ";
        cin >> ticket_price;
    }

    //запись для бинарников
    void write(ofstream &fout)
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

        fout.write((char*)&distance, sizeof(int));
        fout.write((char*)&ticket_price, sizeof(double));
    }

    //чтение для бинарников
    void read(ifstream &fin)
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

        fin.read((char*)&distance, sizeof(int));
        fin.read((char*)&ticket_price, sizeof(double));
        fin.ignore(); //игнор ньюлайнов
    }

    //функции для записи и чтения в обычном формате
    void write_text(ofstream& fout) {
        fout << airport_name << endl;
        fout << flight_name << endl;
        fout << flight_number << endl;
        fout << departure_time << endl;
        fout << distance << endl;
        fout << ticket_price << endl;
    }

    void read_text(ifstream& fin) {
        getline(fin, airport_name);
        getline(fin, flight_name);
        getline(fin, flight_number);
        getline(fin, departure_time);
        fin >> distance;
        fin >> ticket_price;
        fin.ignore(); //игнор ньюлайнов
    }


    void display()
    {
        cout << "Название Аэропорта: " << airport_name << endl;
        cout << "  Наименование рейса: " << flight_name << endl;
        cout << "  Номер рейса: " << flight_number << endl;
        cout <<"  Время вылета: " << departure_time << endl;
        cout << "  Расстояние: " << distance << " км" << endl;
        cout << "  Цена билета: " << ticket_price << " $" << endl;
        cout << endl;
    }
};

vector<Flight> flights;

void loadFlights()
{
    ifstream fin("flights.bin");

    if (fin.is_open())
    {
        while (!fin.eof())
        {
            Flight f;
            f.read(fin);
            flights.push_back(f);
        }

        fin.close();
    }
}

//для бинарников
void saveFlights()
{
    ofstream fout("flights.bin", ios::binary);

    if (fout.is_open())
    {
        for (int i = 0; i < flights.size(); i++)
        {
            flights[i].write(fout);
            //fout << flights[i];
        }

        fout.close();
    }
}

//для тхт
void loadFlightsTxt() {
    ifstream fin("flights.txt");

    if (fin.is_open())
    {
        while (!fin.eof())
        {
            Flight f;
            f.read_text(fin);
            flights.push_back(f);
        }

        fin.close();
    }
}

void saveFlightsTxt() {
    ofstream fout("flights.txt");

    if (fout.is_open())
    {
        for (int i = 0; i < flights.size(); i++)
        {
            flights[i].write_text(fout);
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
    cout << "Введите цену билета(или введите '-1' для любой цены): ";
    cin >> ticket_price;

    cout << endl;

    for (int i = 0; i < flights.size(); i++)
    {
        if (flight_name == "any" || flights[i].getFlightName() == flight_name)
        {
            if (departure_time == "any" || flights[i].getDepartureTime() == departure_time)
            {
                if (ticket_price == -1 || flights[i].getTicketPrice() == ticket_price)
                {
                    flights[i].display();
                }
            }
        }
    }
}

void editTimeFlight()
{
    int index;
    cout << "Введите наименование рейса рейса чтобы изменить время вылета: ";
    cin >> index;

    if (index >= 0 && index < flights.size())
    {
        ofstream fout("flights.bin", ios::binary);

        if (fout.is_open()) {
            string Time = "";
            cout << "Введите новое время вылета: ";
            cin >> Time;
            flights[index].setDepartureTime(Time);
            fout.close();
        }
    }
    else
    {
        cout << "Неправильный номер." << endl;
    }
}

void editPriceFlight()
{
    int index;
    cout << "Введите индекс рейса чтобы изменить его стоимость: ";
    cin >> index;

    if (index >= 0 && index < flights.size())
    {
        ofstream fout("flights.bin", ios::binary);

        if (fout.is_open()) {
            double price;
            cout << "Введите новую стоимость билета: ";
            cin >> price;
            flights[index].setTicketPrice(price);
            fout.close();
        }
    }
    else
    {
        cout << "Неправильный номер." << endl;
    }
}

void deleteFlight()
{
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
        flights[min_index].display();
        cout << "Самый длинный перелет: " << endl;
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

        cout << "Самый короткий перелет: ";
        flights[min_index].display();
        cout << "Самый длинный перелет: ";
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

        cout << "Самый дешевый авиабилет: ";
        flights[min_index].display();
        cout << "Самый дорогой авиабилет: ";
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
        flights[min_index].display();
        cout << "Самый дорогой авиабилет: ";
        flights[max_index].display();
    }
}

int main()
{
    //setlocale(LC_ALL, "Russian");

    loadFlights();
    int choiceLoad = 0;

    cout << "Выберите вариант чтения данных:" << endl;
    cout << "1. Из txt файла" << endl;
    cout << "2. Из bin файла" << endl;
    cin >> choiceLoad;
    cout << endl;

    if (choiceLoad == 1) {
        loadFlightsTxt();
    } else if (choiceLoad == 2){
        loadFlights();
        //удаляет последний элемент вектора классов, решает проблему пустых экземпляров класса FLight при чтении из файла
        //flights.pop_back();
    } else {
        cout << "Ошибка ввода, пожалуйста, попробуйте еще раз" << endl;
        return 0;
    }

    //удаляет последний элемент вектора классов, частично решает проблему пустых экземпляров класса FLight при чтении из файла
    flights.pop_back();


    while (true)
    {
        cout << "===================================================" << endl;
        cout << "____________FLIGHTS CONSOLE APPLICATION____________" << endl;
        cout << "===================================================" << endl;
        cout << "1. Добавить рейс" << endl;
        cout << "2. Показать все рейсы" << endl;
        cout << "3. Поиск рейсов" << endl;
        cout << "4. Редактировать стоимость билета" << endl;
        cout << "5. Редактировать время вылета" << endl;
        cout << "6. Удалить рейс" << endl;
        cout << "7. Найти самые короткий и длинный рейсы" << endl;
        cout << "8. Найти самые дешевые и самые дорогие авиабилеты" << endl;
        cout << "9. Выход" << endl;
        cout << "Сделайте выбор: ";

        int choice;
        cin >> choice;
        cout << endl;
        switch (choice)
        {
            case 1:
                addFlight();
                break;
            case 2:
                displayFlights();
                break;
            case 3:
                searchFlights();
                break;
            case 4:
                editPriceFlight();
                break;
            case 5:
                editTimeFlight();
                break;
            case 6:
                deleteFlight();
                break;
            case 7:
                findClosestAndFarthest();
                break;
            case 8:
                findCheapestAndMostExpensive();
                break;
            case 9:
                exit(0);
                break;
            default:
                cout << "Ошибка ввода" << endl;
                break;
        }

        cout << endl;
    }

    return 0;
}
