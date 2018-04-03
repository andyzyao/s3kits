// Copyright (c) 2018. All rights reserved.
// Author: Andy Yao <andyzyao@vip.qq.com>

#include "gtest/gtest.h"
#include "base64.h"

namespace s3kits {

TEST(Base64EncodeTest, Normal) {
  EXPECT_EQ("TWFu", Base64Encode("Man"));
  EXPECT_EQ("aGVsbG8=", Base64Encode("hello"));
  EXPECT_EQ("YW55IGNhcm5hbCBwbGVhc3VyZS4=", Base64Encode("any carnal pleasure."));
  EXPECT_EQ("YW55IGNhcm5hbCBwbGVhc3VyZQ==", Base64Encode("any carnal pleasure"));
  EXPECT_EQ("YW55IGNhcm5hbCBwbGVhc3Vy", Base64Encode("any carnal pleasur"));
  EXPECT_EQ("YW55IGNhcm5hbCBwbGVhc3U=", Base64Encode("any carnal pleasu"));
  EXPECT_EQ("YW55IGNhcm5hbCBwbGVhcw==", Base64Encode("any carnal pleas"));
}

}  // namespace s3kits
