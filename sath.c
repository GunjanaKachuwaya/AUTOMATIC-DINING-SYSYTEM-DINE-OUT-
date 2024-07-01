#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Structure to hold individual item details
typedef struct {
    char foodItem1[50];
    int quantity;
    float totalcost;
} OrderItem;

// Structure to hold order details
typedef struct {
    OrderItem items[10];
	OrderItem foodItem1[50];  // Array to hold up to 10 items
    int itemCount;
    char foodItem[50];
    char paymentMethod[20];
    char deliveryAddress[100];
    char deliverypno[11];
    char status[20];
    char feedback1[5];
    char feedback2[100];
    float totalcost;
    OrderItem quantity;
} Order;

// Array to hold the food menu
struct MenuItem {
    char name[50];
    int price;
};

// Function prototypes
void displayMenu(struct MenuItem menu[], int size);
void placeOrder(Order *order, struct MenuItem menu[], int size);
void updateOrder(Order *order, struct MenuItem menu[], int size);
void choosePaymentMethod(Order *order);
void processCardPayment(Order *order);
void enterDeliveryDetails(Order *order);
void reviewOrder(Order *order);
void provideFeedback(Order *order);
void generateBill(Order *order);

int main() {
    int restaurant;

    while (1) {
        printf("Welcome. Please select your restaurant:\n");
        printf("1. Khaana Khazana\n");
        printf("2. Hungry Monkey\n");
        printf("3. Sugar Highs\n");
        printf("4. Flavours of the Globe\n");
        printf("5. Exit\n");
        printf("Enter the number of your choice: ");
        if (scanf("%d", &restaurant) != 1) {
            fprintf(stderr, "Invalid input. Exiting.\n");
            return 1;
        }

        struct MenuItem menu[8];
        int size = 0;

        switch (restaurant) {
            case 1: {
                struct MenuItem khanaKhazanaMenu[] = {
                    {"Veg Fried Rice", 150},
                    {"Chicken Dum Biriyani", 250},
                    {"Butter Naan", 50},
                    {"Butter Roti", 20},
                    {"Paneer Butter Masala", 200},
                    {"Dal Tadka", 150},
                    {"Mutton Curry", 300},
                    {"Mirchi ka Salan", 180}
                };
                size = sizeof(khanaKhazanaMenu) / sizeof(khanaKhazanaMenu[0]);
                memcpy(menu, khanaKhazanaMenu, sizeof(khanaKhazanaMenu));
                printf("Khaana Khazana Menu:\n");
                break;
            }
            case 2: {
                struct MenuItem hungryMonkeyMenu[] = {
                    {"Veg Burger", 100},
                    {"Chicken Burger", 150},
                    {"Garden Pizza", 200},
                    {"Chicken Spl Pizza", 250},
                    {"French Fries", 80},
                    {"Garlic Bread Sticks", 120},
                    {"Grilled Cheese Sandwich", 130}
                };
                size = sizeof(hungryMonkeyMenu) / sizeof(hungryMonkeyMenu[0]);
                memcpy(menu, hungryMonkeyMenu, sizeof(hungryMonkeyMenu));
                printf("Hungry Monkey Menu:\n");
                break;
            }
            case 3: {
                struct MenuItem sugarHighsMenu[] = {
                    {"Belgian Chocolate Ice Cream", 180},
                    {"Pistachio Ice Cream", 160},
                    {"Vanilla Ice Cream", 140},
                    {"Gulab Jamun", 100},
                    {"Rasmalai", 120},
                    {"Choco Lava Cake", 200}
                };
                size = sizeof(sugarHighsMenu) / sizeof(sugarHighsMenu[0]);
                memcpy(menu, sugarHighsMenu, sizeof(sugarHighsMenu));
                printf("Sugar Highs Menu:\n");
                break;
            }
            case 4: {
                struct MenuItem flavoursOfTheGlobeMenu[] = {
                    {"Kung Pao Chicken (Chinese)", 250},
                    {"Chow Mein Noodles (Chinese)", 180},
                    {"Mixed Fried Rice (Chinese)", 200},
                    {"Tomato Chilli Pasta (Italian)", 220},
                    {"Onion & Cream Pasta (Italian)", 210},
                    {"Garden Lasagna (Italian)", 240},
                    {"Veg Taco (Mexican)", 150},
                    {"Veg Burrito (Mexican)", 170}
                };
                size = sizeof(flavoursOfTheGlobeMenu) / sizeof(flavoursOfTheGlobeMenu[0]);
                memcpy(menu, flavoursOfTheGlobeMenu, sizeof(flavoursOfTheGlobeMenu));
                printf("Flavours of the Globe Menu:\n");
                break;
            }
            case 5:
                exit(0);
            default:
                printf("Invalid selection. Please try again.\n");
                continue;
        }

        Order order = {0}; // Initializing order structure with default values

        int choice;
        do {
            printf("\n1. Display Menu\n");
            printf("2. Place Order\n");
            printf("3. Update Order\n");
            printf("4. Choose Payment Method\n");
            printf("5. Enter Delivery Details\n");
            printf("6. Review Order\n");
            printf("7. Bill\n");
            printf("8. Provide Feedback\n");
            printf("0. Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    displayMenu(menu, size);
                    break;
                case 2:
                    placeOrder(&order, menu, size);
                    break;
                case 3:
                    updateOrder(&order, menu, size);
                    break;
                case 4:
                    choosePaymentMethod(&order);
                    break;
                case 5:
                    enterDeliveryDetails(&order);
                    break;
                case 6:
                    reviewOrder(&order);
                    break;
                case 7:
                	generateBill(&order);
                    exit(0);
                    case 8:
                    	provideFeedback(&order);
                    	break;
                case 0:
                    printf("Exiting system.\n");
                    break;
                default:
                    printf("Invalid choice. Please try again.\n");
            }
        } while (choice != 0);

        return 0;
    }
}

