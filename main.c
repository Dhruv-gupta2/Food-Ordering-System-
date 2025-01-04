#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 50 // Maximum number of food items allowed in the menu
#define MAX_ORDERS 100 // Maximum number of orders that can be placed

// Structures for Food Item and Order
typedef struct {
    int id; // Unique ID for the food item
    char name[50]; // Name of the food item
    double price; // Price of the food item
} FoodItem;

typedef struct {
    int orderId; // Unique ID for the order
    char username[50]; // Username of the user who placed the order
    int foodIds[MAX_ITEMS]; // Array of food item IDs in the order
    int quantities[MAX_ITEMS]; // Array of quantities corresponding to food items
    int itemCount; // Number of items in the order
    double totalPrice; // Total price of the order
    char sitting[10]; // Sitting type (Dine-In / Delivery)
} Order;

// Global Data
FoodItem menu[MAX_ITEMS]; // Array to store menu items
int menuCount = 0; // Current number of menu items

Order orders[MAX_ORDERS]; // Array to store orders
int orderCount = 0; // Current number of orders

// Utility Functions
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pause() {
    printf("\nPress Enter to continue...");
    getchar();
    getchar();  // To consume the newline character left by previous input
}

// Menu Management Functions
void addFoodItem() {
    if (menuCount >= MAX_ITEMS) {
        printf("Menu is full!\n");
        return;
    }

    FoodItem newItem;
    newItem.id = menuCount + 1; // Assign a unique ID to the food item
    printf("Enter food name: ");
    getchar();  // To consume the newline character left by previous input
    fgets(newItem.name, sizeof(newItem.name), stdin);
    strtok(newItem.name, "\n"); // Remove trailing newline
    printf("Enter price: ");
    scanf("%lf", &newItem.price);
    
    menu[menuCount++] = newItem; // Add the item to the menu
    printf("Food item added successfully!\n");
}

void viewMenu() {
    if (menuCount == 0) {
        printf("No items available in the menu.\n");
        return;
    }
    printf("\nMenu:\n");
    for (int i = 0; i < menuCount; i++) {
        printf("%d. %s - $%.2f\n", menu[i].id, menu[i].name, menu[i].price);
    }
}

// Order Management Functions
void placeOrder(char username[50]) {
    if (orderCount >= MAX_ORDERS) {
        printf("Order limit reached!\n");
        return;
    }

    Order newOrder;
    newOrder.orderId = orderCount + 1; // Assign a unique ID to the order
    strcpy(newOrder.username, username); // Link the order to the user
    newOrder.itemCount = 0;
    newOrder.totalPrice = 0;

    int foodId, quantity;
    char sitting[10];

    printf("Enter sitting type (Dine-In / Delivery): ");
    scanf("%s", sitting);
    strcpy(newOrder.sitting, sitting); // Store sitting type

    do {
        viewMenu(); // Display the menu to the user
        printf("Enter food ID to order (0 to finish): ");
        scanf("%d", &foodId);

        if (foodId == 0) break; // Exit the loop if the user enters 0
        
        if (foodId < 1 || foodId > menuCount) { // Validate the food ID
            printf("Invalid food ID.\n");
            continue;
        }

        printf("Enter quantity: ");
        scanf("%d", &quantity);

        newOrder.foodIds[newOrder.itemCount] = foodId; // Add the food ID to the order
        newOrder.quantities[newOrder.itemCount] = quantity; // Add the quantity to the order
        newOrder.totalPrice += menu[foodId - 1].price * quantity; // Update the total price
        newOrder.itemCount++; // Increment the item count

    } while (1);

    orders[orderCount++] = newOrder; // Add the order to the array
    printf("Order placed successfully! Total price: $%.2f\n", newOrder.totalPrice);
}

void viewOrders(char username[50]) {
    printf("\nYour Orders:\n");
    for (int i = 0; i < orderCount; i++) {
        if (strcmp(orders[i].username, username) == 0) { // Check if the order belongs to the user
            printf("Order ID: %d\n", orders[i].orderId);
            printf("Sitting Type: %s\n", orders[i].sitting);
            printf("Items:\n");
            for (int j = 0; j < orders[i].itemCount; j++) {
                int foodId = orders[i].foodIds[j];
                printf("  - %s (x%d)\n", menu[foodId - 1].name, orders[i].quantities[j]);
            }
            printf("Total Price: $%.2f\n\n", orders[i].totalPrice);
        }
    }
}

void checkout(int orderId) {
    for (int i = 0; i < orderCount; i++) {
        if (orders[i].orderId == orderId) {
            printf("\n--- Bill ---\n");
            printf("Order ID: %d\n", orders[i].orderId);
            printf("Sitting Type: %s\n", orders[i].sitting);
            printf("Items:\n");
            for (int j = 0; j < orders[i].itemCount; j++) {
                int foodId = orders[i].foodIds[j];
                printf("  - %s (x%d) - $%.2f\n", menu[foodId - 1].name, orders[i].quantities[j], menu[foodId - 1].price);
            }
            printf("Total Price: $%.2f\n", orders[i].totalPrice);
            break;
        }
    }
}

// Main Program
int main() {
    // Predefined menu items
    strcpy(menu[menuCount].name, "Pizza");
    menu[menuCount++].price = 12.99;

    strcpy(menu[menuCount].name, "Burger");
    menu[menuCount++].price = 7.49;

    strcpy(menu[menuCount].name, "Pasta");
    menu[menuCount++].price = 8.99;

    strcpy(menu[menuCount].name, "Salad");
    menu[menuCount++].price = 5.49;

    strcpy(menu[menuCount].name, "Soda");
    menu[menuCount++].price = 2.99;

    int choice;
    char username[50];

    while (1) {
        clearScreen();
        printf("Food Delivery System\n");
        printf("1. View Menu\n");
        printf("2. Place Order\n");
        printf("3. View Orders\n");
        printf("4. Checkout\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                viewMenu(); // Call the function to view the menu
                pause();
                break;
            case 2:
                printf("Enter your username: ");
                scanf("%s", username);
                placeOrder(username); // Call the function to place an order
                pause();
                break;
            case 3:
                printf("Enter your username: ");
                scanf("%s", username);
                viewOrders(username); // Call the function to view orders
                pause();
                break;
            case 4:
                printf("Enter order ID to checkout: ");
                int orderId;
                scanf("%d", &orderId);
                checkout(orderId); // Generate the bill for the order
                pause();
                break;
            case 5:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice!\n");
                pause();
        }
    }
}
