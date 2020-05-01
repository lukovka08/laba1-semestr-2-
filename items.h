#ifndef ITEMS_H
#define ITEMS_H
#include <vector>
#include <string>
#include <iostream>

using Strings = std::vector<std::string>;

// Класс товара
class Item {
public:
    // Доверим генерацию конструкторов, деструктора и оператора присваивания
    // самому компилятору. Задействуем ключевое слово default:
    Item() = default;
    Item(const Item&) = default;
    ~Item() = default;
    Item& operator=(const Item&) = default;

    friend std::istream& operator>>(std::istream&, Item&);
    friend std::ostream& operator<<(std::ostream&, const Item&);

    // Расширить ассортимент
    static bool add_assortment(std::string assortment);
    // Узнать ассортимент
    static inline Strings get_assortment() {
        return m_assortment;
    }

    inline unsigned     get_type()      const   { return type; }
    inline std::string  get_name()      const   { return name; }
    inline double       get_weight()    const   { return weight; }
    inline double       get_price()     const   { return price; }

private:
    unsigned type;      // Тип
    std::string name;   // Название
    double weight;      // Масса
    double price;       // Цена
    // Возможный ассортимент товаров. Может расширяться методом
    static Strings m_assortment;
};

using Items = std::vector<Item>;

#endif // ITEMS_H