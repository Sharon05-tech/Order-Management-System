#include <iostream>
#include <string>
#include <unordered_map>
#include <map>
#include <queue>
#include <vector>

using namespace std;

// ------------------ USER ------------------
class User {
public:
    int userId;
    string name;
    bool isPrime;

    // Default constructor (needed for map/unordered_map)
    User() {}

    User(int id, string n, bool prime) {
        userId = id;
        name = n;
        isPrime = prime;
    }
};

// ------------------ PRODUCT ------------------
class Product {
public:
    int productId;
    string name;
    int stock;

    Product() {}

    Product(int id, string n, int s) {
        productId = id;
        name = n;
        stock = s;
    }
};

// ------------------ ORDER ------------------
class Order {
public:
    int orderId;
    int userId;
    int productId;
    int quantity;
    bool isPrime;

    Order() {}

    Order(int oid, int uid, int pid, int q, bool prime) {
        orderId = oid;
        userId = uid;
        productId = pid;
        quantity = q;
        isPrime = prime;
    }
};

// Priority Queue Comparator
class OrderCompare {
public:
    bool operator()(Order &a, Order &b) {
        return a.isPrime < b.isPrime;  // Prime orders first
    }
};

// ------------------ ORDER MANAGER ------------------
class OrderManager {
private:
    unordered_map<int, User> users;
    map<int, Product> products;
    priority_queue<Order, vector<Order>, OrderCompare> orderQueue;
    unordered_map<int, Order> orderHistory;

public:
    void addUser(int id, string name, bool isPrime) {
        users.emplace(id, User(id, name, isPrime));
    }

    void addProduct(int id, string name, int stock) {
        products.emplace(id, Product(id, name, stock));
    }

    void placeOrder(int orderId, int userId, int productId, int quantity) {
        if (users.find(userId) == users.end()) {
            cout << "User not found\n";
            return;
        }

        if (products.find(productId) == products.end()) {
            cout << "Product not found\n";
            return;
        }

        if (products[productId].stock < quantity) {
            cout << "Insufficient stock\n";
            return;
        }

        products[productId].stock -= quantity;

        Order order(orderId, userId, productId, quantity, users[userId].isPrime);
        orderQueue.push(order);
        orderHistory[orderId] = order;

        cout << "Order placed successfully\n";
    }

    void processOrder() {
        if (orderQueue.empty()) {
            cout << "No orders to process\n";
            return;
        }

        Order order = orderQueue.top();
        orderQueue.pop();

        cout << "Processing Order ID: " << order.orderId << endl;
    }

    void searchOrder(int orderId) {
        if (orderHistory.find(orderId) != orderHistory.end()) {
            cout << "Order found: " << orderId << endl;
        } else {
            cout << "Order not found\n";
        }
    }
};

// ------------------ MAIN ------------------
int main() {
    OrderManager manager;

    // Adding users
    manager.addUser(1, "Sharon", true);
    manager.addUser(2, "Alex", false);

    // Adding products
    manager.addProduct(101, "Laptop", 10);
    manager.addProduct(102, "Phone", 20);

    // Placing orders
    manager.placeOrder(1001, 1, 101, 1); // Prime user
    manager.placeOrder(1002, 2, 102, 2); // Normal user

    // Processing orders (Prime first)
    manager.processOrder();

    // Searching orders
    manager.searchOrder(1001);

    return 0;
}

