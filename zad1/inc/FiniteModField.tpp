#include "FiniteModField.hpp" //To help highliting addons.

namespace MyField {

  template<unsigned long long T>
  FiniteModField<T>::FiniteModField(unsigned long long value) : value{value % T} {}

  template<unsigned long long T>
  FiniteModField<T> FiniteModField<T>::operator+(const FiniteModField<T>& number) noexcept {
    return FiniteModField((this->value + number.value) % T);
  }

  template<unsigned long long T>
  FiniteModField<T> FiniteModField<T>::operator-(const FiniteModField<T>& number) noexcept {
    FiniteModField<T> temp = -number;
    return *this + number;
  }

  template<unsigned long long T>
  FiniteModField<T> FiniteModField<T>::operator-() noexcept {
    return T - this->value;
  }

  template<unsigned long long T>
  FiniteModField<T> FiniteModField<T>::operator*(const FiniteModField<T>& number) noexcept {
    return (this->value * number->value ) % T;
  }

  template<unsigned long long T>
  FiniteModField<T> FiniteModField<T>::operator/(const FiniteModField<T>& number) noexcept {
    return 0 //to be implemented;
  }
}
