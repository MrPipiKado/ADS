#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product
{
public:
    Product();
    Product(std::string title, double price);
    std::string getTitle();
    void setTitle(std::string);
    double getPrice();
    void setPrice(double);

private:
    std::string title;
    double price;
};

#endif // PRODUCT_H
