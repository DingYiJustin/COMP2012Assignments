#include <iostream>

using namespace std;

int main()
{
    char username1 = '2';
    char username2 = '1';
    cout<<((username1 - '0' + 'a' + 1) * 0x01010000 + (username2 - '0' + 'A' + 2) * 0x0101);
}