// Program name: M07ProAssgn.cpp
// Author: Ilyas Khamliche
// Date: 2/26/24
// Purpose: Adding a menu option for adding an invoice function.
#include <iostream>
#include <string>
#include <iomanip>
#include "sqlite3.h"

using namespace std;

void printMainMenu();
void viewInvoice(sqlite3 *);
void viewCustomer(sqlite3 *);
int mainMenu();

int main()
{
    int choice;

    sqlite3 *mydb;

    int rc; 

// Open SaleCo.db database
    rc = sqlite3_open("SaleCo.db", &mydb);

    if (rc) {
        cerr << "Error opening database: " << sqlite3_errmsg(mydb) << endl;
        return 1;
    } else {
        cout << "Opened database successfully" << endl;
    }

    cout << "Welcome to SaleCo" << endl;
    choice = mainMenu();
    while (true)
    {
        switch (choice) 
        {
            case 1: viewInvoice(mydb); break;
            case 2: viewCustomer(mydb); break;
            case -1: return 0;
            default: cout << "That is not a valid choice." << endl;
        }
        cout << "\n\n";
        choice = mainMenu();
    }

// Close connection to the database
    sqlite3_close(mydb);
    return 0;
}

void printMainMenu() 
{
    cout << "Please choose an option (enter -1 to quit):  " << endl;
    cout << "1. View an invoice" << endl;
    cout << "2. View Customer Information" << endl;
    cout << "Enter Choice: ";
}

int mainMenu()
{
    int choice = 0;
    
    printMainMenu();
    cin >> choice;
    while ((!cin || choice < 1 || choice > 3) && choice  != -1)
    {       
        if (!cin)
        {
            cin.clear();
            cin.ignore(1000,'/n');
        }
        cout << "That is not a valid choice." << endl << endl;
        printMainMenu();
        cin >> choice;
    } 
    return choice;
}

