#include "basicfuncs.h"
#include "boundaryclass.h"

int main()
{
    cout << "Please, input name of the config file: ";
    string name;
    cin >> name;
    boundary interface(name);
    return 0;
}