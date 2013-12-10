#include "Fraction.hpp"

unsigned long gcd( unsigned long operand1, unsigned long operand2){
  int higher, lower, remainder;
  if ( operand1 > operand2 ){
    higher = operand1;
    lower  = operand2;
  }else{
    higher = operand2;
    lower  = operand1;
  }
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
    if (this->nan || operand2.nan ){
    return false;
  }
  if ( this->numerator == 0 && operand2.numerator == 0){
    return false;
  }else if ( !this->sign && operand2.sign ){
    return true;
  } else if ( this->sign && !operand2.sign) {
    return false;
  } else if ( this->sign && operand2.sign) {
    return ( this->numerator*operand2.denominator < operand2.numerator*this->denominator );
  } else if ( (!this->sign) && (!operand2.sign)) {
    return ( this->numerator*operand2.denominator > operand2.numerator*this->denominator );
  } else {
    std::cout << "Error: not caught case. " <<std::endl;
    exit(1);
  }
}

bool Fraction::operator>( const Fraction &operand2 ) const {
    if (this->nan || operand2.nan ){
    return false;
  }
  return operand2 < (*this);
}

bool Fraction::operator<= ( const Fraction &operand2 ) const {
    if (this->nan || operand2.nan ){
    return false;
  }
  return !(*this > operand2);
}

bool Fraction::operator>= ( const Fraction &operand2 ) const {
  if (this->nan || operand2.nan ){
    return false;
  }
  return !(*this < operand2);
}

bool Fraction::operator==( const Fraction &operand2) const {
  if (this->nan || operand2.nan ){
    return false;
  }
  return !((*this > operand2) || (*this < operand2));
}

Fraction Fraction::operator-() const {
  Fraction result = *this;
  result.sign ^= true;
  return result;
}

Fraction Fraction::operator+( const Fraction &operand2) const{
  Fraction result;
  if (this->nan || operand2.nan ){
    return Fraction();
  }
  if (this->denominator==0 || operand2.denominator==0){
    return Fraction();
  }
  
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
    } else if (this->sign && *this > -operand2) {
      result = -( operand2 + *this);
    } else {
     result = ( operand2 + *this);
    }
  }
  result.reduce();
  return result;
}

Fraction Fraction::operator*( const Fraction &operand2) const {
  if (this->nan || operand2.nan ){
    return Fraction();
  }
  if (this->denominator==0 || operand2.denominator==0){
    return Fraction();
  }
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
  if (this->nan || operand2.nan ){
    return Fraction();
  }
  Fraction result = *this +( -operand2);
  result.reduce();
  return result;
}

Fraction Fraction::operator+() const {
  return *this;
}

Fraction::Fraction( unsigned long numerator, unsigned long denominator) : numerator(numerator), denominator(denominator), sign(true) , nan(false){
}

Fraction::Fraction( const Fraction &fraction){
  this->sign	   = fraction.sign;
  this->nan 	   = fraction.nan; 
  this->numerator   = fraction.numerator;
  this->denominator = fraction.denominator;
}

Fraction::Fraction( ) {
  sign = true;
  nan = true;
  numerator = 0;
  denominator = 1;
}

std::ostream &operator<<( std::ostream &out, const Fraction &fraction){
  if (fraction.nan == true) {
    out << "NaN";
  }else if (fraction.sign == true){
    out << fraction.numerator << "/" << fraction.denominator;
  }else { 
    out << "(-" << fraction.numerator << "/" << fraction.denominator << ")"  ;
  }
  return out;
}