void addInvoice(sqlite3 * db)
{
    string cus_code;
    int choice;
    
    // Ask for the customer code
    cout << "Enter the customer code for the invoice: ";
    cin >> cus_code;

    // Display available products
    string productsQuery = "SELECT PROD_CODE, PROD_DESC FROM PRODUCT";
    sqlite3_stmt *productsRes;
    string m_strLastError;
    
    if (sqlite3_prepare_v2(db, productsQuery.c_str(), -1, &productsRes, NULL) != SQLITE_OK)
    {
        m_strLastError = sqlite3_errmsg(db);
        sqlite3_finalize(productsRes);
        cout << "There was an error: " << m_strLastError << endl;
        return;
    }

    cout << "Available Products:" << endl;
    int i = 1;
    while (sqlite3_step(productsRes) == SQLITE_ROW)
    {
        cout << i << ". " << reinterpret_cast<const char*>(sqlite3_column_text(productsRes, 1)) << endl;
        i++;
    }
    sqlite3_finalize(productsRes);

    // Ask for product and quantity for the invoice
    cout << "Enter the number of the product to add to the invoice (-1 to finish): ";
    cin >> choice;
    
    sqlite3_stmt *invoiceRes;
    string invoiceQuery = "INSERT INTO INVOICE (CUS_CODE) VALUES (?)";

    if (sqlite3_prepare_v2(db, invoiceQuery.c_str(), -1, &invoiceRes, NULL) != SQLITE_OK)
    {
        m_strLastError = sqlite3_errmsg(db);
        sqlite3_finalize(invoiceRes);
        cout << "There was an error: " << m_strLastError << endl;
        return;
    }

    sqlite3_bind_text(invoiceRes, 1, cus_code.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_step(invoiceRes);
    sqlite3_finalize(invoiceRes);

    while (choice != -1)
    {
        // Get product code and quantity
        int quantity;
        cout << "Enter the quantity for product " << choice << ": ";
        cin >> quantity;

        string prod_code_query = "SELECT PROD_CODE FROM PRODUCT LIMIT 1 OFFSET " + to_string(choice - 1);
        string prod_code;
        sqlite3_stmt *prodCodeRes;

        if (sqlite3_prepare_v2(db, prod_code_query.c_str(), -1, &prodCodeRes, NULL) != SQLITE_OK)
        {
            m_strLastError = sqlite3_errmsg(db);
            sqlite3_finalize(prodCodeRes);
            cout << "There was an error: " << m_strLastError << endl;
            return;
        }

        if (sqlite3_step(prodCodeRes) == SQLITE_ROW)
        {
            prod_code = reinterpret_cast<const char*>(sqlite3_column_text(prodCodeRes, 0));
            sqlite3_finalize(prodCodeRes);
        }
        else
        {
            cout << "Invalid product choice." << endl;
            sqlite3_finalize(prodCodeRes);
            return;
        }

        // Insert line record into the database
        string lineQuery = "INSERT INTO LINE (INV_NUMBER, PROD_CODE, LINE_UNITS) VALUES ((SELECT MAX(INV_NUMBER) FROM INVOICE), ?, ?)";
        sqlite3_stmt *lineRes;

        if (sqlite3_prepare_v2(db, lineQuery.c_str(), -1, &lineRes, NULL) != SQLITE_OK)
        {
            m_strLastError = sqlite3_errmsg(db);
            sqlite3_finalize(lineRes);
            cout << "There was an error: " << m_strLastError << endl;
            return;
        }

        sqlite3_bind_text(lineRes, 1, prod_code.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(lineRes, 2, quantity);
        sqlite3_step(lineRes);
        sqlite3_finalize(lineRes);

        cout << "Product added to invoice. Enter the next product number (-1 to finish): ";
        cin >> choice;
    }
    
    cout << "Invoice added successfully!" << endl;
}
void viewCustomer(sqlite3 * db)
{
    string query = "SELECT CUS_CODE, CUS_FNAME, CUS_LNAME FROM CUSTOMER";
    sqlite3_stmt *pRes;
    string m_strLastError;
    string cus_code, cus_fname, cus_lname;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &pRes, NULL) != SQLITE_OK)
    {
        m_strLastError = sqlite3_errmsg(db);
        sqlite3_finalize(pRes);
        cout << "There was an error: " << m_strLastError << endl;
        return;
    }
    else
    {
        cout << "Customer Information:" << endl;
        int i = 1;
        while (sqlite3_step(pRes) == SQLITE_ROW)
        {
            cus_code = reinterpret_cast<const char*>(sqlite3_column_text(pRes, 0));
            cus_fname = reinterpret_cast<const char*>(sqlite3_column_text(pRes, 1));
            cus_lname = reinterpret_cast<const char*>(sqlite3_column_text(pRes, 2));
            cout << i << ". " << cus_fname << " " << cus_lname << endl;
            i++;
        }
        sqlite3_finalize(pRes);
        
        int choice;
        cout << "Enter the number of the customer to view details (-1 to go back to main menu): ";
        cin >> choice;
        if (choice == -1) return;

        string customerQuery = "SELECT CUS_FNAME, CUS_LNAME, CUS_PHONE, CUS_BALANCE FROM CUSTOMER WHERE CUS_CODE = ?";
        sqlite3_stmt *customerRes;

        if (sqlite3_prepare_v2(db, customerQuery.c_str(), -1, &customerRes, NULL) != SQLITE_OK)
        {
            m_strLastError = sqlite3_errmsg(db);
            sqlite3_finalize(customerRes);
            cout << "There was an error: " << m_strLastError << endl;
            return;
        }

        sqlite3_bind_text(customerRes, 1, cus_code.c_str(), -1, SQLITE_TRANSIENT);
        if (sqlite3_step(customerRes) == SQLITE_ROW)
        {
            cout << "Customer Name: " << sqlite3_column_text(customerRes, 0) << " " << sqlite3_column_text(customerRes, 1) << endl;
            cout << "Phone Number: " << sqlite3_column_text(customerRes, 2) << endl;
            cout << "Balance: " << sqlite3_column_double(customerRes, 3) << endl;
        }
        else
        {
            cout << "Customer not found!" << endl;
        }
        sqlite3_finalize(customerRes);
    }
}
