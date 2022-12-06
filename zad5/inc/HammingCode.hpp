#ifndef HAMMING_CODE_HPP
#define HAMMING_CODE_HPP

#include "BinaryField.hpp"
#include <vector>

namespace MyHamming {
  class HammingCode {
    public:
      std::vector<MyFields::BinaryField> encode(std::vector<MyFields::BinaryField> bits);
      std::vector<MyFields::BinaryField> decode(std::vector<MyFields::BinaryField> bits);
  };
}




#endif //HAMMING_CODE_HPP