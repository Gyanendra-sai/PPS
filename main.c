#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "menu.h"
#include "orders.h"
#include "kitchen.h"
#include "reports.h"

void initialize_restaurant(Restaurant *r);

int main(void) {
    Restaurant r;
    initialize_restaurant(&r);

    int choice, table, mid, qty, oid;
    char otype[20];

    // Sample menu items (you can add more here or from file)
    add_menu_item(&r, 1, "Margherita Pizza", 12.50f, "Main Course", 15);
    add_menu_item(&r, 2, "Cold Coffee",      4.00f,  "Beverage",    2);
    add_menu_item(&r, 3, "Burger",           8.50f,  "Main Course", 10);

    printf("=========== WELCOME TO RESTAURANT ORDER SYSTEM ===========\n");

    while (1) {
        printf("\n------------- MAIN MENU -------------\n");
        printf("1. Display Menu\n");
        printf("2. Place New Order\n");
        printf("3. Add Item to Order\n");
        printf("4. Update Order Status\n");
        printf("5. Print Bill (Invoice)\n");
        printf("6. Process Kitchen Queue\n");
        printf("7. Generate Reports\n");
        printf("8. Exit\n");
        printf("-------------------------------------\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Exiting.\n");
            break;
        }

        switch (choice) {
            case 1:
                display_menu(&r);
                break;

            case 2:
                printf("Enter Table Number: ");
                scanf("%d", &table);
                printf("Order Type (dine-in/takeaway): ");
                scanf("%19s", otype);
                oid = place_order(&r, table, otype);
                if (oid != -1)
                    printf("Order placed successfully! Order ID: %d\n", oid);
                else
                    printf("Failed! Order limit reached.\n");
                break;

            case 3:
                printf("Enter Order ID: ");
                scanf("%d", &oid);
                printf("Enter Menu Item ID: ");
                scanf("%d", &mid);
                printf("Enter Quantity: ");
                scanf("%d", &qty);
                add_item_to_order(&r, oid, mid, qty);
                break;

            case 4:
                printf("Enter Order ID: ");
                scanf("%d", &oid);
                printf("New Status (pending/preparing/ready/served/cancelled): ");
                scanf("%19s", otype);
                update_order_status(&r, oid, otype);
                break;

            case 5:
                printf("Enter Order ID: ");
                scanf("%d", &oid);
                calculate_bill(&r, oid);
                print_invoice(&r, oid);
                break;

            case 6:
                process_kitchen_queue(&r);
                break;

            case 7:
                generate_reports(&r);
                break;

            case 8:
                printf("Thanks for using the system! Goodbye!\n");
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}