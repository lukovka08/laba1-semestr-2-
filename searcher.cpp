#include "searcher.h"

bool searcher::Base::operator()(const Item&) {
    return true;
}

searcher::byPrice::byPrice(double left, double right): Base() {
    m_left = left;
    m_right = right;
}

bool searcher::byPrice::operator()(const Item& item) {
    return (item.get_price() >= m_left) && (item.get_price() <= m_right);
}

searcher::byWeight::byWeight(double left, double right): Base() {
    m_left = left;
    m_right = right;
}

bool searcher::byWeight::operator()(const Item& item) {
    return (item.get_weight() >= m_left) && (item.get_weight() <= m_right);
}

searcher::byType::byType(unsigned type): Base() {
    m_type = type;
}

bool searcher::byType::operator()(const Item& item) {
    return item.get_type() == m_type;
}