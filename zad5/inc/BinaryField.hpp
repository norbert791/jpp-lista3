#ifndef BINARY_FIELD_HPP
#define BINARY_FIELD_HPP

#include <exception>
#include "Polynomial.hpp"

namespace MyFields
{
  class BinaryField {
    public:
      BinaryField(unsigned num) {
        value = num % 2 == 1;
      }

      BinaryField(bool num) {
        value = num;
      }

      inline BinaryField operator + (const BinaryField num) const noexcept {
        return BinaryField{this->value != num.value};
      };

      inline BinaryField operator - (const BinaryField num) const noexcept {
        return *this + num;
      };

      inline BinaryField operator * (const BinaryField num) const noexcept {
        return this->value && num.value;
      }

      inline BinaryField operator / (const BinaryField num) const {
        if (!num.value) {
          throw std::domain_error("Zero division");
        }
        return BinaryField{true};
      };

      inline BinaryField operator - () const noexcept{
        return this->value;
      }

      inline bool operator == (const BinaryField num) {
        return num.value == this->value;
      }

    private:
      bool value = false;
  };
}






#endif //BINARY_FIELD_HPP