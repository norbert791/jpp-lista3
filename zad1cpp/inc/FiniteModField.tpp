#include <exception>
#include "FiniteModField.hpp" //To help highliting addons.

namespace MyField {

  template<unsigned long long T>
  FiniteModField<T>::FiniteModField(unsigned long long value) : value{value % T} {}

  template<unsigned long long T>
  FiniteModField<T> FiniteModField<T>::operator+(const FiniteModField<T>& number) const noexcept {
    return FiniteModField((this->value + number.value) % T);
  }

  template<unsigned long long T>
  FiniteModField<T> FiniteModField<T>::operator-(const FiniteModField<T>& number) const noexcept {
    return FiniteModField<T>((this->value + (T - number.value) % T) % T);
  }

  template<unsigned long long T>
  FiniteModField<T> FiniteModField<T>::operator-() const noexcept {
    return FiniteModField<T>((T - this->value) % T);
  }

  template<unsigned long long T>
  FiniteModField<T> FiniteModField<T>::operator*(const FiniteModField<T>& number) const noexcept {
    return FiniteModField<T>((this->value * number.value ) % T);
  }

  template<unsigned long long T>
  FiniteModField<T> FiniteModField<T>::operator/(const FiniteModField<T>& number) const {
    if (number == FiniteModField<T>{0}) {throw std::domain_error("0 division");}
    unsigned long long invert = this->invert(number.value);
    return FiniteModField<T>((this->value * invert) % T);
  }

  template<unsigned long long T>
  FiniteModField<T>& FiniteModField<T>::operator+=(const FiniteModField<T>& number) noexcept {
    this->value = (this->value + number.value) % T;
    return *this;
  }

  template<unsigned long long T>
  FiniteModField<T>& FiniteModField<T>::operator-=(const FiniteModField<T>& number) noexcept {
    this->value = (this->value + (T - number.value) % T) % T;
    return *this;
  }
  
  template<unsigned long long T>
  FiniteModField<T>& FiniteModField<T>::operator*=(const FiniteModField<T>& number) noexcept {
    this->value = (this->value * number.value) % T;
    return *this;
  }

  template<unsigned long long T>
  FiniteModField<T>& FiniteModField<T>::operator/=(const FiniteModField<T>& number) {
    if (number == FiniteModField<T>{0}) {throw std::domain_error("0 division");}
    this->value = (this->value * this->invert(number.value)) % T;
    return *this;
  }

  template<unsigned long long T>
  unsigned long long FiniteModField<T>::invert(unsigned long long num) const noexcept{
    long long m = static_cast<long long>(T);
    long long m0 = m;
    long long a = static_cast<long long>(num);
    long long y = 0;
    long long x = 1;

    while (a > 1) {
      long long q = a / m;
      long long t = m;
      m = a % m; 
      a = t;
      t = y;

      y = x - q * y;
      x = t;
    }

    if (x < 0) {
      x += m0;
    }

    return static_cast<unsigned long long>(x);
  }

  template<unsigned long long T>
  FiniteModField<T>& FiniteModField<T>::operator++() noexcept {
    this->value = (this->value + 1 ) % T;
    return *this;
  }
  template<unsigned long long T>
  FiniteModField<T>& FiniteModField<T>::operator--() noexcept {
    if (this->value == 0) {this->value = T - 1;}
    else {this->value = this->value - 1;}
    return *this;
  }

  template<unsigned long long T>
  FiniteModField<T> FiniteModField<T>::operator++(int) noexcept {
    this->value = (this->value + 1 ) % T;
    return *this;
  }
  
  template<unsigned long long T>
  FiniteModField<T> FiniteModField<T>::operator--(int) noexcept {
    if (this->value == 0) {this->value = T - 1;}
    else {this->value = this->value - 1;}
    return *this;
  }

  template<unsigned long long T>
  std::ostream& operator << (std::ostream& stream, const FiniteModField<T>& number) {
    return (stream << number.value << " mod " <<T);
  }

  template<unsigned long long T>
  std::istream& operator >> (std::istream& stream, FiniteModField<T>& number) {
    unsigned long long temp;
    stream >> temp;
    number.value = temp;
    return stream;
  };

  template<unsigned long long T>
  bool  FiniteModField<T>::operator == (const FiniteModField<T>& number) const noexcept  {
    return number.value == this->value;
  }
}
