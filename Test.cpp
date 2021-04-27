#include "doctest.h"
#include "NumberWithUnits.hpp"
#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <experimental/random>
#include <unistd.h>
#include <algorithm>
using namespace std;
using namespace doctest;
using namespace std;
using namespace ariel;

ifstream units_file{"units.txt"};
const std::string test_file = "./units.txt";

TEST_CASE("onary operatorד: + , - "){
    NumberWithUnits::read_units(units_file);
   
    NumberWithUnits a{100, "kg"};
    NumberWithUnits b{1, "ton"};
    NumberWithUnits x{1,"g"};
    CHECK_NE(x,b);

    CHECK_EQ(+a , NumberWithUnits{100, "kg"});
    CHECK_EQ(+a , NumberWithUnits{0.1, "ton"});
    CHECK_EQ(+b , NumberWithUnits{1, "ton"});
    CHECK_EQ(+b , NumberWithUnits{1000, "kg"});
    CHECK_EQ(-a , NumberWithUnits{-100, "kg"});
    CHECK_EQ(-b , NumberWithUnits{-1, "ton"});
    CHECK_EQ(-a , NumberWithUnits{-0.1, "ton"});
}

TEST_CASE("Add and Remove Operators: + , -"){
    NumberWithUnits::read_units(units_file);
   
    NumberWithUnits a{100, "kg"};
    NumberWithUnits b{400, "kg"};
    NumberWithUnits c{1, "ton"};
    NumberWithUnits d{4, "m"};

    CHECK_EQ(a+b , NumberWithUnits{500, "kg"});
    CHECK_EQ(b+a , NumberWithUnits{0.5, "ton"});
    CHECK_EQ(a+c , NumberWithUnits{1.1, "ton"});
    CHECK_EQ(c+b , NumberWithUnits{1400, "kg"});
    CHECK_EQ(b-a , NumberWithUnits{300, "kg"});
    CHECK_EQ(a-b , NumberWithUnits{-0.3, "ton"});
    CHECK_EQ(c-a , NumberWithUnits{900, "kg"});
    CHECK_EQ(c-b , NumberWithUnits{0.6, "ton"});
  //not the same type
    CHECK_THROWS(a+d);
    CHECK_THROWS(b+d);
    CHECK_THROWS(b-d);
    CHECK_THROWS(c+d);
}

TEST_CASE("Placement operators: += , -="){
    NumberWithUnits::read_units(units_file);
   
    NumberWithUnits a{100, "kg"};
    NumberWithUnits b{400, "kg"};
    NumberWithUnits c{1, "ton"};
    NumberWithUnits d{100, "km"};

    CHECK_EQ(a+=b , NumberWithUnits{500, "kg"});
    CHECK(a == NumberWithUnits{0.5, "ton"});
    CHECK_EQ(a+=c , NumberWithUnits{1.5, "ton"});
    CHECK_EQ(b-=a , NumberWithUnits{-1.1, "ton"});
    CHECK_EQ(b+=c , NumberWithUnits{-100, "kg"});
    CHECK(b == NumberWithUnits{-0.1, "ton"});
    CHECK_EQ(c+=b , NumberWithUnits{900, "kg"});
    CHECK_EQ(c-=a , NumberWithUnits{-0.6, "ton"});
    CHECK(c == NumberWithUnits{-600, "kg"});
  // not the same type
    CHECK_THROWS(a+=d);
    CHECK_THROWS(b+=d);
    CHECK_THROWS(b-=d);
    CHECK_THROWS(c+=d);
}

TEST_CASE("Multiplication operator: * left , right * "){
    NumberWithUnits::read_units(units_file);
   
    NumberWithUnits a{100, "kg"};
    NumberWithUnits b{400, "kg"};
    NumberWithUnits c{1, "ton"};

    CHECK_EQ(a*4000 , NumberWithUnits{400, "ton"});
    CHECK_EQ(a*4 , NumberWithUnits{400, "kg"});
    CHECK_EQ(7*b , NumberWithUnits{2800, "kg"});
    CHECK_EQ(2.5*c , NumberWithUnits{2.5, "ton"});
    CHECK_EQ(-1.8*a , NumberWithUnits{-180, "kg"});
    CHECK_EQ(b*2 , NumberWithUnits{800, "kg"});
    CHECK_EQ(c*9 , NumberWithUnits{9, "ton"});
}

