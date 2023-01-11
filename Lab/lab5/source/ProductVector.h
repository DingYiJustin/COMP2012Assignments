#ifndef PRODUCTVECTOR_H
#define PRODUCTVECTOR_H

#include <iostream>
#include "Product.h"
using namespace std;

template <typename T> class ProductVector
{
    private:
        T* data;
        int capacity;
        int length;

    public:
        ProductVector(int n = 1) : data(new T[n]), capacity(n), length(0) {}

        // Add the new element to the back.
        void push_back(const T& s) {
            if (capacity <= length) {
                T* temp = new T[capacity * 2];
                for (int i = 0; i < length; i++){
                    temp[i] = data[i];
                }
                delete[] data;
                data = temp;
                capacity *= 2;
            }

            data[length] = s;
            length++;
        }

        /* ================================================================
            TODO: Complete get_value(int i)
            HINT: We can access the element at index i using this function
           ================================================================ */
        T get_value(int i)
        {
            return data[i];
        }
        /* ================================================================
            TODO: Complete swap(int i, int j)
            HINT: We can swap the elements present at the given indices
           ================================================================ */
        void swap(int i, int j)
        {
            T temp = get_value(i);
            data[i] = data[j];
            data[j] = temp;
        }

        // Remove the element at index i
        void remove(int x) {
            for (int i = x+1; i < length; i++) {
                data[i - 1] = data[i];
            }
            length--;
        }

        // Return the size of vector
        int size() { return length; }

        ~ProductVector() {
            if (data) {
                delete[] data;
            }
        }
};

/* =================================================================================
    TODO: Complete void compare_price function(a, b)
    This function compares the two given values and prints.
    Hint: 1. Should handle multiple cases shown in main.cpp.
          2. Using function template and template instantiation and specialization.
          3. The function template may have nontype parameters.
          4. Its return type is void. So, you need to print. 
             Refer to the lab page for the printing format.
   ================================================================================= */
template <typename T>
void compare_price(const T& a, const T& b)
{
    cout<<"General case: "<<((a>b)?a:b)<<endl;
}


template<typename T>
void compare_price(const Product& a, const Product& b)
{
    if(a.get_retail_price()>b.get_retail_price())
        cout<<"The product "<< a.get_product_name()<<" is more expensive"<<endl;
    else
        cout<<"The product "<< b.get_product_name()<<" is more expensive"<<endl;
}

template <typename T, int value>
void compare_price(const T& a)
{
    cout<<"General case: "<<((a>value)?a:value)<<endl;
}

template <typename T,int value>
void compare_price(const Product& a)
{
    cout<<"The product "<<a.get_product_name()<< ((a.get_retail_price()>value)?" is more expensive ":" is cheaper ")<<" than  "<< value<<endl;
    /*
    if(a.get_retail_price()>value)
    {
        cout<<"The product "<<a.get_product_name()<< " is more expensive than "<< value<<endl;
    }
    else
    {
        cout<<"The product "<<a.get_product_name()<< " is cheaper than "<< value<<endl;

    }
    */
}
#endif
