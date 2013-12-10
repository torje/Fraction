#include <iostream>
#include <cstdlib>
#include <cassert>
class Fraction {
public:
  bool sign;
  bool nan ;
  unsigned long numerator;
  unsigned long denominator;
public:  
  unsigned long reduce ( );
  bool      operator<  ( const Fraction &operand2) const;
  bool      operator>  ( const Fraction &operand2) const;
  bool      operator<= ( const Fraction &operand2) const;
  bool      operator>= ( const Fraction &operand2) const;
  bool      operator== ( const Fraction &operand2) const;
  Fraction  operator+  ( const Fraction &operand2) const;
  Fraction  operator-  ( const Fraction &operand2) const;
  Fraction  operator*  ( const Fraction &operand2) const;
  Fraction  operator/  ( const Fraction &operand2) const;
  Fraction &operator+= ( const Fraction &operand2);
  Fraction &operator-= ( const Fraction &operand2);
  Fraction &operator*= ( const Fraction &operand2);
  Fraction &operator/= ( const Fraction &operand2);
  Fraction  operator+  ( )                         const; 
  Fraction  operator-  ( )                         const;
  Fraction ( );
  Fraction( const Fraction &fraction);
  Fraction ( unsigned long numerator, unsigned long denominator);
};

std::ostream &operator<<( std::ostream &out, const Fraction &fraction);
