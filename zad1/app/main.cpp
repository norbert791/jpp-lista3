#include <iostream>
#include <FiniteModField.hpp>

int main() {

  constexpr unsigned long long base = 7;
  auto val1 = MyField::FiniteModField<base>(5);
  auto val2 = MyField::FiniteModField<base>(3);

  std::cout<<val1 + val2<< std::endl;
  std::cout<<val1 - val2<< std::endl;
  std::cout<<val1 * val2<< std::endl;
  std::cout<<val1 / val2<< std::endl;
  
  val1 += val2;
  std::cout<< val1 <<std::endl;
  val1 -= val2;
  std::cout<< val1 <<std::endl;
  val1 *= val2;
  std::cout<< val1 <<std::endl;
  val1 /= val2;
  std::cout<< val1 <<std::endl;
  ++val1;
  std::cout<< val1 <<std::endl;
  --val1;
  std::cout<< val1 <<std::endl;
  val1++;
  std::cout<< val1 <<std::endl;
  val1--;
  std::cout<< val1 <<std::endl;
  return 0;
}