#include "orders.h"
#include "menu.h"    // for find_menu_item_by_id
#include "kitchen.h" // for enqueue_kitchen

void initialize_restaurant(Restaurant* rest) {
    rest->menu_count   = 0;
    rest->order_count  = 0;
    rest->next_order_id = 1001;

    rest->kitchen_front = 0;
    rest->kitchen_rear  = -1;

    rest->daily_revenue = 0.0f;

    for (int i = 0; i < 24; i++) {
        rest->order_frequency[i] = 0;
    }
}

int find_order_by_id(Restaurant* rest, int order_id) {
    for (int i = 0; i < rest->order_count; i++) {
        if (rest->orders[i].order_id == order_id) {
            return i;
        }
    }
    return -1;
}

int place_order(Restaurant* rest, int table_num, char* order_type) {
    if (rest->order_count >= MAX_ORDERS) {
        printf("Cannot accept more orders! Kitchen is at full capacity.\n");
        return -1;
    }

    order* new_order = &rest->orders[rest->order_count++];
    new_order->order_id     = rest->next_order_id++;
    new_order->table_number = table_num;
    strcpy(new_order->order_type, order_type);
    new_order->order_time   = time(NULL);
    new_order->item_count   = 0;
    strcpy(new_order->status, "pending");
    new_order->total_amount = 0.0f;
    new_order->tax          = 0.0f;
    new_order->service_charge = 0.0f;
    new_order->final_total  = 0.0f;

    // record hour for frequency analysis
    struct tm* timeinfo = localtime(&new_order->order_time);
    if (timeinfo != NULL) {
        int h = timeinfo->tm_hour;
        if (h >= 0 && h < 24) {
            rest->order_frequency[h]++;
        }
    }

    // add to kitchen queue
    enqueue_kitchen(rest, new_order);

    return new_order->order_id;
}

void add_item_to_order(Restaurant* rest, int order_id, int menu_item_id, int quantity) {
    int order_index = find_order_by_id(rest, order_id);
    if (order_index == -1) {
        printf("Order not found!\n");
        return;
    }

    if (quantity <= 0) {
        printf("Quantity must be positive.\n");
        return;
    }

    order* ord = &rest->orders[order_index];

    if (ord->item_count >= MAX_ORDER_ITEMS) {
        printf("Order is full! Cannot add more items.\n");
        return;
    }

    int menu_index = find_menu_item_by_id(rest, menu_item_id);
    if (menu_index == -1) {
        printf("Menu item not found!\n");
        return;
    }

    menu_item* m = &rest->menu_items[menu_index];

    order_item* it = &ord->items[ord->item_count++];
    it->menu_item_id = menu_item_id;
    it->quantity     = quantity;
    it->subtotal     = m->price * quantity;

    ord->total_amount += it->subtotal;

    printf("Added %d x %s to order %d\n", quantity, m->name, order_id);
}

void update_order_status(Restaurant* rest, int order_id, char* new_status) {
    int idx = find_order_by_id(rest, order_id);
    if (idx == -1) {
        printf("Order not found!\n");
        return;
    }

    order* ord = &rest->orders[idx];
    strcpy(ord->status, new_status);

    printf("Order %d status updated to: %s\n", order_id, new_status);

    // if served, calculate bill and update revenue
    if (strcmp(new_status, "served") == 0) {
        calculate_bill(rest, order_id);
        rest->daily_revenue += ord->final_total;
    }
}

void cancel_order(Restaurant* rest, int order_id) {
    int idx = find_order_by_id(rest, order_id);
    if (idx == -1) {
        printf("Order not found!\n");
        return;
    }

    order* ord = &rest->orders[idx];

    if (strcmp(ord->status, "served") == 0) {
        printf("Cannot cancel served order!\n");
        return;
    }

    strcpy(ord->status, "cancelled");
    printf("Order %d has been cancelled.\n", order_id);
}

void calculate_bill(Restaurant* rest, int order_id) {
    int idx = find_order_by_id(rest, order_id);
    if (idx == -1) {
        printf("Order not found!\n");
        return;
    }

    order* ord = &rest->orders[idx];

    ord->tax            = ord->total_amount * TAX_RATE;
    ord->service_charge = ord->total_amount * SERVICE_CHARGE;
    ord->final_total    = ord->total_amount + ord->tax + ord->service_charge;

    printf("Bill calculated for order %d. Total: $%.2f\n",
           order_id, ord->final_total);
}

void print_invoice(Restaurant* rest, int order_id) {
    int idx = find_order_by_id(rest, order_id);
    if (idx == -1) {
        printf("Order not found!\n");
        return;
    }

    order* ord = &rest->orders[idx];

    printf("\n=== INVOICE ===\n");
    printf("Order ID: %d\n", ord->order_id);
    printf("Table: %d\n", ord->table_number);
    printf("Type: %s\n", ord->order_type);
    printf("Status: %s\n", ord->status);
    printf("Order Time: %s", ctime(&ord->order_time));

    printf("\n%-20s %-8s %-10s %s\n", "Item", "Qty", "Price", "Subtotal");
    printf("--------------------------------------------------------\n");

    for (int i = 0; i < ord->item_count; i++) {
        order_item* it = &ord->items[i];
        int mi = find_menu_item_by_id(rest, it->menu_item_id);
        if (mi != -1) {
            menu_item* m = &rest->menu_items[mi];
            printf("%-20s %-8d $%-9.2f $%-8.2f\n",
                   m->name, it->quantity, m->price, it->subtotal);
        }
    }

    printf("\nSubtotal: $%.2f\n", ord->total_amount);
    printf("Tax (8%%): $%.2f\n", ord->tax);
    printf("Service Charge (10%%): $%.2f\n", ord->service_charge);
    printf("TOTAL: $%.2f\n", ord->final_total);
    printf("====================\n");
}