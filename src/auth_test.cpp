// Copyright (c) 2018. All rights reserved.

#include "gtest/gtest.h"
#include "auth.h"

namespace s3kits {

TEST(CreateSignatureTest, Normal) {
    std::cout << CreateSignature(
            "AKIAIOSFODNN7EXAMPLE",
            "wJalrXUtnFEMI/K7MDENG/bPxRfiCYEXAMPLEKEY",
            "GET\n"
            "\n"
            "\n"
            "Tue, 27 Mar 2007 19:36:42 +0000\n"
            "/johnsmith/photos/puppy.jpg") << std::endl;

    std::cout << CreateSignature(
            "AKIAIOSFODNN7EXAMPLE",
            "wJalrXUtnFEMI/K7MDENG/bPxRfiCYEXAMPLEKEY",
            "PUT\n"
            "4gJE4saaMU4BqNR0kLY+lw==\n"
            "application/x-download\n"
            "Tue, 27 Mar 2007 21:06:08 +0000\n"
            ""
            "x-amz-acl:public-read\n"
            "x-amz-meta-checksumalgorithm:crc32\n"
            "x-amz-meta-filechecksum:0x02661779\n"
            "x-amz-meta-reviewedby:"
            "joe@johnsmith.net,jane@johnsmith.net\n"
            "/static.johnsmith.net/db-backup.dat.gz") << std::endl;
}

}  // namespace s3kits
