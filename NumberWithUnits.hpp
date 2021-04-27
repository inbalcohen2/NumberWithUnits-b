#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>
using namespace std;

namespace ariel{
        class NumberWithUnits {
        private:
          double val;
          string str;

          static double convert(const string& t ,const string& f , double val) ;
          friend bool check( NumberWithUnits const & l, NumberWithUnits const & r );
          
          public:
          NumberWithUnits(double val ,const string& str);
          static void read_units(ifstream& input);

          //************* + , += , + unry , - , -= , - unry  ,* left, right * ****************
          NumberWithUnits operator+( NumberWithUnits const & r ) ;
         
          NumberWithUnits operator+( ) const;
         
          NumberWithUnits & operator+=( NumberWithUnits const & r );
        
          NumberWithUnits operator-( NumberWithUnits const & r ) ;
         
          NumberWithUnits operator-( ) const;

          NumberWithUnits & operator-=( NumberWithUnits const & r );
         
          friend NumberWithUnits operator*(const NumberWithUnits& l,const double &val);

          friend NumberWithUnits operator*(const double &val, const NumberWithUnits& r);

          //***************** > >= < <= == !=  ***************************

          friend bool operator==( NumberWithUnits const & l, NumberWithUnits const & r );

          friend bool operator!=( NumberWithUnits const & l, NumberWithUnits const & r );

          friend bool operator<( NumberWithUnits const & l, NumberWithUnits const & r );

          friend bool operator<=( NumberWithUnits const & l, NumberWithUnits const & r );

          friend bool operator>( NumberWithUnits const & l, NumberWithUnits const & r );

          friend bool operator>=( NumberWithUnits const & l, NumberWithUnits const & r );
          //********************** ++ -- *******************************

          friend  NumberWithUnits operator--( NumberWithUnits & val, int );
          friend  NumberWithUnits & operator--( NumberWithUnits & val );
          friend  NumberWithUnits & operator++( NumberWithUnits & val );
          friend  NumberWithUnits operator++( NumberWithUnits & val, int );

          //operator <<
          friend ostream& operator<<(ostream& out, const NumberWithUnits& val);
          friend istream& operator>>(istream& input, NumberWithUnits& val);
        };
}
