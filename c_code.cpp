#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;

// Global variables
string actualUsername = "user123";
string actualPassword = "abc123";

// Global constants used for input validation
const int MAX_SHOPS = 4;
const int MAX_ITEMS = 3;

struct Item {
    string name;
    int price;
};

struct Shop {
    string name;
    Item items[MAX_ITEMS];
};

Shop shops[MAX_SHOPS] = { 
        { "clothes", { { "baby clothes" , 2000}, { "lady clothes" , 3000}, { "gent clothes" , 2500} } }, 
        { "mobiles", { { "Nokia" , 10000}, { "Samsung" , 35000}, { "iPhone" , 70000} } }, 
        { "jewelry", { { "diamond" , 100000}, { "gold" , 50000}, { "silver" , 30000} }  }, 
        { "shoes", { { "school shoes" , 1600}, { "ladies shoes" , 2000}, { "sports shoes" , 4000} } }, 
        };  

bool isValidLogin(string name, string password) {
    if (name == actualUsername && password == actualPassword) 
        return true;

    cout << "Your name or password is incorrect. Try again." << endl << endl;
    return false;
}

bool validateUser() {
    string username, password;
           
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    return isValidLogin(username, password);
}

void displayBill(int bill) {
    cout << endl << "Thank you for shopping" << endl << "Your current total bill is: " << bill << endl << endl;
}

void displayBoughtItems(string *boughtItems, int totalBoughtItems){
    cout << endl << "List of items are:" << endl;
    if (totalBoughtItems == 0) {
        cout << "No items bought" << endl << endl;
    } else {
        for (int i = 0; i < totalBoughtItems; i++) {
            cout << i + 1 << ". " << boughtItems[i] << endl;
        };
    }   
    cout << endl;
}

void saveShoppingHistory(string *boughtItems, int totalBoughtItems, int bill) {
    fstream savedFile;
    savedFile.open("ShoppingHistory.txt", ios::app);
    savedFile << "### List of bought items ###:" << endl;
    if (totalBoughtItems == 0) {
        savedFile << "No items bought" << endl;
    } else {
        for (int i = 0; i < totalBoughtItems; i++) {
            savedFile << i + 1 << ". " << boughtItems[i] << endl;
        };
    }   
    savedFile << endl << "Total Bill is: " << bill << endl << endl;
    savedFile.close();
}

void clearShoppingHistory() {
    fstream savedFile;
    savedFile.open("ShoppingHistory.txt", ios::out);
    savedFile.close();
    cout << "Shopping history cleared" << endl << endl;
}

void displayShoppingHistory() {
    cout << "Shopping History: " << endl << endl;
    fstream savedFile;
    savedFile.open("ShoppingHistory.txt", ios::in);
    for(string line; getline(savedFile, line );)
        cout << line << endl;
    savedFile.close();
}

void shopAtMall() {

    while(!validateUser()) { }

    cout << endl << "\t\t_**WELCOME TO SHOPPING MALL**_" << endl << endl;

    int choice = 0, choiceShop = 0, choiceItem = 0, bill = 0, totalBoughtItems = 0;
    char confirmation;
    string boughtItems[50];
    bool isShopping = true;

    while (isShopping) {
                
        cout << "Press 1 to buy an item" << endl << "Press 2 for current total bill" << endl << "Press 3 to display the list of current bought items" << endl 
            << "Press 4 to display shopping history" << endl << "Press 5 to clear shopping history" <<  endl << "Press 6 to exit" << endl;

        choice = 0;
        cin >> choice;

        switch(choice) {
            case 1: {                               
                    for (int s = 0; s < MAX_SHOPS; s++) {
                        cout << "\t Press " << s << " for " << shops[s].name << endl;
                    }

                    cin >> choiceShop;
                    if (choiceShop < 0 || choiceShop >= MAX_SHOPS) {
                        cout<< "Invalid shop choice. Try again." << endl << endl;
                        break;
                    }

                    for (int i = 0; i < MAX_ITEMS; i++) {
                        cout << "\t\t Press " << i << " for " << shops[choiceShop].items[i].name << endl;
                    }

                    cin >> choiceItem;
                    if (choiceItem < 0 || choiceItem >= MAX_ITEMS) {
                        cout<< "Invalid item choice. Try again." << endl << endl;
                        break;
                    }

                    cout << "\t\t\t Price of **" << shops[choiceShop].items[choiceItem].name << "** is " << shops[choiceShop].items[choiceItem].price << endl;
                    cout << "\t\t\t If u want to buy this item, press Y. Press any other key to cancel" << endl;
                    cin >> confirmation;
                    if (confirmation == 'y' || confirmation == 'Y') {
                        bill = bill + shops[choiceShop].items[choiceItem].price;
                        boughtItems[totalBoughtItems] = shops[choiceShop].items[choiceItem].name;
                        totalBoughtItems++;                        
                        displayBill(bill);
                    }
                }
                break;
            case 2:
                displayBill(bill);
                break;
            case 3:
                displayBoughtItems(boughtItems, totalBoughtItems);
                break;
            case 4:
                displayShoppingHistory();
                break;
            case 5:
                clearShoppingHistory();
                break;
            case 6:
                isShopping = false;
                break;
            default:
                if (cin.fail()) {
                    cout << "ERROR: cin failure. You did not enter an integer. Exiting code." << endl;
                    exit(-1);
                }
                cout << "Invalid choice. Try again." << endl << endl;
        }
    } 
    if (totalBoughtItems > 0) saveShoppingHistory(boughtItems, totalBoughtItems, bill);
    cout << endl << "Thank you for shopping." << endl << endl;
}

int main() {
    shopAtMall();
    return 0;
}