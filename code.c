// Modern restaurents use order systems to manage dine-in, take away and kitchen order queues to reduce wait times.
//Problem description : 
    // Develop a restaurent order manager that : 
        // stores menu items and active orders using structures.
        // accept orders (table no . / items / quantity) assigns order ID's and places them into a kitchen queue 
        //  implemented using arrays and pointers.
        // Supports order status updates (prepared,ready, served) and cancellation.
        // Computes bills including taxes and service charges, also prints itemized invoices.
        // Provides reports : busisest hrs, most ordered items, daily revenue, Use loops, searches and sorting for frequency analysis.
        // Syllabus topic applied : problem solving, control structures, arrays, strings, functions, pointers, dynamic memory, searching and sorting algorithms.
        

        
        //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Required things for program <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
        // 1.Welcome note
        // 2.Show menu to the customers : available and unavailable items in the menu
        // 3.showing the most ordered items and daily revenue
        // 4.Selecting the order by the customers ; assigns the order ID 
        // 5.Putting that order in the kitchen queue
        // 6.Giving the order status to the customer
        // 7.Last minute cancellation
        // 8.Billing part along with GST discount, invoice, taxes, service charges

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>


#define MAX_MENU_ITEMS 100
#define MAX_ORDERS 50
#define MAX_ORDER_ITEMS 20
#define MAX_NAME_LENGTH 20
#define TAX_RATE 0.008
#define SERVICE_RATE 0.10

////////////////////////////////////////              STRUCTURES            /////////////////////////////////////////////////////////////////////////////////

typedef struct
{
    int id;
    char name[MAX_NAME_LENGTH];
    float price;
    char category[MAX_NAME_LENGTH];
    int preparation_time;      // In minutes
}Menu_item;/////////////////////////////////////          Menu_item

typedef struct
{
    int menu_item_id;
    float quantity;
    float sub_total;
}Order_item;   /////////////////////////////////        Order_item

typedef struct
{
    int order_id;
    int table_no;
    time_t order_time;
    Order_item items[MAX_ORDER_ITEMS];      ///////////// Creating an object of the structure. (items)
    int item_count;
    char status[20];    //preparing, pending, ready, served, cancelled.
    float total_amount;
    float tax;
    float service_charge;
    float final_amount;
}Order;     //////////////////////////////////         Order

typedef struct
{
    Menu_item menu_items[MAX_MENU_ITEMS];
    int menu_count;
    Order orders[MAX_ORDER_ITEMS];
    int order_count;
    int next_order_id;


    //Kitchen queue pointers
    Order* kitchen_queue[MAX_ORDERS];
    int kitchen_front;
    int kitchen_rear;


    //Statistics
    float daily_revenue;
    int order_frequency;        //Orders per hour

}Restaurant;    ///////////////////////////////       Restaurant

/////////////////////////////////////////////////////////     Function prototypes       //////////////////////////////////////////////////////////////////

void intialize_restaurant(Restaurant* rest);
void add_menu_item(Restaurant* rest, int id, char* name, float price, char* category, int prep_time);
void display_menu(Restaurant* rest);
void place_order(Restaurant* rest, int table_no, char* order_type);
void add_item_to_order(Restaurant* rest,int order_id, int menu_item_id, int quantity);
void update_order_status(Restaurant* rest, int order_id, char* new_status);
void cancel_order(Restaurant* rest, int order_id);
void calculate_bill(Restaurant* rest,int order_id);
void print_invoice(Restaurant* rest, int order_id);
void process_kitchen_queue(Restaurant* rest);
void generate_report(Restaurant* rest);
void bubble_sort_orders_by_items(Order arr[], int n);
int binary_search_order(Restaurant* rest, int order_id);

/////////////////////////////////////////////////////////     Queue operations       //////////////////////////////////////////////////////////////////////

void enqueue_kitchen(Restaurant* rest, Order* order);
Order* dequeueKitchen(Restaurant* rest);
int is_kitchen_queue_empty(Restaurant* rest);
int is_kitchen_queue_full(Restaurant* rest);

/////////////////////////////////////////////////////////     Utility functions      //////////////////////////////////////////////////////////////////////

int find_menu_item_by_id(Restaurant* rest, int id);
int find_order_by_id(Restaurant* rest, int id);
void get_current_time_string(char* buffer);
