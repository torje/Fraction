#include <iostream>
#include <cstdlib>
#include <cassert>
#include "Fraction.hpp"
unsigned long gcd( unsigned long operand1, unsigned long operand2){
  int higher, lower, remainder;
  higher = operand1 > operand2 ? operand1 : operand2;
  lower  = operand1 < operand2 ? operand1 : operand2;
  if ( lower == 0){
  return 1;
}
  remainder = higher % lower;
  while( remainder != 0){
    higher = lower;
    lower = remainder;
    remainder = higher % lower;
  }
  return lower;
}

unsigned long Fraction::reduce( ) {
  int divisor = gcd( this->numerator, this->denominator);
  this->numerator /= divisor;
  this->denominator /=divisor;
  if ( numerator == 0 ) {
    sign = false;
  }
  return divisor;
}

bool Fraction::operator<( const Fraction &operand2 ) const {
  if ( !this->sign && operand2.sign ){
    return true;
  } else if ( this->sign && !operand2.sign) {
    return false;
  } else if ( this->sign == operand2.sign) {
    return ( this->sign ) == ( this->numerator*operand2.denominator < operand2.numerator*this->denominator );
  } else {
    std::cout << "Error: not caught case. " <<std::endl;
    exit(1);
  }
}
bool Fraction::operator>( const Fraction &operand2 ) const {
  if ( !this->sign && operand2.sign ){
    return false;
  } else if ( this->sign && !operand2.sign) {
    return true;
  } else if ( this->sign == operand2.sign) {
    return ( this->sign ) == ( this->numerator*operand2.denominator > operand2.numerator*this->denominator );
  } else {
    std::cout << "Error: not caught case. " <<std::endl;
    exit(1);
  }
}
bool Fraction::operator==( const Fraction &operand2) const {
  return !(*this > operand2 || *this < operand2);
}
Fraction Fraction::operator-() const {
  Fraction result = *this;
  result.sign ^= true;
  return result;
}
Fraction Fraction::operator+( const Fraction &operand2) const{
  Fraction result;
  if ( this->sign == operand2.sign ) {
    result = Fraction( this->numerator*operand2.denominator + operand2.numerator*this->denominator, 
		       operand2.denominator*this->denominator);
    result.sign = this->sign;
  } else if ( this->sign !=  operand2.sign){
    if ( !this->sign && -*this > operand2){
      result = -Fraction( this->numerator*operand2.denominator - operand2.numerator*this->denominator,
			  this->denominator*operand2.denominator);
    } else if ( !this->sign ) {
      result = -Fraction( operand2.numerator*this->denominator - this->numerator*operand2.denominator, 
			  this->denominator*operand2.denominator);
    } else {
      result = -( operand2 + *this);
    }
  }
  result.reduce();
  return result;
}
Fraction Fraction::operator*( const Fraction &operand2) const {
  Fraction result =  Fraction( this->numerator*operand2.numerator, this->denominator*operand2.denominator );
  result.sign = this->sign==operand2.sign;
  result.reduce();
  return result;
}
Fraction Fraction::operator/(const Fraction &operand2)const{
  Fraction result =  *this*Fraction( operand2.denominator, operand2.numerator);
  result.sign = this->sign==operand2.sign;
  result.reduce();
  return result;
}
Fraction &Fraction::operator+=( const Fraction &operand2){
  *this = *this+operand2;
  return *this;
}
Fraction &Fraction::operator-=( const Fraction &operand2){
  *this = *this - operand2;
  return *this;
}
Fraction &Fraction::operator*=( const Fraction &operand2){
  *this = *this *operand2;
  return *this;
}
Fraction &Fraction::operator/=( const Fraction &operand2){
  *this = *this/operand2;
  return *this;
}
Fraction Fraction::operator-( const Fraction &operand2) const {
  Fraction result = *this +( -operand2);
  result.reduce();
  return result;
}
Fraction Fraction::operator+() const {
  return *this;
}
Fraction::Fraction( unsigned long numerator, unsigned long denominator) : numerator(numerator), denominator(denominator), sign(true) {
}
Fraction::Fraction( ) {
  sign = true;
  numerator = 0;
  denominator = 1;
}

std::ostream &operator<<( std::ostream &out, const Fraction &fraction){
  out << ( fraction.sign ? "":"(-" ) << fraction.numerator << "/" << fraction.denominator << ( fraction.sign ? "":")" ) ;
  return out;
}
