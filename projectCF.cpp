#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <thread>
#include <windows.h>
#include <iomanip>

using namespace std;

struct FoodItem {
    string name;
    int price;
    int quantity;
    int quantityOrdered;
};

class User {
public:
    string username;
    string password;
    string role;  // Quyền của người dùng: "manager" hoặc "staff"
};

class Restaurant : public User{
private:
    vector<FoodItem> staffMenu;
    vector<FoodItem> managerMenu;
    vector<User> userList;
    string userRole;

public:
    void displayManagerMenu() {
        FoodItem item;
        cout << "Manager Menu:" << endl;
        for (int i = 0; i < managerMenu.size(); i++) {
            cout << i + 1 << ". " << managerMenu[i].name << "| " << managerMenu[i].price << "vnd" << "| " << managerMenu[i].quantity << endl;
        }
        cout << endl;
    }

    void displayStaffMenu() {
        FoodItem item;
        cout << "Staff Menu:" << endl;
        for (int i = 0; i < managerMenu.size(); i++) {
            cout << i + 1 << ". " << managerMenu[i].name << "| " << managerMenu[i].price << "vnd" << "| " << managerMenu[i].quantity << endl;
        }
        cout << endl;
    }

    void input() {
        int n;
        cout << "Enter so luong: ";
        cin >> n;
        cin.ignore(); // Xóa bộ nhớ đệm sau khi nhập số lượng

        for (int i = 0; i < n; i++) {
            FoodItem item;
            cout << "Food " << i + 1 << " ";

            cout << "Name: ";
            getline(cin, item.name);

            cout << "Price: ";
            cin >> item.price;
            cin.ignore(); // Xóa bộ nhớ đệm sau khi nhập giá
            cout << "Enter quantity: " << endl;
            cin >> item.quantity;
            cin.ignore();

            staffMenu.push_back(item);




            managerMenu.push_back(item);
        }
    }

    void saveMenuToFile(const string& filename) {
        ofstream file(filename);

        if (file.is_open()) {
            for (const FoodItem& item : managerMenu) {
                file << item.name << "|" << item.price << "|" << item.quantity << endl;
            }
            file.close();
            cout << "Menu saved to file." << endl;
        } else {
            cout << "Unable to save menu to file." << endl;
        }
    }

    void loadMenuFromFile(const string& filename) {
    ifstream file(filename);

    if (file.is_open()) {
        managerMenu.clear();
        string line;
        while (getline(file, line)) {
            size_t pos = line.find('|');
            if (pos != string::npos) {
                FoodItem item;
                item.name = line.substr(0, pos);
                size_t pos2 = line.find('|', pos + 1);
                if (pos2 != string::npos) {
                    item.price = stod(line.substr(pos + 1, pos2 - pos - 1));
                    item.quantity = stoi(line.substr(pos2 + 1));
                    managerMenu.push_back(item);
                }
            }
        }
        file.close();
        cout << "Menu loaded from file." << endl;
    } else {
        cout << "Unable to load menu from file." << endl;
    }
}

    void addFood() {
        cout << "Enter food name: ";
        string newItem;
        cin.ignore();
        getline(cin, newItem);

        cout << "Enter price: ";
        double newPrice;
        cin >> newPrice;
        cout << "Enter quantity: ";
        int newQuantity;
        cin >> newQuantity;


        FoodItem item;
        item.name = newItem;
        item.price = newPrice;
        item.quantity = newQuantity;
        staffMenu.push_back(item);



        managerMenu.push_back(item);

        cout << "New food has been added." << endl;
    }

    void deleteFood() {
        int itemIndex;
        cout << "Enter index to delete: ";
        cin >> itemIndex;
        if (itemIndex >= 1 && itemIndex <= managerMenu.size()) {
            managerMenu.erase(managerMenu.begin() + itemIndex - 1);
            cout << "Food deleted." << endl;
        } else {
            cout << "Invalid !." << endl;
        }
    }

    void modifyFood() {
        int itemIndex;
        cout << "Enter the index of the item to modify: ";
        cin >> itemIndex;
        if (itemIndex >= 1 && itemIndex <= managerMenu.size()) {
            cout << "Enter the new food name: ";
            string newName;
            cin.ignore();
            getline(cin, newName);
            cout << "Enter the new price: ";
            double newPrice;
            cin >> newPrice;
            int newQuantity;
            cout << "Enter the new quantity: ";
            cin >> newQuantity;

            managerMenu[itemIndex - 1].name = newName;
            managerMenu[itemIndex - 1].price = newPrice;
            managerMenu[itemIndex - 1].quantity = newQuantity;
            cout << "Food modified." << endl;
        } else {
            cout << "Invalid index." << endl;
        }
    }

