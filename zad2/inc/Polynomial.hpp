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
  };

  template <FieldOperations T>
  class Polynomial {
    public:
      Polynomial() = delete;
      Polynomial(const std::vector<T>& coefs);
      Polynomial(const std::vector<T>&& coefs);
      //coefficients[0] == a --> x^0 * a
      Polynomial<T> operator + (const Polynomial<T>& pol) const;
      Polynomial<T> operator - (const Polynomial<T>& pol) const;
      Polynomial<T> operator * (const Polynomial<T>& pol) const;
      Polynomial<T> operator / (const Polynomial<T>& pol) const;

      Polynomial<T>& operator += (const Polynomial<T>& pol) noexcept;
      Polynomial<T>& operator -= (const Polynomial<T>& pol) noexcept;
      Polynomial<T>& operator *= (const Polynomial<T>& pol) noexcept;
      Polynomial<T>& operator /= (const Polynomial<T>& pol) noexcept;

      size_t degree() noexcept;
    private:
      std::vector<T> coefficients{};

  };
}

#include "Polynomial.tpp"
#endif // MY_POLYNOMIAL_HPP