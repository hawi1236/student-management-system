#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>
#include <algorithm>
#include <cctype>
#include <limits>

using namespace std;

// ====================== PERSON ======================
class Person {
protected:
    int id;
    string name;
    string phone;
    string email;

public:
    Person() : id(0) {}
    Person(int id, string name, string phone, string email)
        : id(id), name(name), phone(phone), email(email) {}

    int getId() const { return id; }
    string getName() const { return name; }
    string getPhone() const { return phone; }
    string getEmail() const { return email; }

    void setId(int id) { this->id = id; }
    void setName(string name) { this->name = name; }
    void setPhone(string phone) { this->phone = phone; }
    void setEmail(string email) { this->email = email; }

    virtual void input() {
        cout << "Enter Name: ";
        getline(cin >> ws, name);

        cout << "Enter Phone: ";
        getline(cin, phone);

        cout << "Enter Email: ";
        getline(cin, email);
    }
};

// ====================== CUSTOMER ======================
class Customer : public Person {
private:
    string address;
    string nationality;
    string idProof;
    string idNumber;

public:
    Customer() {}
    Customer(int id, string name, string phone, string email,
             string address, string nationality, string idProof, string idNumber)
        : Person(id, name, phone, email), address(address), nationality(nationality), idProof(idProof), idNumber(idNumber) {}

    string getAddress() const { return address; }
    string getNationality() const { return nationality; }
    string getIdProof() const { return idProof; }
    string getIdNumber() const { return idNumber; }

    void setAddress(string address) { this->address = address; }
    void setNationality(string nationality) { this->nationality = nationality; }
    void setIdProof(string idProof) { this->idProof = idProof; }
    void setIdNumber(string idNumber) { this->idNumber = idNumber; }

    void display() const {
        cout << "\n┌─────────────────────────────────────────────────────┐" << endl;
        cout << "│                 CUSTOMER INFORMATION                │" << endl;
        cout << "├─────────────────────────────────────────────────────┤" << endl;
        cout << "│ ID:           " << setw(38) << left << id << "│" << endl;
        cout << "│ Name:         " << setw(38) << left << name << "│" << endl;
        cout << "│ Phone:        " << setw(38) << left << phone << "│" << endl;
        cout << "│ Email:        " << setw(38) << left << email << "│" << endl;
        cout << "│ Address:      " << setw(38) << left << address << "│" << endl;
        cout << "│ Nationality:  " << setw(38) << left << nationality << "│" << endl;
        cout << "│ ID Proof:     " << setw(38) << left << idProof << "│" << endl;
        cout << "│ ID Number:    " << setw(38) << left << idNumber << "│" << endl;
        cout << "└─────────────────────────────────────────────────────┘" << endl;
    }

    void input() override {
        Person::input();
        cout << "Enter Address: ";
        getline(cin >> ws, address);
        cout << "Enter Nationality: ";
        getline(cin, nationality);
        cout << "Enter ID Proof Type (Passport/Driving License/ID Card): ";
        getline(cin, idProof);
        cout << "Enter ID Number: ";
        getline(cin, idNumber);
    }
};

// ====================== ROOM ======================
class Room {
private:
    int roomNumber;
    string roomType;
    double pricePerNight;
    bool isAvailable;
    int maxCapacity;

public:
    Room() : roomNumber(0), roomType("Standard"), pricePerNight(100.0), isAvailable(true), maxCapacity(1) {}
    Room(int roomNumber, string roomType, double pricePerNight, bool isAvailable, int maxCapacity)
        : roomNumber(roomNumber), roomType(roomType), pricePerNight(pricePerNight), isAvailable(isAvailable), maxCapacity(maxCapacity) {}

    int getRoomNumber() const { return roomNumber; }
    string getRoomType() const { return roomType; }
    double getPricePerNight() const { return pricePerNight; }
    bool getIsAvailable() const { return isAvailable; }
    int getMaxCapacity() const { return maxCapacity; }

