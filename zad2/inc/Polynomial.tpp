#ifndef MY_POLYNOMIAL_TPP
#define MY_POLYNOMIAL_TPP
#include <vector>
#include <functional>
#include <exception>
#include <iostream>
#include <utility>
#include <algorithm>
#include "Polynomial.hpp"

namespace MyPolynomial {

  template<FieldOperations T>
  Polynomial<T>::Polynomial(const std::vector<T>& v) {
    if (v.size() == 0) {throw std::domain_error("v must not be empty");}
    coefficients.assign(v.begin(), v.end());
    Polynomial<T>::trimVector(coefficients);
  }

  template<FieldOperations T>
  Polynomial<T>::Polynomial(const std::vector<T>&& v) : coefficients{std::move(v)} {
    if (coefficients.size() == 0) {throw std::domain_error("v must not be empty");}
    Polynomial<T>::trimVector(coefficients);
  }

  template<FieldOperations T>
  Polynomial<T> Polynomial<T>::operator+(const Polynomial<T>& pol) const noexcept {
    const std::vector<T>& larger = pol.degree() > this->degree() ? pol.coefficients : this->coefficients;
    const std::vector<T>& smaller = pol.degree() > this->degree() ? this->coefficients : pol.coefficients;

    Polynomial result({0});
    result.coefficients.assign(larger.begin(), larger.end());

    for (size_t i = 0; i < smaller.size(); i++) {
      result.coefficients.at(i) = result.coefficients.at(i) + smaller.at(i);
    }

    Polynomial<T>::trimVector(result.coefficients);

    return result;
  }

  template<FieldOperations T>
  Polynomial<T> Polynomial<T>::operator-(const Polynomial<T>& pol) const noexcept {  
    return *this + (- pol);
  }

  template<FieldOperations T>
  Polynomial<T> Polynomial<T>::operator - () const noexcept{
    std::vector<T> negated(this->coefficients.size());
    std::transform<>(this->coefficients.cbegin(), this->coefficients.cend(),
                      negated.begin(), std::negate<T>{});
    return negated;
  }

  template<FieldOperations T>
  Polynomial<T> Polynomial<T>::operator*(const Polynomial<T>& pol) const noexcept {
    auto p1 = pol.coefficients;
    auto p2 = this->coefficients;

    while (p1.size() > p2.size()) {
      p2.emplace_back(T{0});
    }
    while (p1.size() < p2.size()) {
      p1.emplace_back(T{0});
    }

    if (p1.size() % 2 == 1) {
      p1.emplace_back(T{0});
      p2.emplace_back(T{0});
    }

    auto result = Polynomial<T>::karatsubaMulti(p1, p2);
    Polynomial<T>::trimVector(result);
    return result;
  }

  template<FieldOperations T>
  Polynomial<T> Polynomial<T>::operator/(const Polynomial<T>& pol) const {
    if (pol.degree() == 0 && pol.coefficients.at(0) == 0) {
      throw std::domain_error("0 division");
    }

    return divAlgorithm(*this, pol).first;
  }

  template<FieldOperations T>
  Polynomial<T> Polynomial<T>::operator%(const Polynomial<T>& pol) const {
    if (pol.degree() == 0 && pol.coefficients.at(0) == 0) {
      throw std::domain_error("0 division");
    }
    
    return divAlgorithm(*this, pol).second;
  }

  template<FieldOperations T>
  Polynomial<T>& Polynomial<T>::operator+=(const Polynomial<T>& first) noexcept{
    *this = *this + first;
    return *this;
  }

  template<FieldOperations T>
  Polynomial<T>& Polynomial<T>::operator-=(const Polynomial<T>& first) noexcept{
    *this = *this - first;
    return *this;
  }

  template<FieldOperations T>
  Polynomial<T>& Polynomial<T>::operator*=(const Polynomial<T>& first) noexcept{
    *this = *this * first;
    return *this;
  }

  template<FieldOperations T>
  Polynomial<T>& Polynomial<T>::operator/=(const Polynomial<T>& first) {
    *this = *this / first;
    return *this;
  }

  template<FieldOperations T>
  Polynomial<T>& Polynomial<T>::operator%=(const Polynomial<T>& first) {
    *this = *this % first;
    return *this;
  }

