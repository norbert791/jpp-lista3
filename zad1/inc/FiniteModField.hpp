#ifndef FINITE_MOD_FIELD_HPP
#define FINITE_MOD_FIELD_HPP
#include <iostream>
namespace MyField {
  template<unsigned long long T>
  std::ostream& operator << (std::ostream& stream, const FiniteModField<T>& number);
  template<unsigned long long T>
  std::istream& operator >> (std::istream& stream, FiniteModField<T>& number);
  
  consteval bool checkIfPrime(unsigned long long num) {
    if (num < 2) {return false;}
    
    for (unsigned long long i = 2; i * i <= num; i++) {
      if (num % i == 0) {return false;}
    }

    return true;
  }

  consteval bool checkConstraints(unsigned long long num) {
    unsigned long long temp = num * num;
    return temp / num == num;
  }

  template<unsigned long long T>
  class FiniteModField final {
    static_assert(checkIfPrime(T) && checkConstraints(T), "FiniteModField parameter must be prime and less or equal to sqrt of max ull");
    public:
      FiniteModField(unsigned long long value);
      FiniteModField() = delete;
      explicit FiniteModField(signed long long number);
      FiniteModField<T> operator + (const FiniteModField<T>& number) noexcept const;
      FiniteModField<T> operator - (const FiniteModField<T>& number) noexcept const;
      FiniteModField<T> operator * (const FiniteModField<T>& number) noexcept const;
      FiniteModField<T> operator / (const FiniteModField<T>& number) noexcept const;
      FiniteModField<T> operator - () noexcept const;
      FiniteModField<T>& operator ++ () noexcept;
      FiniteModField<T>& operator -- () noexcept;
      FiniteModField<T>& operator += (const FiniteModField<T>& number) noexcept;
      FiniteModField<T>& operator -= (const FiniteModField<T>& number) noexcept;
      FiniteModField<T>& operator *= (const FiniteModField<T>& number) noexcept;
      FiniteModField<T>& operator /= (const FiniteModField<T>& number) noexcept;
      bool operator == (const FiniteModField<T>& number) noexcept const;
      inline unsigned long long returnBase() const noexcept {return T;}
      inline unsigned long long returnValue() const noexcept {return value;}
      friend std::ostream& operator << (std::ostream& stream, const FiniteModField<T>& number);
      friend std::istream& operator >> (std::istream& stream, FiniteModField<T>& number);
    private:
      unsigned long long value = 0;
  };
}
#include "FiniteModField.tpp"
#endif //FINITE_MOD_FIELD_HPP
