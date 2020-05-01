#ifndef UI_H
#define UI_H
#include <vector>
#include <string>
#include "stock.h"

class UI {
public:
    UI(std::string filename);
    ~UI();

    void main_loop();

private:
    int  main_menu();
    void add();
    void change();
    void remove();
    void search();
    unsigned search_by_type();
    void search_by_price(double& left, double& right);
    void search_by_weight(double& left, double& right);
    void show_items();
    void show_items(const Items& items);
    void add_assortment();
    unsigned show_assortment();
    Item getNewItem();

    // Загрузка файла
    void load();
    // Сохранение файла
    void save();

    Stock* m_stock;
    std::string m_filename;

};

#endif // UI_H
