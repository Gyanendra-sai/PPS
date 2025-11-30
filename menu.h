#pragma once
#ifndef MENU_H
#define MENU_H

#include "restaurant_struct.h"

void add_menu_item(Restaurant* rest, int id, char* name, float price,
                   char* category, int prep_time);
void display_menu(Restaurant* rest);
int  find_menu_item_by_id(Restaurant* rest, int id);

#endif