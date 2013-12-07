#include "unittest.hpp"
int main(){
  unittest();
  return 0;
}

void testtwo( Fraction a, Fraction b){
  std::cout << a << " == " << b << ": " << ( a == b ) << std::endl;
  std::cout << a << " >  " << b << ": " << ( a > b )  << std::endl;
  std::cout << a << " <  " << b << ": " << ( a < b )  << std::endl;
  std::cout << a << " +  " << b << ": " << ( a+b )    << std::endl;
  std::cout << a << " -  " << b << ": " << ( a-b )    << std::endl;
  std::cout << a << " *  " << b << ": " << ( a*b )    << std::endl;
  std::cout << a << " /  " << b << ": " << ( a/b )    << std::endl;
}


void unittest(){
  Fraction fraction1 = Fraction(1,2),
    fraction2 = Fraction(1, 4);
  testtwo(fraction1, fraction1);
  testtwo(fraction2, fraction1);
  testtwo(fraction1, fraction2);
  std::cout << "------------------" << std::endl;
  testtwo(-fraction1, fraction1);
  testtwo(-fraction2, fraction1);
  testtwo(-fraction1, fraction2);
  std::cout << "------------------" << std::endl;
  testtwo(fraction1, -fraction1);
  testtwo(fraction2, -fraction1);
  testtwo(fraction1, -fraction2);
}
