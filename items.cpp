#include "items.h"
#include <algorithm>
#include <fstream>
using namespace std;

// Задаем начальные значения для статического члена Item
Strings Item::m_assortment = {"Chocolate", "Cake", "Sugar"};

// Вот так бы выглядели реализации конструкторов и иже с ними
// без ключегого слова default:
/*
Item::Item(): type(0), weight(0), price(0) {}
Item::~Item() {}

Item::Item(const Item& item) {
    this->operator=(item);
}

Item& Item::operator=(const Item& item) {
    type   = item.type;
    name   = item.name;
    weight = item.weight;
    price  = item.price;
    return *this;
}
*/

bool Item::add_assortment(string assortment) {
    // Прежде чем добавить новый тип товара, нужно проверить его наличие
    if(find(m_assortment.begin(),
            m_assortment.end(),
            assortment) == m_assortment.end())
        m_assortment.push_back(assortment);
    else
        return false;

    return true;
}

istream& operator>>(istream& istr, Item& item) {
    istr >> item.type >> item.name >> item.weight >> item.price;
    return istr;
}

ostream& operator<<(ostream& ostr, const Item& item) {
    /* Пытаемся "проапкастить" (привести объект ostream)
     * к классу ofstream. Нам это нужно для различного вывода
     * на стандартное устройство и файл
     */
    if(dynamic_cast<ofstream*>(&ostr) == nullptr) {
        // Если ostr не является объектом ofstream, т.е работаем с cout,
        // то выводим на стандартное устройство не номер типа,
        // а его название, соответствующее номеру
        Strings assortment = Item::get_assortment();
        if(item.type >= assortment.size())
            ostr << "UNKNOWN_TYPE(" << item.type << ") ";
        else
            ostr << assortment[item.type] << ' ';
    }
    // Если же мы работаем с файлом, то выводим номер типа
    else
        ostr << item.type << ' ';
    ostr << item.name << ' '
         << item.weight << ' '
         << item.price;
    return ostr;
}