#include <vector>
#include "Polynomial.hpp"

namespace MyPolynomial {

  template<FieldOperations T>
  Polynomial<T>::Polynomial(const std::vector<T>& v) {
    coefficients.assign(v.begin(), v.end());
  }

  template<FieldOperations T>
  Polynomial<T>::Polynomial(const std::vector<T>&& v) {
    coefficients = v;
  }

  template<FieldOperations T>
  Polynomial<T>::Polynomial(const std::vector<T>&& v) {
    coefficients = v;
  }

  template<FieldOperations T>
  Polynomial<T> Polynomial<T>::operator+(const Polynomial<T>& pol) const{
    const std::vector& larger;
    const std::vector& smaller;
    
    if (pol.degree() > this->degree()) {
      larger = pol.coefficients; smaller = *this;
    } else {
      larger = this->coefficients; smaller = *pol;
    }

    Polynomial result;
    result.coefficients.assign(larger.begin(), larger.end());

    for (size_t i = 0; i < smaller.size(); i++) {
      result.coefficients[i] = result.coefficients[i] + smaller[i];
    }

    return result;
  }

  template<FieldOperations T>
  Polynomial<T> Polynomial<T>::operator-(const Polynomial<T>& pol) const{
    const std::vector& larger;
    const std::vector& smaller;
    
    if (pol.degree() > this->degree()) {
      larger = pol.coefficients; smaller = *this;
    } else {
      larger = this->coefficients; smaller = *pol;
    }

    Polynomial result;
    result.coefficients.assign(larger.begin(), larger.end());

    for (size_t i = 0; i < smaller.size(); i++) {
      result.coefficients[i] = result.coefficients[i] - smaller[i];
    }

    return result;
  }
}