  template<FieldOperations T>
  std::ostream& operator << (std::ostream& stream, const Polynomial<T>& pol) {
    
    size_t counter = 0;
    for (auto it : pol.coefficients) {
      stream<<it<<"x^"<<counter;
      if (counter + 1 < pol.coefficients.size()) {
        stream<<" + ";
      }
      counter++;
    }

    return stream;
  }

  template<FieldOperations T>
  std::istream& operator << (std::istream& stream, Polynomial<T>& pol) {
    
    size_t size = 0;
    stream >> size;
    std::vector<T> resultV(size);
    T temp;
    while (size > 0 && stream >> temp) {
      resultV.emplate_at(resultV.end(), temp);
    }

    pol = {resultV};
    return stream;
  }

  template<FieldOperations T>
  bool Polynomial<T>::operator == (const Polynomial<T>& pol) noexcept {
    if (this->degree() != pol.degree()) {return false;}
    
    for (size_t i = 0; i < this->coefficients.size(); i++) {
      if (coefficients->at(i) != pol->coefficients.at(i)) {
        return false;
      }
    }

    return true;
  }
  
  template<FieldOperations T>
  std::pair<Polynomial<T>, Polynomial<T>> Polynomial<T>::divAlgorithm(const Polynomial<T>& left,
                                             const Polynomial<T>& right) {
    if (right.degree() > left.degree()) {
      return std::make_pair(Polynomial<T>{std::vector<T>{T{0}}}, left);
    }

    Polynomial<T> quotient(left);
    Polynomial<T> remainder({0});

    while(quotient.degree() >= right.degree()) {
      std::vector<T> temp(quotient.degree(), {0});
      temp.at(quotient.degree() - right.degree()) = quotient.coefficients.back() / right.coefficients.back();
      remainder += Polynomial<T>{temp};
      //quotient.coefficients.pop_back();
      //trimVector(quotient.coefficients);
      //check it
      quotient -= (right * Polynomial<T>{temp});
      std::cout<<"quotient: "<<quotient<<" deg: "<<quotient.degree()<<std::endl;
      std::cout<<"right: "<<right<<" deg: "<<right.degree()<<std::endl;
    }

    return std::make_pair(quotient, remainder);
  }

  template<FieldOperations T>
  std::vector<T> Polynomial<T>::karatsubaMulti(const std::vector<T>&
   first, const std::vector<T>& second) noexcept {
    if (first.size() == 1) {
      return {first.at(0) * second.at(0)};
    }

    std::vector<T> first2{first};
    std::vector<T> second2{second};

    if (first2.size() % 2 == 1) {
      first2.emplace_back(T{0});
      second2.emplace_back(T{0});
    }

    std::vector<T> firstLower(first2.begin(), first2.begin() + (first2.size() / 2));
    std::vector<T> firstHigher(first2.begin() + (first2.size() / 2), first2.end());
    std::vector<T> secondLower(second2.begin(), second2.begin() + (second2.size() / 2));
    std::vector<T> secondHigher(second2.begin() + (second2.size() / 2), second2.end());

    auto x = Polynomial<T>::karatsubaMulti(firstHigher, secondHigher); //A1 * B1
    auto y = Polynomial<T>::karatsubaMulti(firstLower, secondLower); //A0 * B0
    auto u = Polynomial<T>{firstLower} + Polynomial<T>{firstHigher}; //A1 + A0
    auto w = Polynomial<T>{secondLower} + Polynomial<T>{secondHigher}; //B1 + B0
    auto z = Polynomial<T>::karatsubaMulti(u.coefficients, w.coefficients); //(A1 + A0) * (B1 + B0)
    z = (Polynomial<T>{z} - Polynomial<T>{x} - Polynomial<T>{y}).coefficients;
    std::vector<T> left(first2.size(), {0});
    std::vector<T> mid(first2.size() / 2, {0}); 
    left.insert(left.end(), x.begin(), x.end()); //A1 * B1 * x^n
    mid.insert(mid.end(), z.begin(), z.end()); //((A1 + A0) * (B1 + B0) - A0 * B0 - A1 * B1) * x^(n/2)

    return (Polynomial<T>{left} + Polynomial<T>{mid} + y).coefficients;
  }

  template<FieldOperations T>
  void Polynomial<T>::trimVector(std::vector<T>& v) {
    while(v.size() > 1 && v.back() == T{0}) {
      v.pop_back();
    }
  }
}

#endif //MY_POLYNOMIAL_TPP