 void readMenuFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        managerMenu.clear(); // Xóa dữ liệu hiện tại trong managerMenu

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string name;
            int price;
            int quantity;

            if (std::getline(iss, name, '|') && iss >> price && iss.ignore() && iss >> quantity) {
                FoodItem item{name, price, quantity, 0}; // Khởi tạo quantityOrdered ban đầu là 0
                managerMenu.push_back(item);
            } else {
                std::cout << "Invalid data format in the file." << std::endl;
            }
        }

        file.close();
    } else {
        std::cout << "Failed to open the file." << std::endl;
    }
}

int calculateTotalPrice() {
    int totalPrice = 0;
    for (const FoodItem& item : managerMenu) {
        totalPrice += item.price * item.quantityOrdered;
        
         
    }
    return totalPrice;
}

void order() {
    int orderIndex;
    int quantity;
    readMenuFromFile("menu.txt");
    std::cout << "Enter the index of the food item to order: ";
    std::cin >> orderIndex;
    std::cout << "Enter the quantity to order: ";
    std::cin >> quantity;

    if (orderIndex >= 1 && orderIndex <= managerMenu.size()) {
        std::cout << "You ordered " << quantity << " " << managerMenu[orderIndex - 1].name << "." << std::endl;
        managerMenu[orderIndex - 1].quantity -= quantity;
        managerMenu[orderIndex - 1].quantityOrdered += quantity;
        int totalPrice = calculateTotalPrice();
        std::cout << "Total price: " << totalPrice << "vnd" << std::endl;




    } else {
        std::cout << "Invalid index." << std::endl;
    }
}


void addUser() {
    User user;

    cout << "Enter username: ";
    cin >> user.username;
    cout << "Enter password: ";
    cin >> user.password;

    user.role = (user.username == "tudepchai" && user.password == "tudepchai123") ? "manager" : "staff"; // toán tử điều kiện

    userList.push_back(user);
    saveUserListToFile("userlist.txt", userList);
    cout << user.role << " account created successfully." << endl;
}

bool Manager() {
    string username, password;

    while (true) {
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        if (username == "tudepchai" && password == "tudepchai123") {
            userRole = "manager";
            cout << "Login successful. Welcome, manager!" << endl;
            break;
        } else {
            cout << "Invalid username or password. Please try again." << endl;
        }
    }

    return true;
}
bool Staff() {
    User user;

    cout << "Enter username: ";
    cin >> user.username;
    cout << "Enter password: ";
    cin >> user.password;

    user.role = "staff";

    userList.push_back(user);
    saveUserListToFile("userlist.txt", userList);

    cout << "Staff account created successfully." << endl;
    return true;
}
void saveUserListToFile(const string& filename, const vector<User>& userList) {
    ofstream file(filename);

    if (file.is_open()) {
        for (const auto& user : userList) {
            file << user.username << "|" << user.password << "|" << user.role << endl;
        }
        file.close();
        cout << "User list saved to file." << endl;
    } else {
        cout << "Unable to save user list to file." << endl;
    }
}

void loadUserListFromFile(const string& filename, vector<User>& userList) {
    ifstream file(filename);

    if (file.is_open()) {
        userList.clear();
        string line;
        while (getline(file, line)) {
            size_t pos1 = line.find('|');
            if (pos1 != string::npos) {
                User user;
                user.username = line.substr(0, pos1);
                size_t pos2 = line.find('|', pos1 + 1);
                if (pos2 != string::npos) {
                    user.password = line.substr(pos1 + 1, pos2 - pos1 - 1);
                    user.role = line.substr(pos2 + 1);
                    userList.push_back(user);
                }
            }
        }
        file.close();
        cout << "User list loaded from file." << endl;
    } else {
        cout << "Unable to load user list from file." << endl;
    }
}

void displayUserList() {
    vector<User> userList;
   string filename = "userlist.txt";

    loadUserListFromFile(filename, userList);

    cout << "User List:" << endl;
    for (const auto& user : userList) {
        cout << "Username: " << user.username << " | Role: " << user.role << endl;
    }
    cout << endl;
}

