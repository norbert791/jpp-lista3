#include <Polynomial.hpp>



int main() {

  MyPolynomial::Polynomial<float> pol1({1, 2, 3});
  MyPolynomial::Polynomial<float> pol2({4, 3, 2, 5});
  std::cout<<pol1 + pol2<<std::endl;
  std::cout<<pol2 - pol1<<std::endl;
  std::cout<<pol2 * pol1<<std::endl;
  std::cout<<pol2 / pol1<<std::endl;
  std::cout<<pol2 % pol1<<std::endl;
  std::cout<<pol2 / pol2<<std::endl;
  std::cout<<pol2 % pol2<<std::endl;
  return 0;
}