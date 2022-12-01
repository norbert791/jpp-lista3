#ifndef MY_POLYNOMIAL_HPP
#define MY_POLYNOMIAL_HPP
#include <concepts>
#include <vector>

namespace MyPolynomial {

  template<typename T>
  concept FieldOperations = requires(T a, T b) {
    {a + b} -> std::same_as<T>;
    {a - b} -> std::same_as<T>;
    {a * b} -> std::same_as<T>;
    {a / b} -> std::same_as<T>;
    {a = b} -> std::same_as<T&>;
    {- a} -> std::same_as<T>;
    {T{0}};
    {T{1}};
  };

  template <FieldOperations T>
  class Polynomial {
    public:
      Polynomial() = delete;
      Polynomial(const std::vector<T>& coeffs); //TODO: throw if coefs.size() == 0
      Polynomial(const std::vector<T>&& coeffs);
      //coefficients[0] == a --> x^0 * a
      Polynomial<T> operator + (const Polynomial<T>& pol) const noexcept;
      Polynomial<T> operator - (const Polynomial<T>& pol) const noexcept;
      Polynomial<T> operator * (const Polynomial<T>& pol) const noexcept;
      Polynomial<T> operator / (const Polynomial<T>& pol) const;

      Polynomial<T>& operator += (const Polynomial<T>& pol) noexcept;
      Polynomial<T>& operator -= (const Polynomial<T>& pol) noexcept;
      Polynomial<T>& operator *= (const Polynomial<T>& pol) noexcept;
      Polynomial<T>& operator /= (const Polynomial<T>& pol);

      bool operator == (const Polynomial<T>& pol) noexcept;

      size_t degree() noexcept;
    private:
      std::vector<T> coefficients{};
      static std::vector<T> karatsubaMulti(const std::vector<T>& first, const std::vector<T>& second);
  };
}

#endif /*MY_POLYNOMIAL_HPP*/
#include "Polynomial.tpp"
