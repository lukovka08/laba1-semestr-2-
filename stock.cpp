#include <vector>
#include <string>
#include <algorithm>
#include "stock.h"
using namespace std;

Stock::Stock() {}
Stock::~Stock() {}

void Stock::add(const Item& item) {
    m_items.push_back(item);
}

bool Stock::change(unsigned num, const Item& item) {
    if(num >= totalItems())
        // Прости, дружок, ты не попал в массив
        return false;

    m_items[num] = item;
    return true;
}

bool Stock::remove(unsigned num) {
    if(num >= totalItems())
        return false;

    m_items.erase(m_items.begin() + static_cast<int>(num));
    return true;
}

void Stock::clear() {
    m_items.clear();
}

Items Stock::search(Searcher* searcher) {
    /* Итак, что здесь происходит.
     * Мы проходимся по каждому товару, и те, для которых поисковик
     * вернул истину, мы кладем в конечный массив, который в итоге
     * возвращаем.
     */
    Items items;
    for(unsigned i = 0; i < m_items.size(); i++) {
       if((*searcher)(m_items[i]))
           items.push_back(m_items[i]);
    }
    return items;
}