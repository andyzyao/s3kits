// Copyright (c) 2018. All rights reserved.
// Author: Andy Yao <andyzyao@vip.qq.com>

#include "base64.h"
#include <iostream>

namespace s3kits {

static const char base64_index_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

std::string Base64Encode(const std::string& str) {
  std::string result;
  result.reserve((str.size() + 2) / 3 * 4);

  for (std::size_t i = 0; i <= (str.size() - 3); i += 3) {
    unsigned int data = (str[i] << 16) | (str[i+1] << 8) | (str[i+2]);
    result += base64_index_table[(data & 0b111111000000000000000000) >> 18];
    result += base64_index_table[(data & 0b000000111111000000000000) >> 12];
    result += base64_index_table[(data & 0b000000000000111111000000) >> 6];
    result += base64_index_table[data & 0b000000000000000000111111];
  }

  std::size_t remainder = str.size() % 3;
  if (remainder == 0) {
  } else if (remainder == 1) {
    unsigned int data = (str[str.size() - 1] << 16);
    result += base64_index_table[(data & 0b111111000000000000000000) >> 18];
    result += base64_index_table[(data & 0b000000111111000000000000) >> 12];
    result += '=';
    result += '=';
  } else if (remainder == 2) {
    unsigned int data = (str[str.size() - 2] << 16) | (str[str.size() - 1] << 8);	  
    result += base64_index_table[(data & 0b111111000000000000000000) >> 18];
    result += base64_index_table[(data & 0b000000111111000000000000) >> 12];
    result += base64_index_table[(data & 0b000000000000111111000000) >> 6];
    result += '=';
  }

  return result;
}

}  // namespace s3kits
