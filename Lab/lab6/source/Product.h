
#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <sstream>
#include <string>
using namespace std;
class Product
{
    private: 
        double regular_price;
        string product_name;
    public: 
        Product() : regular_price(0), product_name("") {}
        Product(double regular_price, const string& product_name)
          : regular_price(regular_price), product_name(product_name) {}
        string get_product_name() const { return product_name; }
        double get_regular_price() const { return regular_price; }

        virtual double get_retail_price() const = 0; 
        virtual void print() const = 0;

    /* ===================================================================
        TODO: operator overloading
              Refer to the main.cpp.
       =================================================================== */

    // TODO: Overload `operator>` to compare the get_retail_price(), when the parameter is Prodouct.
    // Compare_price function template in ProductVector.h will be replaced by this operator.
    bool operator>(const Product& p)
    {
        return this->get_retail_price()>p.get_retail_price();
    }
    // TODO: Overload `operator>` to compare the get_retail_price(), when the parameter is int.
    // Compare_price function template in ProductVector.h will be replaced by this operator.
    bool operator>(int v)
    {
        return this->get_retail_price()>v;
    }
    // TODO: Overload `operator<<` to print get_product_name()
    // Hint: Using the "friend" keyword, declare stream insertion operator function `operator<<`
    // cout << product; -> output is product.get_product_name()
    friend ostream& operator<<(ostream& os, const Product& p);

    // {
    //     return (os<<(p.get_product_name()));
    // }
    // TODO: Overload `operator==` to compare get_product_name(), when the parameter is string.
    // Hint: If they are equal, return ture or opposite.
    // The member function isExist of ProductVector will use this operator.
    bool operator==(const string& name)
    {
        return this->product_name == name;
    }
    

};

ostream& operator<<(ostream& os, const Product& p)
{
        //return (os<<(p.get_product_name()));
        return (os<<(p.product_name));
}

#endif
