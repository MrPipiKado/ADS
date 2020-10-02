#include "product.h"

Product::Product()
{
    this->title = "";
    this->price = 0.0;
}

Product::Product(std::string title, double price)
{
    this->title = title;
    this->price = price;
}

double Product::getPrice()
{
    return this->price;
}

void Product::setPrice(double price)
{
    this->price = price;
}

std::string Product::getTitle()
{
    return this->title;
}

void Product::setTitle(std::string title)
{
    this->title = title;
}
