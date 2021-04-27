
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

#include "NumberWithUnits.hpp"
using namespace ariel;

int main() {
  ofstream outfile ("unit.txt");

  string str="";

  cout<< "Create File, Example: 1 km = 1000 m"<<endl;

  while(getline(std::cin, str) ){
    if(str == "exit"){
      break;
    }
         outfile << str << std::endl;
           cout<< "Stop -write exit"<<endl;
    }

    outfile.close();


    ifstream units_file{"unit.txt"};
    // read unit and insert to map
    NumberWithUnits::read_units(units_file);

    cout<< "choose 2 variable (1.number 2.type), Example: 700[km] "<<endl;

    NumberWithUnits a{0, "km"};
    cin>>a;
    NumberWithUnits b{0, "km"};
    cin>>b;

    string op;
    while(op != "exit"){
        cout<< "choose operator: + / - / += / -= / == / * / < / > / <= / >= "<<endl;

        cin>>op;

        if(op=="+"){
          cout << (a+b) << '\n';
        }
         if(op=="-"){
          cout << (a-b) << '\n';
        }
        if(op=="+="){
          cout << (a+=b) << '\n';
        }
         if(op=="-="){
          cout << (a-=b) << '\n';
        }
         if(op=="=="){
          cout << boolalpha;
          cout << (a==b) << '\n';
        }
        if(op=="<"){
          cout << boolalpha;
          cout << (a<b) << '\n';
        }
        if(op==">"){
          cout << boolalpha;
          cout << (a>b) << '\n';
        }
        if(op==">="){
          cout << boolalpha;
          cout << (a>=b) << '\n';
        }
         if(op=="<="){
          cout << boolalpha;
          cout << (a<=b) << '\n';
        }
    }
    return 0;
}