void deleteUser() {
    vector<User> userList;
   string filename = "userlist.txt";
    loadUserListFromFile(filename, userList);

    cout << "Enter the username of the user to delete: ";
    string username;
    cin >> username;

    bool foundUser = false;
    for (auto it = userList.begin(); it != userList.end(); ++it) {
        if (it->username == username) {
            userList.erase(it);
            foundUser = true;
            break;
        }
    }

    if (foundUser) {
        cout << "User deleted." << endl;
        saveUserListToFile(filename, userList);
    } else {
        cout << "User not found." << endl;
    }
}
void setBackgroundColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    WORD currentAttributes = consoleInfo.wAttributes;
    int backgroundColor = color << 4;
    SetConsoleTextAttribute(hConsole, currentAttributes | backgroundColor);
}

void resetColor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

  void login() {
    string filename;
    string username;
    string password;
Restaurant restaurant;
User user;
    vector<User> userList;
    loadUserListFromFile("userlist.txt", userList);

    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    bool userFound = false;
    string userRole;
    for (const User& user : userList) {
        if (user.username == username && user.password == password) {
            userFound = true;
            userRole = user.role;
            break;
        }
    }

    while (!userFound) {
        cout << "Invalid username or password. Please try again." << endl;
        cout << "Username: ";
        cin >> username;
        cout << "Password: ";
        cin >> password;

        for (const User& user : userList) {
            if (user.username == username && user.password == password) {
                userFound = true;
                userRole = user.role;
                break;
            }
        }
    }

    // Xử lý tương ứng với userRole
    cout << "Logged in as: " << username << " (" << userRole << ")" << endl;
    saveUserListToFile("userlist.txt", userList);



    if (userRole == "manager") {
        cout << "\t\tLogin successful." << endl;
        cout << "\t\tWelcome, manager!" << endl;
        int choice;

        do {

    std::cout << "\t\t╔══════════════════════════╗" << std::endl;
    std::cout << "\t\t║        MENU              ║" << std::endl;
    std::cout << "\t\t╠══════════════════════════╣" << std::endl;
    std::cout << "\t\t║  1. Display Manager Menu ║" << std::endl;
    std::cout << "\t\t║  2. Input Menu           ║" << std::endl;
    std::cout << "\t\t║  3. Save Menu            ║" << std::endl;
    std::cout << "\t\t║  4. Add Food             ║" << std::endl;
    std::cout << "\t\t║  5. Delete Food          ║" << std::endl;
    std::cout << "\t\t║  6. Modify Food          ║" << std::endl;
    std::cout << "\t\t║  7. Display User List    ║" << std::endl;
    std::cout << "\t\t║  8. Delete User          ║" << std::endl;
    std::cout << "\t\t║  9. Load Menu from File  ║" << std::endl;
    std::cout << "\t\t║  0. Exit                 ║" << std::endl;
    std::cout << "\t\t╚══════════════════════════╝" << std::endl;

            cout << "Enter your choice: ";
            cin >> choice;
                switch (choice) {
                    case 1:
                        restaurant.displayManagerMenu();
                        break;

                    case 2:
                        restaurant.input();
                        break;
                    case 3:
                        if (userRole == "manager") {
                        cout << "Enter the filename to save the menu: ";

                        cin.ignore();
                        getline(cin, filename);
                        restaurant.saveMenuToFile(filename);
                    } else {
                        cout << "KHONG DU QUYEN TRUY CAP !" << endl;
                    }
                    break;

                    case 4:
                        restaurant.addFood();
                        break;
                    case 5:
                        restaurant.deleteFood();
                        break;
                    case 6:
                        restaurant.modifyFood();
                        break;
                    case 7:

                        restaurant.displayUserList();
                        break;
                        case 8:

                        restaurant.deleteUser();
                        break;
                        case 9:
                        cout << "Enter file name of menu: ";

                        cin.ignore();
                        getline(cin, filename);
                        restaurant.loadMenuFromFile(filename);
                    break;
                    case 0:
                        cout << "Exiting the program." << endl;
                        break;
                    default:
                        cout << "Invalid choice. Please try again." << endl;
                        break;
                }
            } while (choice != 0);
            // Menu and user management functions
        } else if (userRole == "staff") {
            cout << "\t\tLogin successful." << endl;
            cout << "\t\tWelcome, staff!" << endl;
            // Functions for staff members
            int choice;
            do {

    std::cout << "\t\t╔══════════════════════════╗" << std::endl;
    std::cout << "\t\t║         MENU             ║" << std::endl;
    std::cout << "\t\t╠══════════════════════════╣" << std::endl;
    std::cout << "\t\t║  1. Load Menu from File  ║" << std::endl;
    std::cout << "\t\t║  2. Display Staff Menu   ║" << std::endl;
    std::cout << "\t\t║  3. Order Food           ║" << std::endl;
    std::cout << "\t\t║  4. Total                ║" << std::endl;
    std::cout << "\t\t║  0. Exit                 ║" << std::endl;
    std::cout << "\t\t╚══════════════════════════╝" << std::endl;

                cout << "Enter your choice: ";
                cin >> choice;

                switch (choice) {
                    case 1:

                        cout << "Enter file name of menu: ";

                        cin.ignore();
                        getline(cin, filename);
                        restaurant.loadMenuFromFile(filename);

                        break;
                    case 2:
                        restaurant.displayStaffMenu();
                        break;
                    case 3:
                        restaurant.order();
                        break;
                    case 4:
                         cout << "Total Price: " << restaurant.calculateTotalPrice() << "vnd" << endl;
                            break;


                    case 0:
                        cout << "Exiting the program." << endl;
                        break;
                    default:
                        cout << "Invalid choice. Please try again." << endl;
                        break;
                }
            } while (choice != 0);


    } else {
        cout << "Invalid username or password." << endl;
    }
}
};


       int main() {

    // Các phần khác của chương trình
Restaurant restaurant;
    cout << setfill('-') << setw(74) << "-" << endl;
    cout << "|                     Welcome to Anh Tu CoffeeShop!                     |" << endl;
    cout << "|               Sign up to use the CoffeeShop system                 |" << endl;
    cout << setfill('-') << setw(74) << "-" << endl;
cout.flush(); // Đảm bảo thông báo xuất hiện ngay lập tức

       for (int i = 0; i <= 100; i+=10) {
        Sleep(1000);
        cout << "Loading..." << " "<< i << "%" << endl;

        cout.flush(); // Đảm bảo dấu chấm xuất hiện ngay lập tức
    }
    cout << "Completed!" << endl;
    int signUpChoice;

    cout << "\t\t Do you want to sign up ?" << endl;
    cout << setfill('*') << setw(60) << "*" << endl;
    cout << "*                  Sign up Options                   *" << endl;
    cout << setfill('-') << setw(60) << "-" << endl;
    cout << "|  1. Yes                                          |" << endl;
    cout << "|  0. No                                           |" << endl;
    cout << setfill('-') << setw(60) << "-" << endl;

    cin >> signUpChoice;
    if (signUpChoice == 0) {
        cout << "\t\t Skipping sign up..." << endl;
        cout.flush(); // Đảm bảo thông báo xuất hiện ngay lập tức

       for (int i = 0; i <= 100; i+=20) {
        Sleep(1000);
        cout << "Loading..." << " "<< i  << "%" << endl;

        cout.flush(); // Đảm bảo dấu chấm xuất hiện ngay lập tức
    }
    cout << "Completed!" << endl;

    } else {

        restaurant.addUser();
    }


    cout << "\t\t Do you want to login ?" << endl;
    cout << setfill('-') << setw(60) << "-" << endl;
    cout << "|                   Login Options                      |" << endl;
    cout << setfill('-') << setw(60) << "-" << endl;
    cout << "|  yes (click 1)                                       |" << endl;
    cout << "|  no  (click 0)                                       |" << endl;
    cout << setfill('-') << setw(60) << "-" << endl;

    int loginChoice;
    cin >> loginChoice;
    if (loginChoice == 0) {
        cout << "Exiting the program...";
        cout.flush(); // Đảm bảo thông báo xuất hiện ngay lập tức

       for (int i = 0; i <= 100; i+=10) {
        Sleep(1000);
        cout << "Loading..." << " "<< i  << "%" << endl;

        cout.flush(); // Đảm bảo dấu chấm xuất hiện ngay lập tức
    }

    cout << "Completed!" << endl;
    return 0;
    } else {
        switch (loginChoice) {
            case 1:

                restaurant.login();
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }

    return 0;
}









// Path: cccxc.cpp