void displayMenu(struct MenuItem menu[], int size) {
	int i;
    printf("---------------------------------------------------------\n");
    printf("| %-3s | %-30s | %-20s |\n", "No", "Dish", "Price (INR)");
    printf("---------------------------------------------------------\n");
    for ( i = 0; i < size; i++) {
        printf("| %-3d | %-30s | %-20d |\n", i + 1, menu[i].name, menu[i].price);
    }
    printf("---------------------------------------------------------\n");
}

void placeOrder(Order *order, struct MenuItem menu[], int size) {
    if (order->itemCount >= 10) {
        printf("Cannot place more than 10 items in a single order.\n");
        return;
    }

    int choice;
    displayMenu(menu, size);
    printf("Enter the number of the food item you want to order: ");
    scanf("%d", &choice);

    if (choice > 0 && choice <= size) {
        OrderItem *item = &order->items[order->itemCount];
        strcpy(item->foodItem1, menu[choice - 1].name);
        printf("Enter quantity: ");
        scanf("%d", &item->quantity);
        item->totalcost = menu[choice - 1].price * item->quantity;
        order->totalcost += item->totalcost;
        order->itemCount++;
        strcpy(order->status, "Order Placed");
        printf("Order has been placed successfully.\n");
    } else {
        printf("Invalid choice. Order not placed.\n");
    }
}
void updateOrder(Order *order, struct MenuItem menu[], int size) {
	int i;
    if (order->itemCount == 0) {
        printf("No items to update.\n");
        return;
    }
    
    int choice, action, newQuantity;
    printf("\nCurrent Order Items:\n");
    for ( i = 0; i < order->itemCount; i++) {
        printf("%d. %s - %d x INR %.2f = INR %.2f\n", i + 1, order->items[i].foodItem1, order->items[i].quantity, order->items[i].totalcost / order->items[i].quantity, order->items[i].totalcost);
    }
    
    printf("Enter the number of the item you want to update: ");
    scanf("%d", &choice);

    if (choice > 0 && choice <= order->itemCount) {
        printf("Choose action:\n");
        printf("1. Cancel item\n");
        printf("2. Increase quantity\n");
        printf("3. Decrease quantity\n");
        printf("Enter your choice: ");
        scanf("%d", &action);

        switch (action) {
            case 1:
                // Cancel item
                order->totalcost -= order->items[choice - 1].totalcost;
                for ( i = choice - 1; i < order->itemCount - 1; i++) {
                    order->items[i] = order->items[i + 1];
                }
                order->itemCount--;
                printf("Item has been cancelled successfully.\n");
                if (order->itemCount == 0) {
                    strcpy(order->status, "No Order");
                }
                break;
            case 2:
                // Increase quantity
                printf("Enter the new quantity: ");
                scanf("%d", &newQuantity);
                if (newQuantity > order->items[choice - 1].quantity) {
                    order->totalcost -= order->items[choice - 1].totalcost;
                    order->items[choice - 1].quantity = newQuantity;
                    order->items[choice - 1].totalcost = newQuantity * (order->items[choice - 1].totalcost / order->items[choice - 1].quantity);
                    order->totalcost += order->items[choice - 1].totalcost;
                    printf("Quantity has been updated successfully.\n");
                } else {
                    printf("New quantity should be greater than the current quantity.\n");
                }
                break;
            case 3:
                // Decrease quantity
                printf("Enter the new quantity: ");
                scanf("%d", &newQuantity);
                if (newQuantity > 0 && newQuantity < order->items[choice - 1].quantity) {
                    order->totalcost -= order->items[choice - 1].totalcost;
                    order->items[choice - 1].quantity = newQuantity;
                    order->items[choice - 1].totalcost = newQuantity * (order->items[choice - 1].totalcost / order->items[choice - 1].quantity);
                    order->totalcost += order->items[choice - 1].totalcost;
                    printf("Quantity has been updated successfully.\n");
                } else {
                    printf("New quantity should be less than the current quantity and greater than zero.\n");
                }
                break;
            default:
                printf("Invalid action.\n");
        }
    } else {
        printf("Invalid choice. Item not updated.\n");
    }
}


