#include <iostream>
#include <cstdlib>
#include <cassert>
#include "Fraction.hpp"
bool Fraction::operator<( const Fraction &operand2 ) const {
    

  //std::cout <<this->numerator*operand2.denominator << " ::"<< operand2.numerator*this->denominator << std::endl;
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
  if ( this->sign == operand2.sign ) {
    Fraction result = Fraction( this->numerator*operand2.denominator + operand2.numerator*this->denominator, 
				operand2.denominator*this->denominator);
    result.sign = this->sign;
    return result;
  } else if ( this->sign !=  operand2.sign){
    if ( !this->sign && -*this > operand2){
      return -Fraction( this->numerator*operand2.denominator - operand2.numerator*this->denominator,
			this->denominator*operand2.denominator);
    } else if ( !this->sign ) {
      return -Fraction( operand2.numerator*this->denominator - this->numerator*operand2.denominator, 
			this->denominator*operand2.denominator);
    } else {
      return -( operand2 + *this);
    }
  }
  std::cout << "Shit just got real!"<< std::endl;
  assert(0);
}
Fraction Fraction::operator*( const Fraction &operand2) const {
  Fraction result =  Fraction( this->numerator*operand2.numerator, this->denominator*operand2.denominator );
  result.sign = this->sign==operand2.sign;
  return result;
}
Fraction Fraction::operator/(const Fraction &operand2)const{
  Fraction result =  *this*Fraction( operand2.denominator, operand2.numerator);
  result.sign = this->sign==operand2.sign;
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
  return *this +( -operand2);
}
Fraction Fraction::operator+() const {
  return *this;
}
Fraction::Fraction( unsigned long numerator, unsigned long denominator) : numerator(numerator), denominator(denominator), sign(true) {
}


std::ostream &operator<<( std::ostream &out, const Fraction &fraction){
  out << ( fraction.sign ? "":"(-" ) << fraction.numerator << "/" << fraction.denominator << ( fraction.sign ? "":")" ) ;
  return out;
}
