#include <Polynomial.hpp>



int main() {

  MyPolynomial::Polynomial<int> pol1({1, 2, 3});
  MyPolynomial::Polynomial<int> pol2({4, 3, 2, 5});
  std::cout<<pol1 + pol2<<std::endl;
  std::cout<<pol2 - pol1<<std::endl;
  std::cout<<pol2 * pol1<<std::endl;
  std::cout<<pol2 / pol1<<std::endl;
  std::cout<<pol2 % pol1<<std::endl;
  return 0;
}