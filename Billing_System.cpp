#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

class Product {
public:
    string name;
    double price;
    int quantity;

    // Default constructor
    Product() {
        name = "";      // Initialize name as an empty string
        price = 0.0;    // Initialize price as 0.0
        quantity = 0;    // Initialize quantity as 0
    }

    // Parameterized constructor
    Product(string pName, double pPrice, int pQuantity) {
        name = pName;         
        price = pPrice;        
        quantity = pQuantity; 
    }
};

class CartItem {
public:
    Product product;
    int quantity;

    // Constructor
    CartItem(Product p, int qty) {
        product = p;    
        quantity = qty;  
    }
};

class Supermarket {
private:
    vector<Product> inventory;
    vector<CartItem> cart;

public:
    Supermarket();  // Constructor to initialize inventory
    void addItem();
    void viewInventory();
    void addToCart();
    void viewCart();
    void generateBill();
    void adminLogin();
    void customerInterface();
};

Supermarket::Supermarket() {
    inventory.push_back(Product("Chocolates", 2.50, 100));
    inventory.push_back(Product("Cheese", 3.00, 50));
    inventory.push_back(Product("Soft Drinks", 1.50, 200));
    inventory.push_back(Product("Chips", 1.25, 150));
}



void Supermarket::viewInventory() {
    if (inventory.empty()) {
        cout << "\nNo products available in the inventory." << endl;
        return;
    }

    cout << "\n--- Inventory ---" << endl;
    for (const auto &product : inventory) {
        cout << "Name: " << product.name
                  << ", Price: " << fixed << setprecision(2) << product.price
                  << ", Quantity: " << product.quantity << endl;
    }
}

void Supermarket::addItem() {
    string name;
    double price;
    int qty;

    cout << "Enter Product Name: ";
    cin.ignore();  // Clear leftover newline character before getline
    getline(cin, name);

    cout << "Enter Product Price: ";
    cin >> price;

    cout << "Enter Product Quantity: ";
    cin >> qty;

    inventory.push_back(Product(name, price, qty));
    cout << "Product added successfully!" << endl;
}

void Supermarket::addToCart() {
    string name;
    int qty;

    cout << "Enter Product Name to Add to Cart: ";
    cin.ignore();  // Clear leftover newline character before getline
    getline(cin, name);

    for (auto &product : inventory) {
        if (product.name == name) {
            cout << "Enter Quantity: ";
            cin >> qty;

            if (qty > product.quantity) {
                cout << "Insufficient stock!" << endl;
                return;
            }

            cart.push_back(CartItem(product, qty)); // Add to cart
            product.quantity -= qty; // Decrease the inventory quantity
            cout << "Item added to cart!" << endl;
            return;
        }
    }
    cout << "Product not found!" << endl;
}

void Supermarket::viewCart() {
    double subtotal = 0;
    cout << "\n--- Cart ---" << endl;
    for (const auto &cartItem : cart) {
        double itemTotal = cartItem.product.price * cartItem.quantity;
        cout << "Name: " << cartItem.product.name
                  << ", Price: " << fixed << setprecision(2) << cartItem.product.price
                  << ", Quantity: " << cartItem.quantity
                  << ", Total: " << itemTotal << endl;
        subtotal += itemTotal;
    }
    cout << "Subtotal: " << subtotal << endl;
}

void Supermarket::generateBill() {
    double total = 0;
    cout << "\n--- Generating Bill ---" << endl;
    for (const auto &cartItem : cart) {
        total += cartItem.product.price * cartItem.quantity;
        cout << "Name: " << cartItem.product.name
                  << ", Total: " << cartItem.product.price * cartItem.quantity << endl;
    }
    cout << "Total Amount: " << total << endl;
    cout << "Thank you for shopping!" << endl;
}

void Supermarket::adminLogin() {
    string username, password;
    cout << "Enter Admin Username: ";
    cin >> username;
    cout << "Enter Admin Password: ";
    cin >> password;

    // Dummy login check
    if (username == "admin" && password == "password") {
        cout << "Login successful!" << endl;
        int choice;
        do {
            cout << "\n1. Add Item\n2. View Inventory\n3. Logout\n";
            cout << "Enter your choice: ";
            cin >> choice;
            switch (choice) {
                case 1: addItem(); break;
                case 2: viewInventory(); break;
                case 3: cout << "Logged out successfully!" << endl; break;
                default: cout << "Invalid choice!" << endl; break;
            }
        } while (choice != 3);
    } else {
        cout << "Invalid credentials!" << endl;
    }
}

void Supermarket::customerInterface() {
    int choice;
    do {
        cout << "\n1. View Inventory\n2. Add to Cart\n3. View Cart\n4. Generate Bill\n5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: viewInventory(); break;
            case 2: addToCart(); break;
            case 3: viewCart(); break;
            case 4: generateBill(); break;
            case 5: cout << "Thank you for visiting!" << endl; break;
            default: cout << "Invalid choice!" << endl; break;
        }
    } while (choice != 5);
}

int main() {
    Supermarket supermarket;
    int role;

    cout << "Welcome to the Supermarket Billing System" << endl;
    cout << "Choose your role: \n1. Admin \n2. Customer\n";
    cout << "Enter your choice: ";
    cin >> role;

    if (role == 1) {
        supermarket.adminLogin();
    } else if (role == 2) {
        supermarket.customerInterface();
    } else {
        cout << "Invalid role!" << endl;
    }

    return 0;
}


