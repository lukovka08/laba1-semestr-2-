#include <iostream>
#include <fstream>
#include "items.h"
#include "searcher.h"
#include "stock.h"
#include "ui.h"
#define FILENAME_ITEMTYPES "itemtypes.txt"
using namespace std;
using namespace searcher;

void UI::main_loop() {
    while(1) {
        switch(main_menu()) {
        case 0: return;
        case 1: add();
                break;
        case 2: change();
                break;
        case 3: remove();
                break;
        case 4: show_items();
                break;
        case 5: search();
                break;
        case 6: add_assortment();
                break;
        case 7: load();
                break;
        case 8: save();
                break;
        }
    }
}

//=============================================================================

inline void menu_head(string head) {
    cout << endl << "*** " << head << " ***" << endl << endl;
}

static void printMenu(const Strings& ui_strings) {
    for(unsigned i = 0; i < ui_strings.size(); i++)
        cout << ui_strings[i] << endl;
}
// Функция выбора пункта меню
static int getMenuCount(unsigned size);

UI::UI(string filename): m_filename(filename) {
    m_stock = new Stock();
    load();
}

UI::~UI() {
    save();
    delete m_stock;
}

int UI::main_menu() {
    menu_head("MAIN MENU");
    cout << "Total goods on the stock: " << m_stock->totalItems() << endl;
    Strings strings = {
        "1. Add item",
        "2. Change item",
        "3. Remove item",
        "4. Show items",
        "5. Search items",
        "6. Add assortment",
        "7. Load data from " + m_filename,
        "8. Save data to " + m_filename,
        "0. Exit"
    };
    printMenu(strings);
    return getMenuCount(strings.size());
}

void UI::add() {
    menu_head("NEW ITEM");
    m_stock->add(getNewItem());
    cout << "An item has been added" << endl;
}

void UI::change() {
    menu_head("CHANGE ITEM");
    cout << "Enter the num of the item (from 0 to "
         << m_stock->totalItems() - 1 << ")" << endl;
    unsigned num;
    cin >> num;
    if(m_stock->change(num, getNewItem()))
        cout << "The item has been changed" << endl;
    else
        cout << "Change error" << endl;
}

void UI::remove() {
    menu_head("REMOVE ITEM");
    cout << "Enter the num of the item (from 0 to "
         << m_stock->totalItems() - 1 << ")" << endl;
    unsigned num;
    cin >> num;
    if(m_stock->remove(num))
        cout << "The item has been removed" << endl;
    else
        cout << "Remove error" << endl;
}

void UI::search() {
    menu_head("SEARCH");
    vector<string> strings {
        "1. By type",
        "2. By price",
        "3. By weight",
        "0. Back"
    };
    double left, right;
    Searcher* srch = nullptr;

    printMenu(strings);
    switch(getMenuCount(strings.size())) {
    case 0:
        return;
    case 1:
        srch = new byType(search_by_type());
        break;
    case 2:
        search_by_price(left, right);
        srch = new byPrice(left, right);
        break;
    case 3:
        search_by_weight(left, right);
        srch = new byWeight(left, right);
    }
    show_items(m_stock->search(srch));
    delete srch;
}

unsigned UI::search_by_type() {
    menu_head("SEARCH BY TYPE");
    return static_cast<unsigned>(getMenuCount(show_assortment()));
}

void UI::search_by_price(double& left, double& right) {
    menu_head("SEARCH BY PRICE");
    cout << "Enter the left limit: ";
    cin >> left;
    cout << "Enter the right limit: ";
    cin >> right;
}

void UI::search_by_weight(double& left, double& right) {
    menu_head("SEARCH BY WEIGHT");
    cout << "Enter the left limit: ";
    cin >> left;
    cout << "Enter the right limit: ";
    cin >> right;
}

int getMenuCount(unsigned size) {
    int key = 0;
    // "Защита от дурака"
    do {
        cout << "$: ";
        cin >> key;
    }
    while(key < 0 || static_cast<unsigned>(key) >= size);

    return key;
}

Item UI::getNewItem() {
    Item item;
    cout << "Enter the type, the name, weight and price," << endl;
    cout << "where types:" << endl;
    show_assortment();
    cin >> item;
    return item;
}

void UI::show_items() {
    Searcher getAll;
    show_items(m_stock->search(&getAll));
}

void UI::show_items(const Items& items) {
    string separator = "====================";
    cout << separator << endl;

    if(items.empty()) {
        cout << "No items found" << endl;
        cout << separator << endl;
        return;
    }
    Strings assortment = Item::get_assortment();
    for(unsigned i = 0; i < items.size(); i++) {
        cout << items[i] << endl;
        cout << separator << endl;
    }
}

unsigned UI::show_assortment() {
    Strings assortment = Item::get_assortment();
    for(unsigned i = 0; i < assortment.size(); i++)
        cout << i << " " << assortment[i] << endl;
    return assortment.size();
}

void UI::add_assortment() {
    show_assortment();
    cout << "Enter new item type: ";
    string assortment;
    cin >> assortment;
    if(Item::add_assortment(assortment))
        cout << assortment << " has been added to the type list" << endl;
    else cout << "Something went wrong" << endl;
}

void UI::load() {
    ifstream istr(m_filename);
    // Проверка на предмет открытия файла
    if(!istr.is_open()) {
        cout << "Read file error: " << m_filename << endl;
        cout << "Data hasn't been loaded" << endl;
    }
    else {
        // Перед загрузкой очистим имеющийся список
        m_stock->clear();

        Item loaded;
        do {
            istr >> loaded;
            // Покидаем цикл, если достигнут конец файла
            if(istr.eof())
                break;
            m_stock->add(loaded);
        }
        while(1);

        istr.close();
        cout << "Data from " << m_filename << " has been loaded" << endl;
    }
    istr.open(FILENAME_ITEMTYPES);
    if(istr.is_open()) {
        string item_type;
        do {
            istr >> item_type;
            if(istr.eof())
                break;
            Item::add_assortment(item_type);
        }
        while(1);
        istr.close();
        cout << "Item types from " << FILENAME_ITEMTYPES
             << " has been loaded" << endl;
    }
    else {
        cout << "Read file error: " << FILENAME_ITEMTYPES << endl;
        cout << "Item types hasn't been loaded" << endl;
    }
}

void UI::save() {
    ofstream ostr(m_filename);
    // Проверка на предмет открытия файла
    if(!ostr.is_open()) {
        cout << "Write data error: " << m_filename;
        cout << "Data hasn't been saved" << endl;
    }
    else {
        Searcher srch;
        Items items = m_stock->search(&srch);

        for(unsigned i = 0; i < items.size(); i++)
            ostr << items[i] << endl;

        ostr.close();
        cout << "Data has been saved to " << m_filename << endl;
    }
    ostr.open(FILENAME_ITEMTYPES);
    if(ostr.is_open()) {
        Strings assortment = Item::get_assortment();
        for(unsigned i = 0; i < assortment.size(); i++)
            ostr << assortment[i] << endl;

        ostr.close();
        cout << "Item types has been saved to " << FILENAME_ITEMTYPES << endl;
    }
    else {
        cout << "Write item types error: " << FILENAME_ITEMTYPES;
        cout << "Item types hasn't been saved" << endl;
    }
}