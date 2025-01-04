# Food-Ordering-System-
### **User Flow and Structure of the Food Delivery System**

The food delivery system provides users with an interactive way to place orders, view their past orders, and checkout. Below is a detailed breakdown of the user flow, the underlying structure, and how each component works.

---

### **System Overview**

The system consists of:

1. **Food Menu**: Where items (such as Pizza, Burger, Pasta, etc.) are displayed with their prices.
2. **Orders**: Users can place orders by selecting food items and specifying quantities. Each order is linked to a user and consists of food items, quantities, and the total price.
3. **Checkout**: When an order is ready, the user can check out by reviewing the itemized bill, which includes the total cost of all items ordered.
4. **User-Specific Flow**: Users can place multiple orders, view previous orders, and get bills.

---

### **Data Structures**

1. **FoodItem Structure**:
    - Represents each food item in the menu.
    - Contains:
      - `id`: A unique identifier for the food item.
      - `name`: The name of the food item (e.g., Pizza).
      - `price`: The price of the food item.

    Example:
    ```c
    typedef struct {
        int id; // Unique ID for food item
        char name[50]; // Name of food item
        double price; // Price of food item
    } FoodItem;
    ```

2. **Order Structure**:
    - Represents an order placed by a user.
    - Contains:
      - `orderId`: A unique identifier for the order.
      - `username`: The username of the user who placed the order.
      - `foodIds[]`: An array of food item IDs selected for the order.
      - `quantities[]`: An array of quantities corresponding to each selected food item.
      - `itemCount`: The number of items in the order.
      - `totalPrice`: The total price for the order.
      - `sitting`: Whether the order is for **Dine-In** or **Delivery**.

    Example:
    ```c
    typedef struct {
        int orderId; // Unique order ID
        char username[50]; // Username of user who placed the order
        int foodIds[MAX_ITEMS]; // Array to store food item IDs
        int quantities[MAX_ITEMS]; // Array to store quantities for each food item
        int itemCount; // Number of items in the order
        double totalPrice; // Total price of the order
        char sitting[10]; // Sitting type (Dine-In / Delivery)
    } Order;
    ```

3. **Global Variables**:
    - Arrays to store food items and orders:
      - `menu[MAX_ITEMS]`: Holds the food items.
      - `orders[MAX_ORDERS]`: Holds all the placed orders.
    - Counters to track the current number of items and orders:
      - `menuCount`: Keeps track of how many food items are in the menu.
      - `orderCount`: Tracks how many orders have been placed.

---

### **Program Workflow**

The program works in a loop, presenting the user with different options, allowing them to interact with the system. Here’s how it works:

1. **Main Menu (User Choice)**:
   - The program displays a menu with several options, and the user chooses what they want to do:
     - **View Menu**: Displays all available food items and their prices.
     - **Place Order**: Allows the user to place an order by selecting food items and specifying quantities.
     - **View Orders**: Lets the user view their previous orders.
     - **Checkout**: The user can view the itemized bill for a particular order.
     - **Exit**: Ends the program.

---

### **User Flow in Detail**

#### 1. **View Menu**:
   - When the user chooses **"View Menu"**, the program displays all food items available for order, along with their prices. 
   - The system simply loops through the `menu` array and prints out the `id`, `name`, and `price` of each item.

   Example:
   ```
   Menu:
   1. Pizza - $12.99
   2. Burger - $7.49
   3. Pasta - $8.99
   4. Salad - $5.49
   5. Soda - $2.99
   ```

#### 2. **Place Order**:
   - When the user chooses **"Place Order"**, the system asks for the **username** and **sitting type** (whether they are dining in or opting for delivery).
   - The user is then presented with the menu to select food items by their **food ID** and specify **quantity**.
   - The system continues to allow the user to add food items until they choose to finish by entering `0` as the food ID.
   - After the user finishes, the system calculates the total price of the order and stores the order in the `orders` array.
   
   Example order process:
   ```
   Enter sitting type (Dine-In / Delivery): Dine-In
   Menu:
   1. Pizza - $12.99
   2. Burger - $7.49
   3. Pasta - $8.99
   4. Salad - $5.49
   5. Soda - $2.99
   Enter food ID to order (0 to finish): 1
   Enter quantity: 2
   Enter food ID to order (0 to finish): 3
   Enter quantity: 1
   Enter food ID to order (0 to finish): 0
   Order placed successfully! Total price: $34.97
   ```

#### 3. **View Orders**:
   - When the user selects **"View Orders"**, the program retrieves and displays all orders placed by the user based on their username.
   - Each order displays the food items ordered, their quantities, and the total price.
   
   Example output:
   ```
   Your Orders:
   Order ID: 1
   Sitting Type: Dine-In
   Items:
     - Pizza (x2)
     - Pasta (x1)
   Total Price: $34.97
   ```

#### 4. **Checkout**:
   - The user is asked to enter an **order ID** to checkout.
   - Once the order is identified, the system prints the detailed bill for that order, including each item with its quantity and price, as well as the total price.
   
   Example checkout:
   ```
   --- Bill ---
   Order ID: 1
   Sitting Type: Dine-In
   Items:
     - Pizza (x2) - $12.99
     - Pasta (x1) - $8.99
   Total Price: $34.97
   ```

---

### **How it Works**

1. **Menu Management**:
   - Admin can add food items to the menu by providing the food name and price. This information is stored in the `menu` array.
   - The menu can be accessed by all users who can view it before placing an order.

2. **Order Placement**:
   - Users select food items by ID and specify how many they want to order. The program calculates the total price by multiplying the price of each selected food item by the quantity ordered.
   - The order is stored with a unique order ID, user information, selected food items, quantities, and total price.

3. **User Interaction**:
   - The user flow involves a series of menus where the user selects from different actions such as viewing the menu, placing an order, or viewing past orders.
   - After placing an order, the user can check out to see an itemized bill and the total amount to pay.

4. **Checkout and Bill Generation**:
   - The system generates a bill for the selected order ID, including all ordered items, quantities, and the total price.
   - If the user selected **Dine-In**, no additional delivery charge is applied. If **Delivery** is chosen, additional charges could be added (this can be enhanced in future versions).

---

### **Conclusion**

This program provides an efficient way to place food orders, view menus, and generate bills. The structure is simple and user-friendly, with the ability to handle multiple orders and keep track of the total cost. The use of clear user prompts ensures smooth interaction, and the system's design allows easy extension for future functionalities (like adding delivery charges, user login, or adding new food items).