TEST_CASE("Equality operators: == , !="){
    NumberWithUnits::read_units(units_file);
   
    NumberWithUnits a{100, "kg"};;
    NumberWithUnits b{1, "ton"};

    CHECK_EQ(NumberWithUnits{0.5, "km"} , NumberWithUnits{500, "m"});
    CHECK(a == NumberWithUnits{0.1, "ton"});
    CHECK(b!=  NumberWithUnits{1.5, "ton"});
    CHECK_NE(NumberWithUnits{10, "ton"}  , NumberWithUnits{1000, "kg"});
    CHECK_NE(NumberWithUnits{6, "hour"}, NumberWithUnits{3500, "min"});
    CHECK_EQ(NumberWithUnits{1.3, "ton"} , NumberWithUnits{1300, "kg"});
    CHECK_EQ(NumberWithUnits{5000, "m"} , NumberWithUnits{5, "km"});
    CHECK_EQ(NumberWithUnits{300, "cm"}, NumberWithUnits{3, "m"});
    CHECK_NE(NumberWithUnits{1, "km"}, NumberWithUnits{10000000, "cm"});
    CHECK_EQ(NumberWithUnits{1000, "g"}, NumberWithUnits{1, "kg"});

  
}
TEST_CASE("Comparative operators: < , <= , > , >="){
    NumberWithUnits::read_units(units_file);
   
    NumberWithUnits a{100, "kg"};
    NumberWithUnits b{400, "kg"};
    NumberWithUnits c{1, "ton"};
    NumberWithUnits d{100, "km"};
    NumberWithUnits f{5000, "m"};

    CHECK(a < b);
    CHECK(c > b);
    CHECK(d >= f);
    CHECK_LT(NumberWithUnits{5, "hour"}  , NumberWithUnits{3100, "min"});
    CHECK_GT(NumberWithUnits{80, "min"}, NumberWithUnits{1, "hour"});
    CHECK_LT(NumberWithUnits{5, "ton"}  , NumberWithUnits{6000, "kg"});
    CHECK_GT(NumberWithUnits{80, "m"}, NumberWithUnits{0.07, "km"});

}

TEST_CASE("Increment/decrement operators: ++left , right++ ,  --left , right--"){
    NumberWithUnits::read_units(units_file);
   
    NumberWithUnits a{100, "g"};
    NumberWithUnits b{400, "g"};
    NumberWithUnits c{1, "kg"};

    CHECK(a++ == NumberWithUnits{100, "g"});
    CHECK(a == NumberWithUnits{101, "g"});
    CHECK(++a == NumberWithUnits{102, "g"});
    CHECK(a == NumberWithUnits{102, "g"});
    CHECK(b-- == NumberWithUnits{400, "g"});
    CHECK(b == NumberWithUnits{399, "g"});
    CHECK(--b == NumberWithUnits{398, "g"});
    CHECK(b == NumberWithUnits{398, "g"});
    CHECK(c++ == NumberWithUnits{1, "kg"});
    CHECK(--c == NumberWithUnits{1, "kg"});
    CHECK(++c == NumberWithUnits{2, "kg"});
    CHECK(c-- == NumberWithUnits{2, "kg"});
    CHECK(c == NumberWithUnits{1, "kg"});

}
TEST_CASE( "<< >>"){
// // ****** << >> *********
  NumberWithUnits::read_units(units_file);  
    NumberWithUnits a{100, "USD"};
    NumberWithUnits b{400, "ILS"};
    NumberWithUnits c{200, "kg"};
    NumberWithUnits d{500, "ton"};
    NumberWithUnits e{300, "min"};
    NumberWithUnits f{600, "hour"};
 //<<
 stringstream _b;
    _b << b;
    CHECK((_b.str() == "400[ILS]") == true);
     stringstream _c;
    _c << c;
    CHECK((_c.str() == "200[kg]") == true);
    stringstream _e;    
    _e << e;
    CHECK((_e.str() == "300[min]") == true);

 //>>
    istringstream str1{"250[USD]"};
    str1 >> a;
    CHECK(a == NumberWithUnits{250, "USD"});
    istringstream str2{"1000[ton]"};
    str2 >> d;
    CHECK(d == NumberWithUnits{1000, "ton"});
    istringstream str3{"6[hour]"};
    str3 >> f;
    CHECK(f == NumberWithUnits{6, "hour"});
}