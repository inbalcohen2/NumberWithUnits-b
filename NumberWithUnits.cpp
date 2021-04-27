#include "NumberWithUnits.hpp"

namespace ariel{

// create map 
  unordered_map<string,unordered_map<string ,double>> map;
 
 //constructor
  NumberWithUnits::NumberWithUnits(double val ,const string& str){
// if not found the same str  
    if(map.find(str) == map.end()) {__throw_invalid_argument("Eror not same type");}
    this->val= val;
    this->str= str;
  }

// f= from t =to , example f= km , t = m
// convert from km to m 
//val = 3 , map[f][t]=1000
  double NumberWithUnits::convert(const string& t ,const string& f , double val){
    if(f==t){
      return val;
    }
      return map[f][t] * val;
  }

  bool check( NumberWithUnits const & l, NumberWithUnits const & r ) {
    // if they equals and one of them found in the file -> false
    if((l.str==r.str) && map.find(l.str) != map.end()) {return false;}
    // check if l.str in the file and than if the r.str found in the map of l.str
    if ( map.find(l.str) != map.end() && (map[l.str].find(r.str) != map[l.str].end())) {
                    return false;
            }
    return true;
  }
  // 1 km = 1000 m 
  // 1 m = 1/1000 km 
  // 1 m = 100 cm 
  // 1 cm = 100 mm

  void casting(const string &str1 ,const string &str2){
    for (auto& p : map[str1]){
      double cast=map[str2][str1] * p.second;
      map[str2][p.first]= cast;
      map[p.first][str2]= 1/cast;
  }
    for (auto& p : map[str2]){
      double cast=map[str1][str2] * p.second;
      map[str1][p.first]= cast;
      map[p.first][str1]= 1/cast;
  }
  }

  void NumberWithUnits::read_units(ifstream& input){
        string other;
        string str1;
        string str2;
        double val1= 0;
        double val2=0;
        while(input >> val1 >> str1 >> other >> val2 >> str2){
            map[str1][str2]=val2;
            map[str2][str1]=1/val2;
            casting(str1,str2);
    }
  }

  //************* + , =+ , + unry , - , =- , - unry  ,* left, right * ****************


   NumberWithUnits NumberWithUnits::operator+( NumberWithUnits const & r ) {
     if(check(*this,r)) {  __throw_invalid_argument("Eror not same type");}
       double conv=NumberWithUnits::convert(this->str,r.str,r.val);
       //return without change this, NumberWithUnits new
       return NumberWithUnits(this->val+conv,this->str);
   }
   //a.plus()

     NumberWithUnits NumberWithUnits::operator+( ) const{
        return NumberWithUnits(this->val,this->str);
   }

   NumberWithUnits & NumberWithUnits::operator+=( NumberWithUnits const & r ){
      *this=(*this+r);
      //return change this
      return *this;
   }

   NumberWithUnits NumberWithUnits::operator-( NumberWithUnits const & r ) {
     if(check(*this,r)) {  __throw_invalid_argument("Eror not same type");}
       double conv=NumberWithUnits::convert(this->str,r.str,r.val);
       return NumberWithUnits(this->val-conv,this->str);
   }

   NumberWithUnits NumberWithUnits::operator-( ) const{
     return NumberWithUnits(-1*(this->val),this->str);
   }
// return the same this after changes
   NumberWithUnits & NumberWithUnits::operator-=( NumberWithUnits const & r ){
      *this=(*this-r);
      return *this;
   }

// return new NumberWithUnits
   NumberWithUnits operator*(const NumberWithUnits& l,const double &val){
     return NumberWithUnits(l.val*val,l.str);
   }

// return new NumberWithUnits
   NumberWithUnits operator*(const double &val, const NumberWithUnits& r){
     return NumberWithUnits(r.val*val,r.str);
   }

  //***************** > >= < <= == !=  ***************************

   bool operator==( NumberWithUnits const & l, NumberWithUnits const & r ){
      if(check(l,r)) {  __throw_invalid_argument("Eror not same type");}
       double conv=NumberWithUnits::convert(l.str,r.str,r.val);
       const double eps =0.0001;
       if (std::abs(l.val - conv) < eps){
         return true;  return false;
       }
         return false;
   }

   bool operator!=( NumberWithUnits const & l, NumberWithUnits const & r ){

      if(check(l,r)) {  __throw_invalid_argument("Eror not same type");}

       double conv=NumberWithUnits::convert(l.str,r.str,r.val);
       if(l.val != conv){
         return true; return false;
       }
         return false;
   }

   bool operator<( NumberWithUnits const & l, NumberWithUnits const & r ){
     if(check(l,r)) {  __throw_invalid_argument("Eror not same type");}
       double conv=NumberWithUnits::convert(l.str,r.str,r.val);
         return l.val < conv;
      
       }


   bool operator<=( NumberWithUnits const & l, NumberWithUnits const & r ){
      return l == r || l < r;
   }

   bool operator>( NumberWithUnits const & l, NumberWithUnits const & r ){
      if(check(l,r)){  __throw_invalid_argument("Eror not same type");}

       double conv=NumberWithUnits::convert(l.str,r.str,r.val);
       if(l.val > conv){
         return true;  return false;
       }
         return false;

   }

   bool operator>=( NumberWithUnits const & l, NumberWithUnits const & r ){
     return l == r || l > r;
   }
  //********************** ++ -- *******************************

     //val--
    NumberWithUnits operator--( NumberWithUnits & val, int ){
        return NumberWithUnits(val.val--,val.str);
    }
    //--val
    NumberWithUnits & operator--( NumberWithUnits & val ){
      val.val--;
      return val;
    }
// ++val 
    NumberWithUnits & operator++( NumberWithUnits & val ){
         val.val++;
        return val;
    }
    // val++
    NumberWithUnits operator++( NumberWithUnits & val, int ){
        return NumberWithUnits(val.val++,val.str);
    }

// ****************** << >> ***************************
    ostream& operator<<(ostream& out, const NumberWithUnits& val){
        return out<<val.val<<"["<<val.str<<"]";
        // example 2[km]
    }

   istream& operator>>(istream& input, NumberWithUnits& val){
     //example
     //700 [ kg ]
     //         9 0 0  [r_ton]
     //20 [r_sec]
    
     string str;
     getline(input, str, ']');
     string delimiter = "[";
     string num = str.substr(0, str.find(delimiter));
     string token = str.substr(str.find(delimiter));
     string s;

     for(char& c : num) {
       if((isdigit(c)!=0) || c=='-' || c=='.'){
         s+=c;
       }
     }

     string s1;
     for(char& c : token) {
       if((isalpha(c)!=0)|| c=='_'){
         s1+=c;
       }
     }
     if(map.find(s1) == map.end()) {__throw_invalid_argument("Eror not same type");}

     //c_str function convert string to char *
     //atof function get char * convert to double
     val = NumberWithUnits(atof(s.c_str()), s1);
     return input;
   }
}