void generateBill(Order *order) {
	int i;
	printf("\nBILL\n");
    printf("---------------------------------------------------------\n");
    printf("| %-3s | %-30s | %-8s | %-10s |\n", "No", "Dish", "Qty", "Total Cost");
    printf("---------------------------------------------------------\n");
    
    for ( i = 0; i < order->itemCount; i++) {
        printf("| %-3d | %-30s | %-8d | %-10.2f |\n", i + 1, order->items[i].foodItem1, order->items[i].quantity, order->items[i].totalcost);
    }
    
    printf("---------------------------------------------------------\n");
    printf("| %-43s | %-10.2f |\n", "Total Cost", order->totalcost);
    printf("---------------------------------------------------------\n");
    printf("\nDelivery Address: %s\n", order->deliveryAddress);
    printf("Delivery Phone Number: %s\n", order->deliverypno);
    printf("Payment Method: %s\n", order->paymentMethod);
    printf("Order Status: %s\n", order->status);
    printf("\nThank you for your order!\n");
}

void choosePaymentMethod(Order *order) {
    int method;
    printf("Choose payment method:\n");
    printf("1. Cash on Delivery\n");
    printf("2. Online Payment\n");
    printf("Enter your choice: ");
    scanf("%d", &method);
    if (method == 1) {
        strcpy(order->paymentMethod, "Cash on Delivery");
        printf("Processing cash payment...\n");
        printf("Amount: %.2f\n", order->totalcost);
        printf("Payment due upto delivery.\n");
    } else if (method == 2) {
        strcpy(order->paymentMethod, "Online Payment");
        processCardPayment(order);
    } else {
        printf("Invalid payment method.\n");
    }
}

void processCardPayment(Order *order) {
   char cardNumber[20],expiryDate1[5],expiryDate2[5],cvv[5];
	printf("Enter card number: ");
            scanf("%s", cardNumber);
            printf("Enter expiry date (MM/YY):\nMM:");
            scanf("%s", expiryDate1);
            printf("YY:");
            scanf("%s", expiryDate2);
            printf("Enter CVV: ");
            scanf("%s", cvv);
    printf("Processing card payment...\n");
    printf("Amount: %.2f\n", order->totalcost);
    printf("Card Number: %s\n", cardNumber);
    printf("Expiry Date: %s/%s\n", expiryDate1,expiryDate2);
    printf("CVV: %s\n", cvv);
    printf("Payment successful!\n");
}

void enterDeliveryDetails(Order *order) {
    printf("Enter delivery address: ");
    scanf("%s",order->deliveryAddress);
    printf("\nEnter mobile number: ");
    scanf("%s",order->deliverypno);
    printf("Delivery details have been set.\n");
}
void reviewOrder(Order *order) {
	int i;
    if (strcmp(order->status, "No Order") == 0) {
        printf("No order placed.\n");
        return;
    }

    printf("---------------------------------------------------------\n");
    printf("| %-3s | %-30s | %-5s | %-10s |\n", "No", "Dish", "Qty", "Total Cost");
    printf("---------------------------------------------------------\n");
    for ( i = 0; i < order->itemCount; i++) {
        printf("| %-3d | %-30s | %-5d | %-10.2f |\n", i + 1, order->items[i].foodItem1, order->items[i].quantity, order->items[i].totalcost);
    }
    printf("---------------------------------------------------------\n");
    printf("| %-40s | %-10.2f |\n", "Total Cost", order->totalcost);
    printf("---------------------------------------------------------\n");
    printf("Payment Method: %s\n", order->paymentMethod);
    printf("Delivery Address: %s\n", order->deliveryAddress);
    printf("Delivery Phone Number: %s\n", order->deliverypno);
    printf("Order Status: %s\n", order->status);
    printf("Rating for order experience : %s\n", order->feedback1);
    printf("Feedback for the food: %s\n", order->feedback2);
}
void provideFeedback(Order *order) {
    if (strcmp(order->status, "Order Placed") == 0 || strcmp(order->status, "Order Delivered") == 0) {
       printf("Enter your ratings for the order experience:  (1-5) ");
       scanf("%s",order->feedback1);
       printf("Enter your feedback for the food: ");
       scanf("%s",order->feedback2);
        }
        printf("Thank you for your feedback!\n");
}
