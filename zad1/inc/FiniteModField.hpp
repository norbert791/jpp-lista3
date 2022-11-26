#ifndef FINITE_MOD_FIELD_HPP
#define FINITE_MOD_FIELD_HPP
#include <iostream>
namespace MyField {
  template<unsigned long long T>
  class FiniteModField;

  template<unsigned long long T>
  std::ostream& operator << (std::ostream& stream, const FiniteModField<T>& number);
  template<unsigned long long T>
  std::istream& operator >> (std::istream& stream, FiniteModField<T>& number);
  
  //has to be used after checkConstraints
  consteval bool checkIfPrime(unsigned long long num) {
    if (num < 2) {return false;}
    
    for (unsigned long long i = 2; i * i <= num; i++) {
      if (num % i == 0) {return false;}
    }

    return true;
  }

  consteval bool checkConstraints(unsigned long long num) {
    //Check if multiplication overflows
    unsigned long long temp = num * num;
    if (temp / num != num) {return false;}
    //Check if long long is able to store unsigned long long unchanged
    volatile long long cast = static_cast<long long>(num);
    volatile unsigned long long prev = static_cast<unsigned long long>(cast);
    return num == prev;
  }

  template<unsigned long long T>
  class FiniteModField final {
    static_assert(checkConstraints(T), "Long long and Unsigned long long do not allowed for safe operations for this type");
    static_assert(checkIfPrime(T), "FiniteModField parameter must be prime and less or equal to sqrt of max ull");
    public:
      FiniteModField(unsigned long long value);
      FiniteModField() = delete;
      FiniteModField<T> operator + (const FiniteModField<T>& number) const noexcept;
      FiniteModField<T> operator - (const FiniteModField<T>& number) const noexcept;
      FiniteModField<T> operator * (const FiniteModField<T>& number) const noexcept;
      FiniteModField<T> operator / (const FiniteModField<T>& number) const noexcept;
      FiniteModField<T> operator - () const noexcept;
      FiniteModField<T> operator ++ (int) noexcept;
      FiniteModField<T> operator -- (int) noexcept;
      FiniteModField<T>& operator ++ () noexcept;
      FiniteModField<T>& operator -- () noexcept;
      FiniteModField<T>& operator += (const FiniteModField<T>& number) noexcept;
      FiniteModField<T>& operator -= (const FiniteModField<T>& number) noexcept;
      FiniteModField<T>& operator *= (const FiniteModField<T>& number) noexcept;
      FiniteModField<T>& operator /= (const FiniteModField<T>& number) noexcept;
      bool operator == (const FiniteModField<T>& number) const noexcept ;
      inline unsigned long long returnBase() const noexcept {return T;}
      inline unsigned long long returnValue() const noexcept {return value;}
      template<unsigned long long S>
      friend std::ostream& operator << (std::ostream& stream, const FiniteModField<S>& number);
      template<unsigned long long S>
      friend std::istream& operator >> (std::istream& stream, FiniteModField<S>& number);
    private:
      unsigned long long value = 0;
      unsigned long long invert(unsigned long long num) const noexcept;
  };
}
#include "FiniteModField.tpp"
#endif //FINITE_MOD_FIELD_HPP