    void setRoomNumber(int roomNumber) { this->roomNumber = roomNumber; }
    void setRoomType(string roomType) { this->roomType = roomType; }
    void setPricePerNight(double pricePerNight) { this->pricePerNight = pricePerNight; }
    void setIsAvailable(bool isAvailable) { this->isAvailable = isAvailable; }
    void setMaxCapacity(int maxCapacity) { this->maxCapacity = maxCapacity; }

    void display() const {
        string status = isAvailable ? "Available" : "Occupied";
        cout << "\n┌─────────────────────────────────────────────────────┐" << endl;
        cout << "│                   ROOM INFORMATION                  │" << endl;
        cout << "├─────────────────────────────────────────────────────┤" << endl;
        cout << "│ Room Number:  " << setw(38) << left << roomNumber << "│" << endl;
        cout << "│ Room Type:    " << setw(38) << left << roomType << "│" << endl;
        cout << "│ Price/Night: $" << setw(37) << left << fixed << setprecision(2) << pricePerNight << "│" << endl;
        cout << "│ Status:       " << setw(38) << left << status << "│" << endl;
        cout << "│ Max Capacity: " << setw(38) << left << maxCapacity << "│" << endl;
        cout << "└─────────────────────────────────────────────────────┘" << endl;
    }

    void input() {
        cout << "Enter Room Number: ";
        while (!(cin >> roomNumber)) {
            cout << "Invalid input. Enter numeric room number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "Room Types Available:" << endl;
        vector<string> types = getRoomTypes();
        for (int i = 0; i < (int)types.size(); ++i) {
            cout << i+1 << ". " << types[i] << " - $" << getTypePrice(types[i]) << "/night" << endl;
        }

        int choice;
        cout << "Select Room Type (1-" << types.size() << "): ";
        while (!(cin >> choice) || choice < 1 || choice > (int)types.size()) {
            cout << "Invalid choice. Select (1-" << types.size() << "): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        roomType = types[choice - 1];
        pricePerNight = getTypePrice(roomType);

        cout << "Enter Maximum Capacity: ";
        while (!(cin >> maxCapacity) || maxCapacity < 1) {
            cout << "Invalid. Enter a positive integer for capacity: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        isAvailable = true;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    double calculatePrice(int nights) const {
        return pricePerNight * nights;
    }

    static vector<string> getRoomTypes() {
        return {"Standard", "Deluxe", "Suite", "Executive Suite", "Presidential Suite"};
    }

    static double getTypePrice(const string& roomType) {
        if (roomType == "Standard") return 100.0;
        if (roomType == "Deluxe") return 150.0;
        if (roomType == "Suite") return 250.0;
        if (roomType == "Executive Suite") return 400.0;
        if (roomType == "Presidential Suite") return 800.0;
        return 100.0;
    }
};

// ====================== BOOKING ======================
class Booking {
private:
    static int nextBookingId;

    int bookingId;
    Customer customer;
    Room room;
    string checkInDate;
    string checkOutDate;
    int numberOfNights;
    int numberOfGuests;
    string bookingStatus;

public:
    Booking() : bookingId(nextBookingId++), numberOfNights(0), numberOfGuests(1), bookingStatus("Confirmed") {}

    Booking(Customer customer, Room room, string checkInDate, string checkOutDate, int numberOfGuests)
        : bookingId(nextBookingId++), customer(customer), room(room), checkInDate(checkInDate), checkOutDate(checkOutDate), numberOfGuests(numberOfGuests), bookingStatus("Confirmed") {
        numberOfNights = calculateNights(checkInDate, checkOutDate);
    }

    int getBookingId() const { return bookingId; }
    Customer getCustomer() const { return customer; }
    Room getRoom() const { return room; }
    string getCheckInDate() const { return checkInDate; }
    string getCheckOutDate() const { return checkOutDate; }
    int getNumberOfNights() const { return numberOfNights; }
    int getNumberOfGuests() const { return numberOfGuests; }
    string getBookingStatus() const { return bookingStatus; }

    void setCustomer(Customer customer) { this->customer = customer; }
    void setRoom(Room room) { this->room = room; }
    void setCheckInDate(string checkInDate) { this->checkInDate = checkInDate; if (!checkOutDate.empty()) numberOfNights = calculateNights(checkInDate, checkOutDate); }
    void setCheckOutDate(string checkOutDate) { this->checkOutDate = checkOutDate; if (!checkInDate.empty()) numberOfNights = calculateNights(checkInDate, checkOutDate); }
    void setNumberOfGuests(int numberOfGuests) { this->numberOfGuests = numberOfGuests; }
    void setBookingStatus(string bookingStatus) { this->bookingStatus = bookingStatus; }

    void display() const {
        cout << "\n┌─────────────────────────────────────────────────────┐" << endl;
        cout << "│                 BOOKING INFORMATION                 │" << endl;
        cout << "├─────────────────────────────────────────────────────┤" << endl;
        cout << "│ Booking ID:   " << setw(38) << left << bookingId << "│" << endl;
        cout << "│ Customer:     " << setw(38) << left << customer.getName() << "│" << endl;
        cout << "│ Room No:      " << setw(38) << left << room.getRoomNumber() << "│" << endl;
        cout << "│ Room Type:    " << setw(38) << left << room.getRoomType() << "│" << endl;
        cout << "│ Check-In:     " << setw(38) << left << checkInDate << "│" << endl;
        cout << "│ Check-Out:    " << setw(38) << left << checkOutDate << "│" << endl;
        cout << "│ Nights:       " << setw(38) << left << numberOfNights << "│" << endl;
        cout << "│ Guests:       " << setw(38) << left << numberOfGuests << "│" << endl;
        cout << "│ Total Cost:  $" << setw(37) << left << fixed << setprecision(2) << calculateTotalCost() << "│" << endl;
        cout << "│ Status:       " << setw(38) << left << bookingStatus << "│" << endl;
        cout << "└─────────────────────────────────────────────────────┘" << endl;
    }

    void input(vector<Room>& rooms, vector<Customer>& customers) {
        if (customers.empty()) {
            cout << "No customers available. Please add a customer first." << endl;
            return;
        }

        cout << "\nSelect Customer:" << endl;
        for (int i = 0; i < (int)customers.size(); ++i) {
            cout << i+1 << ". " << customers[i].getName() << " (ID: " << customers[i].getId() << ")" << endl;
        }

        int customerChoice;
        cout << "Enter choice (1-" << customers.size() << "): ";
        while (!(cin >> customerChoice) || customerChoice < 1 || customerChoice > (int)customers.size()) {
            cout << "Invalid choice. Enter (1-" << customers.size() << "): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        customer = customers[customerChoice - 1];

        vector<int> availableIndices;
        for (int i = 0; i < (int)rooms.size(); ++i) if (rooms[i].getIsAvailable()) availableIndices.push_back(i);

        if (availableIndices.empty()) {
            cout << "No rooms available for booking." << endl;
            return;
        }

        cout << "\nAvailable Rooms:" << endl;
        for (int i = 0; i < (int)availableIndices.size(); ++i) {
            int idx = availableIndices[i];
            cout << i+1 << ". Room " << rooms[idx].getRoomNumber() << " - " << rooms[idx].getRoomType() << " - $" << rooms[idx].getPricePerNight() << "/night" << endl;
        }

        int roomChoice;
        cout << "Select Room (1-" << availableIndices.size() << "): ";
        while (!(cin >> roomChoice) || roomChoice < 1 || roomChoice > (int)availableIndices.size()) {
            cout << "Invalid. Enter (1-" << availableIndices.size() << "): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        int selectedRoomIndex = availableIndices[roomChoice - 1];
        room = rooms[selectedRoomIndex];
        rooms[selectedRoomIndex].setIsAvailable(false); // mark occupied

        cout << "Enter Check-In Date (DD/MM/YYYY): ";
        cin >> checkInDate;
        cout << "Enter Check-Out Date (DD/MM/YYYY): ";
        cin >> checkOutDate;

        numberOfNights = calculateNights(checkInDate, checkOutDate);

        cout << "Enter Number of Guests: ";
        while (!(cin >> numberOfGuests) || numberOfGuests < 1) {
            cout << "Invalid. Enter positive number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        bookingStatus = "Confirmed";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    double calculateTotalCost() const {
        return room.calculatePrice(numberOfNights);
    }

    bool isDateValid(string date) const {
        return date.length() == 10 && date[2] == '/' && date[5] == '/';
    }

    static string getCurrentDate() {
        time_t now = time(0);
        tm* localtm = localtime(&now);
        stringstream ss;
        ss << setw(2) << setfill('0') << localtm->tm_mday << "/"
           << setw(2) << setfill('0') << (localtm->tm_mon + 1) << "/"
           << (localtm->tm_year + 1900);
        return ss.str();
    }

    int calculateNights(string checkIn, string checkOut) {
        // naive calculation, handles same-month simple cases
        try {
            int d1 = stoi(checkIn.substr(0,2));
            int m1 = stoi(checkIn.substr(3,2));
            int y1 = stoi(checkIn.substr(6,4));
            int d2 = stoi(checkOut.substr(0,2));
            int m2 = stoi(checkOut.substr(3,2));
            int y2 = stoi(checkOut.substr(6,4));

            if (y1==y2 && m1==m2) return max(1, d2 - d1);

            // fallback: compute difference using tm
            tm a = {0}, b = {0};
            a.tm_mday = d1; a.tm_mon = m1-1; a.tm_year = y1-1900;
            b.tm_mday = d2; b.tm_mon = m2-1; b.tm_year = y2-1900;
            time_t ta = mktime(&a);
            time_t tb = mktime(&b);
            if (ta!= (time_t)-1 && tb != (time_t)-1) {
                double diff = difftime(tb, ta);
                int days = (int)(diff / (60*60*24));
                return max(1, days);
            }
            return 1;
        } catch (...) {
            return 1;
        }
    }
};

int Booking::nextBookingId = 1000;

// ====================== BILL ======================
class Bill {
private:
    static int nextBillId;

    int billId;
    Booking booking;
    double roomCharges;
    double serviceCharges;
    double tax;
    double discount;
    double totalAmount;
    string paymentMethod;
    string paymentStatus;

public:
    Bill() : billId(nextBillId++), roomCharges(0), serviceCharges(0), tax(0), discount(0), totalAmount(0), paymentMethod("Cash"), paymentStatus("Pending") {}

    Bill(Booking booking) : billId(nextBillId++), booking(booking), roomCharges(0), serviceCharges(0), tax(0), discount(0), totalAmount(0), paymentMethod("Cash"), paymentStatus("Pending") {
        generateBill();
    }

    int getBillId() const { return billId; }
    Booking getBooking() const { return booking; }
    double getRoomCharges() const { return roomCharges; }
    double getServiceCharges() const { return serviceCharges; }
    double getTax() const { return tax; }
    double getDiscount() const { return discount; }
    double getTotalAmount() const { return totalAmount; }
    string getPaymentMethod() const { return paymentMethod; }
    string getPaymentStatus() const { return paymentStatus; }

    void setBooking(Booking booking) { this->booking = booking; generateBill(); }
    void setPaymentMethod(string paymentMethod) { this->paymentMethod = paymentMethod; }
    void setPaymentStatus(string paymentStatus) { this->paymentStatus = paymentStatus; }
    void setDiscount(double discount) { this->discount = discount; calculateTotal(); }

    void display() const {
        cout << "\n═══════════════════════════════════════════════════════════" << endl;
        cout << "                       HOTEL BILL                          " << endl;
        cout << "═══════════════════════════════════════════════════════════" << endl;
        cout << "  Bill ID:           " << billId << endl;
        cout << "  Booking ID:        " << booking.getBookingId() << endl;
        cout << "  Customer:          " << booking.getCustomer().getName() << endl;
        cout << "  Room No:           " << booking.getRoom().getRoomNumber() << endl;
        cout << "  Check-In:          " << booking.getCheckInDate() << endl;
        cout << "  Check-Out:         " << booking.getCheckOutDate() << endl;
        cout << "  Nights:            " << booking.getNumberOfNights() << endl;
        cout << endl;
        cout << "  -------------------------------------------------------" << endl;
        cout << "  Room Charges:      $" << setw(10) << right << fixed << setprecision(2) << roomCharges << endl;
        cout << "  Service Charges:   $" << setw(10) << right << serviceCharges << endl;
        cout << "  Tax (15%):         $" << setw(10) << right << tax << endl;
        cout << "  Discount:         -$" << setw(10) << right << discount << endl;
        cout << "  -------------------------------------------------------" << endl;
        cout << "  TOTAL AMOUNT:      $" << setw(10) << right << totalAmount << endl;
        cout << endl;
        cout << "  Payment Method:    " << paymentMethod << endl;
        cout << "  Payment Status:    " << paymentStatus << endl;
        cout << "═══════════════════════════════════════════════════════════" << endl;
    }

    void printBill() const { display(); cout << "\nThank you for choosing our hotel!" << endl; }

    void saveToFile() const {
        ofstream file("bills.txt", ios::app);
        if (file.is_open()) {
            file << "Bill ID: " << billId << endl;
            file << "Customer: " << booking.getCustomer().getName() << endl;
            file << "Total: $" << fixed << setprecision(2) << totalAmount << endl;
            file << "Date: " << Booking::getCurrentDate() << endl;
            file << "------------------------" << endl;
            file.close();
        }
    }

    void generateBill() { calculateCharges(); calculateTax(); calculateTotal(); }

    void calculateCharges() { roomCharges = booking.calculateTotalCost(); serviceCharges = roomCharges * 0.10; }
    void calculateTax() { tax = (roomCharges + serviceCharges) * 0.15; }
    void calculateTotal() { totalAmount = roomCharges + serviceCharges + tax - discount; }

    static vector<string> getPaymentMethods() { return {"Cash", "Credit Card", "Debit Card", "Bank Transfer", "Online Payment"}; }
};

int Bill::nextBillId = 5000;

// ====================== HOTEL ======================
class Hotel {
private:
    string hotelName, hotelAddress, hotelPhone, hotelEmail;
    vector<Customer> customers;
    vector<Room> rooms;
    vector<Booking> bookings;
    vector<Bill> bills;

public:
    Hotel(string name = "My Hotel", string address = "", string phone = "", string email = "")
        : hotelName(name), hotelAddress(address), hotelPhone(phone), hotelEmail(email) {
        initializeRooms();
    }

    string getHotelName() const { return hotelName; }
    string getHotelAddress() const { return hotelAddress; }
    string getHotelPhone() const { return hotelPhone; }
    string getHotelEmail() const { return hotelEmail; }

    void displayHotelInfo() const {
        cout << "\n═══════════════════════════════════════════════════════════" << endl;
        cout << "                    " << hotelName << "                      " << endl;
        cout << "═══════════════════════════════════════════════════════════" << endl;
        cout << "  Address:  " << hotelAddress << endl;
        cout << "  Phone:    " << hotelPhone << endl;
        cout << "  Email:    " << hotelEmail << endl;
        cout << "═══════════════════════════════════════════════════════════" << endl;
    }

    void initializeRooms() {
        // initial rooms
        rooms.push_back(Room(101, "Standard", 100.0, true, 2));
        rooms.push_back(Room(102, "Standard", 100.0, true, 2));
        rooms.push_back(Room(103, "Deluxe", 150.0, true, 3));
        rooms.push_back(Room(104, "Deluxe", 150.0, true, 3));
        rooms.push_back(Room(201, "Suite", 250.0, true, 4));
        rooms.push_back(Room(202, "Suite", 250.0, true, 4));
        rooms.push_back(Room(301, "Executive Suite", 400.0, true, 4));
        rooms.push_back(Room(302, "Presidential Suite", 800.0, true, 6));
    }

    void addCustomer() {
        // clear screen (works on Windows). If not Windows, it's harmless.
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        cout << "\n═══════════════════════════════════════════════════════════" << endl;
        cout << "                     ADD NEW CUSTOMER                      " << endl;
        cout << "═══════════════════════════════════════════════════════════" << endl;

        Customer customer;
        customer.setId(generateCustomerId());
        customer.input();

        customers.push_back(customer);

        cout << "\n✅ Customer added successfully!" << endl;
        cout << "Customer ID: " << customer.getId() << endl;
        cout << "Press Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }

    void displayAllCustomers() const {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        cout << "\n═══════════════════════════════════════════════════════════" << endl;
        cout << "                     ALL CUSTOMERS                         " << endl;
        cout << "═══════════════════════════════════════════════════════════" << endl;

        if (customers.empty()) {
            cout << "\n📭 No customers found!" << endl;
        } else {
            cout << "\nTotal Customers: " << customers.size() << endl;
            cout << "┌──────┬──────────────────────┬────────────────┬──────────────────────┐" << endl;
            cout << "│  ID  │        Name          │     Phone      │        Email         │" << endl;
            cout << "├──────┼──────────────────────┼────────────────┼──────────────────────┤" << endl;
            for (const auto& customer : customers) {
                cout << "│ " << setw(4) << left << customer.getId() << " │ "
                     << setw(20) << left << (customer.getName().length() > 20 ? customer.getName().substr(0, 17) + "..." : customer.getName()) << " │ "
                     << setw(14) << left << customer.getPhone() << " │ "
                     << setw(20) << left << (customer.getEmail().length() > 20 ? customer.getEmail().substr(0, 17) + "..." : customer.getEmail()) << " │" << endl;
            }
            cout << "└──────┴──────────────────────┴────────────────┴──────────────────────┘" << endl;
        }
        cout << "\nPress Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }

    void searchCustomer() const {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        cout << "\n═══════════════════════════════════════════════════════════" << endl;
        cout << "                     SEARCH CUSTOMER                       " << endl;
        cout << "═══════════════════════════════════════════════════════════" << endl;

        int id;
        cout << "Enter Customer ID to search: ";
        while (!(cin >> id)) {
            cout << "Invalid. Enter numeric ID: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        bool found = false;
        for (const auto& customer : customers) {
            if (customer.getId() == id) {
                customer.display();
                found = true;
                break;
            }
        }

        if (!found) cout << "\n❌ Customer with ID " << id << " not found!" << endl;

        cout << "Press Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }

    Customer* findCustomerById(int id) {
        for (auto& customer : customers) if (customer.getId() == id) return &customer;
        return nullptr;
    }

    int generateCustomerId() const {
        static int nextId = 1000;
        return nextId++;
    }

    void addRoom() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        cout << "\n═══════════════════════════════════════════════════════════" << endl;
        cout << "                       ADD NEW ROOM                        " << endl;
        cout << "═══════════════════════════════════════════════════════════" << endl;

        Room room;
        room.input();
        rooms.push_back(room);

        cout << "\n✅ Room added successfully!" << endl;
        cout << "Press Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }

    void displayAllRooms() const {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        cout << "\n═══════════════════════════════════════════════════════════" << endl;
        cout << "                       ALL ROOMS                           " << endl;
        cout << "═══════════════════════════════════════════════════════════" << endl;

        if (rooms.empty()) {
            cout << "\n📭 No rooms found!" << endl;
        } else {
            cout << "\nTotal Rooms: " << rooms.size() << endl;
            cout << "┌────────────┬──────────────────┬─────────────┬─────────┬──────────────┐" << endl;
            cout << "│ Room No    │     Type         │   Price     │ Status  │  Capacity    │" << endl;
            cout << "├────────────┼──────────────────┼─────────────┼─────────┼──────────────┤" << endl;
            for (const auto& room : rooms) {
                string status = room.getIsAvailable() ? "Available" : "Occupied";
                cout << "│ " << setw(10) << left << room.getRoomNumber() << " │ "
                     << setw(16) << left << room.getRoomType() << " │ $" << setw(10) << left << fixed << setprecision(2) << room.getPricePerNight() << " │ "
                     << setw(7) << left << status << " │ " << setw(12) << left << room.getMaxCapacity() << " │" << endl;
            }
            cout << "└────────────┴──────────────────┴─────────────┴─────────┴──────────────┘" << endl;
        }

        cout << "\nPress Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }

    void createBooking() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        cout << "\n═══════════════════════════════════════════════════════════" << endl;
        cout << "                      CREATE BOOKING                       " << endl;
        cout << "═══════════════════════════════════════════════════════════" << endl;

        Booking booking;
        booking.input(rooms, customers);

        // only push if booking has a valid customer (customer id != 0)
        if (booking.getNumberOfNights() > 0 && booking.getBookingStatus() == "Confirmed") {
            bookings.push_back(booking);
            cout << "\n✅ Booking created. Booking ID: " << booking.getBookingId() << endl;
        } else {
            cout << "\nBooking not created." << endl;
        }

        cout << "Press Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }

    void displayAllBookings() const {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        cout << "\n═══════════════════════════════════════════════════════════" << endl;
        cout << "                      ALL BOOKINGS                         " << endl;
        cout << "═══════════════════════════════════════════════════════════" << endl;

        if (bookings.empty()) {
            cout << "\n📭 No bookings found!" << endl;
        } else {
            for (const auto& b : bookings) b.display();
        }

        cout << "\nPress Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }

    void generateBill() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        if (bookings.empty()) {
            cout << "\nNo bookings available. Create a booking first." << endl;
            cout << "Press Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            return;
        }

        cout << "\nSelect Booking to generate bill:" << endl;
        for (int i = 0; i < (int)bookings.size(); ++i) {
            cout << i+1 << ". Booking ID: " << bookings[i].getBookingId() << " - Customer: " << bookings[i].getCustomer().getName() << "\n";
        }

        int choice;
        cout << "Enter choice (1-" << bookings.size() << "): ";
        while (!(cin >> choice) || choice < 1 || choice > (int)bookings.size()) {
            cout << "Invalid. Enter (1-" << bookings.size() << "): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        Booking sel = bookings[choice - 1];
        Bill bill(sel);

        cout << "\nGenerated Bill:" << endl;
        bill.display();

        cout << "\nDo you want to save this bill to file? (y/n): ";
        char c; cin >> c;
        if (c == 'y' || c == 'Y') {
            bill.saveToFile();
            cout << "Saved to bills.txt" << endl;
        }

        bills.push_back(bill);
        cout << "Press Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }

    void displayAllBills() const {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        cout << "\n═══════════════════════════════════════════════════════════" << endl;
        cout << "                         ALL BILLS                         " << endl;
        cout << "═══════════════════════════════════════════════════════════" << endl;

        if (bills.empty()) {
            cout << "\n📭 No bills found!" << endl;
        } else {
            for (const auto& bill : bills) bill.display();
        }

        cout << "\nPress Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }
};

// ====================== MAIN ======================
int main() {
    Hotel hotel("Hawi Hotel", "Addis Ababa, Ethiopia", "+251900000000", "info@hawihotel.com");

    int choice = -1;
    while (true) {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        cout << "\n========== HOTEL MANAGEMENT SYSTEM ==========" << endl;
        cout << "1. Add Customer" << endl;
        cout << "2. View All Customers" << endl;
        cout << "3. Search Customer" << endl;
        cout << "4. Add Room" << endl;
        cout << "5. View All Rooms" << endl;
        cout << "6. Create Booking" << endl;
        cout << "7. View All Bookings" << endl;
        cout << "8. Generate Bill" << endl;
        cout << "9. View All Bills" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1: hotel.addCustomer(); break;
            case 2: hotel.displayAllCustomers(); break;
            case 3: hotel.searchCustomer(); break;
            case 4: hotel.addRoom(); break;
            case 5: hotel.displayAllRooms(); break;
            case 6: hotel.createBooking(); break;
            case 7: hotel.displayAllBookings(); break;
            case 8: hotel.generateBill(); break;
            case 9: hotel.displayAllBills(); break;
            case 0: cout << "Goodbye!\n"; return 0;
            default: cout << "Invalid choice!"; break;
        }
    }

    return 0;
}
