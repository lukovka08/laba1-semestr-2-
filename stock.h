#ifndef STOCK_H
#define STOCK_H
#include <vector>
#include <string>
#include "items.h"
#include "searcher.h"

using Searcher = searcher::Base;
// Класс "Склад"
// Содержит методы работы над товарами,
// а также метод расширения ассортимента
class Stock {
public:
    Stock();
    ~Stock();

    // Добавить
    void add(const Item& item);
    // Изменить
    bool change(unsigned num, const Item& item);
    // Удалить
    bool remove(unsigned num);
    // Очистить
    void clear();

    // Количество товара на складе
    inline unsigned totalItems() {
        return m_items.size();
    }

    // Поиск
    Items search(Searcher* searcher);

private:
    // Сами товары
    Items m_items;
};

#endif // STOCK_H
