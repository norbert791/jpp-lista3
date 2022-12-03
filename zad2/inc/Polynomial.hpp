#ifndef MY_POLYNOMIAL_HPP
#define MY_POLYNOMIAL_HPP
#include <concepts>
#include <vector>
#include <iostream>
#include <utility>

namespace MyPolynomial {
 template<typename T>
  concept FieldOperations = requires(T a, T b) {
    {a + b} -> std::same_as<T>;
    {a - b} -> std::same_as<T>;
    {a * b} -> std::same_as<T>;
    {a / b} -> std::same_as<T>;
    {a = b} -> std::same_as<T&>;
    {- a} -> std::same_as<T>;
    {a == b} -> std::same_as<bool>;
    {T{0}};
    {T{1}};
    {std::cout << a};
    {std::cin >> a};
  };

  template<FieldOperations T>
  class Polynomial;

  template<FieldOperations T>
  std::ostream& operator << (std::ostream& stream, const Polynomial<T>& pol);
  template<FieldOperations T>
  std::istream& operator >> (std::istream& stream, Polynomial<T>& pol);

  template <FieldOperations T>
  class Polynomial {
    public:
      Polynomial() = delete;
      //! coefficients[0] == a --> x^0 * a
      Polynomial(const std::vector<T>& coeffs);
      Polynomial(const std::vector<T>&& coeffs);
      Polynomial(const Polynomial<T>& coeffs) = default;
      Polynomial<T> operator + (const Polynomial<T>& pol) const noexcept;
      Polynomial<T> operator - (const Polynomial<T>& pol) const noexcept;
      Polynomial<T> operator * (const Polynomial<T>& pol) const noexcept;
      Polynomial<T> operator / (const Polynomial<T>& pol) const;
      Polynomial<T> operator % (const Polynomial<T>& pol) const;
      Polynomial<T> operator - () const noexcept;

      Polynomial<T>& operator += (const Polynomial<T>& pol) noexcept;
      Polynomial<T>& operator -= (const Polynomial<T>& pol) noexcept;
      Polynomial<T>& operator *= (const Polynomial<T>& pol) noexcept;
      Polynomial<T>& operator /= (const Polynomial<T>& pol);
      Polynomial<T>& operator %= (const Polynomial<T>& pol);

      //TODO: implements
      bool operator == (const Polynomial<T>& pol) noexcept;

      inline size_t degree() const noexcept {return coefficients.size() - 1;};

      template<FieldOperations S>
      friend std::ostream& operator << (std::ostream& stream, const Polynomial<S>& pol);
      template<FieldOperations S>
      friend std::istream& operator >> (std::istream& stream, Polynomial<S>& pol);

    private:
      std::vector<T> coefficients{};
      //Remove trailing 0s.
      static void trimVector(std::vector<T>& v);
      //Note: use this if and only if first and second have equal size.
      static std::vector<T> karatsubaMulti(const std::vector<T>& first, const std::vector<T>& second) noexcept;

      static std::pair<Polynomial<T>, Polynomial<T>> divAlgorithm(const Polynomial<T>& left,
                                                                  const Polynomial<T>& right);
  };
}

#endif /*MY_POLYNOMIAL_HPP*/
#include "Polynomial.tpp"
