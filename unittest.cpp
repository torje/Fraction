#include "unittest.hpp"
#include "vector"
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

struct Triplet{
  Fraction operand1;
  Fraction operand2;
  Fraction expectAddition,
    expectSubtraction,
    expectMultiplication,
    expectDivision;
  bool correctAddition        ,
    correctSubtraction   ,
    correctMultiplication,
    correctDivision     ;

  
  Triplet( ){
  }
  Triplet( Fraction operand1, 
	   Fraction operand2,   
	   Fraction expectAddition,
	   Fraction expectSubtraction,
	   Fraction expectMultiplication,
	   Fraction expectDivision ) : 
    operand1(operand1), 
    operand2(operand2), 
    expectAddition      (expectAddition      ),
    expectSubtraction   (expectSubtraction   ),
    expectMultiplication(expectMultiplication),
    expectDivision     (expectDivision)       {  }

  void test(){
    if ( 
	((operand1    + operand2      == expectAddition  ) ||( (operand1    + operand2).nan      && expectAddition.nan  )) &&
	((operand2    + operand1      == expectAddition  ) ||( (operand2    + operand1).nan      && expectAddition.nan  ))&&
	((-(-operand1 + (-operand2) ) == expectAddition  ) ||( (-(-operand1 + (-operand2) )).nan && expectAddition.nan  ))&&
	((-operand1   + (-operand2)   == -expectAddition ) ||( (-operand1   + (-operand2)).nan   && -expectAddition.nan ))
	 ){
      correctAddition = true;
    }else{
      correctAddition = false;
    } 
    
    if (
	((operand1 - operand2  == expectSubtraction ) || ((operand1 - operand2).nan  && expectSubtraction.nan ))&&
	((operand2 -operand1 == -expectSubtraction )  || ((operand2 -operand1).nan && expectSubtraction.nan ))
	 ){
      correctSubtraction = true;
    }else{
      correctSubtraction = false;
    } 

    if (
	( (operand1 * operand2 == expectMultiplication) || ((operand1 * operand2).nan && expectMultiplication.nan)  ) && 
	( (operand2 * operand1 == expectMultiplication) || ((operand2 * operand1).nan && expectMultiplication.nan) )
	)      {
      correctMultiplication = true;
    }else{
      correctMultiplication = false;
    } 
    
    if ( (operand1 / operand2 == expectDivision) ||  ((operand1 / operand2).nan && expectDivision.nan)  ) {
      correctDivision = true;
    }else{
      correctDivision = false;
    } 
  }

  std::string toString(){
    std::stringstream ss;
    if ( !(correctAddition && 
  	 correctSubtraction &&
	 correctMultiplication &&
	 correctDivision) ){
      ss << "operand1: " << operand1 << " operand2: " << operand2 << " failed:: "<< std::endl;
      ss << "addition: " << correctAddition << " subtraction: " << correctSubtraction << " multiplication: " << correctMultiplication << " division: " << correctDivision<< std::endl;
      if ( !correctAddition){
	ss<<"addition"<<std::endl;
	ss<<( (operand1    + operand2      == expectAddition  ) ||( (operand1    + operand2).nan      && expectAddition.nan  ) ) << "";
	ss<<( (operand2    + operand1      == expectAddition  ) ||( (operand2    + operand1).nan      && expectAddition.nan  ) ) << " " ;
	ss<<( (-(-operand1 + (-operand2) ) == expectAddition  ) ||( (-(-operand1 + (-operand2) )).nan && expectAddition.nan  ) ) << "";
	ss<<( (-operand1   + (-operand2)   == -expectAddition ) ||( (-operand1   + (-operand2)).nan   && -expectAddition.nan ) ) << "";
	ss<<std::endl;
	ss<< operand2 + operand1 << " :: "<< expectAddition;
	ss<<std::endl;

	ss<< operand2 << " + " <<operand1 << " :: "<< expectAddition;
	ss<<std::endl;

      }
      if (!correctSubtraction ){
	ss<<"subtraction"<<std::endl;
	ss<<(operand1 - operand2  == expectSubtraction );
	ss<<(operand2 -operand1 == -expectSubtraction );
	
      }
      if(!correctMultiplication){
	ss<<"multiplication"<<std::endl;
	ss<<	( (operand1 * operand2 == expectMultiplication) || ((operand1 * operand2).nan && expectMultiplication.nan)  ) ;
	ss<<( (operand2 * operand1 == expectMultiplication) || ((operand2 * operand1).nan && expectMultiplication.nan) );

      }
      if (!correctDivision){
	ss<<"division"<<std::endl;
	ss<<((operand1 / operand2 == expectDivision) ||  ((operand1 / operand2).nan && expectMultiplication.nan)) << std::endl;
	ss<<operand1 / operand2 << " :: " << expectDivision << " ";
	ss<< (operand1 / operand2).nan << "  " << expectDivision.nan <<std::endl;
	ss<<std::endl;
      }
    } else {
      ss << "Arithmetics test passed ";
    }
    return ss.str();
  }
};

