#ifndef MY_POLYNOMIAL_TPP
#define MY_POLYNOMIAL_TPP
#include <vector>
#include <functional>
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
    std::vector<T> negated(pol.size());
    std::transform(pol.begin(), pol.end(), negated.begin(), std::negate);

    return *this + negated;
  }

  template<FieldOperations T>
  Polynomial<T> Polynomial<T>::operator*(const Polynomial<T>& pol) const {
    auto p1 = pol.coefficients();
    auto p2 = this->coefficients();

    while (p1.size() > p2.size()) {
      p2.emplace_back({0});
    }
    while (p1.size() < p2.size()) {
      p1.emplace_back({0});
    }

    if (p1.size() % 2 == 1) {
      p1.emplace_back({0});
      p2.emplace_back({0});
    }

    return karatsubaMulti(p1, p2);
  }

  template<FieldOperations T>
  static std::vector<T> karatsubaMulti(const std::vector<T>& first, const std::vector<T>& second) {
    if (first.size() == 1) {
      return {first[0] * second[0];}
    }
    
    std::vector<T> first2{first};
    std::vector<T> second2{second};

    if (first2.size() % 2 == 1) {
      first2.emplace_back({0});
      second2.emplace_back({0});
    }

    std::vector<T> firstLower(first2.begin(), first2.begin() + (first2.size() / 2));
    std::vector<T> firstHigher(first2.begin() + (first2.size() / 2), first2.end());
    std::vector<T> secondLower(second2.begin(), second2.begin() + (second2.size() / 2));
    std::vector<T> secondHigher(second2.begin() + (second2.size() / 2), second2.end());

    auto x = karatsubaMulti(firstHigher, secondHigher); //A1 * B1
    auto y = karatsubaMulti(firstLower, secondLower); //A0 * B0

    auto u = firstLower + firstHigher; //A1 + A0
    auto w = secondLower + secondHigher; //B1 + B0
    auto z = karatsubaMulti(u, w); //(A1 + A0) * (B1 + B0)
    auto z = z - x - y;
    std::vector<T> left(first2.size(), {0});
    std::vector<T> mid(first2.size() / 2, {0}); 
    left.insert(left.end(), x.begin(), x.end()); //A1 * B1 * x^n
    mid.insert(mid.end(), z.begin(), z.end()); //((A1 + A0) * (B1 + B0) - A0 * B0 - A1 * B1) * x^(n/2)

    return left + mid + y;
  }
}

#endif // MY_POLYNOMIAL_TPP