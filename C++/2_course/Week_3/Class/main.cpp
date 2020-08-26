#include <iostream>
#include "phone_number.h"

using namespace std;

int main()
{
    PhoneNumber num("+sad-sddas-26-asdfg");
    cout << num.GetCountryCode() << endl;
    cout << num.GetCityCode() << endl;
    cout << num.GetLocalNumber() << endl;
    cout << num.GetInternationalNumber() << endl;
    PhoneNumber* number = new PhoneNumber("+7-495-111-22-33 home");
            cout << number->GetCountryCode() << " "
                << number->GetCityCode() << " "
                << number->GetLocalNumber() << " "
                << number->GetInternationalNumber() << '\n';

  return 0;
}