class ComparatorTester{
public:
  Fraction operand1, operand2;
  bool less, equal, more;
  bool resultLess, resultEqual, resultMore; 
  ComparatorTester(Fraction operand1, Fraction operand2, bool less, bool equal, bool more ) : operand1(operand1), operand2(operand2), less(less), equal(equal), more(more) {
  }
  void test(){
    resultLess = (operand1 < operand2) == less;
    resultEqual = (operand1 == operand2) == equal;
    resultMore = (operand1 > operand2) == more;
  }
  std::string toString(){
    std::stringstream ss;
    if ( !resultLess || !resultEqual || !resultMore){ 
    if ( !resultLess){
      ss << "< failed";
    }
    if ( !resultEqual){
      ss << "== failed";
    }
    if ( !resultMore){
      ss << "> failed";
    } 
    }else {
      ss << "passed";
    }
    return ss.str();
  }
};

void unittest(){
  std::vector<ComparatorTester> compareTest;
  compareTest.push_back(  
			ComparatorTester(
					 Fraction(1,2),
					 Fraction(1,2),
					 false, true, false
					 )
			  );
  compareTest.push_back(
			ComparatorTester(
				      Fraction(1,4),
				      Fraction(1,2),
				      true, false, false
				      )
			);
  compareTest.push_back(
			ComparatorTester(
				      Fraction(1,2),
				      Fraction(1,4),
				      false, false, true
				      )
			);
  compareTest.push_back(
			ComparatorTester(
				      Fraction(0,2),
				      Fraction(0,4),
				      false, true, false
				      )
			);
  compareTest.push_back(
			ComparatorTester(Fraction(),
					 Fraction(),
					 false, false, false
					 )
			);
  compareTest.push_back(
			ComparatorTester(Fraction(),
					 Fraction(1,2),
					 false, false, false
					 )
			);
  for( int i = 0 ; i < compareTest.size() ; i++){
    compareTest.at(i).test();
    std::cout <<  compareTest.at(i).toString()<< std::endl;
  }

  Fraction fraction1 = Fraction(1,2),
    fraction2 = Fraction(1, 4);
  std::vector<Triplet> test_cases;
  test_cases.push_back(Triplet( -Fraction(1,2),
				-Fraction(1,2),
				-Fraction(1,1),
				Fraction(0,1),
				Fraction(1,4),
				Fraction(1,1)
				)
		       );
  test_cases.push_back(Triplet( -Fraction(1,2),
				Fraction(1,2),
				Fraction(0,1),
				-Fraction(1,1),
				-Fraction(1,4),
				-Fraction(1,1)
				)
		       );
  test_cases.push_back(Triplet( -Fraction(1,2),
				Fraction(0,2),
				-Fraction(1,2),
				-Fraction(1,2),
				Fraction(0,9),
				Fraction()
				)
		       );
  test_cases.push_back(Triplet( -Fraction(1,2),
				Fraction(0,2),
				-Fraction(1,2),
				-Fraction(1,2),
				-Fraction(0,9),
				Fraction()
				)
		       );
  test_cases.push_back(Triplet( -Fraction(0,2),
				Fraction(0,2),
				-Fraction(0,2),
				-Fraction(0,2),
				-Fraction(0,2),
				Fraction()
				)
		       );
  test_cases.push_back(Triplet( -Fraction(0,2),
				Fraction(0,0),
				Fraction(),
				Fraction(),
				Fraction(),
				Fraction()
				)
		       );
  for ( int i = 0 ; i < test_cases.size(); i++){
    test_cases.at(i).test();
  }
  for ( int i = 0 ; i < test_cases.size(); i++){
    std::cout << test_cases.at(i).toString() << std::endl;
  }  
}
