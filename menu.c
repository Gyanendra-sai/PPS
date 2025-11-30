#include "menu.h"

void add_menu_item(Restaurant* rest, int id, char* name, float price,
                   char* category, int prep_time) {
    if (rest->menu_count >= MAX_MENU_ITEMS) {
        printf("Menu is full! Cannot add more items.\n");
        return;
    }

    menu_item* item = &rest->menu_items[rest->menu_count++];
    item->id = id;
    strcpy(item->name, name);
    strcpy(item->category, category);
    item->price = price;
    item->preparation_time = prep_time;
}

void display_menu(Restaurant* rest) {
    printf("\n=== RESTAURANT MENU ===\n");
    printf("%-4s %-20s %-15s %-10s %s\n",
           "ID", "Name", "Category", "Price", "Prep Time");
    printf("---------------------------------------------------------------\n");

    for (int i = 0; i < rest->menu_count; i++) {
        menu_item* m = &rest->menu_items[i];
        printf("%-4d %-20s %-15s $%-9.2f %d mins\n",
               m->id, m->name, m->category, m->price, m->preparation_time);
    }
}

int find_menu_item_by_id(Restaurant* rest, int id) {
    for (int i = 0; i < rest->menu_count; i++) {
        if (rest->menu_items[i].id == id) {
            return i;
        }
    }
    return -1;
}